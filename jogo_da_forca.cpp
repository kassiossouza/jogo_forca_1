#include <iostream>
#include <string>  
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

string palavra_secreta;

map<char, bool> chutou;
vector<char> chutes_errados;

bool letra_existe(char letra_chutada) {
    for(char letra : palavra_secreta) {
        if(letra_chutada == letra) {
            return true;
        }
    }
    return false;
} //Verifica se a letra existe na palavra secreta.

bool nao_acertou() {
    for(char letra : palavra_secreta) {
        if(!chutou[letra]) {
            return true;
        }
    }
    return false;
} //Verifica se a letra ainda não foi chutada;

bool nao_enforcou() {
    return chutes_errados.size() < 5;

} //Verifica se o usuário já atingiu ou não o limite de tentativas permitidas.

void imprimir_erros() {
    cout << "Chutes errados: ";

    for(char letra : chutes_errados) {
        cout << letra << " ";
    }   
    cout << endl;
} //Função que imprime as letras erradas que o usuário já digitou naquela partida do jogo.

void imprimir_palavra() {
    for(char letra : palavra_secreta) {
        if(chutou[letra]) {
            cout << letra << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;

} //Imprime as letras acertadas até o momento e os espaços que ainda precisam ser preenchidos.

void chutar_letra() {
    cout << "Digite seu chute: ";
    
    char letra_chutada;
    cin >> letra_chutada;

    letra_chutada = toupper(letra_chutada); //Torna todas as letras maiúsculas.

    chutou[letra_chutada] = true;

    //cout << "O seu chute foi o " << letra_chutada << endl;

    if(letra_existe(letra_chutada)) {
        cout << "Acertou o chute!" << endl;
    } else {
        cout << "Errou o chute!" << endl;
        chutes_errados.push_back(letra_chutada); //push_back() adiciona os chutes errados ao final do vetor declarado.
    }

    cout << endl; 

} //Lê e armazena o chute do usuário e retorna se ele acertou ou errou o chute

vector<string> leitura_arquivo_txt() {
    ifstream arquivo_txt;
    arquivo_txt.open("nomes_times.txt");

    if(arquivo_txt.is_open()) {
        int quantidade_palavras;
        arquivo_txt >> quantidade_palavras;

        //cout << "O arquivo possui " << quantidade_palavras << " palavras." << endl;

        vector<string> palavras_arquivo;

        for(int i = 0; i < quantidade_palavras; i++) {
            string palavra_lida;
            arquivo_txt >> palavra_lida;

            //cout << "Na linha " << i << " : " << palavra_lida << endl;
            
            palavras_arquivo.push_back(palavra_lida); //Insere as palavras lidas no vetor que vai servir de base para o sorteio da palavra secreta.
        }
        
        arquivo_txt.close();
        return palavras_arquivo;

    } else {
        cout << "Erro ao acessar o banco de palavras!" << endl;
        cout << "Tente acessar o jogo novamente mais tarde!" << endl;
        exit(0);
    }

} //Função responsável por fazer a leitura do arquivo que contém as palavras secretas utilizadas no jogo.

void sortear_palavra_secreta() {
    vector<string> palavras = leitura_arquivo_txt();

    srand(time(NULL));
    int indice_sorteado = rand() % palavras.size();

    palavra_secreta = palavras[indice_sorteado];

} //Função responsável por sortear uma palavra secreta de forma aleatória.

void salvar_arquivo_txt(vector<string> nova_lista) {
    ofstream arquivo_txt;
    arquivo_txt.open("nomes_times.txt");

    if(arquivo_txt.is_open()) {
        arquivo_txt << nova_lista.size() << endl;

        for(string palavra : nova_lista) {
            arquivo_txt << palavra << endl;
        }
        
        arquivo_txt.close();

    } else {
        cout << "Erro ao acessar o banco de palavras!" << endl;
        cout << "Tente acessar o jogo novamente mais tarde!" << endl;
        exit(0);
    }

} //Função que salva uma nova lista de palavras secretas toda vez que uma nova palavra for adicionada pelo usuário.

void adicionar_nova_palavra() {
    cout << "Digite a nova palavra (usando letras maisculas): " << endl;
    string nova_palavra;
    cin >> nova_palavra;

    vector<string> lista_palavras = leitura_arquivo_txt();
    lista_palavras.push_back(nova_palavra);

    salvar_arquivo_txt(lista_palavras);

} //Função para auxiliar novas palavras pelo usuário ao final do jogo.

int main() {
    cout << "****************************************" << endl;
    cout << "*** Jogo da Forca * Times de Futebol ***" << endl;
    cout << "****************************************" << endl;
    cout << endl;

    leitura_arquivo_txt();
    sortear_palavra_secreta();

    while(nao_acertou() && nao_enforcou()) {
        imprimir_erros();

        imprimir_palavra();

        chutar_letra();   
    }

    cout << "*** FIM DE JOGO ***" << endl;
    cout << "A palavra secreta era: " << palavra_secreta << "." << endl;

    if(nao_acertou()) {
        cout << "GAME OVER!!! Tente novamente!" << endl;
    } else {
        cout << "Parabensss!!! Acertou a palavra secreta <3" << endl;

        cout << "Deseja adicionar uma nova palavra ao banco de dados? (S/N) ";
        char resposta;
        cin >> resposta;

        resposta = toupper(resposta);

        if(resposta == 'S') {
            adicionar_nova_palavra();
        }
    }
} //Para usar o makefile no Windows: mingw32-make forca