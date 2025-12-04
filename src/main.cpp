#include "C:\VSCod\PNG-image-of-the-IEC-61499-function-block\include\FB_lib.h"
#include "SFML\Graphics.hpp"

int main(){
    BasicFB* a = create_basic_fb("C:\\VSCod\\PNG-image-of-the-IEC-61499-function-block\\test_data_xml\\INT2INT.xml");
    get_name(a);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Test");
    sf::RectangleShape rect(sf::Vector2f(400, 300));
    rect.setFillColor(sf::Color::Red);
    rect.setPosition(200, 150);
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(rect);
        window.display();
    }
    return 0;


}