#include"fourier.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>


bool Fourier::load_image(std::string filename){
    return image.loadFromFile(filename); //(!texture_image.loadFromFile("data/capture.jpg")); 
}

void Fourier::convert_image_to_WnB(unsigned int tresh){
    sf::Vector2<unsigned int> size = image.getSize(); 
    image_WnB.create(size.x, size.y, sf::Color(0, 0, 0)); 
    for (auto x=0; x<size.x; x++){
        for (auto y=0; y<size.y; y++){
            if ((image.getPixel(x, y).r + image.getPixel(x, y).g + image.getPixel(x, y).b) >= tresh*3){
                image_WnB.setPixel(x, y, sf::Color(255, 255, 255));
            }
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