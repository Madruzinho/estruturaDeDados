#include "lista.h"

Lista** Lista::InserirS(Lista **LS, int N)
{
    Lista *novo = new Lista();
    novo->Num = N;
    if (LS[0] == NULL)
    {
        LS[0] = novo;
        LS[1] = novo;
        LS[1]->elo = NULL;
    }
    else
    {
        Lista *ant = NULL, *atual = LS[0];
        while (atual != NULL && novo->Num > atual->Num)
        {
            ant = atual;
            atual = atual->elo;
        }
        if (ant == NULL)
        {
            novo->elo = LS[0];
            LS[0] = novo;
        }
        else if (atual == NULL)
        {
            LS[1]->elo = novo;
            LS[1] = novo;
            LS[1]->elo = NULL;
        }
        else
        {
            ant->elo = novo;
            novo->elo = atual;
        }
    }
    return LS;
};

void Lista::ListarS(Lista *I)
{
    Lista *aux = I;
    while (aux != NULL)
    {
        std ::cout << aux->Num << " ";
        aux = aux->elo;
    }
};
Lista **Lista::InserirD(Lista **LD, int n)
{
    Lista *novo = new Lista();
    novo->Num = n;
    if (LD[0] == NULL)
    {
        LD[0] = novo;
        LD[1] = novo;
        LD[0]->ant = NULL;
        LD[1]->prox = NULL;
    }
    else
    {
        Lista *aux;
        if (n % 2 == 0)
        {
            aux = LD[0];
            while (aux != NULL && novo->Num > aux->Num && aux->Num % 2 == 0)
                aux = aux->prox;
        }
        else
        {
            aux = LD[1];
            while (aux != NULL && novo->Num > aux->Num && aux->Num % 2 != 0)
                aux = aux->ant;
        }
        if (((aux == NULL) && (novo->Num % 2 != 0)) ||
            ((aux == LD[0]) && (novo->Num % 2 == 0)))
        {
            novo->prox = LD[0];
            LD[0]->ant = novo;
            LD[0] = novo;
            LD[0]->ant = NULL;
        }
        else if (((aux == NULL) && (novo->Num % 2 == 0)) ||
                 ((aux == LD[1]) && (novo->Num % 2 != 0)))
        {
            LD[1]->prox = novo;
            novo->ant = LD[1];
            LD[1] = novo;
            LD[1]->prox = NULL;
        }
        else if (novo->Num % 2 == 0)
        {
            novo->prox = aux;
            novo->ant = aux->ant;
            aux->ant->prox = novo;
            aux->ant = novo;
        }
        else
        {
            novo->ant = aux;
            novo->prox = aux->prox;
            aux->prox->ant = novo;
            aux->prox = novo;
        }
    }
    return LD;
};

void Lista::ListarD(Lista **LD)
{
    Lista *aux = LD[0];
    while (aux != NULL && aux->Num % 2 == 0)
    {
        std ::cout << aux->Num << " ";
        aux = aux->prox;
    }
    aux = LD[1];
    while (aux != NULL && aux->Num % 2 != 0)
    {
        std ::cout << aux->Num << " ";
        aux = aux->ant;
    }
};

Lista** Lista::Copiar(Lista **LD, Lista *I)
{
    Lista *auxS = I;
    while (auxS != NULL)
    {
        LD = InserirD(LD, auxS->Num);
        auxS = auxS->elo;
    }
    return LD;
};
