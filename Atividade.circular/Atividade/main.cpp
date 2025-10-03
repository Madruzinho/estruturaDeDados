#include <iostream>
#include <unistd.h>

using namespace std;

class lista {
    public:
    string nome;
    int tempo;
    lista* elo;
    lista** inserir(lista**, string n, int t);
    lista** excluir(lista**, string n);
    void listar(lista**);
    lista* pesquisar(lista**, string n);
    lista** executar(lista**);
};

lista** lista::inserir(lista** r, string n, int t) {
    lista *novo = new lista();
    novo->nome = n;
    novo->tempo = t;

    if(r[0] == NULL) {
        r[0] = novo;
        r[1] = novo;
        r[1]->elo = novo; 
    } else {
        lista *ant = NULL, *atual = r[0];
        while(atual != r[1] && novo->nome > atual->nome) {
            ant = atual;
            atual = atual->elo;
        }

        if (atual == r[0] && novo-> nome < atual->nome) {
            novo->elo = r[0];
            r[0] = novo;
            r[1]->elo = r[0];
        } else if (atual == r[1] && novo->nome > atual-> nome) {
            r[1]->elo = novo;
            r[1] = novo;
            r[1]->elo = r[0];
        } else {
            ant->elo = novo;
            novo->elo = atual;
        }
    }
    return r;
};

void lista::listar(lista **r) {
    lista *aux = r[0];

    if(r[0] == NULL) {
        cout << "Não possui processos";
    } else {
    while ( aux != r[1]) {
        cout << aux-> nome << aux-> tempo << endl;
        aux = aux->elo;
    }
    cout << aux->nome << aux->tempo;
    }
};

lista* lista::pesquisar(lista **r, string n) {
    lista *aux = r[0];
    while(aux != r[1] && aux->nome != n) {
        aux = aux->elo;
    } if(aux->nome == n)
        return aux;
        else 
        return NULL;
};

lista** lista::excluir(lista **r, string n) {
    lista *aux = r[0], *ant = NULL;
    while (aux != r[1] && aux->nome != n) {
        ant = aux;
        aux = aux->elo;
    } if (r[0] == r[1]) {
        r[0] = r[1] = NULL;
    } else if (aux == r[0]) {
        r[0] = r[0]-> elo;
        r[1]->elo = r[0];
    } else if (aux == r[1]) {
        r[1] = ant;
        r[1]-> elo = r[0];
    } else {
        ant->elo = aux->elo;
    }
    delete(aux);
    return r;
};

lista** lista::executar(lista **r) {
    unsigned int microsegundo = 1000000;
    lista *aux1 = r[0], *aux2;
    while(aux1 != NULL) {
        if (aux1->tempo > 0) {
            cout << aux1->nome << " " << aux1->tempo << endl;
            usleep(microsegundo);
            aux1->tempo--;
            aux1 = aux1->elo;
        } else {
            aux2 = aux1-> elo;
            r = excluir(r, aux1->nome);
            if(r[0] != NULL) 
                aux1 = aux2;
            else
            aux1 = r[0];
        }
    }
    return r;
};

void menu() {
    cout << "1 - Inserir processos" << endl;
    cout << "2 - Exibir processos" << endl;
    cout << "3 - Executar processos" << endl;
    cout << "4 - Excluir processo" << endl;
    cout << "5 - Finalizar programa" << endl;
}

int main() {
    lista obj, **L, *resp;
    L = new lista*[2];
    L[0] = L[1] = NULL;
    string nome;
    int tempo, op;

    do {
        menu();
        cin >> op;
        switch (op)
        {
        case 1:
            cin >> nome >> tempo;
            L = obj.inserir(L, nome, tempo);
            break;
        
        case 2:
            obj.listar(L);
            break;

        case 3:
            L = obj.executar(L);
            break;
            
        case 4:
            cin >> nome;
            resp = obj.pesquisar(L, nome);
            if(resp != NULL)
             L = obj.excluir(L , nome) ;
            else
              cout << "Não achou";
            break; 
        default:
            cout << "Insira uma opçao valida";
            break;
        }
        cout << endl;
    } while (op != 5);

    return 0;
} 