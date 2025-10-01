#include <SFML/Graphics/Color.hpp>
#include<iostream>
#include"interface/interface.hpp"
#include"fourier/fourier.hpp"
//g++ main.cpp -fPIC interface/interface.cpp fourier/fourier.cpp -o prog -lsfml-graphics -lsfml-window -lsfml-system

int main()
{
   // Interface interface;
    Fourier image;
    image.load_image("data/capture.jpg"); 
    image.convert_image_to_contour();
    image.convert_image_to_WnB(90);
    image.minimal_display(image.image);
    image.minimal_display(image.image_contour);
    image.minimal_display(image.image_WnB);
    /*
    while(interface.isOpen()){
        interface.events();
        interface.show();
        interface.update();
    }
    */
    return 0;
}