#include <iostream>
#include <string>

#include "config_parser.h"

int main()
{
    Config config("example1.ini");

    for (const auto& it : config["Example"])
    {
        std::cout << "`" << it.first << "` -> `" << it.second << "`\n";
    }

    return 0;
}
