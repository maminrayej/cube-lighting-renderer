#include <string>
#include <fstream>
#include <stdexcept>

#include "io.h"

using std::string;

string readContent(const string& filePath) {
    std::ifstream input {filePath};

    if (!input) {
        throw std::runtime_error{"Could not open file: " + filePath};
    }

    string content {};
    while (input) {
        string line {};
        std::getline(input, line);
        content.append(line + "\n");
    }

    return content;
}
