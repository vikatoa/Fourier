#include <SFML/Graphics/Color.hpp>
#include<iostream>
#include"interface/interface.hpp"
#include"fourier/fourier.hpp"
//g++ main.cpp -fPIC interface/interface.cpp fourier/fourier.cpp -o prog -lsfml-graphics -lsfml-window -lsfml-system

int main()
{
   Interface interface;
    // Fourier image;
    // image.load_image("data/capture.jpg"); 
    // sf::Image i1 = image.app_kernel(image.image, {{1, 1, 1}, {0, 0, 0}, {-1, -1, -1}});
    // sf::Image i2 = image.app_kernel(image.image, {{1, 0, -1}, {1, 0, -1}, {1, 0, -1}});
    // sf::Image i  = image.add_images(i1, i2);
    // sf::Image w  = image.WnB(i, 60);
    // image.minimal_display(image.image);
    // image.minimal_display(i1);
    // image.minimal_display(i2);
    // image.minimal_display(i);
    // image.minimal_display(w);

    
    while(interface.isOpen()){
        if(interface.timeToFrame()){
            interface.events();
            interface.show();
        }
        interface.update();
    }
    
    return 0;
}