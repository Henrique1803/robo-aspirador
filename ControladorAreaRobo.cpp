#include <iostream>
#include <string>
#include <vector>
#include "Cenario.cpp"

// Classe utilizada para extrair os cenários do conteúdo do arquivo XML
// e realizar o controle da área a ser limpa pelo robô
class ControladorAreaRobo {

public:

    ControladorAreaRobo(std::string _conteudoXML) {
        conteudoXML = _conteudoXML;
        extrairCenarios();
    }

    std::string getConteudoXML() {
        return conteudoXML;
    }

    std::vector<Cenario> getCenarios() {
        return cenarios;
    }

private:

    void extrairCenarios() {
        // Variável que vai ser utilizada para saber a partir de onde deve-se buscar uma determinada tag 
        size_t posInicio = 0;
        while (true){
            // Salva a posição da primeira ocorrência de "cenario" partir da posição específicada
            size_t posAbertura = conteudoXML.find("<cenario>", posInicio);
            // Salva a posição da primeira ocorrência de fechamento da tag "cenario" a partir da posição específicada
            size_t posFechamento = conteudoXML.find("</cenario>", posAbertura);
            // Escopo de um cenário X é determinado
            // Variável strAuxiliar vai ser utilizada no decorrer do algoritmo para o cálculo
            // da posição que vai ser "cortada" ou "extraída" da string
            std::string strAuxiliar = "<cenario>";
            // Caso não encontre as tags, significa que não há mais ocorrências de chaves e a string terminou
            if (posAbertura == std::string::npos || posFechamento == std::string::npos) {
                break;// Sai do laço principal
            }
            // Passa a posição de abertura para a primeira posição após a tag <cenario> terminar
            posAbertura += strAuxiliar.size();
            // Determina o escopo de um cenário X extraindo a string com base nas posições de abertura e fechamento da tag "cenario"
            // Com base nessa string, que delimita um cenário, outros atributos são extraídos
            std::string cenarioStr = conteudoXML.substr(posAbertura, posFechamento - posAbertura);

            /*--------------------------------------------------- Extrair nome ---------------------------------------------------------*/
            
            strAuxiliar = "<nome>";
            size_t posAberturaExtraido = cenarioStr.find("<nome>", 0);
            size_t posFechamentoExtraido = cenarioStr.find("</nome>", 0);

            std::string nome = cenarioStr.substr(posAberturaExtraido+strAuxiliar.size(), posFechamentoExtraido - (posAberturaExtraido+strAuxiliar.size()));

            /*--------------------------------------------------- Extrair altura ---------------------------------------------------------*/
            
            strAuxiliar = "<altura>";
            posAberturaExtraido = cenarioStr.find("<altura>", 0);
            posFechamentoExtraido = cenarioStr.find("</altura>", 0);

            int altura = std::stoi(cenarioStr.substr(posAberturaExtraido+strAuxiliar.size(), posFechamentoExtraido - (posAberturaExtraido+strAuxiliar.size())));

            /*--------------------------------------------------- Extrair largura ---------------------------------------------------------*/
            
            strAuxiliar = "<largura>";
            posAberturaExtraido = cenarioStr.find("<largura>", 0);
            posFechamentoExtraido = cenarioStr.find("</largura>", 0);

            int largura = std::stoi(cenarioStr.substr(posAberturaExtraido+strAuxiliar.size(), posFechamentoExtraido - (posAberturaExtraido+strAuxiliar.size())));

            /*--------------------------------------------------- Extrair x do robo ---------------------------------------------------------*/
            
            strAuxiliar = "<x>";
            posAberturaExtraido = cenarioStr.find("<x>", 0);
            posFechamentoExtraido = cenarioStr.find("</x>", 0);

            int xRobo = std::stoi(cenarioStr.substr(posAberturaExtraido+strAuxiliar.size(), posFechamentoExtraido - (posAberturaExtraido+strAuxiliar.size())));

            /*--------------------------------------------------- Extrair y do robo ---------------------------------------------------------*/
            
            strAuxiliar = "<y>";
            posAberturaExtraido = cenarioStr.find("<y>", 0);
            posFechamentoExtraido = cenarioStr.find("</y>", 0);

            int yRobo = std::stoi(cenarioStr.substr(posAberturaExtraido+strAuxiliar.size(), posFechamentoExtraido - (posAberturaExtraido+strAuxiliar.size())));

            /*--------------------------------------------------- Extrair matriz ---------------------------------------------------------*/
            
            strAuxiliar = "<matriz>";
            posAberturaExtraido = cenarioStr.find("<matriz>", 0);
            posFechamentoExtraido = cenarioStr.find("</matriz>", 0);

            std::string matrizStr = cenarioStr.substr(posAberturaExtraido+strAuxiliar.size(), posFechamentoExtraido - (posAberturaExtraido+strAuxiliar.size()));

            std::string resultado;
            // Remover espaços em brancos e quebras de linha
            for (char c : matrizStr) {
                if (!std::isspace(c) && !(c == '\n'))
                    resultado += c;
            }

            matrizStr = resultado; // Matriz de  0s e 1s "limpa"

            // Adicionando o novo cenário à lista de cenários
            cenarios.push_back(Cenario(nome, altura, largura, xRobo, yRobo, matrizStr));
            // Na próxima iteração, o conteúdo vai ser pesquisado a partir dessa posição 
            // (posição de fechamento do cenário atual)
            posInicio = posFechamento + 1;
        }
    }

    std::string conteudoXML;
    std::vector<Cenario> cenarios;
};
