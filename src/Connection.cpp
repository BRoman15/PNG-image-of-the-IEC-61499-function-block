#include "Connection.h"
#include <iostream>
#include <map>
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
    const int height_event = max(FB->get_count_eventInputs() * 30 + 40, FB->get_count_eventOutputs() * 30 + 40);
    const int height_var = max(FB->get_count_varsInputs() * 30 + 40, FB->get_count_varsOutputs() * 30 + 40);
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
    
    // добавление var input
    int top_margin = 25;
    int extra_length_connection = FB->get_countEvent_InputWith_var()*5;
    map<string, float> var_for_connection;
    for (InputVars event : FB->inputVars_attrebutes){
        image->addTriangle_Blue(x_FB, y_FB + top_margin);
        image->addText(event.name,
            x_FB + image->text_size / 2 + 5,
            y_FB + top_margin - 5);
        image->addLine(x_FB,
            y_FB + top_margin + image->text_size/2,
            -(10 + image->size_square * FB->get_countEvent_InputWith_var() + 10 + extra_length_connection));

        image->addText(event.type,
            x_FB - (10 + image->size_square * FB->get_countEvent_InputWith_var() + 5 + extra_length_connection) - image->get_width_text(event.type) -15,
            y_FB + top_margin - 5);

        if (event.comment.empty() == false){
            image->addLine(
                x_FB - (10 + image->size_square * FB->get_countEvent_InputWith_var() + 5 + extra_length_connection) - image->get_width_text(event.type) -35,
                y_FB + top_margin + image->text_size/2,
                5);
        }
        
        image->addText(event.comment,
            x_FB - (10 + image->size_square * FB->get_countEvent_InputWith_var() + 5 + extra_length_connection) - image->get_width_text(event.type) -50 - image->get_width_text(event.comment),
            y_FB + top_margin - 5);
        var_for_connection[event.name] = y_FB + top_margin + image->text_size/2;
        top_margin += 30;
    }

    // добавление var output
    top_margin = 25;
    extra_length_connection = FB->get_countEvent_InputWith_var()*5;
    for (OutputVars event : FB->outputVars_attrebutes){
        image->addTriangle_Blue(x_FB + width_FB - image->text_size/2, y_FB + top_margin);
        image->addText(event.name,
            x_FB + width_FB - image->text_size * 2 - 12,
            y_FB + top_margin - 5);
        image->addLine(x_FB + width_FB,
            y_FB + top_margin + image->text_size/2,
            10 + image->size_square * FB->get_countEvent_InputWith_var() + 10 + extra_length_connection);

        image->addText(event.type,
            x_FB + width_FB + (10 + image->size_square * FB->get_countEvent_InputWith_var() + 5 + extra_length_connection) +15,
            y_FB + top_margin - 5);

        if (event.comment.empty() == false){
            image->addLine(
                x_FB + width_FB + (10 + image->size_square * FB->get_countEvent_InputWith_var() + 5 + extra_length_connection) + image->get_width_text(event.type) + 30,
                y_FB + top_margin + image->text_size/2,
                5);
        }

        image->addText(event.comment,
            x_FB + width_FB + (10 + image->size_square * FB->get_countEvent_InputWith_var() + 5 + extra_length_connection) + image->get_width_text(event.type) + 45,
            y_FB + top_margin - 5);
        
        var_for_connection[event.name] = y_FB + top_margin + image->text_size/2;
        top_margin += 30;
    }

    image->update();

    // добавление event input
    top_margin = 25;
    int coefficient_order_connections = 0;
    extra_length_connection = FB->get_countEvent_InputWith_var()*5;
    for (EventInputs event : FB->eventInputs_attrebutes){
        image->addTriangle_Green(x_FB, y_FB - height_event + top_margin);
        image->addText(event.name, x_FB + image->text_size / 2 + 5, y_FB - height_event + top_margin - 5);
        image->addLine(x_FB,
            y_FB - height_event + top_margin + image->text_size/2,
            -(10 + image->size_square * FB->get_countEvent_InputWith_var() + 10 + extra_length_connection));

        if (event.vars.empty() == false){
            for (string var : event.vars){
                image->addConnection(x_FB - 10 - image->size_square - coefficient_order_connections,
                    y_FB - height_event + top_margin + image->text_size/2,
                    var_for_connection[var] - (y_FB - height_event + top_margin + image->text_size/2));
            }
            coefficient_order_connections += 15;
        }
        image->addText(event.type,
            x_FB - (10 + image->size_square * FB->get_countEvent_InputWith_var() + 5 + extra_length_connection) - image->get_width_text(event.type) -15,
            y_FB - height_event + top_margin - 5);
        
        if (event.comment.empty() == false){
            image->addLine(
                x_FB - (10 + image->size_square * FB->get_countEvent_InputWith_var() + 5 + extra_length_connection) - image->get_width_text(event.type) -35,
                y_FB - height_event + top_margin + image->text_size/2,
                5);
        }

        image->addText(event.comment,
            x_FB - (10 + image->size_square * FB->get_countEvent_InputWith_var() + 5 + extra_length_connection) - image->get_width_text(event.type) -50 - image->get_width_text(event.comment),
            y_FB - height_event + top_margin - 5);
        top_margin += 30;
    }
 
    // добавление event outputs
    top_margin = 25;
    coefficient_order_connections = 0;
    extra_length_connection = FB->get_countEvent_OutputsWith_var()*5;
    for (EventOutputs event : FB->eventOutputs_attrebutes){
        image->addTriangle_Green(x_FB + width_FB - image->text_size/2, y_FB - height_event + top_margin);
        image->addText(event.name,
            x_FB + width_FB - image->text_size * 2 - 12,
            y_FB - height_event + top_margin - 5);

        image->addLine(x_FB + width_FB,
            y_FB - height_event + top_margin + image->text_size/2,
            10 + image->size_square * FB->get_countEvent_OutputsWith_var() + 10 + extra_length_connection);

        if (event.vars.empty() == false){
            for (string var : event.vars){
                image->addConnection(x_FB + width_FB + 10 + image->size_square + coefficient_order_connections,
                    y_FB - height_event + top_margin + image->text_size/2,
                    var_for_connection[var] - (y_FB - height_event + top_margin + image->text_size/2));
            }
            coefficient_order_connections += 15;
        }
        image->addText(event.type,
            x_FB + width_FB + (10 + image->size_square * FB->get_countEvent_InputWith_var() + 5 + extra_length_connection) +15,
            y_FB - height_event + top_margin - 5);

        if (event.comment.empty() == false){
            image->addLine(
                x_FB + width_FB + (10 + image->size_square * FB->get_countEvent_InputWith_var() + 5 + extra_length_connection) + image->get_width_text(event.type) + 30,
                y_FB - height_event + top_margin + image->text_size/2,
                5);
        }

        image->addText(event.comment,
            x_FB + width_FB + (10 + image->size_square * FB->get_countEvent_InputWith_var() + 5 + extra_length_connection) + image->get_width_text(event.type) + 45,
            y_FB - height_event + top_margin - 5);
        top_margin += 30;
    }
}
