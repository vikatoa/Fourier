#ifndef MAIN_HPP
#define MAIN_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <stdio.h>
#include <queue>
#include <iostream>
#include <string>
#include <complex>
#include <algorithm> 
#include <array>

enum step{
    caption,
    computing,
    drawing,
    closing,
};

class Interface{
    private:
        sf::RenderWindow window;
        step state;
        std::vector<sf::Vector2f> points;
        bool running;
        bool leftButton;
        sf::Font font;
        sf::Text text;
        sf::Clock clock;
        std::queue<sf::Time> frame;
        int nb_circles;
        std::vector<std::pair<std::complex<float>, int>> circles;
        std::vector<sf::Vector2f> sketch;
        int x;
        float periode;
        int fps;

    public:
        Interface();
        ~Interface();

        bool isOpen();
        void update();
        void draw();
        void show();
        void compute();
        void events();
};

#endif