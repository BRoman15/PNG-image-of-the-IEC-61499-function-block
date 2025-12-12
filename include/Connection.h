#pragma once
#include "FB_lib.h"
#include "FB_lib_graphic.h"


class Connection{
    private:
        unique_ptr<BasicFB> FB;
        unique_ptr<BasicFB_image> image;
        const int x_size_window = 1280;
        const int y_size_window = 720;
    public:
        Connection();
        
        bool load_from_XML(const string& xmlFilePath);
        void showWindow();
        void rendering_FB();
};