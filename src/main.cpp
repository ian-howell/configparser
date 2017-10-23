#include "config_parser.h"
#include <iostream>

int main()
{
    Config* config = new Config("example1.ini");

    for (const auto& it : config->get_section("Example"))
    {
        std::cout << "`" << it.first << "` -> `" << it.second << "`\n";
    }

    delete config;
}
