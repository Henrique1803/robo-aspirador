#include <iostream>
#include <string>

// Classe utilizada para armazenar os atributos extraídos de cada cenário do XML
class Cenario {

public:

    Cenario(std::string _nome, int _altura, int _largura, int _xRobo, int _yRobo, std::string conteudoMatriz) {
        nome = _nome;
        altura = _altura;
        largura = _largura;
        xRobo = _xRobo;
        yRobo = _yRobo;

        // Alocando dinamicamente a matriz
        matriz = new int*[_altura];
        for (int i = 0; i < _altura; ++i) {
            matriz[i] = new int[_largura];
        }

        // Preenchendo a matriz com conteúdo inicial, presente na string conteudoMatriz
        int index = 0;
        for (int i = 0; i < _altura; ++i) {
            for (int j = 0; j < _largura; ++j) {
                matriz[i][j] = conteudoMatriz[index++] - '0'; // Convertendo de caractere para inteiro
            }
        }
    }

    /*// Destrutor (está aqui somente para utilizar como algoritmo base para desalocar a memória no main)
    // Esse código deve ser removido após ter feito o algoritmo necessário no main
    ~Cenario() {
        // Liberando a memória alocada para a matriz
        std::cout << "destrutor chamado\n";
        for (int i = 0; i < altura; ++i) {
            delete[] matriz[i];
        }
        delete[] matriz;
    }*/

    std::string getNome() const {
        return nome;
    }

    int getAltura() const {
        return altura;
    }

    int getLargura() const {
        return largura;
    }

    int getXRobo() const {
        return xRobo;
    }

    int getYRobo() const {
        return yRobo;
    }

    int** getMatriz() const {
        return matriz;
    }

    // Método toString para imprimir todos os dados do cenário, caso seja necessário
    std::string toString() {
        std::string result = "Nome: " + nome + "\n";
        result += "Altura: " + std::to_string(altura) + "\n";
        result += "Largura: " + std::to_string(largura) + "\n";
        result += "Posição do Robô (x, y): (" + std::to_string(xRobo) + ", " + std::to_string(yRobo) + ")\n";
        result += "Matriz:\n";
        for (int i = 0; i < altura; ++i) {
            for (int j = 0; j < largura; ++j) {
                result += std::to_string(matriz[i][j]) + " ";
            }
            result += "\n";
        }
        return result;
    }

private:
    std::string nome;
    int altura;
    int largura;
    int xRobo;
    int yRobo;
    int** matriz;
};
