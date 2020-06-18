#include <cstdio>
#include <cstring>
#include <fstream>
#include <json/json.h>
#include "config.h"

/// Print the current build version in a human readable format.
void print_version_string(void) {
    char format[] = "%s %s.%s %s";

    if (VER_BUILD_LONG == 4lu)
        std::strcat(format, " [%s]");

    std::fprintf(stdout, format, LIB_NAME, VER_MAJOR, VER_MINOR, BUILD_STRING, BUILD_DATE);
}

/// The debug build entrypoint function.
/// @param argc The number of arguments passed to the executable file.
/// @param argv The contents of the arguments passed to the executable file.
int main(int argc, char **argv) {
    print_version_string();
    std::fprintf(stdout, "\n");

    Json::Value root;
    std::ifstream json_string("test.json", std::ifstream::binary);
    json_string >> root;

    const Json::Value cd = root["cd"];
    Json::StreamWriterBuilder wbuilder;

    std::fprintf(stdout, Json::writeString(wbuilder, cd[1]).c_str());
    return 0;
}