#include <iostream>
#include <string>
#include "./array_stack.h"

class VerificadorXML {
public:

    bool verificar(std::string conteudoXML) {

        structures::ArrayStack<std::string> pilhaChaves(1000);
        size_t posInicio = 0;

        while (true){
            size_t posAbertura = conteudoXML.find('<', posInicio);
            size_t posFechamento = conteudoXML.find('>', posAbertura);

            if (posAbertura == std::string::npos || posFechamento == std::string::npos) {
                break;
            }

            std::string chave = conteudoXML.substr(posAbertura + 1, posFechamento - posAbertura - 1);

            if (chave[0] == '/'){ // Se for uma tag de fechamento
                // Retira a barra (/) da chave e vê se a pilha está vazia
                if (pilhaChaves.empty() || pilhaChaves.top() != chave.substr(1)) { 
                    return false;  // Tag de fechamento sem tag correspondente na pilha
                }
                pilhaChaves.pop(); // Remove a tag de abertura correspondente da pilha
            } else {
                if (pilhaChaves.full()) { // Verifica se a pilha não está cheia
                    return false;  // Pilha cheia
                }
                pilhaChaves.push(chave); // Adiciona a tag de abertura à pilha
            }

            posInicio = posFechamento + 1;
        }

        return pilhaChaves.empty(); // Se a pilha estiver vazia, todas as tags foram fechadas corretamente
    }
};
