#include <iostream>

using namespace std;

class fila
{
public:
    string nome_do_cliente;
    int idade;
    char tipo_do_cliente;
    fila *ant, *prox;

    fila* inserir(fila* inicio, string n, int i);
    fila* excluir(fila* inicio, char tipo);
    void exibirFila(fila* inicio);
};


bool verificarPreferencia(int i) {
    if(i >= 60) {
        return true;
    }
    return false; 
}

fila* fila::inserir(fila* inicio, string n, int i) {
    fila* novo = new fila();
    novo->nome_do_cliente = n;
    novo->idade = i;
    novo->tipo_do_cliente = verificarPreferencia(i) ? 'P' : 'C';
    novo->prox = NULL;
    novo->ant = NULL;

    if (inicio == NULL) {
        return novo; // primeira inserção
    }

    // Preferencial → insere no início
    if (novo->tipo_do_cliente == 'P') {
        novo->prox = inicio;
        inicio->ant = novo;
        return novo;
    }

    // Comum → insere no fim
    fila* aux = inicio;
    while (aux->prox != NULL) {
        aux = aux->prox;
    }
    aux->prox = novo;
    novo->ant = aux;

    return inicio;
}

fila* fila::excluir(fila* inicio, char tipo) {
    if (inicio == NULL) {
        cout << "Fila vazia!" << endl;
        return NULL;
    }

    fila* aux;

    if (tipo == 'P') { // remove do início
        aux = inicio;
        inicio = inicio->prox;
        if (inicio != NULL) {
            inicio->ant = NULL;
        }
        delete aux;
        return inicio;
    }

    if (tipo == 'C') { // remove do final
        aux = inicio;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        if (aux->ant != NULL) {
            aux->ant->prox = NULL;
        } else {
            inicio = NULL; // lista ficou vazia
        }
        delete aux;
    }

    return inicio;
}

void fila::exibirFila(fila* inicio) {
    fila* aux = inicio;

    cout << "Fila preferencial:" << endl;
    while (aux != NULL && aux->tipo_do_cliente == 'P') {
        cout << aux->nome_do_cliente << " - " << aux->idade << endl;
        aux = aux->prox;
    }

    cout << "Fila comum:" << endl;
    while (aux != NULL) {
        cout << aux->nome_do_cliente << " - " << aux->idade << endl;
        aux = aux->prox;
    }
}

void Menu() {
    cout << "1. Inserir" << endl;
    cout << "2. Excluir" << endl;
    cout << "3. Listagem geral" << endl;
    cout << "4. Finalizar programa" << endl;
}

int main()
{
    fila O;
    fila* L = NULL;
    string nome;
    int idade, op;
    char tipo;

    L = O.inserir(L, "Lucio", 5);   
    L = O.inserir(L, "Joao Vitor", 15 );    
    L = O.inserir(L, "Jose Eduardo", 80);   
    L = O.inserir(L, "Luana", 61);     

    do {
        Menu();
        cin >> op;

        switch (op) {
        case 1:
            cout << "Informe o nome e idade: ";
            cin >> nome >> idade;
            L = O.inserir(L, nome, idade);
            cout << ((idade >= 60) ? "Inserido na fila preferencial" : "Inserido na fila comum") << endl;
            break;

        case 2:
            cout << "Excluir (P = preferencial, C = comum): ";
            cin >> tipo;
            L = O.excluir(L, tipo);
            break;

        case 3:
            if (L == NULL) cout << "Fila vazia!" << endl;
            else O.exibirFila(L);
            break;

        case 4:
            cout << "Tchau!" << endl;
            break;

        default:
            cout << "Opcao invalida!" << endl;
        }

    } while (op != 4);

    return 0;
}