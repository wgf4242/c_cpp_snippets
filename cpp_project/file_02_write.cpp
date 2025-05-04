#include <iostream>
#include <fstream>

using namespace std;

int main() {
    // Create and open a text file
    ofstream MyFile("C:\\program.txt");

    // Write to the file
    MyFile << "Files can be tricky, but it is fun enough!\n";
    MyFile << "Line2";

    // Close the file
    MyFile.close();
}
