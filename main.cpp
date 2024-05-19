#include <iostream>
#include "LeitorXML.cpp"
#include "VerificadorXML.cpp"
#include "ControladorAreaRobo.cpp"

// Alunos:
// Henrique Mateus Teodoro
// Rodrigo Schwartz

int main() {

    // Caminho e nome do arquivo XML de entrada
    char xmlfilename[100];

    std::cin >> xmlfilename;  // entrada
    
    // Responsável por passar o arquivo XML para uma string
    LeitorXML leitor = LeitorXML(xmlfilename);
    leitor.lerArquivo(); // Método responsável por ler o arquivo

    // Responsável por verificar se o arquivo XML está com as tags aninhadas corretamente
    VerificadorXML verificador;

    // Caso o aninhamento de tags esteja incorreto, imprime a mensagem "erro"
    if (!verificador.verificar(leitor.getConteudoXML())){
        std::cout << "erro" << std::endl;
        return 1;
    }

    // Instancia um ControladorAreaRobo que extrai os cenários do conteúdo do XML
    // e conta a quantidade de 1s de cada cenário
    ControladorAreaRobo controladorAreaRobo = ControladorAreaRobo(leitor.getConteudoXML());
    // Imprime as informações de cada cenário
    for (Cenario* cenario : controladorAreaRobo.getCenarios()) {
        std::cout << cenario->toString();
    }

    return 0;
}
