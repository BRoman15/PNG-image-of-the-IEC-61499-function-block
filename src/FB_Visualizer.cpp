#include "FB_Visualizer.h"
#include <iostream>
#include <map>
#include <cmath>

FB_Visualizer::FB_Visualizer(){
    image = std::make_unique<BasicFB_image>();
}

FB_Visualizer::~FB_Visualizer(){
    FB.reset();
    image.reset();
}

void FB_Visualizer::load_from_XML(const std::string& xmlFilePath){
    FB = std::make_unique<Parser>(xmlFilePath);
    FB->get_attributes();
    if (FB->name_FB.empty()){
        std::cerr << "Warning: The FB name was not found. Using defolt name." << std::endl;
        FB->name_FB = "defolt";
    }
}

void FB_Visualizer::rendering_FB(){
    std::string filename = FB->name_FB + ".png";
    image->setAutoSaveFilename(filename);
    
    // Добавление главного контура
    const int bevelSize = 20;
    const int width_inf_line = 30;
    const int vertical_indent = 40;
    const int horizontal_indent = 30;
    const int height_event = std::max(FB->get_count_eventInputs() * width_inf_line + vertical_indent, 
                                FB->get_count_eventOutputs() * width_inf_line + vertical_indent);
    const int height_var = std::max(FB->get_count_varsInputs() * width_inf_line + vertical_indent,
                                FB->get_count_varsOutputs() * width_inf_line + vertical_indent);
    int width_FB = image -> get_width_text(FB -> get_name_FB()) + horizontal_indent;
    const int x_FB = x_size_window / 2 - width_FB / 2;
    const int y_FB = (y_size_window - (height_event + height_var)) / 2 + height_event;

    if (width_FB < 150){
        width_FB = 150;
    }

    image -> addMainContour(x_FB, y_FB, width_FB, height_event, height_var, bevelSize);

    // Название
    image ->addText(FB->get_name_FB(),
        x_FB + trunc(width_FB/2) - trunc(image->get_width_text(FB->get_name_FB())/2),
        y_FB - trunc((image->text_size)+10)/2);
    
    // добавление var input
    int top_margin = 25;
    int extra_length_connection = FB->get_countEvent_InputWith_var()*5;
    std::map<std::string, float> var_for_connection;
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
            for (std::string var : event.vars){
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
            for (std::string var : event.vars){
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

void FB_Visualizer::showWindow(){
    while (image->isWindowOpen()) {
        image->update();
    }
}

void FB_Visualizer::show_and_save_FB(const std::string& xmlFilePath){
    load_from_XML(xmlFilePath);
    rendering_FB();
    showWindow();
}