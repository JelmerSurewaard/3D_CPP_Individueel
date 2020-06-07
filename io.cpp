#include "io.h"
#include <iostream>
#include <fstream>

io::io()
{
}

io::~io()
{
}

std::string io::readFile()
{
    std::string line;
    std::ifstream myfile("score.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            std::cout << line << '\n';
        }
        myfile.close();
    }

    return line;
}

void io::writeFile(std::string text)
{
    std::ofstream myfile;
    myfile.open("score.txt");
    myfile << text;
    myfile.close();
}