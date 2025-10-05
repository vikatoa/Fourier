#ifndef FOURIER_HPP
#define FOURIER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <stdio.h>
#include <iostream>
#include <array>

class Fourier{
    public :
        bool load_image(std::string);
        void minimal_display(sf::Image);
        void convert_image_to_WnB(unsigned int);
        void convert_image_to_contour();
        sf::Image app_kernel(sf::Image img, std::vector<std::vector<float>> kernel);
        sf::Image add_images(sf::Image img1, sf::Image img2);
        sf::Image WnB(sf::Image img, int tresh);
        sf::Image WnB(sf::Image img);
         

        sf::Image image;
        sf::Image image_WnB;
        sf::Image image_contour;
        sf::Texture texture_image;
        //sf::Texture contour_image;
    
    private:

};

#endif