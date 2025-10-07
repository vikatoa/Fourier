#include <SFML/Graphics/Color.hpp>
#include<iostream>
#include"interface/interface.hpp"
#include"fourier/fourier.hpp"
//g++ main.cpp -fPIC interface/interface.cpp fourier/fourier.cpp -o prog -lsfml-graphics -lsfml-window -lsfml-system

int main()
{
    Interface interface;
    sf::Image img;
    img = load_image("data/capture.jpg"); 
    sf::Image w  = contour(img, 50);
    minimal_display(w);


    interface.getPoints(toPoints(w));
    while(interface.isOpen()){
        if(interface.timeToFrame()){
            interface.events();
            interface.show();
        }
        interface.update();
    }
    
    return 0;
}