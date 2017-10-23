#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H
#include <exception>
#include <stdio.h>
#include <string>
#include <map>

const extern int __CONFIG_BUFFER_SIZE;

class Config
{
    public:
        Config(std::string filename);

        std::map<std::string, std::string>
        get_section(std::string section_name);

        void
        dump(FILE* log_file);

    private:
        std::map<std::string, std::map<std::string, std::string> > sections;
};
#endif
