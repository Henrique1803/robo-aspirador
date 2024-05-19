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
        quantidade_de_1s = 0;
        
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

    // Destrutor que desaloca a memória
    ~Cenario() {
        // Liberando a memória alocada para a matriz
        for (int i = 0; i < altura; ++i) {
            delete[] matriz[i];
        }
        delete[] matriz;
    }

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

    void incrementa_qtd_1s() {
        quantidade_de_1s++;
    }

    int getQuantidadeDe1s() const {
        return quantidade_de_1s;
    }

    // Método toString para retornar os dados do cenário para impressão
    std::string toString() {
        return nome + " " + std::to_string(getQuantidadeDe1s()) + "\n";
    }

private:
    std::string nome;
    int altura;
    int largura;
    int xRobo;
    int yRobo;
    int** matriz;
    int quantidade_de_1s;
};
