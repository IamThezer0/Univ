#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class lista;

class prod_mag
{

private:
    int tip_obj,
        cod_produs;
    string producator;
    prod_mag *next;

public:
    prod_mag(int typee, string prod, int cod)
    {
        tip_obj = typee;
        producator = prod;
        cod_produs = cod;
    }
    virtual void afisare()
    {
        cout << "Producatorul este: " << producator << endl;
        cout << "Codul produsului este: " << cod_produs << endl;
    }
    int getType()
    {
        return tip_obj;
    }
    friend class lista;
};

class scanner : public prod_mag
{
private:
    string soft_inclus;

public:
    scanner(int typee, string prod, int cod, string soft) : prod_mag(typee, prod, cod)
    {
        soft_inclus = soft;
    }
    void afisare()
    {
        prod_mag::afisare();
        cout << "Softul scanner-ului este: " << soft_inclus << endl;
    }
    friend class lista;
};

class imprimanta : public prod_mag
{
private:
    string format;

public:
    imprimanta(int typee, string prod, int cod, string form) : prod_mag(typee, prod, cod)
    {
        format = form;
    }
    void afisare()
    {
        prod_mag::afisare();
        cout << "Formatul paginii este: " << format << endl;
    }
    friend class lista;
};

class lista
{
public:
    prod_mag *prim;
    void adaugare(prod_mag *urm);
    void afisare_lista();
    void introducere(lista &list);
};

void lista::adaugare(prod_mag *a)
{
    prod_mag *p;
    p = prim;
    if (p)
    {
        if (a->producator < p->producator)
        {
            a->next = prim;
            prim = a;
        }
        else
        {
            while (p->next && (p->next)->producator < a->producator)
                p = p->next;
            a->next = p->next;
            p->next = a;
        }
    }
    else
    {
        prim = a;
    }
}
void lista::afisare_lista()
{
    prod_mag *a;
    a = prim;
    int type;
    cout << "\nCe tip? (0-scanner/!0-imprimanta): ";
    cin >> type;
    if (!a)
        cout << "Lista este vida!" << endl;
    else
        while (a)
        {
            if (a->getType() == type)
                a->afisare();
            a = a->next;
        }
}
void introducere(lista &list)
{
    prod_mag *ProdMag;
    string producator,
        soft_inclus,
        format;
    int tip,
        cod_prod;

    cout << "\nIntroduceti producatorul: ";
    cin >> producator;
    cout << "\nintroduceti codul produsului:";
    cin >> cod_prod;
    cout << "\nce tip de produs (0-scanner/!0-imprimanta)";
    cin >> tip;
    if (!tip)
    {
        scanner *sc;
        cout << "Introduceti soft-ul dispozitivului:";
        cin >> soft_inclus;
        sc = new scanner(tip, producator, cod_prod, soft_inclus);
        ProdMag = sc;
    }
    else
    {
        imprimanta *imprim;
        cout << "Dati formatul dorit:";
        cin >> format;
        imprim = new imprimanta(tip, producator, cod_prod, format);
        ProdMag = imprim;
    }
    list.adaugare(ProdMag);
}
int main()
{
    int opt;
    int x;
    lista l;
    l.prim = NULL;
    do
    {
        cout << "\n1. Adagare scanere in lista";
        cout << "\n2. Afisare";
        cout << "\nAlege: ";
        cin >> opt;
        switch (opt)
        {
        case 1:
            introducere(l);
            break;
        case 2:
            l.afisare_lista();
            break;
        case 0:
            break;
        default:
            cout << "\nOpt gres";
            break;
        }

    } while (opt != 0);

    return 0;
}