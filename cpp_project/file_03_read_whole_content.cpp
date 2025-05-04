#include <fstream>
#include <iostream>
#include <sstream> //std::stringstream

using namespace std;

int main() {
    const char *fptr = "C:\\program.txt";
    std::ifstream inFile;
    inFile.open(fptr); //open the input file

    std::stringstream strStream;
    strStream << inFile.rdbuf(); //read the file
    std::string str = strStream.str(); //str holds the content of the file

    std::cout << str << "\n"; //you can do anything with the string!!!
}