#pragma once
#include "Parser.h"
#include "FB_lib_graphic.h"


class FB_Visualizer{
    private:
        unique_ptr<Parser> FB;
        unique_ptr<BasicFB_image> image;
        const int x_size_window = 1280;
        const int y_size_window = 720;
    public:
        FB_Visualizer();
        ~FB_Visualizer();
        bool load_from_XML(const string& xmlFilePath);
        void show_and_save_FB();
        void rendering_FB();
};