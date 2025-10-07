#ifndef FOURIER_HPP
#define FOURIER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <stdio.h>
#include <iostream>
#include <array>
#include <queue>

sf::Image load_image(std::string);
void minimal_display(sf::Image image);
sf::Image app_kernel(sf::Image img, std::vector<std::vector<float>> kernel);
sf::Image add_images(sf::Image img1, sf::Image img2);
sf::Image WnB(sf::Image img, int tresh);
sf::Image WnB(sf::Image img);
std::vector<sf::Vector2f> toPoints(sf::Image img);
sf::Image contour(sf::Image img, int tresh);

#endif