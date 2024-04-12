#include <iostream>
#include <string>
#include "./array_stack.h"

// Classe utilizada para verificar a validade do conteúdo XML (se todas as tags estão aninhadas corretamente)
class VerificadorXML {
    
public:

    bool verificar(std::string conteudoXML) {
        // Pilha que vai ser utilizada para a verificação
        structures::ArrayStack<std::string> pilhaChaves(1000); // Definida como padrão uma pilha de tamanho 1000
        // Variável que vai ser utilizada para saber a partir de onde deve-se buscar uma determinada tag 
        size_t posInicio = 0;
        // Laço principal do algoritmo
        while (true){
            // Salva a posição da primeira ocorrência de abertura de tag a partir da posição específicada
            size_t posAbertura = conteudoXML.find('<', posInicio); 
            // Salva a posição da primeira ocorrência de fechamento de marcação de abertura
            size_t posFechamento = conteudoXML.find('>', posAbertura);
            // Caso não encontre as tags, significa que não há mais ocorrências de chaves e a string terminou
            if (posAbertura == std::string::npos || posFechamento == std::string::npos) {
                break; // Sai do laço principal
            }
            // Extrai o conteúdo da string entre as posições de abertura e fechamento de tag
            std::string chave = conteudoXML.substr(posAbertura + 1, posFechamento - posAbertura - 1);
            // Se for uma tag de fechamento a string possui uma barra na posição 0
            if (chave[0] == '/'){
                // Verifica se a pilha está vazia e se o conteúdo das chaves são iguais
                if (pilhaChaves.empty() || pilhaChaves.top() != chave.substr(1)) { // Retira a barra (/) da chave para a comparação
                    return false;  // Tag de fechamento sem tag correspondente na pilha
                }
                pilhaChaves.pop(); // Remove a tag de abertura correspondente da pilha
            } else {
                if (pilhaChaves.full()) { // Verifica se a pilha não está cheia
                    return false;  // Pilha cheia
                }
                pilhaChaves.push(chave); // Adiciona a tag de abertura à pilha
            }
            // Na próxima iteração, o conteúdo vai ser pesquisado a partir dessa posição 
            // (posição de fechamento da tag atual)
            posInicio = posFechamento + 1; 
        }
        // Se a pilha estiver vazia, todas as tags foram fechadas corretamente
        return pilhaChaves.empty();
    }
};
