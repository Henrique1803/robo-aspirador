#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class LeitorXML {
public:
    LeitorXML(std::string _nomeArquivo) {
        nomeArquivo = _nomeArquivo;
        xmlData = "";
    }

    void lerArquivo() {
        std::string info;
        std::ifstream input(nomeArquivo);
        if (input.is_open()) {
            while (!input.eof()) {
                std::getline(input, info);
                xmlData += info + "\n";
            }
        } else {
                std::cerr << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
        }
    }

    std::string getXMLData() {
        return xmlData;
    }

private:
    std::string nomeArquivo;
    std::string xmlData;
};
