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


class Parser{

    string xml_file_address;
    int countEvent_InputWith_var = 0;
    int countEvent_OutputsWith_var = 0;

    public:
        vector<EventInputs>  eventInputs_attrebutes;
        vector<EventOutputs>  eventOutputs_attrebutes;
        vector<InputVars> inputVars_attrebutes;
        vector<OutputVars> outputVars_attrebutes;
        string name_FB;
    
        Parser(const char * xml_file_address_);
        Parser(const std::string& xml_file_address_);
        void get_attributes();
        int get_count_eventInputs();
        int get_count_eventOutputs();
        int get_count_varsInputs();
        int get_count_varsOutputs();
        int get_countEvent_InputWith_var();
        int get_countEvent_OutputsWith_var();
        const string get_name_FB();
};