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

        std::map<std::string, std::string> get_section(const std::string& section_name);

        std::map<std::string, std::string> operator[](const std::string& section_name);

        void dump(FILE* log_file);

    private:
        std::map<std::string, std::map<std::string, std::string> > sections;

        std::string read_header(const std::string& line);

        void read_configuration(const std::string& line, const std::string& header);

        // trim from start (in place)
        void ltrim(std::string &s);

        // trim from end (in place)
        void rtrim(std::string &s);

        // trim from both ends (in place)
        void trim(std::string &s);

        // trim from start (copying)
        std::string ltrim_copy(std::string s);

        // trim from end (copying)
        std::string rtrim_copy(std::string s);

        // trim from both ends (copying)
        std::string trim_copy(std::string s);
};
#endif
