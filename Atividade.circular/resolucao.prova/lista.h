#include <iostream>

class Lista
{
public:
public:
    int Num;
    Lista *elo, *ant, *prox;
    Lista** InserirS(Lista**, int);
    void ListarS(Lista*);
    Lista** InserirD(Lista**, int);
    void ListarD(Lista**);
    Lista** Copiar(Lista**, Lista*);
};