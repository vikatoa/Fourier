#include "interface.hpp"
// g++ main.cpp -fPIC interface/interface.cpp -o prog -lsfml-graphics -lsfml-window -lsfml-system

bool compareComplex(std::pair<std::complex<float>, int> i, std::pair<std::complex<float>, int> j){
    return std::abs(i.second + 0.1) < std::abs(j.second + 0.1);
}

bool in(std::list<sf::Vector2f> vect_l, sf::Vector2f v){
    for(auto vect : vect_l){
        if(floor(vect.x) == floor(v.x) && floor(vect.y) == floor(v.y)){
            return true;
        }
    }
    return false;
}

bool in(std::vector<sf::Vector2f> vect_l, sf::Vector2f v){
    for(auto vect : vect_l){
        if(floor(vect.x) == floor(v.x) && floor(vect.y) == floor(v.y)){
            return true;
        }
    }
    return false;
}

Interface::Interface(){
    this->window.create(sf::VideoMode(1920, 1080), "fourier", sf::Style::Fullscreen);
    this->fps = 60;
    // this->window.setFramerateLimit(this->fps);
    this->font.loadFromFile("data/UbuntuMono.ttf");
    this->text.setFont(this->font);
    this->state = caption;
    this->clock.restart();
    this->clock.getElapsedTime();
    this->leftButton = false;
    this->nb_circles = 2;
    this->periode = 20;
    this->algo = standard_methode;
    this->show_circles = true;
    this->clock.restart();
    this->last_frame_time = 0;
    this->max = 1000;
}

Interface::~Interface(){
    this->points.clear();
    this->circles.clear();
    this->points_to_draw.clear();
    this->sketch.clear();
    this->window.close();
    this->sketch.clear();
}

void Interface::show(){
    this->window.clear(sf::Color::Black);
    if(this->state == caption){
        for(sf::Vector2f point : this->points_to_draw){
            sf::RectangleShape rec(sf::Vector2f(1, 1));
            rec.setFillColor(sf::Color(0, 255, 0));
            rec.setPosition(point.x, point.y);
            window.draw(rec);
        }
    }

    else if(this->state == drawing){
        for(sf::Vector2f point : this->points_to_draw){
            sf::RectangleShape rec(sf::Vector2f(1, 1));
            rec.setFillColor(sf::Color(255, 255, 255));
            rec.setPosition(point.x, point.y);
            window.draw(rec);
        }

        sf::Vector2f pos(-1920/2, -1080/2);
        float avancement = this->clock.getElapsedTime().asSeconds() * 2. * M_PI / this->periode;
        for(auto circle : this->circles){
            float r = std::abs(circle.first);
            float n = circle.second;
            if(this->show_circles){
                sf::CircleShape shape(r);
                shape.setFillColor(sf::Color::Transparent);
                shape.setOutlineColor(sf::Color::White);
                shape.setOutlineThickness(1.f);
                shape.setOrigin(sf::Vector2f(pos.x + r, pos.y + r));
                window.draw(shape);
            }

            sf::RectangleShape line(sf::Vector2f(1, r));
            line.setPosition(-pos);
            line.setRotation((std::arg(circle.first) + n * avancement)*180/M_PI);

            line.setFillColor(sf::Color::White);
            window.draw(line);

            pos = sf::Vector2f(pos.x + r * std::cos(std::arg(circle.first) + n * avancement - M_PI_2), pos.y + r * std::sin(std::arg(circle.first) + n * avancement - M_PI_2));
        }
        float g = 255;

        for(sf::Vector2f point : this->sketch){
            sf::RectangleShape rec(sf::Vector2f(1, 1));
            rec.setFillColor(sf::Color(0, g, 0));
            rec.setPosition(point.x, point.y);
            g -= 255./this->max;
            window.draw(rec);
        }
    }

    // Show information with text
    std::string txt = "fps : ";
    txt.append(std::to_string(this->frame.size()));
    txt.append("\t points : ");
    txt.append(std::to_string(this->points.size()));
    txt.append("\t periode : ");
    txt.append(std::to_string(this->periode));
    txt.append("\t nb cercle : ");
    txt.append(this->algo == standard_methode ? std::to_string(this->nb_circles * 2 + 1) : std::to_string((unsigned long long int) pow(2, this->nb_circles)));
    txt.append("\t"); txt.append(this->algo == standard_methode ? "methode standard" : "Cooley-Turkey FFT");
    txt.append("\t points : ");
    txt.append(std::to_string(this->sketch.size()));
    this->text.setString(txt);
    this->text.setCharacterSize(24);
    this->window.draw(this->text);

    this->frame.push(this->clock.getElapsedTime());
    while(this->frame.front().asMilliseconds() < this->frame.back().asMilliseconds() - 1000){
        this->frame.pop();
    }


    this->window.display();
    this->last_frame_time = clock.getElapsedTime().asSeconds();
}

void Interface::events(){
    sf::Event event;
    while(this->window.pollEvent(event)){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            this->state = closing;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
            this->state = closing;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            if(this->state == caption && this->points.size() > 0){
                this->state = computing;
            }
        }
        if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            this->periode += 1;
            this->sketch.clear();
        }
        if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            this->periode -= 1;
            this->sketch.clear();
        }
        if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            this->nb_circles--;
            this->state = computing;
            this->circles.clear();
            this->sketch.clear();
        }
        if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            this->nb_circles++;
            this->state = computing;
            this->circles.clear();
            this->sketch.clear();
        }
        if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            this->algo = this->algo == standard_methode ? cooly_turkey : standard_methode;
            if(this->state == drawing) this->state = computing;
            this->circles.clear();
            this->sketch.clear();
        }
        if(event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
            this->show_circles = !this->show_circles;
        }
    }

    if(this->leftButton || sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
        this->leftButton = true;
        if(this->state == caption){
            sf::Vector2f mousePos = this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window));
            this->points.push_back(mousePos);
            if(!in(this->points_to_draw, mousePos)){
                this->points_to_draw.push_back(mousePos);
            }
        }
    }
    if(!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
        this->leftButton = false;
    }
}

bool Interface::timeToFrame(){
    if(this->clock.getElapsedTime().asSeconds() - this->last_frame_time >= 1./60){
        return true;
    }
    return false;
}

void Interface::update(){
    if(this->state == computing){
        if(this->algo == standard_methode){
            std::vector<std::complex<float>> complexPoints;
            std::complex<float> i(0, 1);
            for(sf::Vector2f point : this->points){
                complexPoints.push_back(std::complex<float>(point.x, point.y));
            }
            for(int n = -this->nb_circles ; n < this->nb_circles + 1 ; n++){
                // Comute the integral
                std::complex<float> inter = 0;
                std::complex<float> center(1920/2, 1080/2);
                for(int x = 0 ; x < complexPoints.size() ; x++){
                    inter += (complexPoints[x] - center) * std::exp(std::complex<float>(0, -2 * M_PI * n * x / complexPoints.size()));
                }

                this->circles.push_back(std::pair(inter / std::complex<float>(0, complexPoints.size()), n));
            }
            std::sort(this->circles.begin(), this->circles.end(), compareComplex);
            this->state = drawing;
        }
        else if(this->algo == cooly_turkey){

        }
    }
    if(this->state == drawing){
        sf::Vector2f pos(-1920/2, -1080/2);
        float avancement = this->clock.getElapsedTime().asSeconds() * 2. * M_PI / this->periode;
        for(auto circle : this->circles){
            float r = std::abs(circle.first);
            float n = circle.second;

            pos = sf::Vector2f(pos.x + r * std::cos(std::arg(circle.first) + n * avancement - M_PI_2), pos.y + r * std::sin(std::arg(circle.first) + n * avancement - M_PI_2));
        }
        if(!in(sketch, -pos)){
            this->sketch.push_front(-pos);
        }
        if(sketch.size() > this->max){
            sketch.pop_back();
        }
    }
}

bool Interface::isOpen(){
    return this->state != closing;
}
