#include <iostream>
#include <unistd.h>

using namespace std;

unsigned int microsecond = 1000000;

class Lista
{
public:
    string nome;
    int tempo;
    Lista *ant, *prox;
    Lista **Inserir(Lista **, string nome, int t);
    Lista **Excluir(Lista **, string nome);
    void Listar(Lista **);
};

Lista** Lista::Inserir(Lista **LD, string n, int t)
{
    Lista *novo = new Lista();
    novo->nome = n;
    novo->tempo = t;
    if (LD[0] == LD[1]) // se é o primeiro
    {
        LD[0] = novo;
        LD[1] = novo;
        LD[0]->ant = LD[1];
        LD[1]->prox = LD[0];
    }
    else
    {
        Lista *aux;
        aux = LD[0];
        while (aux != LD[1] && novo->nome > aux->nome)
            aux = aux->prox;

        if (aux->ant == LD[1] && novo->nome < LD[1]->nome)
        { // checar se é o primeiro, aux-> ant tem q ser LD[1] e o nome tem q < q LD[1]->nome
            novo->prox = LD[0];
            LD[0]->ant = novo;
            LD[0] = novo;
            LD[0]->ant = LD[1];
        }
        else if (aux->prox == LD[0])
        { // ultimo, aux->prox tem q ser LD[0]
            novo->ant = LD[1];
            LD[1]->prox = novo;
            LD[1] = novo;
            LD[1]->prox = LD[1];
        }
        else
        { // meio de alguem
            novo->prox = aux;
            novo->ant = aux->ant;
            aux->ant->prox = novo;
            aux->ant = novo;
        }
        return LD;
    }
};

Lista** Lista::Excluir(Lista **LD, string n)
{
    Lista *aux = LD[0];
    while (aux != LD[1] && aux->nome != n)
        aux = aux->prox;

    if (LD[0] == LD[1])
    { // só tem um na lista
        LD[1] = LD[0] = NULL;
    }

    else if (aux == LD[0] && aux->nome == LD[0]->nome)
    { // se é o primeiro
        LD[0] = LD[0]->prox;
        LD[0]->ant = LD[1];
    }
    else if (aux == LD[1])
    { // se é o ultimo
        LD[1] = LD[1]->ant;
        LD[1]->prox = LD[0];
    }
    else
    { // no meio de dois
        aux->ant->prox = aux->prox;
    }

    delete (aux);
    return LD;
};

void Lista::Listar(Lista **LD)
{
    Lista *aux = LD[0];
    while (aux != LD[1])
    {
        cout << aux->nome << " " << aux->tempo;
        aux = aux->prox;
    }
};

void Menu()
{
    cout << "1. Inserir processos" << endl;
    cout << "2. Exibir processor" << endl;
    cout << "3. Executar processos" << endl;
    cout << "4. Excluir processos" << endl;
    cout << "5. Finalizar programa" << endl;
}

int main()
{
    Lista LD, **L, *resp;
    L = new Lista *[2];
    L[0] = L[1] = NULL;
    string nome;
    int tempo;
    int op;

    do
    {
        Menu();
        cin >> op;
        switch (op)
        {
        case 1:
            cout << "Informe o nome, raça, idade e tipo: ";
            cin >> nome;
            cin >> tempo;

            L = LD.Inserir(L, nome, tempo);
            cout << "Processo inserido" << endl;
            break;
        }
    } while (op != 5);

    return 0;
}
