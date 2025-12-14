#include "Parser.h"
#include "pugixml.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>


Parser::Parser(const char * xml_file_address_){
    xml_file_address = xml_file_address_;
}

Parser::Parser(const std::string& xml_file_address_)
    : xml_file_address(xml_file_address_) {
}

void Parser::get_attributes(){
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(xml_file_address.c_str());
    if (!result){
        std::cerr << "ERROR: " << result.description() << std::endl;
    }

    //Получение имени функционального блока
    pugi::xpath_node_set elements_fb = doc.select_nodes("/FBType");
    for (pugi::xpath_node xpath_node : elements_fb) {
        pugi::xml_node node = xpath_node.node();
        name_FB = node.attribute("Name").as_string();
    }

    //Получаем атрибуты подузлов узла EventInputs
    pugi::xpath_node_set elements_input = doc.select_nodes("//EventInputs//Event");           
    for (pugi::xpath_node xpath_node : elements_input) {
        pugi::xml_node node = xpath_node.node();
        EventInputs event_input;
        for (pugi::xml_attribute attribut : node.attributes()){
            if ((std::string)attribut.name() == "Name"){
                event_input.name = attribut.as_string();
            }
            else if ((std::string)attribut.name() == "Type"){
                event_input.type = attribut.as_string();                        
            }
            else if ((std::string)attribut.name() == "Comment"){
                event_input.comment = attribut.as_string();                        
            }
        }
        if ((std::string)node.first_child().name() == "With"){
            countEvent_InputWith_var += 1;
            for (pugi::xml_node node_with : node.children())
                event_input.vars.push_back(node_with.first_attribute().as_string());                        
        }
        eventInputs_attrebutes.push_back(event_input);
    }

    //Получаем атрибуты подузлов узла EventOutput
    pugi::xpath_node_set elements_output = doc.select_nodes("//EventOutputs//Event");          
    for (pugi::xpath_node xpath_node : elements_output) {
        pugi::xml_node node = xpath_node.node();
        EventOutputs event_output; 
        for (pugi::xml_attribute attribut : node.attributes()){
            if ((std::string)attribut.name() == "Name"){
                event_output.name = attribut.as_string();
            }
            else if ((std::string)attribut.name() == "Type"){
                event_output.type = attribut.as_string();                        
            }
            else if ((std::string)attribut.name() == "Comment"){
                event_output.comment = attribut.as_string();                        
            }
        }
        if ((std::string)node.first_child().name() == "With"){
            countEvent_OutputsWith_var += 1;
            for (pugi::xml_node node_with : node.children())
                event_output.vars.push_back(node_with.first_attribute().as_string());                         
        }
        eventOutputs_attrebutes.push_back(event_output);
    }


    //Получаем атрибуты подузлов узла InputVars
    pugi::xpath_node_set elements_vinput = doc.select_nodes("//InputVars//*");          
    for (pugi::xpath_node xpath_node : elements_vinput) {
        pugi::xml_node node = xpath_node.node();
        InputVars vardeclaration_input; 
        for (pugi::xml_attribute attribut : node.attributes()){
            if ((std::string)attribut.name() == "Name"){
                vardeclaration_input.name = attribut.as_string();
            }
            else if ((std::string)attribut.name() == "Type"){
                vardeclaration_input.type = attribut.as_string();                        
            }
            else if ((std::string)attribut.name() == "Comment"){
                vardeclaration_input.comment = attribut.as_string();                        
            }
        }
        inputVars_attrebutes.push_back(vardeclaration_input);
    }


    //Получаем атрибуты подузлов узла OutputVars
    pugi::xpath_node_set elements_voutput = doc.select_nodes("//OutputVars//*");          
    for (pugi::xpath_node xpath_node : elements_voutput) {
        pugi::xml_node node = xpath_node.node();
        OutputVars vardeclaration_output; 
        for (pugi::xml_attribute attribut : node.attributes()){
            if ((std::string)attribut.name() == "Name"){
                vardeclaration_output.name = attribut.as_string();
            }
            else if ((std::string)attribut.name() == "Type"){
                vardeclaration_output.type = attribut.as_string();                        
            }
            else if ((std::string)attribut.name() == "Comment"){
                vardeclaration_output.comment = attribut.as_string();                        
            }
        }
        outputVars_attrebutes.push_back(vardeclaration_output);
    }


}

// кол-во событий на вход
int Parser::get_count_eventInputs(){
    return eventInputs_attrebutes.size();
}

// кол-во событий на выход
int Parser::get_count_eventOutputs(){
    return eventOutputs_attrebutes.size();
}

// кол-во данных на вход
int Parser::get_count_varsInputs(){
    return inputVars_attrebutes.size();
}

// кол-во данных на выход
int Parser::get_count_varsOutputs(){
    return outputVars_attrebutes.size();
}

// получаем ФБ
const std::string Parser::get_name_FB(){
    return name_FB;
}

// кол-во событий на вход, которые связанны с данными
int Parser::get_countEvent_InputWith_var(){
    return countEvent_InputWith_var;
}

// кол-во событий на выход, которые связанны с данными
int Parser::get_countEvent_OutputsWith_var(){
    return countEvent_OutputsWith_var;
}