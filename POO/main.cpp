#define _CRT_SECURE_NO_WARNINGS
#include <iostream>	
#include <string>
#include <string.h>

using namespace std;

class lista;

class prod_mag {

private:
	int tip_obj;
	string producator;
	int cod_produs;
	prod_mag* next;
public:
	prod_mag(int typee, string prod, int cod)
	{
		tip_obj = typee;
		producator = prod;
		cod_produs = cod;
		next = NULL;
	}
	virtual void afisare() {

		cout << "Producatorul este: " << producator << endl;
		cout << "Codul produsului este: " << cod_produs << endl;
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
	void afisare() {

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
	imprimanta(int typee, string prod, int cod, string form) : prod_mag(typee, prod, cod) {
		format = form;
	}
	void afisare() {
		prod_mag::afisare();
		cout << "Formatul paginii este: " << format << endl;
	}
	friend class lista;
};

class lista
{
public:
	prod_mag* prim;
	void adaugare(prod_mag* urm);
	void afisare_lista();
};

void lista::adaugare(prod_mag* a) {
	prod_mag* p;
	p = prim;
	if (p) {
		if (a->producator > p->producator)
		{
			a->next = prim;
			prim = a;
		}
		else
		{
			while (p->next && (p->next)->producator > a->producator)
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
void lista::afisare_lista() {

	prod_mag* a;

	if (!a) {
		cout << "Lista este vida!" << endl;
	}
	else {
		while (a)
		{
			a->afisare();
			a = a->next;
		}
	}
}
void introducere(lista* l, int x)
{
	int tip_obj;
	string producator;
	int cod_prod;
	string soft_inclus;
	string format;
	prod_mag* ProdMag;

	cout << "Introduceti producatorul: " << endl;
	cin >> producator;
	cout << "introduceti codul produsului:" << endl;
	cin >> cod_prod;

	if (x == 0)
	{
		scanner* sc;
		cout << "Introduceti soft-ul dispozitivului:";
		cin >> soft_inclus;
		sc = new scanner(1, producator, cod_prod, soft_inclus);
		ProdMag = sc;
		l->adaugare(ProdMag);
	}
	else if (x == 1) {
		imprimanta* imprim;
		cout << "Dati formatul dorit:";
		cin >> format;
		imprim = new imprimanta(2, producator, cod_prod, format);
		ProdMag = imprim;
		l->adaugare(ProdMag);
	}
}
int main() {
	int opt;
	int x;
	lista* l;
	l->prim = NULL;
	do {
		cout << "1. Adagare scanere in lista" << endl;
		cout << "2. Adagare imrprim in lista" << endl;
		cout << "3. afisare" << endl;
		cout << "alege:";
		cin >> opt;
		switch (opt)
		{
		case 1: introducere(l, x);
			break;
		case 2: introducere(l, x);
			break;
		case 3: l->afisare_lista();
			break;
		case 0: break;
		default:cout << "opt gres";
			break;
		}

	} while (opt != 0);

return 0;}