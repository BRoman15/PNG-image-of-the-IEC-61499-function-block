#include "C:\\VSCod\\PNG-image-of-the-IEC-61499-function-block\\include\\Connection.h"
#include <iostream>
#include <cmath>

Connection::Connection(){
    image = make_unique<BasicFB_image>();
}

bool Connection::load_from_XML(const string& xmlFilePath){
    FB = make_unique<BasicFB>(xmlFilePath);
    FB->get_attributes();
    if (FB->name_FB.empty()){
        cout << "ERROR: file "<< xmlFilePath <<" not found";
        FB.reset();
        return false;
    }
    cout << "Successfully loaded FB: " << FB->name_FB << endl;
    return true;
}

void Connection::showWindow(){
    if (!image) {
        cout << "ERROR: image not initialized" << endl;
        return;
    }
    while (image->isWindowOpen()) {
        image->update();
    }
}

void Connection::rendering_FB(){
    if (!FB || !image) {
        cout << "ERROR: FB or image not initialized" << endl;
        return;
    }
    // Добавление главного контура
    const int count_event = FB -> get_count_event();
    const int count_var = FB -> get_count_vars();
    const int height_event = count_event * 30 + 40;
    const int height_var = count_var * 30 + 40;
    int width_FB = image -> get_width_text(FB -> get_name_FB()) + 30;
    const int x_FB = x_size_window / 2 - width_FB / 2;
    const int y_FB = (y_size_window - (height_event + height_var)) / 2 + height_event;

    if (width_FB < 150){
        width_FB = 150;
    }

    image -> addMainContour(x_FB, y_FB, width_FB, height_event, height_var, 20);

    // Название
    image ->addText(FB->get_name_FB(),
        x_FB + trunc(width_FB/2) - trunc(image->get_width_text(FB->get_name_FB())/2),
        y_FB - trunc((image->text_size)+10)/2);
    
    // добавление event in/out
    // for(int i; i < FB -> eventInputs_attrebutes.size(); i++){
    int top_margin = 20;
    for (EventInputs event : FB->eventInputs_attrebutes){
        image->addText(event.)
    }
    // }

    image->update();
}
