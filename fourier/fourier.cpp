#include"fourier.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

sf::Image app_kernel(sf::Image img, std::vector<std::vector<float>> kernel){
    sf::Image image;
    float max = 0;

    int n = kernel.size();
    int m = kernel[0].size();
    std::vector<std::vector<std::vector<float>>> memoire;
    image.create(img.getSize().x + 1 - n, img.getSize().y + 1 - m, sf::Color(0, 0, 0));

    for(int i = n/2 ; i < img.getSize().x - (n/2) ; i++){
        memoire.push_back({});
        for(int j = m/2 ; j < img.getSize().y - (m/2) ; j++){
            memoire.back().push_back({});
            float r = 0, g = 0, b = 0;
            for(int x = 0 ; x < n ; x++){
                for(int y = 0 ; y < m ; y++){
                    r += img.getPixel(i - n/2 + x, j - m/2 + y).r * kernel[x][y];
                    g += img.getPixel(i - n/2 + x, j - m/2 + y).g * kernel[x][y];
                    b += img.getPixel(i - n/2 + x, j - m/2 + y).b * kernel[x][y];
                }
            }
            r = std::abs(r);
            g = std::abs(g);
            b = std::abs(b);

            if(max < r) max = r;
            if(max < g) max = g;
            if(max < b) max = b;
            memoire.back().back().push_back(r);
            memoire.back().back().push_back(g);
            memoire.back().back().push_back(b);
        }
    }
    max /= 255.;
    for(int i = 0 ; i < image.getSize().x ; i++){
        for(int j = 0 ; j < image.getSize().y ; j++){
            image.setPixel(i, j, sf::Color(memoire.at(i).at(j).at(0) / max, memoire.at(i).at(j).at(1) / max, memoire.at(i).at(j).at(2) / max));
        }
    }
    return image;
}

sf::Image add_images(sf::Image img1, sf::Image img2){
    sf::Image image;

    if(img1.getSize() != img2.getSize()){
        std::cout << "les images ne sont pas de la même taille" << std::endl;
    }
    image.create(img1.getSize().x, img1.getSize().y, sf::Color(0, 0, 0));

    for(int x = 0 ; x < image.getSize().x ; x++){
        for(int y = 0 ; y < image.getSize().y ; y++){
            image.setPixel(x, y, sf::Color(
                std::sqrt(img1.getPixel(x, y).r * img1.getPixel(x, y).r + img2.getPixel(x, y).r * img2.getPixel(x, y).r)/1.41421356237,
                std::sqrt(img1.getPixel(x, y).g * img1.getPixel(x, y).g + img2.getPixel(x, y).g * img2.getPixel(x, y).g)/1.41421356237,
                std::sqrt(img1.getPixel(x, y).b * img1.getPixel(x, y).b + img2.getPixel(x, y).b * img2.getPixel(x, y).b)/1.41421356237
            ));
        }
    }
    return image;
}

sf::Image WnB(sf::Image img, int tresh){
    sf::Image image;

    image.create(img.getSize().x, img.getSize().y, sf::Color(0, 0, 0));

    for(int x = 0 ; x < image.getSize().x ; x++){
        for(int y = 0 ; y < image.getSize().y ; y++){
            float w = (img.getPixel(x, y).r + img.getPixel(x, y).g + img.getPixel(x, y).b) / 3.;
            if(w  < tresh) w = 0; else w = 255;
            image.setPixel(x, y, sf::Color(w, w, w));
        }
    }
    return image;
}

sf::Image WnB(sf::Image img){
    sf::Image image;

    image.create(img.getSize().x, img.getSize().y, sf::Color(0, 0, 0));

    for(int x = 0 ; x < image.getSize().x ; x++){
        for(int y = 0 ; y < image.getSize().y ; y++){
            float w = (img.getPixel(x, y).r + img.getPixel(x, y).g + img.getPixel(x, y).b) / 3.;
            image.setPixel(x, y, sf::Color(w, w, w));
        }
    }
    return image;
}

sf::Image load_image(std::string filename){
    sf::Image img;
    img.loadFromFile(filename);
    return img; //(!texture_image.loadFromFile("data/capture.jpg")); 
}

std::vector<sf::Vector2f> toPoints(sf::Image img){
    std::vector<sf::Vector2f> points;
    int x = 0;
    int y = 0;

    std::queue<sf::Vector2i> todo;
    std::queue<sf::Vector2i> todoBlack;
    todo.push(sf::Vector2i(x, y));
    while(!todo.empty() || !todoBlack.empty()){
        while(! todo.empty()){
            sf::Vector2i temp = todo.front();
            x = temp.x;
            y = temp.y;
            todo.pop();
            // std::cout << x << ", " << y << std::endl;
            if(x < 0 || x >= img.getSize().x || y < 0 || y >= img.getSize().y){
                // std::cout << x << ", " << y << std::endl;
                continue;
            }
            if(img.getPixel(x, y).r == 0){
                todoBlack.push(sf::Vector2i(x, y));
                continue;
            }
            else if(img.getPixel(x, y).r == 1){
                continue;
            }
            
            points.push_back(sf::Vector2f(x, y));
            img.setPixel(x, y, sf::Color(1, 0, 0));

            if(x > 0)
                todo.push(sf::Vector2i(x-1, y));
            if(y > 0)
                todo.push(sf::Vector2i(x, y-1));
            if(x < img.getSize().x - 1)
                todo.push(sf::Vector2i(x+1, y));
            if(y < img.getSize().y - 1)
                todo.push(sf::Vector2i(x, y+1));
        }
        while(todo.empty()){
            sf::Vector2i temp = todoBlack.front();
            x = temp.x;
            y = temp.y;
            if(x == 613 && y == 470)
                std::cout << "\t" << x << ", " << y << std::endl;
            todoBlack.pop();
            if(x < 0 || x >= img.getSize().x || y < 0 || y >= img.getSize().y){
                std::cout << "\t" << x << ", " << y << std::endl;
                continue;
            }
            if(img.getPixel(x, y).r > 1){
                todo.push(sf::Vector2i(x, y));
                continue;
            }
            else if(img.getPixel(x, y).r == 1){
                continue;
            }

            img.setPixel(x, y, sf::Color(1, 0, 0));

            if(x > 0)
                todo.push(sf::Vector2i(x-1, y));
            if(y > 0)
                todo.push(sf::Vector2i(x, y-1));
            if(x < img.getSize().x - 1)
                todo.push(sf::Vector2i(x+1, y));
            if(y < img.getSize().y - 1)
                todo.push(sf::Vector2i(x, y+1));
        }
    }
    return points;
}

void minimal_display(sf::Image image){
    int x = 100;
    int y = 100;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Hello Window");
    while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                            window.close();
            }

            window.clear(sf::Color::Black);
            sf::Texture texture;
            texture.loadFromImage(image);
            sf::Sprite image;
            image.setTexture(texture);
            image.setPosition(sf::Vector2f(x,y));
            image.scale(sf::Vector2f(1,1.5));
            window.clear();
            window.draw(image);

            window.display();
    }
}

sf::Image contour(sf::Image img, int tresh){
    return WnB(add_images(app_kernel(img, {{1, 1, 1}, {0, 0, 0}, {-1, -1, -1}}), app_kernel(img, {{1, 0, -1}, {1, 0, -1}, {1, 0, -1}})), tresh);
}