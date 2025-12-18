#include "FB_lib_graphic.h"
#include <iostream>
#include <fstream>
#include <vector>

BasicFB_image::BasicFB_image(){
    window.create(sf::VideoMode(1280, 720), "Save to PNG", sf::Style::Default);
    renderTexture.create(1280, 720);
    window.setFramerateLimit(25);

    // Загрузка шрифта
    font = std::make_unique<sf::Font>();

    const char* font_paths[] = {
        "cour.ttf",
        "C:/Windows/Fonts/cour.ttf",
        "C:/Windows/Fonts/courbd.ttf",
        "C:/Windows/Fonts/couri.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
    };
    
    bool font_loaded = false;
    for (const char* fount_path : font_paths){
        std::ifstream testFile(fount_path);
        if (testFile.good()){
            if (font->loadFromFile(fount_path)){
                font_loaded = true;
                break;
            }
            testFile.close();
        }
    }

    if (!font_loaded) {
        throw std::runtime_error("Cour font not found.");
    }
}

BasicFB_image::~BasicFB_image() {
    if (window.isOpen()) {
        window.close();
    }
}

// Создание окна
void BasicFB_image::save_to_PNG(const std::string& image_filename) {
    renderTexture.getTexture().copyToImage().saveToFile(image_filename);
}

void BasicFB_image::update() {
    if (window.isOpen()){
        window.clear(sf::Color::White);
        renderTexture.clear(sf::Color::White);

        // Отрисовка всех объектов
        for (auto& drawFunc : drawables){
            drawFunc(window);
            drawFunc(renderTexture);
        }

        window.display();
        renderTexture.display();

        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                save_to_PNG(filename_for_save);
                window.close();
            }
        }
    }
}

void BasicFB_image::set_filename_for_save(const std::string& filename){
    filename_for_save = filename;
}

bool BasicFB_image::is_window_open(){
    return window.isOpen();
}

// Добавление объектов
void BasicFB_image::addDrawable(std::function<void(sf::RenderTarget&)> drawFunc) {
    drawables.push_back(drawFunc);
}

// Контур функционального блока
void BasicFB_image::addMainContour(float x, float y, float width, float height_event, float height_vars, float bevelSize) {
    addDrawable([=](sf::RenderTarget& target) {        
        sf::ConvexShape shape;
        shape.setPointCount(14);
        
        shape.setPoint(0, sf::Vector2f(x + width - bevelSize, y));
        shape.setPoint(1, sf::Vector2f(x + width, y + bevelSize));
        shape.setPoint(2, sf::Vector2f(x + width, y + height_vars - bevelSize));
        shape.setPoint(3, sf::Vector2f(x + width - bevelSize, y + height_vars));
        shape.setPoint(4, sf::Vector2f(x + bevelSize, y + height_vars));
        shape.setPoint(5, sf::Vector2f(x, y + height_vars - bevelSize));
        shape.setPoint(6, sf::Vector2f(x, y + bevelSize));
        shape.setPoint(7, sf::Vector2f(x + bevelSize, y));
        shape.setPoint(8, sf::Vector2f(x, y - bevelSize));
        shape.setPoint(9, sf::Vector2f(x, y + bevelSize - height_event));
        shape.setPoint(10, sf::Vector2f(x + bevelSize, y - height_event));
        shape.setPoint(11, sf::Vector2f(x - bevelSize + width, y - height_event));
        shape.setPoint(12, sf::Vector2f(x + width, y - height_event + bevelSize));
        shape.setPoint(13, sf::Vector2f(x + width, y - bevelSize));

        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(1);
        
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

// Получачем длинну строки в прикселях
float BasicFB_image::get_width_text(const std::string& text_){
    if (!font || font->getInfo().family.empty()) {
        return text_.length() * 12;  //Примерное значение
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
        shape.setPoint(1, sf::Vector2f(x + (text_size * 0.5), y + text_size/2));
        shape.setPoint(2, sf::Vector2f(x, y + text_size));

        shape.setFillColor(sf::Color::Green);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(1);
        
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
        shape.setOutlineThickness(1);
        
        target.draw(shape);
    });
}

// Линия
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

// Соединение event-var
void BasicFB_image::addConnection(float x, float y, float y_var){
    addDrawable([=](sf::RenderTarget& target) {
        sf::ConvexShape shape;
        shape.setPointCount(4);

        shape.setPoint(0, sf::Vector2f(x - size_square/2, y - size_square/2));
        shape.setPoint(1, sf::Vector2f(x + size_square/2, y - size_square/2));
        shape.setPoint(2, sf::Vector2f(x + size_square/2, y + size_square/2));
        shape.setPoint(3, sf::Vector2f(x - size_square/2, y + size_square/2));

        shape.setFillColor(sf::Color::Transparent);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(1);
        
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
        shape1.setOutlineThickness(1);

        target.draw(shape1);
    });
}

// Геттеры
int BasicFB_image::get_text_size(){
    return text_size;
}

int BasicFB_image::get_size_square(){
    return size_square;
}