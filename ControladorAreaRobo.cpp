#include <iostream>
#include <string>
#include <vector>
#include "Cenario.cpp"
#include "array_queue.h"
#include "Coordenada.cpp"

// Classe utilizada para extrair os cenários do conteúdo do arquivo XML
// e realizar o controle da área a ser limpa pelo robô
class ControladorAreaRobo {

public:

    ControladorAreaRobo(std::string _conteudoXML) {
        conteudoXML = _conteudoXML;
        extrairCenarios();
        areaDoEspaco();
    }

    std::string getConteudoXML() {
        return conteudoXML;
    }

    std::vector<Cenario*> getCenarios() {
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
            
            Cenario* cenario = new Cenario(nome, altura, largura, xRobo, yRobo, matrizStr);
            // Adicionando o novo cenário à lista de cenários
            cenarios.push_back(cenario);
            // Na próxima iteração, o conteúdo vai ser pesquisado a partir dessa posição 
            // (posição de fechamento do cenário atual)
            posInicio = posFechamento + 1;
        }
    }

    int** createAuxMatrix(Cenario* _cenario) {
        // Alocando dinamicamente a matriz auxiliar 
        int** matriz = new int*[_cenario->getAltura()];
        for (int i = 0; i < _cenario->getAltura(); ++i) {
            matriz[i] = new int[_cenario->getLargura()];
        }

        // Preenchendo a matriz auxiliar com 0
        for (int i = 0; i < _cenario->getAltura(); ++i) {
            for (int j = 0; j < _cenario->getLargura(); ++j) {
                matriz[i][j] = 0; // Convertendo de caractere para inteiro
            }
        }

        return matriz;
    }

    void areaDoEspaco() {
        // Calcula o número de cenários que estão dentro do vetor cenarios
        int quantidade_cenarios = getCenarios().size();
        // Percorre cada cenário para calcular a quantidade de 1's de cada um deles
        for (int i = 0; i < quantidade_cenarios; i++) {
            Cenario* cenario = getCenarios()[i];
            int** matriz_auxiliar = createAuxMatrix(cenario);

            // Pega a posição inicial do robô e a matriz de cada cenário
            int** matriz_cenario  = cenario->getMatriz();
            int xRobo = cenario->getXRobo();
            int yRobo = cenario->getYRobo();

            // Cria a fila que será utilizada para o algoritmo de verificação de quais elementos são 1 na matriz de cada cenário
            std::size_t altura = static_cast<std::size_t>(cenario->getAltura());
            std::size_t largura = static_cast<std::size_t>(cenario->getLargura());
            structures::ArrayQueue<Coordenada> fila(altura * largura);

            // Adiciona o ponto inicial do robô na fila, e na matriz_auxiliar seta essa posição inicial para 1
            Coordenada coordenada = Coordenada(xRobo, yRobo);

            if (matriz_cenario[coordenada.getX()][coordenada.getY()] == 1) {
                fila.enqueue(coordenada);
                matriz_auxiliar[coordenada.getX()][coordenada.getY()] = 1;
            }

            while(!fila.empty()) {
                Coordenada posicao = fila.dequeue();
                cenario->incrementa_qtd_1s();

                
                if (posicao.getX() - 1 >= 0 && posicao.getX() - 1 < cenario->getAltura()) {
                    Coordenada posicao1 = Coordenada(posicao.getX() - 1, posicao.getY());
                    if (matriz_cenario[posicao1.getX()][posicao1.getY()] == 1 && matriz_auxiliar[posicao1.getX()][posicao1.getY()] == 0) {
                        fila.enqueue(posicao1);
                        matriz_auxiliar[posicao1.getX()][posicao1.getY()] = 1;
                    }
                }

                if (posicao.getX() + 1 >= 0 && posicao.getX() + 1 < cenario->getAltura()) {
                    Coordenada posicao1 = Coordenada(posicao.getX() + 1, posicao.getY());
                    if (matriz_cenario[posicao1.getX()][posicao1.getY()] == 1 && matriz_auxiliar[posicao1.getX()][posicao1.getY()] == 0) {
                        fila.enqueue(posicao1);
                        matriz_auxiliar[posicao1.getX()][posicao1.getY()] = 1;
                    }
                }

                if (posicao.getY() - 1 >= 0 && posicao.getY() - 1 < cenario->getLargura()) {
                    Coordenada posicao1 = Coordenada(posicao.getX(), posicao.getY() - 1);
                    if (matriz_cenario[posicao1.getX()][posicao1.getY()] == 1 && matriz_auxiliar[posicao1.getX()][posicao1.getY()] == 0) {
                        fila.enqueue(posicao1);
                        matriz_auxiliar[posicao1.getX()][posicao1.getY()] = 1;
                    }
                }

                if (posicao.getY() + 1 >= 0 && posicao.getY() + 1 < cenario->getLargura()) {
                    Coordenada posicao1 = Coordenada(posicao.getX(), posicao.getY() + 1);
                    if (matriz_cenario[posicao1.getX()][posicao1.getY()] == 1 && matriz_auxiliar[posicao1.getX()][posicao1.getY()] == 0) {
                        fila.enqueue(posicao1);
                        matriz_auxiliar[posicao1.getX()][posicao1.getY()] = 1;
                    }
                }
            }

            for (int i = 0; i < cenario->getAltura(); ++i) {
                delete[] matriz_auxiliar[i];
            }
            delete[] matriz_auxiliar;
        }        
    }

    std::string conteudoXML;
    std::vector<Cenario*> cenarios;
};