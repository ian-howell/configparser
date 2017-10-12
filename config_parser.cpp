#include <string.h>

#include "config_parser.h"

Config::Config(string filename)
{
    if (FILE *file = fopen(filename.c_str(), "r"))
    {
        char* buffer = new char[BUFFER_SIZE];
        char* section_buffer = new char[BUFFER_SIZE];
        char* config_buffer = new char[BUFFER_SIZE];
        while (fgets(buffer, BUFFER_SIZE, file))
        {
            switch(buffer[0])
            {
                // Newlines and comments
                case '\n': case '#': /* Ignore */ break;
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
        char err_msg[BUFFER_SIZE];
        sprintf(err_msg, "File `%s` does not exist", filename.c_str());
        throw invalid_argument(err_msg);
    }
}

map<string, string> Config::get_section(string section_name)
{
    return sections[section_name];
}

void Config::dump(FILE* log_file)
{
    // Set up iterators
    std::map<std::string, string>::iterator itr1;
    std::map<string, std::map<std::string, string> >::iterator itr2;
    for(itr2 = sections.begin(); itr2 != sections.end(); itr2++)
    {
        fprintf(log_file, "[%s]\n", itr2->first.c_str());
        for(itr1 = itr2->second.begin(); itr1 != itr2->second.end(); itr1++)
        {
            fprintf(log_file, "%s=%s\n", itr1->first.c_str(), itr1->second.c_str());
        }
    }

}
