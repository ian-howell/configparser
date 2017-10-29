#include <algorithm>
#include <cctype>
#include <fstream>
#include <string>

#include "config_parser.h"

const int __CONFIG_BUFFER_SIZE = 80;

Config::Config(std::string filename)
{
    if (FILE *file = fopen(filename.c_str(), "r"))
    {
        char* buffer = new char[__CONFIG_BUFFER_SIZE];
        char* section_buffer = new char[__CONFIG_BUFFER_SIZE];
        char* config_buffer = new char[__CONFIG_BUFFER_SIZE];
        while (fgets(buffer, __CONFIG_BUFFER_SIZE, file))
        {
            switch(buffer[0])
            {
                // Newlines and comments
                case '\n': case '#': case ';': /* Ignore */ break;
                // Section headers
                case '[':
                    sscanf(buffer, "[%80[^]]]\n", section_buffer);
                    break;
                // Everything else will be configurations
                default:
                    // Horrible pointer black magic
                    sscanf(buffer, "%s\n", config_buffer);
                    char* equal_pos = strchr(config_buffer, '=');
                    *equal_pos = '\0';
                    sections[section_buffer][config_buffer] = (equal_pos+1);
            }
        }

        // Clean up
        delete [] buffer;
        delete [] section_buffer;
        delete [] config_buffer;
        fclose(file);
    }
    else
    {
        char err_msg[__CONFIG_BUFFER_SIZE];
        sprintf(err_msg, "File `%s` does not exist", filename.c_str());
        throw std::invalid_argument(err_msg);
    }
}

std::map<std::string, std::string>
Config::get_section(std::string section_name)
{
    return sections[section_name];
}

void
Config::dump(FILE* log_file)

// trim from start (in place)
void Config::ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
                return !std::isspace(ch);
                }));
}

// trim from end (in place)
void Config::rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
                return !std::isspace(ch);
                }).base(), s.end());
}

// trim from both ends (in place)
void Config::trim(std::string &s)
{
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
std::string Config::ltrim_copy(std::string s)
{
    ltrim(s);
    return s;
}

// trim from end (copying)
std::string Config::rtrim_copy(std::string s)
{
    rtrim(s);
    return s;
}

// trim from both ends (copying)
std::string Config::trim_copy(std::string s)
{
    trim(s);
    return s;
}
