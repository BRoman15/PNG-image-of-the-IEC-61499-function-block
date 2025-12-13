#pragma once
#include "Parser.h"
#include "FB_lib_graphic.h"


class FB_Visualizer{
    private:
        unique_ptr<Parser> FB;
        unique_ptr<BasicFB_image> image;
        const int x_size_window = 1280;
        const int y_size_window = 720;
        void load_from_XML(const string& xmlFilePath);
        void rendering_FB();
        void showWindow();
    public:
        FB_Visualizer();
        ~FB_Visualizer();
        void show_and_save_FB(const string& xmlFilePath);
};