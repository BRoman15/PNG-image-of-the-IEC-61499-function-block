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

    string xml_file_address;


    public:
        vector<EventInputs>  eventInputs_attrebutes;
        vector<EventOutputs>  eventOutputs_attrebutes;
        vector<InputVars> inputVars_attrebutes;
        vector<OutputVars> outputVars_attrebutes;
        string name_FB;
    
        BasicFB(const char * xml_file_address_);
        BasicFB(const std::string& xml_file_address_);
        void get_attributes();
        int get_count_event();
        int get_count_vars();
        int get_countEvent_InputWith_var();
        int get_countEvent_OutputsWith_var();
        const string get_name_FB();
};