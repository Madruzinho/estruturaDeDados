#include "lista.h"

using namespace std;

int main()
{
    Lista **L1, **L2, l;
    L1 = new Lista *[2];
    L1[0] = L1[1] = NULL;
    L2 = new Lista *[2];
    L2[0] = L2[1] = NULL;
    int n;
    srand(time(NULL));
    do
    {
        n = rand() % 100 + 1;
        if (n != 3)
        {
            L1 = l.InserirS(L1, n);
        }
    } while (n != 3);
    cout << " Lista Simplesmente Ordenada: ";
    l.ListarS(L1[0]);
    cout << "\n\n\n";
    L2 = l.Copiar(L2, L1[0]);
    cout << "\n\nLista Duplamente Ordenada: ";
    l.ListarD(L2);

    return 0;
}