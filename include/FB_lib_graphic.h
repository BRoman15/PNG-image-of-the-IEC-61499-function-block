#pragma once
#include <SFML/Graphics.hpp>

class ImageCreator {
private:
    sf::RenderTexture renderTexture;
    sf::Vector2u imageSize;
    sf::RectangleShape rectangle;
    
public:
    // Конструктор
    ImageCreator(unsigned int width = 800, unsigned int height = 600);
    
    // Создание изображения
    bool createImage();
    
    // Получение спрайта для отрисовки
    sf::Sprite getSprite() const;
    
    // Сохранение в файл
    bool saveToFile(const std::string& filename);
};