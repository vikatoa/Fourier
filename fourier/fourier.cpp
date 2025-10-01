#include"fourier.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>

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
            int k_x_b = (image.getPixel(x-1, y-1).b + image.getPixel(x, y-1).b + image.getPixel(x+1, y-1).b) - (image.getPixel(x-1, y+1).r + image.getPixel(x, y+1).b + image.getPixel(x+1, y+1).b); 
            int k_y_b = (image.getPixel(x-1, y-1).b + image.getPixel(x-1, y).b + image.getPixel(x-1, y+1).b) - (image.getPixel(x+1, y-1).r + image.getPixel(x+1, y).b + image.getPixel(x+1, y+1).b);
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