#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#define MAXL 1000
#define IL_PROB 5
#define ROZ 100

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


int main(){
	srand(time(NULL));
	std::string tablica[7];
	tablica[0]="SCHRAGE1.DAT";
	tablica[1]="SCHRAGE2.DAT";
	tablica[2]="SCHRAGE3.DAT";

	int tab_roz[3]={ROZ,10*ROZ,100*ROZ};
	for(int ile=0;ile<IL_PROB;ile++){
//generowanie danych
		for(int i=0;i<3;i++){
			ofstream zapis(tablica[i]);
			zapis<<tab_roz[i]<<endl;
			for(int j=0;j<tab_roz[i];j++){
				int r,p,q;
				r=rand()%MAXL;
				p=rand()%MAXL;
				q=rand()%MAXL;
				zapis<<r<<" "<<p<<" "<<q<<endl;
			}
		}

// iteracja jakas zjebana
	for(int iter=0;iter<3;iter++){
		fstream plik;
		plik.open(tablica[iter]); //otwiera pliki Schrage

		Kolejka N,G;
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
			int t = 0, k = 0, Cmax = 0,e=0;

			long double roznica;
			clock_t start,koniec;
			cout.setf(ios::fixed);
			cout.precision(5);
//============================TU JEST KOD ======================================
			start=clock();
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
					k++; // pozycja w permutacji
				 // zaimplementować tablice zadań
				 t = t + tempp;
				 Cmax = max(Cmax, (t + tempq));
			 }
			 //cout << Cmax << endl;
			koniec=clock();
			//=============================KONIEC======================================
			roznica=(koniec-start)/(double)CLOCKS_PER_SEC;
			cout<<"Czas wykonania dla pliku: "<<tab_roz[iter]<<" = "<<roznica<<endl;
		}

	else std::cout << "Nie ma takiego pliku!" << std::endl;
	plik.close();
}
system("pause");
}
return 0;
}
