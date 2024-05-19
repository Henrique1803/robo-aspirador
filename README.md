# 🤖 Robô Aspirador
Este projeto consiste na utilização de estruturas lineares e aplicação de conceitos de pilha e fila para o processamento de arquivos XML contendo matrizes binárias que representam cenários de ação de um robô aspirador.
# Grupo
- Henrique Mateus Teodoro
- Rodrigo Schwartz

# Sobre

Este projeto é o primeiro trabalho da disciplina de Estruturas de Dados do curso de Ciências da Computação na UFSC, semestre 2024.1. O objetivo do trabalho é implementar um programa que simula o funcionamento de um robô aspirador em diferentes cenários descritos em um arquivo `.xml`.

## Descrição

O programa deve:
1. Ler um arquivo `.xml` contendo cenários representados por matrizes binárias de tamanhos variados.
2. Validar o arquivo `.xml`, garantindo que todas as tags estão corretamente aninhadas. Em caso de erro, uma mensagem deve ser exibida.
3. Para cada cenário, o robô aspirador deve varrer as posições que contêm o caractere “1”, a partir de uma posição inicial dada, verificando as quatro direções possíveis (vizinhança-4) para decidir se pode avançar.
4. No final, o programa deve retornar o número de posições contendo o caractere “1” que o robô aspirador varreu em cada cenário.

## Estruturas de Dados Utilizadas

#### Pilha (LIFO - Last In First Out)
- Utilizada para validar o aninhamento das tags do arquivo `.xml`.

#### Fila (FIFO - First In First Out)
- Utilizada no algoritmo de reconstrução de componente conexo para determinar as possíveis direções em que o robô aspirador pode avançar.

# Funcionalidades

- **Leitura e validação do arquivo .xml**: Verifica se todas as tags estão corretamente aninhadas.
- **Simulação do robô aspirador**: Varre as posições contendo "1" a partir de uma posição inicial, usando um algoritmo baseado em fila para determinar as direções possíveis.
- **Contagem de posições varridas**: Retorna o número de posições "1" varridas pelo robô em cada cenário.

# Como utilizar
1. Clone o repositório:
   ```
   git clone https://github.com/Henrique1803/robo-aspirador.git
   ```
2. Navegue até o diretório do projeto:
   ```
   cd robo-aspirador
   ```

3. Compile o código:
   ```
   g++ main.cpp -o program
   ```

4. Execute o programa:
   ```
   ./program
   ```
5. Entrada:<br><p>O programa vai requisitar uma entrada ao usuário, que deve digitar o path do arquivo a ser testado. Por exemplo, para testar a aplicação com o arquivo cenarios4.xml digite o seguinte e aperte enter:</p>
   ```
    resources/cenarios4.xml
   ```
