#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <stdio.h>
#include <queue>
#include <iostream>
#include <string>
#include <complex>
#include <algorithm> 
#include <array>
#include <list>

enum step{
    caption,
    computing,
    drawing,
    closing,
};
enum algorithm{
    standard_methode,
    cooly_turkey,
};

class Interface{
    private:
        sf::RenderWindow window;
        step state;
        std::vector<sf::Vector2f> points;
        std::vector<sf::Vector2f> points_to_draw;
        bool running;
        bool leftButton;
        sf::Font font;
        sf::Text text;
        sf::Clock clock;
        std::queue<sf::Time> frame;
        int nb_circles;
        std::vector<std::pair<std::complex<float>, int>> circles;
        std::list<sf::Vector2f> sketch;
        float periode;
        int fps;
        float last_frame_time;
        algorithm algo;
        bool show_circles;
        int max;


    public:
        Interface();
        ~Interface();

        bool timeToFrame();
        bool isOpen();
        void update();
        void draw();
        void show();
        void compute();
        void events();
};

#endif