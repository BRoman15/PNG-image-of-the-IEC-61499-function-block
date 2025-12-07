#include "C:\VSCod\PNG-image-of-the-IEC-61499-function-block\include\FB_lib_graphic.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "SFML\Graphics.hpp"

BasicFB_image::BasicFB_image() : window(sf::VideoMode(800, 600), "Save to PNG", sf::Style::Default){
    isOpen = true;
    renderTexture.create(800, 600);
    window.setFramerateLimit(60);
}

BasicFB_image::~BasicFB_image() {
    if (window.isOpen()) {
        window.close();
    }
}

// Создание окна

bool BasicFB_image::saveToPNG(const std::string& image_filename) {
    return renderTexture.getTexture().copyToImage().saveToFile(image_filename);
}

void BasicFB_image::update() {
    if (!isOpen) return;

    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            close();
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S) {
            saveToPNG("FB.png");
        }
    }

    window.clear(sf::Color::White);
    renderTexture.clear(sf::Color::White);
    
    // Отрисовка всех объектов
    for (auto& drawFunc : drawables) {
        drawFunc(window);           // Рисуем в окно
        drawFunc(renderTexture);    // Рисуем в текстуру для сохранения
    }
    
    window.display();
    renderTexture.display();
}

bool BasicFB_image::isWindowOpen(){
    return isOpen;
}

void BasicFB_image::close() {
    isOpen = false;
    window.close();
}


// Добавление объектов

void BasicFB_image::addDrawable(std::function<void(sf::RenderTarget&)> drawFunc) {
    drawables.push_back(drawFunc);
}

// Прямоугольник со скошенными углами (фаской)
void BasicFB_image::addTransparentBeveledRectangle(float x, float y, float width, float height, float bevelSize, float outlineThickness) {
    
    addDrawable([=](sf::RenderTarget& target) {
        // Проверяем и ограничиваем размер фаски
        float safeBevel = bevelSize;
        float maxBevel = std::min(width, height) / 2.0f;
        if (bevelSize > maxBevel) {
            safeBevel = maxBevel;
        }
        
        // Создаем ConvexShape
        sf::ConvexShape shape;
        shape.setPointCount(7);
        
        // Устанавливаем точки для фаски
        shape.setPoint(0, sf::Vector2f(x + safeBevel, y));
        shape.setPoint(1, sf::Vector2f(x + width - safeBevel, y));
        shape.setPoint(2, sf::Vector2f(x + width, y + safeBevel));
        shape.setPoint(3, sf::Vector2f(x + width, y + height - safeBevel));
        shape.setPoint(4, sf::Vector2f(x + width - safeBevel, y + height));
        shape.setPoint(5, sf::Vector2f(x + safeBevel, y + height));
        shape.setPoint(6, sf::Vector2f(x, y + height - safeBevel));
        // shape.setPoint(7, sf::Vector2f(x, y + safeBevel));
        
        // ПРОЗРАЧНАЯ заливка, ЧЕРНЫЙ контур
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(outlineThickness);
        
        target.draw(shape);
    });
}