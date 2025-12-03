#include <iostream>
// // #include "FB_lib.h"


// // int main(){
// //     BasicFB* a = create_basic_fb("C:\\VSCod\\PNG-image-of-the-IEC-61499-function-block\\test_data_xml\\ADD_2.xml");
// //     get_name(a);
// // }

#include <SFML/Graphics.hpp>
// #include "FB_lib_graphic.h"

int main() {

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



// #include <SFML/Graphics.hpp>

// int main()
// {
//     // Создаем окно размером 800x600 с заголовком "SFML Window"
//     sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
    
//     // Главный цикл программы
//     while (window.isOpen())
//     {
//         // Обработка событий
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             // Закрытие окна при нажатии на крестик
//             if (event.type == sf::Event::Closed)
//                 window.close();
            
//             // Закрытие окна при нажатии клавиши Escape
//             if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
//                 window.close();
//         }
        
//         // Очистка окна черным цветом
//         window.clear(sf::Color::Black);
        
//         // Здесь можно рисовать объекты
//         // window.draw(someObject);
        
//         // Отображение нарисованного
//         window.display();
//     }
    
//     return 0;
// }