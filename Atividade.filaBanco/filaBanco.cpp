#include <iostream>

using namespace std;

class fila
{
public:
    string nome_do_cliente;
    int idade;
    char tipo_do_cliente;
    fila *ant, *prox;
    fila **inserir(fila **, string, int);
    fila **excluir(fila **, char);
    void exibirFila(fila **);
};

bool verificarPreferencia(int i) {
    if(i >= 60) {
        return true;
    }
    return false; 
}

fila **fila::inserir(fila **p, string n, int i)
{
    fila *novo = new fila();
    novo->nome_do_cliente = n;
    novo->idade = i;
    if(verificarPreferencia(i)) novo->tipo_do_cliente = 'P';
    else novo->tipo_do_cliente = 'C';
    novo->prox = NULL;
    novo->ant = NULL;

    if (p[0] == NULL)
    {
        p[0] = novo;
        p[1] = novo;
        return p;
    }

    fila *aux;
    if (novo->tipo_do_cliente == 'P')
    {
        aux = p[0];
        while ((aux != NULL) && (aux->tipo_do_cliente == 'P'))
            aux = aux->prox;
    }
    else 
    {
        aux = p[1];
        while ((aux != NULL) && (aux->tipo_do_cliente == 'C'))
            aux = aux->ant;
    }

    if (aux == NULL && novo->tipo_do_cliente == 'P')
    {
        p[1]->prox = novo;
        novo->ant = p[1];
        p[1] = novo;
    }
    else if (aux == NULL && novo->tipo_do_cliente == 'C')
    {
        novo->prox = p[0];
        p[0]->ant = novo;
        p[0] = novo;
    }
    else if (novo->tipo_do_cliente == 'P')
    {
        novo->prox = aux;
        novo->ant = aux->ant;
        if (aux->ant != NULL) {
            aux->ant->prox = novo;
        }
        else {
            p[0] = novo;
        }
        aux->ant = novo;
    }
    else
    {
        novo->prox = aux->prox;
        novo->ant = aux;

        if (aux->prox != NULL)
            aux->prox->ant = novo;
        else
            p[1] = novo;

        aux->prox = novo;
    }

    return p;
}

fila **fila::excluir(fila **p, char t)
{
    fila *aux;
    if (aux == p[0])
    {
        p[0] = p[0]->prox;
        p[0]->ant = NULL;
    }
    else
    {
        p[1] = p[1]->ant;
        p[1]->prox = NULL;
    }
        delete (aux);
        return p;
    }

void fila::exibirFila(fila **p)
{
    fila *aux;
    
    cout << "Fila preferencial: " << endl;
        aux = p[0];
        while ((aux != NULL) && (aux->tipo_do_cliente == 'P'))
        {
            cout << aux->nome_do_cliente << "-" << aux->idade << endl;
            aux = aux->prox;
        }
    
    cout << "Fila comum: " << endl;
        aux = p[1];
        while (aux != NULL)
        {
            cout << aux->nome_do_cliente << "-" << aux->idade << endl;
            aux = aux->prox;
        }
    };

void Menu() {
    cout << "1. Inserir" << endl;
    cout << "2. Excluir" << endl;
    cout << "3. Listagem geral" << endl;
    cout << "4. Finalizar programa" << endl;
}

int main()
{
    fila O, **L, *resp;
    L = new fila*[2];
    L[0] = L[1] = NULL;
    string nome_do_cliente;
    int idade, op;

    L = O.inserir(L, "Lucio", 5);   
    L = O.inserir(L, "Joao Vitor", 15 );    
    L = O.inserir(L, "Jose Eduardo", 80);   
    L = O.inserir(L, "Luana", 61);     

    do
    {
        Menu();
        cin >> op;
        switch (op)
        {
        case 1:
            cout << "Informe o nome e idade: ";
            cin >> nome_do_cliente;
            cin >> idade;

            L = O.inserir(L, nome_do_cliente, idade);
                if(idade >= 60)
                cout << "cliente inserido na fila preferencial" << endl;
                else {
                    cout << "Cliente inserido na fila comum" << endl;
                }
            break;

        case 3: // listagem geraL
            if (L[0] == NULL)
            {
                cout << "Sem registros!" << endl;
            }
            else
            {
                cout << "Listagem: " << endl;
                O.exibirFila(L);
            }
            break;

        case 4:
            cout << "TCHAUU";

        default:
            cout << "Opcao invalida" << endl;
            break;
        }
        cin.ignore().get();
    } while (op != 7);

    return 0;
}