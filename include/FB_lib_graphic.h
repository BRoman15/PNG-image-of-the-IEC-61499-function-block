#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>
#include <iomanip>

class BasicFB_image{
    int cout_event_inputoutput;
    bool isOpen;
    sf::RenderWindow window;
    sf::RenderTexture renderTexture;
    std::vector<std::function<void(sf::RenderTarget&)>> drawables;
    std::string autoSaveFilename;
    bool saveToPNG(const std::string& filename);
    sf::Color text_color = sf::Color::Black;
    std::unique_ptr<sf::Font> font;
    const int size_square = 10;
    const int text_size = 20;

    public:
        BasicFB_image();
        ~BasicFB_image();
        bool isWindowOpen();
        void update();
        void setAutoSaveFilename(const std::string& filename);
        void close();
        void addDrawable(std::function<void(sf::RenderTarget&)> drawFunc);
        void addMainContour(float x, float y, float width, float height_event, float height_vars, float bevelSize, float outlineThickness = 1.0f);
        void addText(const std::string& text, float x, float y);
        float get_width_text(const std::string& text);
        void addTriangle_Green(float x, float y);
        void addTriangle_Blue(float x, float y);
        void addLine(float x, float y, float length);
        void addConnection(float x, float y, float y_var);
        int get_text_size();
        int get_size_square();
};