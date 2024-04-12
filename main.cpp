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

    // -------------------------------------------- Somente para testes ---------------------------------------------------------------
    // Instancia um ControladorAreaRobo e extrai os cenários do conteúdo do XML
    ControladorAreaRobo controladorAreaRobo = ControladorAreaRobo(leitor.getConteudoXML());
    // Imprime os atributos de cada cenário
    for (Cenario cenario : controladorAreaRobo.getCenarios()) {
        std::cout << cenario.toString() << std::endl;
    }
    // ------------------------------------------ Fim Somente para testes -------------------------------------------------------------




    // ATENÇÂO!!!! ESSE CÓDIGO É UTILIZADO PARA DESALOCAR A MEMÓRIA ALOCADA PELAS MATRIZES DE CADA CENÁRIO
    // É necessário deixá-lo no final do main
    for (Cenario cenario : controladorAreaRobo.getCenarios()) {
        // Liberando a memória alocada para a matriz de cada cenário
        for (int i = 0; i < cenario.getAltura(); ++i) {
            delete[] cenario.getMatriz()[i];
        }
        delete[] cenario.getMatriz();
    }

    return 0;
}
