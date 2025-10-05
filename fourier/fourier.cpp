#include"fourier.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

sf::Image Fourier::app_kernel(sf::Image img, std::vector<std::vector<float>> kernel){
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

sf::Image Fourier::add_images(sf::Image img1, sf::Image img2){
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

sf::Image Fourier::WnB(sf::Image img, int tresh){
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

sf::Image Fourier::WnB(sf::Image img){
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

bool Fourier::load_image(std::string filename){
    return image.loadFromFile(filename); //(!texture_image.loadFromFile("data/capture.jpg")); 
}

void Fourier::convert_image_to_WnB(unsigned int tresh){
    sf::Vector2<unsigned int> size = image_contour.getSize(); 
    image_WnB.create(size.x, size.y, sf::Color(0, 0, 0)); 
    for (auto x=0; x<size.x; x++){
        for (auto y=0; y<size.y; y++){
            if ((image_contour.getPixel(x, y).r + image_contour.getPixel(x, y).g + image_contour.getPixel(x, y).b) >= tresh*3){
                image_WnB.setPixel(x, y, sf::Color(255, 255, 255));
            }
        }
    }
}

void Fourier::convert_image_to_contour(){
    sf::Vector2<unsigned int> size = image.getSize(); 
    image_contour.create(size.x-2, size.y-2, sf::Color(0, 0, 0)); 
    for (auto x=1; x<size.x-1; x++){
        for (auto y=1; y<size.y-1; y++){
            int k_x_r = (image.getPixel(x-1, y-1).r + image.getPixel(x, y-1).r + image.getPixel(x+1, y-1).r) - (image.getPixel(x-1, y+1).r + image.getPixel(x, y+1).r + image.getPixel(x+1, y+1).r); 
            int k_y_r = (image.getPixel(x-1, y-1).r + image.getPixel(x-1, y).r + image.getPixel(x-1, y+1).r) - (image.getPixel(x+1, y-1).r + image.getPixel(x+1, y).r + image.getPixel(x+1, y+1).r);
            unsigned int score_r = (int)floor(std::pow(k_x_r*k_x_r+k_y_r*k_y_r, 0.5));
            int k_x_g = (image.getPixel(x-1, y-1).g + image.getPixel(x, y-1).g + image.getPixel(x+1, y-1).g) - (image.getPixel(x-1, y+1).g + image.getPixel(x, y+1).g + image.getPixel(x+1, y+1).g); 
            int k_y_g = (image.getPixel(x-1, y-1).g + image.getPixel(x-1, y).g + image.getPixel(x-1, y+1).g) - (image.getPixel(x+1, y-1).g + image.getPixel(x+1, y).g + image.getPixel(x+1, y+1).g);
            unsigned int score_g = (int)floor(std::pow(k_x_g*k_x_g+k_y_g*k_y_g, 0.5));
            int k_x_b = (image.getPixel(x-1, y-1).b + image.getPixel(x, y-1).b + image.getPixel(x+1, y-1).b) - (image.getPixel(x-1, y+1).b + image.getPixel(x, y+1).b + image.getPixel(x+1, y+1).b); 
            int k_y_b = (image.getPixel(x-1, y-1).b + image.getPixel(x-1, y).b + image.getPixel(x-1, y+1).b) - (image.getPixel(x+1, y-1).b + image.getPixel(x+1, y).b + image.getPixel(x+1, y+1).b);
            unsigned int score_b = (int)floor(std::pow(k_x_b*k_x_b+k_y_b*k_y_b, 0.5));
            image_contour.setPixel(x-1, y-1, sf::Color(score_r, score_g, score_b));
        }
    }
}



void Fourier::minimal_display(sf::Image image){
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