#ifndef FOURIER_HPP
#define FOURIER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <stdio.h>
#include <iostream>

class Fourier{
    public :
        bool load_image(std::string);
        void minimal_display(sf::Image);
        void convert_image_to_WnB(unsigned int);

        sf::Image image;
        sf::Image image_WnB;
        sf::Texture texture_image;
        //sf::Texture contour_image;
    
    private:

};

#endif