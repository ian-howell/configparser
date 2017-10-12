#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H
#include <exception>
#include <stdio.h>
#include <string>
#include <map>

#include "aux.h"

using std::invalid_argument;
using std::map;
using std::string;

class Config
{
    public:
        Config(string filename);
        map<string, string> get_section(string section_name);
        void dump(FILE* log_file);

    private:
        map<string, map<string, string> > sections;
};
#endif
