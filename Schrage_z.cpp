#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <windows.h>
#include <cstdlib>
#include <math.h>
#include <ctime>
#define MAXL 100
#define IL_PROB 5
#define ROZ 10

#define WIELKOSC 1000

using namespace std;

struct Lista{
	Lista *next;
	int r, p, q;
};

class Kolejka {
private:
	Lista *glowa;
	Lista *ogon;

public:
	Kolejka();
	~Kolejka();

	bool pusty();
	void push(int,int,int);
	void push_sort_q(int, int, int);
	void pop();
	void wyswietl(Kolejka);
	int topr(Kolejka);
	int topp(Kolejka);
	int topq(Kolejka);
};

Kolejka::Kolejka() {
	glowa = ogon = NULL;
}

Kolejka::~Kolejka(){
	while (glowa)
		pop();
}

//Sprawdza czy kolejka jest pusta - True jeśli tak/ False jeśli nie
bool Kolejka::pusty() {
	return !glowa;
}
// Wrzucanie elemtów do kolejki oraz sortowanie po elemencie 'r'
void Kolejka::push(int r, int p, int q) {
	Lista *s, *t;
	s = new Lista;
	s->next = NULL;
	s->r = r;
	s->p = p;
	s->q = q;

	if (!glowa) // Jeżeli jest to pierwszy element listy wpisz go od razu
		glowa = ogon = s;
	else if (glowa->r > r){ // Jeżeli element 'r' jest większy od elementu na szczycie wpisz go na szczyt
		s->next = glowa; // Przesunięcie wskaźnika na następne miejsce
		glowa = s; // Przypisanie struktury danych na 1 miejsce
	}
	else{
		t = glowa;
		while ((t->next) && (t->next->r <= r)) // Przesukiwanie elementów w kolejce żeby umieścić je w środku kolejki
			t = t->next;
		s->next = t->next;
		t->next = s;
		if (!s->next) // Jeżeli nie ma następnego elementu, jest to ogon
			ogon = s;
	}
}

void Kolejka::push_sort_q(int r, int p, int q){
	Lista *s, *t;
	s = new Lista;
	s->next = NULL;
	s->r = r;
	s->p = p;
	s->q = q;

	if (!glowa)
		glowa = ogon = s;
	else if (glowa->q < q){
		s->next = glowa;
		glowa = s;
	}
	else{
		t = glowa;
		while ((t->next) && (t->next->q >= q))
			t = t->next;
		s->next = t->next;
		t->next = s;
		if (!s->next)
			ogon = s;
	}
}

void Kolejka::pop(){ // ściągnie elementów z kolejki
	if (glowa){
		Lista * p = glowa;
		glowa = glowa->next;
		if (!glowa)
			ogon = NULL;
		//delete p; // usuwanie elementów niestety nie działa więc przesuwamy tylko wskaźnik
	}
}

void Kolejka::wyswietl(Kolejka Q){ // Wyświetlanie elemtnu na szczycie listy
	cout << Q.glowa->r << " " << Q.glowa->p << " " << Q.glowa->q << endl;

}

int Kolejka::topr(Kolejka Q){ // Zwraca wartość 'r' na szczycie
	if (glowa)
		return glowa->r;
}

int Kolejka::topp(Kolejka Q){ // Zwraca wartość 'p' na szczycie
	if (glowa)
		return glowa->p;
}

int Kolejka::topq(Kolejka Q){ // Zwraca wartość 'q' na szczycie
	if (glowa)
		return glowa->q;
}

int Schrage(string nazwa){
	fstream plik;
	plik.open(nazwa.c_str()); //otwiera pliki Schrage
	// iteracja jakas zjebana
			Kolejka N,G,Q2;
			int r, p, q;

			if (plik.good()){
				int ilosc;
				plik >> ilosc;
				ilosc = ilosc + 1;
				for (int i = 1; i < ilosc; i++){
					plik >> r;
					plik >> p;
					plik >> q;
					N.push(r, p, q); // Tworzymy zbiór N
				}
//================================================================
        int C[WIELKOSC];
        		C[0] = 0;
        		for (int i = 1; i < ilosc; i++)        		{
        			C[i] = max(N.topr(N), C[i - 1]) + N.topp(N);
        			N.pop();
        		}

        		int D[WIELKOSC];
        		for (int i = 1; i < ilosc; i++){
        			D[i] = C[i] + Q2.topq(Q2);
        			Q2.pop();
        		}

        		int max = D[1];
        		for (int i = 1; i < ilosc; i++){
        			if (D[i] > max)
        				max = D[i];
        		}

        		//cout << max << endl;

				int t = 0, k = 0, Cmax = 0,e=0;

				cout.setf(ios::fixed);
				cout.precision(5);
	//============================TU JEST KOD ======================================

				while (!(G.pusty()) || !(N.pusty())){
					flaga:
					while (!(N.pusty()) && (N.topr(N) <= t)){
						int tempr, tempp, tempq;
						tempr = N.topr(N);
						tempp = N.topp(N);
						tempq = N.topq(N);
						N.pop();
						G.push_sort_q(tempr, tempp, tempq);
					}
						if (G.pusty()){
							t = N.topr(N);
							goto flaga;
						}
						e = G.topq(G);
						int tempp = G.topp(G);
						int tempq = G.topq(G);
						G.pop();
						k++;
					 t = t + tempp;
					 Cmax = max(Cmax, (t + tempq));
				 }
			}
		else std::cout << "Nie ma takiego pliku!" << std::endl;
		plik.close();
}

void gen(int rozmiar,string nazwa){
	for(int i=0;i<4;i++){
		std::ofstream zapis(nazwa.c_str());
		zapis<<rozmiar<<endl;
		for(int j=0;j<rozmiar;j++){
			int r,p,q;
			r=rand()%MAXL;
			p=rand()%MAXL;
			q=rand()%MAXL;
			zapis<<r<<" "<<p<<" "<<q<<endl;
		}
	}
}

int main(){
	clock_t START,KONIEC;
	START=clock();
	srand(time(NULL));
	std::string tablica[4];
	tablica[0]="SCHRAGE10.DAT";
	tablica[1]="SCHRAGE100.DAT";
	tablica[2]="SCHRAGE1000.DAT";
	tablica[3]="SCHRAGE10000.DAT";
	int tab_roz[4]={ROZ,10*ROZ,100*ROZ,1000*ROZ};


	for(int ile=0;ile<IL_PROB;ile++){
		for(int r=0;r<4;r++){
			clock_t start,koniec;
			gen(tab_roz[r],tablica[r]);
			long double roznica;
			start=clock();
			Schrage(tablica[r]);
			koniec=clock();
			roznica=1000000*(koniec-start)/(double)CLOCKS_PER_SEC;
			cout<<"Czas wykonania dla pliku: "<<tab_roz[r]<<" = "<<roznica<<endl;
		}
	}
	KONIEC=clock();
	long double ROZNICA;
	ROZNICA=(KONIEC-START)/(double)CLOCKS_PER_SEC;
	cout<<"CZAS: "<<ROZNICA<<endl;
	return 0;
}
