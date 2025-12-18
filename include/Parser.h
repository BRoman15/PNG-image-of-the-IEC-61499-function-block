#pragma once
#include <vector>
#include <iomanip>
#include <stdexcept>
#include "pugixml.hpp"

struct EventInputs{
    std::string name;
    std::string comment;
    std::string type;
    std::vector<std::string> vars;
};

struct EventOutputs : public EventInputs{};

struct InputVars{
    std::string name;
    std::string comment;
    std::string type;
};

struct OutputVars : public InputVars{};


class Parser{

    std::string xml_file_address;
    int countEvent_InputWith_var = 0;
    int countEvent_OutputsWith_var = 0;
    std::string name_FB;
    std::vector<EventInputs>  eventInputs_attrebutes;
    std::vector<EventOutputs>  eventOutputs_attrebutes;
    std::vector<InputVars> inputVars_attrebutes;
    std::vector<OutputVars> outputVars_attrebutes;

    public:
        Parser(const std::string& xml_file_address_);
        ~Parser() = default;

        std::vector<EventInputs>  get_eventInputs_attrebutes();
        std::vector<EventOutputs>  get_eventOutputs_attrebutes();
        std::vector<InputVars> get_inputVars_attrebutes();
        std::vector<OutputVars> get_outputVars_attrebutes();
        void get_attributes();
        int get_count_eventInputs();
        int get_count_eventOutputs();
        int get_count_varsInputs();
        int get_count_varsOutputs();
        int get_countEvent_InputWith_var();
        int get_countEvent_OutputsWith_var();
        const std::string get_name_FB();
};