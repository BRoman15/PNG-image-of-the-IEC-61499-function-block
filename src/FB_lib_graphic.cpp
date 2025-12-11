#include "C:\VSCod\PNG-image-of-the-IEC-61499-function-block\include\FB_lib_graphic.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include "SFML\Graphics.hpp"

BasicFB_image::BasicFB_image() : window(sf::VideoMode(1280, 720), "Save to PNG", sf::Style::Default){
    isOpen = true;
    renderTexture.create(1280, 720);
    window.setFramerateLimit(60);

    // Загрузка шрифта
    font = std::make_unique<sf::Font>();
    
    // Пытаемся загрузить шрифт из разных мест
    const char* fontPaths[] = {
        "cour.ttf",
        "C:/Windows/Fonts/cour.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        nullptr
    };
    
    bool fontLoaded = false;
    for (int i = 0; fontPaths[i] != nullptr; i++) {
        if (font->loadFromFile(fontPaths[i])) {
            fontLoaded = true;
            break;
        }
    }
    
    if (fontLoaded == false) {
        std::cout << "ERROR: font is not loaded" << std::endl;
        std::cout << "Place the arial.ttf file in the program folder" << std::endl;
    }
}

BasicFB_image::~BasicFB_image() {
    if (window.isOpen()) {
        window.close();
    }
    font.reset();
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

// Контур функционального блока
void BasicFB_image::addMainContour(float x, float y, float width, float height_event, float height_vars, float bevelSize, float outlineThickness) {
    
    addDrawable([=](sf::RenderTarget& target) {
        // Проверяем и ограничиваем размер фаски
        float safeBevel = bevelSize / 2;
        float maxBevel = std::min(width, height_vars) / 2.0f;
        if (bevelSize > maxBevel) {
            safeBevel = maxBevel;
        }
        
        // Создаем ConvexShape
        sf::ConvexShape shape;
        shape.setPointCount(14);
        
        // Устанавливаем точки фигуры
        shape.setPoint(0, sf::Vector2f(x + width - safeBevel, y));
        shape.setPoint(1, sf::Vector2f(x + width, y + safeBevel));
        shape.setPoint(2, sf::Vector2f(x + width, y + height_vars - safeBevel));
        shape.setPoint(3, sf::Vector2f(x + width - safeBevel, y + height_vars));
        shape.setPoint(4, sf::Vector2f(x + safeBevel, y + height_vars));
        shape.setPoint(5, sf::Vector2f(x, y + height_vars - safeBevel));
        shape.setPoint(6, sf::Vector2f(x, y + safeBevel));
        shape.setPoint(7, sf::Vector2f(x + safeBevel, y));
        shape.setPoint(8, sf::Vector2f(x, y - safeBevel));
        shape.setPoint(9, sf::Vector2f(x, y + safeBevel - height_event));
        shape.setPoint(10, sf::Vector2f(x + safeBevel, y - height_event));
        shape.setPoint(11, sf::Vector2f(x - safeBevel + width, y - height_event));
        shape.setPoint(12, sf::Vector2f(x + width, y - height_event + safeBevel));
        shape.setPoint(13, sf::Vector2f(x + width, y - safeBevel));



        // ПРОЗРАЧНАЯ заливка, ЧЕРНЫЙ контур
        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(outlineThickness);
        
        target.draw(shape);
    });
}

// Текст
void BasicFB_image::addText(const std::string& text, float x, float y) {
    drawables.push_back([this, text, x, y](sf::RenderTarget& target) {
        sf::Text textObj(text, *font, text_size);
        textObj.setPosition(x, y);
        textObj.setFillColor(text_color);
        target.draw(textObj);
    });
}

float BasicFB_image::get_width_text(const std::string& text_){
    if (!font || font->getInfo().family.empty()) {
        return text_.length() * 12;  // Возвращаем примерное значение
    }
    sf::Text text(text_, *font, 20);
    sf::FloatRect bounds = text.getLocalBounds();
    float width = bounds.width;
    return width;
}

// Треугольник
void BasicFB_image::addTriangle_Green(float x, float y){

        addDrawable([=](sf::RenderTarget& target) {
        sf::ConvexShape shape;
        shape.setPointCount(3);

        shape.setPoint(0, sf::Vector2f(x, y));
        shape.setPoint(1, sf::Vector2f(x + (text_size * 0.5), y + text_size/2)); //0.866
        shape.setPoint(2, sf::Vector2f(x, y + text_size));

        shape.setFillColor(sf::Color::Green); // Transparent
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(1.0f);
        
        target.draw(shape);
    });
}

void BasicFB_image::addTriangle_Blue(float x, float y){

        addDrawable([=](sf::RenderTarget& target) {
        sf::ConvexShape shape;
        shape.setPointCount(3);

        shape.setPoint(0, sf::Vector2f(x, y));
        shape.setPoint(1, sf::Vector2f(x + (text_size * 0.5), y + text_size/2));
        shape.setPoint(2, sf::Vector2f(x, y + text_size));

        shape.setFillColor(sf::Color::Blue);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(1.0f);
        
        target.draw(shape);
    });
}

// Линии

void BasicFB_image::addLine(float x, float y, float length){
    addDrawable([=](sf::RenderTarget& target) {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(x, y);
        line[1].position = sf::Vector2f(x + length, y);

        line[0].color = sf::Color::Black;
        line[1].color = sf::Color::Black;
        target.draw(line);
    });
}

void BasicFB_image::addLine(float x, float y, float length, const int a){
    addDrawable([=](sf::RenderTarget& target) {
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(x, y);
        line[1].position = sf::Vector2f(x, y + length);

        line[0].color = sf::Color::Black;
        line[1].color = sf::Color::Black;
        target.draw(line);
    });
}

// Соединение event-var
void BasicFB_image::addConnection(float x, float y, float y_var){
    addDrawable([=](sf::RenderTarget& target) {
        // Создаем ConvexShape
        sf::ConvexShape shape;
        shape.setPointCount(4);

        shape.setPoint(0, sf::Vector2f(x - size_square/2, y - size_square/2));
        shape.setPoint(1, sf::Vector2f(x + size_square/2, y - size_square/2));
        shape.setPoint(2, sf::Vector2f(x + size_square/2, y + size_square/2));
        shape.setPoint(3, sf::Vector2f(x - size_square/2, y + size_square/2));

        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(1.0f);
        
        target.draw(shape);

        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(x, y);
        line[1].position = sf::Vector2f(x, y + y_var);

        line[0].color = sf::Color::Black;
        line[1].color = sf::Color::Black;
        target.draw(line);

        sf::ConvexShape shape1;
        shape1.setPointCount(4);

        shape1.setPoint(0, sf::Vector2f(x - size_square/2, y + y_var - size_square/2));
        shape1.setPoint(1, sf::Vector2f(x + size_square/2, y + y_var - size_square/2));
        shape1.setPoint(2, sf::Vector2f(x + size_square/2, y + y_var + size_square/2));
        shape1.setPoint(3, sf::Vector2f(x - size_square/2, y + y_var + size_square/2));

        shape1.setFillColor(sf::Color::Transparent);
        shape1.setOutlineColor(sf::Color::Black);
        shape1.setOutlineThickness(1.0f);

        target.draw(shape1);
    });
}