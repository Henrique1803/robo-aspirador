#include <iostream>
#include "LeitorXML.cpp"
#include "VerificadorXML.cpp"

using namespace std;

int main() {

    // Caminho e nome do arquivo XML de entrada
    std::string caminhoArquivoXML;
    std::cin >> caminhoArquivoXML; // Entrada

    // Responsável por passar o arquivo XML para uma string
    LeitorXML leitor = LeitorXML(caminhoArquivoXML);
    leitor.lerArquivo(); // Método responsável por ler o arquivo

    // Responsável por verificar se o arquivo XML está com as tags aninhadas corretamente
    VerificadorXML verificador;

    if (!verificador.verificar(leitor.getXMLData())){
        std::cout << "erro" << std::endl;
        return 1;
    }

    std::cout << "tudo correto!!" << std::endl;

    return 0;
}
