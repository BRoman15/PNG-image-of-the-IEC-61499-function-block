#pragma once
#include <vector>
#include <iomanip>
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
    

    public:
        BasicFB(const char * xml_file_address_);
        void get_attributes();
};


BasicFB* create_basic_fb(const char* xml_file_address);
void get_name(BasicFB *a);
