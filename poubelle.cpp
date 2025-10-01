
int main(){
        int x = 100;
        int y = 100;
        sf::RenderWindow window(sf::VideoMode(800, 600), "Hello Window");
        sf::Texture texture;
        if (!texture.loadFromFile("data/capture.jpg")) {
                std::cout << "Could not load enemy texture" << std::endl;
                return 0;
        }
        while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed)
                                window.close();
                }

                window.clear(sf::Color::Black);

                sf::Sprite image;
                image.setTexture(texture);
                image.setPosition(sf::Vector2f(x,y));
                image.scale(sf::Vector2f(1,1.5));
                window.clear();
                window.draw(image);

                window.display();

        }

        return 0;
}