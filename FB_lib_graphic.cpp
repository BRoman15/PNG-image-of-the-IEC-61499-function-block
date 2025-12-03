#include "FB_lib_graphic.h"
#include <iostream>

ImageCreator::ImageCreator(unsigned int width, unsigned int height) 
    : imageSize(width, height) {
    
    // Создаем черный прямоугольник (по центру, размером 50% от изображения)
    rectangle.setSize(sf::Vector2f(width * 0.5f, height * 0.5f));
    rectangle.setFillColor(sf::Color::Black);
    rectangle.setPosition(width * 0.25f, height * 0.25f);
}

bool ImageCreator::createImage() {
    // Создаем текстуру для рендеринга
    if (!renderTexture.create(imageSize.x, imageSize.y)) {
        std::cerr << "Ошибка создания RenderTexture!" << std::endl;
        return false;
    }
    
    // Очищаем белым цветом
    renderTexture.clear(sf::Color::White);
    
    // Рисуем прямоугольник
    renderTexture.draw(rectangle);
    
    // Завершаем рендеринг
    renderTexture.display();
    
    return true;
}

sf::Sprite ImageCreator::getSprite() const {
    return sf::Sprite(renderTexture.getTexture());
}

bool ImageCreator::saveToFile(const std::string& filename) {
    return renderTexture.getTexture().copyToImage().saveToFile(filename);
}