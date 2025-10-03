#include <iostream>
#include <stdlib.h>
#include <ctime>

using namespace std;

class lista
{
public:
    int num;
    int qtd;
    lista *elo;
    lista **inserir(lista **, int, int);
    void exibir(lista **);
    lista **excluir(lista **, int);
    lista *pesquisar(lista **, int);
    int pesquisarInserir(lista **, int);
};

lista **lista::inserir(lista **r, int num, int qtd)
{
    lista *novo = new lista();
    novo->num = num;
    novo->qtd = qtd;

    if (r[0] == NULL)
    {
        r[0] = novo;
        r[1] = novo;
        r[1]->elo = novo;
    }
    else
    {
        lista *ant = NULL, *atual = r[0];
        while (atual != r[1] && novo->qtd > atual->qtd)
        {
            ant = atual;
            atual = atual->elo;
        }

        while (atual != r[1] && novo->num < atual->num)
        {
            ant = atual;
            atual = atual->elo;
        }

        if (atual == r[0] && novo->qtd < atual->qtd)
        {
            novo->elo = r[0];
            r[0] = novo;
            r[1]->elo = r[0];
        }
        else if (atual == r[1] && novo->qtd > atual->qtd)
        {
            r[1]->elo = novo;
            r[1] = novo;
            r[1]->elo = r[0];
        }
        else
        {
            ant->elo = novo;
            novo->elo = atual;
        }
    }
    return r;
};

void lista::exibir(lista **r)
{
    lista *aux = r[0];

    if (r[0] == NULL)
    {
        cout << "não possui registros";
    }
    else
    {
        while (aux != r[1])
        {
            cout << aux->num << aux->qtd << endl;
            aux = aux->elo;
        }
        cout << "numero: " << aux->num << "quantidade: " << aux->qtd << endl;
    }
};

lista **lista::excluir(lista **r, int num)
{
    lista *aux = r[0], *ant = NULL;
    while (aux != r[1] && aux->num != num)
    {
        ant = aux;
        aux = aux->elo;
    }
    if (r[0] == r[1])
    {
        r[0] = r[1] = NULL;
    }
    else if (aux == r[0])
    {
        r[0] = r[0]->elo;
        r[1]->elo = r[0];
    }
    else if (aux == r[1])
    {
        r[1] = ant;
        r[1]->elo = r[0];
    }
    else
    {
        ant->elo = aux->elo;
    }
    delete (aux);
    return r;
};

lista *lista::pesquisar(lista **r, int num)
{
    lista *aux = r[0];
    while (aux != r[1] && aux->num != num)
    {
        aux = aux->elo;
    }

    if (aux->num == num)
    {
        return aux;
    }
    else
    {
        return NULL;
    }
};

void menu()
{
    cout << "1 - Inserir Numeros" << endl;
    cout << "2 - Exibir Numeros" << endl;
    cout << "3 - Excluir processo" << endl;
    cout << "4 - Finalizar programa" << endl;
}

int main()
{

    srand(time(NULL));

    lista obj, **L, *resp = NULL;
    L = new lista *[2];
    L[0] = L[1] = NULL;
    int num, qtd, op;

    do
    {
        menu();
        cin >> op;
        switch (op)
        {
        case 1:
            int num;
            do
            {
                num = rand() % 101;

                if (num == 0)
                {
                    break;
                }

                if (L[0] == NULL)
                {
                    L = obj.inserir(L, num, 0);
                    break;
                }
                else
                {

                    resp = obj.pesquisar(L, num);
                    if (resp != NULL)
                    {
                        L = obj.excluir(L, num);
                        L = obj.inserir(L, num, resp->qtd++);
                    }
                    L = obj.inserir(L, num, 0);
                }
            } while (num != 0);

            break;
        case 2:
            obj.exibir(L);
        default:
            break;
        }
    } while (op != 4);

    return 0;
}