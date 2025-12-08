#pragma once
// #include "FB_lib.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>
#include <iomanip>

// class BasicFB_image{
// private:
//     std::unique_ptr<BasicFB> fb;
//     sf::RenderTexture renderTexture;
//     sf::Font font;
    
//     // Colors - простые и четкие
//     sf::Color backgroundColor = sf::Color::White;
//     sf::Color borderColor = sf::Color::Black;
//     sf::Color titleColor = sf::Color(0, 0, 0); // Серый для названия
//     sf::Color eventInputColor = sf::Color(200, 230, 255); // Светло-голубой
//     sf::Color eventOutputColor = sf::Color(200, 255, 230); // Светло-зеленый
//     sf::Color dataInputColor = sf::Color(255, 240, 200); // Светло-бежевый
//     sf::Color dataOutputColor = sf::Color(255, 220, 255); // Светло-розовый
//     sf::Color textColor = sf::Color::Black;
    
//     // Dimensions
//     const float fbWidth = 600.0f;
//     const float fbHeight = 400.0f;
//     const float elementHeight = 25.0f;
//     const float padding = 15.0f;
    
// public:
//     BasicFB_image(const char* xml_file_address);
//     ~BasicFB_image() = default;
    
//     bool loadFont(const std::string& fontPath = "");
//     void drawFB();
//     bool saveToPNG(const std::string& filename);
    
// private:
//     void drawMainRectangle(sf::RenderTexture& texture);
//     void drawDashedLine(sf::RenderTexture& texture, float x1, float y1, float x2, float y2);
//     void drawTitle(sf::RenderTexture& texture);
//     void drawEventSection(sf::RenderTexture& texture);
//     void drawDataSection(sf::RenderTexture& texture);
//     void drawLeftSide(sf::RenderTexture& texture, float startY, const std::vector<EventInputs>& events,
//                      const std::vector<InputVars>& vars, const sf::Color& eventColor, const sf::Color& dataColor);
//     void drawRightSide(sf::RenderTexture& texture, float startY, const std::vector<EventOutputs>& events,
//                       const std::vector<OutputVars>& vars, const sf::Color& eventColor, const sf::Color& dataColor);
// };


class BasicFB_image{
    int cout_event_inputoutput;
    bool isOpen;
    sf::RenderWindow window;
    sf::RenderTexture renderTexture;
    std::vector<std::function<void(sf::RenderTarget&)>> drawables;
    bool saveToPNG(const std::string& filename);
    const int text_size = 20;
    sf::Color text_color = sf::Color::Black;
    std::unique_ptr<sf::Font> font;


    public:
        BasicFB_image();
        ~BasicFB_image();
        bool isWindowOpen();
        void update();
        void close();
        void addDrawable(std::function<void(sf::RenderTarget&)> drawFunc);
        void addTransparentBeveledRectangle(float x, float y, float width, float height_event, float height_vars, float bevelSize, float outlineThickness = 1.0f);
        void addText(const std::string& text, float x, float y);
        void addTriangle(float x, float y);
        void addLine(float x, float y, float length);
        void addLine(float x, float y, float length, const int a);

};