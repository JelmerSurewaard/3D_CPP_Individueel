#pragma once
#include <string>

class io {
public:
    io(void);
    ~io(void);
    std::string readFile();
    void writeFile(std::string text);
};