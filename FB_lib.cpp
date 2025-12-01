#include "FB_lib.h"
#include "pugixml-1.15/src/pugixml.hpp"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;


struct EventInputs{
    string name;
    string comment;
    string type;
    vector<string> vars;

};

struct EventOutputs : public EventInputs{};

struct InputVars{
    string name;
    string comment;
    string type;
};

struct OutputVars : public InputVars{};



class BasicFB{
    const char * xml_file_address;
    vector<EventInputs>  eventInputs_attrebutes;
    vector<EventOutputs>  eventOutputs_attrebutes;
    vector<InputVars> inputVars_attrebutes;
    vector<OutputVars> outputVars_attrebutes;

    string name_FB;

    pugi::xml_document doc;
    public:
        BasicFB(const char * xml_file_address_){
            xml_file_address = xml_file_address_;
            pugi::xml_parse_result result = doc.load_file(xml_file_address);
            if (!result){
                cout << "ERROR: " << result.description();
            }
        }


        void get_main_attributes(){
            //Getting the name of the function block
            pugi::xpath_node_set elements_fb = doc.select_nodes("/FBType");
            for (pugi::xpath_node xpath_node : elements_fb) {
                pugi::xml_node node = xpath_node.node();
                name_FB = node.first_attribute().as_string();
            }
            cout << name_FB;
        }

        void get_eventInputs_attributes(){
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
        }

        void get_eventOutputs_attributes(){
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
        }

        void get_inputVars_attributes(){
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
        }

        void get_outputVars_attributes(){
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
};

class PNG_image{
    
};

int main(){
    BasicFB a("test_data_xml//ADD_2.xml");
    a.get_main_attributes();
}