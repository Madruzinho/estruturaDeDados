#include <iostream>

using namespace std;

class pet
{
public:
    string nome, raca;
    int tipo, idade;
    pet *ant, *prox;
    pet **inserir(pet **, string, string, int, int);
    pet **excluir(pet **, string, int);
    void listar(pet **, int);
    bool pesquisar(pet **, string, int);
};

pet **pet::inserir(pet **p, string n, string r, int i, int t)
{
    pet *novo = new pet();
    novo->nome = n;
    novo->raca = r;
    novo->tipo = t;
    novo->idade = i;
    novo->prox = NULL;
    novo->ant = NULL;

    if (p[0] == NULL)
    {
        p[0] = novo;
        p[1] = novo;
        return p;
    }

    pet *aux;
    if (novo->tipo == 1)
    {
        aux = p[0];
        while ((aux != NULL) && (novo->nome > aux->nome) && (aux->tipo == 1))
            aux = aux->prox;
    }
    else 
    {
        aux = p[1];
        while ((aux != NULL) && (novo->nome > aux->nome) && (aux->tipo == 2))
            aux = aux->ant;
    }

    if (aux == NULL && novo->tipo == 1)
    {
        p[1]->prox = novo;
        novo->ant = p[1];
        p[1] = novo;
    }
    else if (aux == NULL && novo->tipo == 2)
    {
        novo->prox = p[0];
        p[0]->ant = novo;
        p[0] = novo;
    }
    else if (novo->tipo == 1)
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

pet **pet::excluir(pet **p, string n, int t)
{
    pet *aux;
    if (t == 1)
    {
        aux = p[0];
        while (aux->nome != n)
        {
            aux = aux->prox;
        }
    }
    else
    {
        aux = p[1];
        while (aux->nome != n)
        {
            aux = aux->ant;
        }
    }
    if (aux == p[0])
    {
        p[0] = p[0]->prox;
        p[0]->ant = NULL;
    }
    else if (aux == p[1])
    {
        p[1] = p[1]->ant;
        p[1]->prox = NULL;
    }
    else
    {
        aux->ant->prox = aux->prox;
        aux->prox->ant = aux->ant;
        delete (aux);
    };
    return p;
}

void pet::listar(pet **p, int op)
{
    pet *aux;
    if (op == 0)
    {
        aux = p[0];
        while (aux != NULL)
        {
            cout << aux->nome << endl;
            aux = aux->prox;
        }
    }
    else if (op == 1)
    {
        aux = p[0];
        while (aux != NULL && aux->tipo == 1)
        {
            cout << aux->nome << endl;
            aux = aux->prox;
        }
    }
    else
    {
        aux = p[1];
        while (aux != NULL && aux->tipo == 2)
        {
            cout << aux->nome << endl;
            aux = aux->ant;
        }
    }
}

bool pet::pesquisar(pet **p, string n, int t)
{
    pet *aux;
    if (t == 1)
    {
        aux = p[0];
        while (aux != NULL && aux->nome != n && aux->tipo == 1)
        {
            aux = aux->prox;
        }
    }
    else
    {
        aux = p[1];
        while (aux != NULL & aux->nome != n && aux->tipo == 2)
        {
            aux = aux->ant;
        }
    }
    if ((aux == NULL) || (aux != NULL && aux->tipo != t))
    {
        return false;
    }
    return true;
}

void Menu() {
    cout << "1. Cadastrar pet" << endl;
    cout << "2. Excluir" << endl;
    cout << "3. Listagem geral" << endl;
    cout << "4. Listagem de caes" << endl;
    cout << "5. Listagem de gatos" << endl;
    cout << "6. Pesquisar" << endl;
    cout << "7. Finalizar programa" << endl;
}

int main()
{
    pet O, **L, *resp;
    L = new pet*[2];
    L[0] = L[1] = NULL;
    string nome, raca;
    int idade, tipo;
    int op;

    L = O.inserir(L, "Rex", "ViraLata", 3, 1);   // Cachorro
    L = O.inserir(L, "Bolt", "Pastor", 5, 1);    // Cachorro
    L = O.inserir(L, "Mimi", "Siamês", 2, 2);    // Gato
    L = O.inserir(L, "Luna", "Persa", 4, 2);     // Gato

    do
    {
        Menu();
        cin >> op;
        switch (op)
        {
        case 1:
            cout << "Informe o nome, raça, idade e tipo: ";
            cin >> nome;
            cin >> raca;
            cin >> idade; 
            cin >> tipo;

            L = O.inserir(L, nome, raca, idade, tipo);
                cout << "Nome inserido" << endl;
            break;

        case 2:
            if (L[0] == NULL)
            {
                cout << "Sem registros!" << endl;
            }
            else
            {
                cout << "Informe o nome e o tipo: ";
                cin >> nome;
                cin >> tipo;
                if (O.pesquisar(L, nome, tipo))
                {
                     L = O.excluir(L, nome, tipo);
                    cout << "Cadastro de pet excluido!" << endl;
                }
                else
                {
                    cout << "Nao existe!" << endl;
                }
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
                O.listar(L, 0); // 0 = todos, 1 = cachorro, 2 = gato
            }
            break;

        case 4: // listagem cachorro
            if (L[0] == NULL)
            {
                cout << "Sem registros!" << endl;
            }
            else
            {
                cout << "Listagem: " << endl;
                O.listar(L, 1); // 0 = todos, 1 = cachorro, 2 = gato
            }
            break;

        case 5: // listagem gatos
            if (L[0] == NULL)
            {
                cout << "Sem registros!" << endl;
            }
            else
            {
                cout << "Listagem: " << endl;
                O.listar(L, 2); // 0 = todos, 1 = cachorro, 2 = gato
            }
            break;

        case 6:
            if (L[0] == NULL)
            {
                cout << "Sem registros!" << endl;
            }
            else
            {
                cout << "Informe o nome e o tipo: ";
                cin >> nome;
                cin >> tipo;
                if (O.pesquisar(L, nome, tipo))
                {
                     L = O.excluir(L, nome, tipo);
                    cout << "Pet esta cadastrado!" << endl;
                }
                else
                {
                    cout << "Pet ainda nao cadastrado!" << endl;
                }
            }
            break;

        case 7:
            cout << "TCHAUU";
            break;

        default:
            cout << "Opcao invalida" << endl;
            break;
        }
        cin.ignore().get();
    } while (op != 7);

    return 0;
}