#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class XMLReader {
public:
    XMLReader(std::string _filename) {
        filename = _filename;
        xmlData = "";
        
    }

    void readFile() {
        std::string info;
        std::ifstream input(filename);
        if (input.is_open()) {
            while (!input.eof()) {
                std::getline(input, info);
                xmlData += info + "\n";
            }
        } else {
                std::cerr << "Failed to open file: " << filename << std::endl;
        }
    }

    std::string getXMLData() {
        return xmlData;
    }

private:
    std::string filename;
    std::string xmlData;
};
