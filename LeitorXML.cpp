#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Classe responsável por ler o arquivo XML e passar o conteúdo para uma string
class LeitorXML {

public:

    LeitorXML(std::string _nomeArquivo) {
        nomeArquivo = _nomeArquivo;
        conteudoXML = "";
    }

    void lerArquivo() {
        std::string info; // Variável será usada para armazenar cada linha do arquivo à medida que é lida
        std::ifstream input(nomeArquivo); // Objeto usado para ler o arquivo
        if (input.is_open()) { // Verifica se o arquivo foi aberto com sucesso
            while (!input.eof()) { // Continua no laço enquanto o final do arquivo não for alcançado
                std::getline(input, info); // Lê uma linha do arquivo e salva em info
                conteudoXML += info + "\n"; // Junta as linhas do arquivo (\n é utilizado pra manter as quebras de linhas originais)
            }
        } else {
                std::cerr << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
        }
    }

    std::string getConteudoXML() {
        return conteudoXML;
    }

private:
    std::string nomeArquivo;
    std::string conteudoXML;
};
