#include "C:\VSCod\PNG-image-of-the-IEC-61499-function-block\include\FB_lib.h"
#include "pugixml.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;


BasicFB::BasicFB(const char * xml_file_address_){
    xml_file_address = xml_file_address_;
}

BasicFB::BasicFB(const std::string& xml_file_address_)
    : xml_file_address(xml_file_address_) {
}


void BasicFB::get_attributes(){
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(xml_file_address.c_str());
    if (!result){
        cout << "ERROR: " << result.description();
    }

    //Getting the name of the function block
    pugi::xpath_node_set elements_fb = doc.select_nodes("/FBType");
    for (pugi::xpath_node xpath_node : elements_fb) {
        pugi::xml_node node = xpath_node.node();
        name_FB = node.attribute("Name").as_string();
    }

    //Get the attributes of the subnodes of node EventInputs
    pugi::xpath_node_set elements_input = doc.select_nodes("//EventInputs//Event");           
    for (pugi::xpath_node xpath_node : elements_input) {
        pugi::xml_node node = xpath_node.node();
        EventInputs event_input;
        for (pugi::xml_attribute attribut : node.attributes()){
            if ((string)attribut.name() == "Name"){
                event_input.name = attribut.as_string();
            }
            else if ((string)attribut.name() == "Type"){
                event_input.type = attribut.as_string();                        
            }
            else if ((string)attribut.name() == "Comment"){
                event_input.comment = attribut.as_string();                        
            }
        }
        if ((string)node.first_child().name() == "With"){
            for (pugi::xml_node node_with : node.children())
                event_input.vars.push_back(node_with.first_attribute().as_string());                        
        }
        eventInputs_attrebutes.push_back(event_input);
    }

    //Get the attributes of the subnodes of node EventOutput
    pugi::xpath_node_set elements_output = doc.select_nodes("//EventOutputs//Event");          
    for (pugi::xpath_node xpath_node : elements_output) {
        pugi::xml_node node = xpath_node.node();
        EventOutputs event_output; 
        for (pugi::xml_attribute attribut : node.attributes()){
            if ((string)attribut.name() == "Name"){
                event_output.name = attribut.as_string();
            }
            else if ((string)attribut.name() == "Type"){
                event_output.type = attribut.as_string();                        
            }
            else if ((string)attribut.name() == "Comment"){
                event_output.comment = attribut.as_string();                        
            }
        }
        if ((string)node.first_child().name() == "With"){
            for (pugi::xml_node node_with : node.children())
                event_output.vars.push_back(node_with.first_attribute().as_string());                         
        }
        eventOutputs_attrebutes.push_back(event_output);
    }


    //Get the attributes of the subnodes of node InputVars
    pugi::xpath_node_set elements_vinput = doc.select_nodes("//InputVars//*");          
    for (pugi::xpath_node xpath_node : elements_vinput) {
        pugi::xml_node node = xpath_node.node();
        InputVars vardeclaration_input; 
        for (pugi::xml_attribute attribut : node.attributes()){
            if ((string)attribut.name() == "Name"){
                vardeclaration_input.name = attribut.as_string();
            }
            else if ((string)attribut.name() == "Type"){
                vardeclaration_input.type = attribut.as_string();                        
            }
            else if ((string)attribut.name() == "Comment"){
                vardeclaration_input.comment = attribut.as_string();                        
            }
        }
        inputVars_attrebutes.push_back(vardeclaration_input);
    }


    //Get the attributes of the subnodes of node OutputVars
    pugi::xpath_node_set elements_voutput = doc.select_nodes("//OutputVars//*");          
    for (pugi::xpath_node xpath_node : elements_voutput) {
        pugi::xml_node node = xpath_node.node();
        OutputVars vardeclaration_output; 
        for (pugi::xml_attribute attribut : node.attributes()){
            if ((string)attribut.name() == "Name"){
                vardeclaration_output.name = attribut.as_string();
            }
            else if ((string)attribut.name() == "Type"){
                vardeclaration_output.type = attribut.as_string();                        
            }
            else if ((string)attribut.name() == "Comment"){
                vardeclaration_output.comment = attribut.as_string();                        
            }
        }
        outputVars_attrebutes.push_back(vardeclaration_output);
    }


}

int BasicFB::get_count_event(){
    return eventInputs_attrebutes.size();
}

int BasicFB::get_count_vars(){
    return inputVars_attrebutes.size();
}

const string BasicFB::get_name_FB(){
    return name_FB;
}

int BasicFB::get_countEvent_InputWith_var(){
    int count = 0;
    for(EventInputs a : eventInputs_attrebutes){
        if (a.vars.empty() == false){
            count += 1;
        }
    }
    return count;
}

int BasicFB::get_countEvent_OutputsWith_var(){
    int count = 0;
    for(EventOutputs a : eventOutputs_attrebutes){
        if (a.vars.empty() == false){
            count += 1;
        }
    }
    return count;
}