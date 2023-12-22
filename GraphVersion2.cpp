#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <queue>
#include <set>


using namespace std;

class Graf {

	string* imena;
	struct Elem {
		int postoji, tezina;
		int a, b;
	};
	int brojac;
	Elem** matrica;


	Elem** praviMatricu();
	Elem** pocetnaInicijalizacija();


public:

	Graf(int broj) : brojac(broj) {

		matrica = praviMatricu();
		matrica = pocetnaInicijalizacija();
		imena = new string[brojac];
		for (int i = 0; i < brojac; i++) {
			string novoIme;
			cout << "Unesite ime " << i << "-tog cvora: ";
			cin >> imena[i];
		}
	}
	Graf(const Graf& g) = delete;
	Graf(Graf&& g) = delete;
	Graf& operator = (Graf&& g) = delete;
	~Graf();


	//inkrementer i dekrement za broj elemenata
	int inc() {
		return ++brojac;
	}
	int dec() {
		return --brojac;
	}

	//meotode za dodavanje elementa
	Elem** dodajElement();
	string* dodajIme(string novoIme);

	//metode za brisanje elementa
	Elem** ukloniElement(string ime);
	string* ukloniIme(string ime);

	//metoda za dodavanje grane
	Elem** dodajGranu(int a, int b, int tezina) {

		if (a > brojac || b > brojac || a < 0 || b < 0) {
			cout << "Uneli ste cvor koji ne postoji" << endl;
		}
		if (tezina < 0) {
			cout << "Unesli ste negativnu tezinu. " << endl;
		}

		if (matrica[a][b].postoji == 1) {
			cout << "Unesena grana vec postoji" << endl;

		}
		else
		{

			matrica[a][b].tezina = matrica[b][a].tezina = tezina;
			matrica[a][b].postoji = matrica[b][a].postoji = 1;
			matrica[a][b].a = matrica[b][a].a = a;
			matrica[a][b].b = matrica[b][a].b = b;

		}
		return matrica;
	}

	Elem** dodajTezinu(int tezina, int a, int b) {

		if (a > brojac || b > brojac || a < 0 || b < 0) {
			cout << "Uneli ste cvor koji ne postoji" << endl;
		}
		if (tezina < 0) {
			cout << "Unesli ste negativnu tezinu. " << endl;
		}
		if (matrica[a][b].postoji == 1) {
			cout << "Unesena grana vec postoji" << endl;
			return matrica;
		}
		else {
			matrica[a][b].tezina = matrica[b][a].tezina = tezina;
			matrica[a][b].postoji = matrica[b][a].postoji = 0;
			matrica[a][b].a = matrica[b][a].a = a;
			matrica[a][b].b = matrica[b][a].b = b;
			return matrica;
		}

	}

	//metoda za brisanje grane
	Elem** brisiGranu(int a, int b) {
		if (a > brojac || b > brojac) {
			cout << "Uneli ste cvor koji ne postoji" << endl;
		}
		if (matrica[a][b].postoji == 0) {
			cout << "Ova dva cvora nisu susedi" << endl;
		}
		else {
			matrica[a][b].postoji = matrica[b][a].postoji = 0;
			matrica[a][b].tezina = matrica[b][a].tezina = 0;
			matrica[a][b].a = matrica[b][a].a = 0;
			matrica[a][b].b = matrica[b][a].b = 0;
		}

		return matrica;
	}

	//metoda za ispisivanje reprezentacije matrice
	void ispisi(ostream& os) const;

	//metoda za brisanje
	void brisiObjekat(const Graf& g) {
		
		delete& g;
	}

	friend ostream& operator << (ostream& os, const Graf& g) {
		g.ispisi(os);
		return os;
	}

	friend void kruskal(const Graf& g);

	void dijkstra(int v);

};


Graf::Elem** Graf::praviMatricu() {
	matrica = new Elem * [brojac];
	for (int i = 0; i < brojac; i++) {
		matrica[i] = new Elem[brojac];
	}
	return matrica;
}

Graf::Elem** Graf::pocetnaInicijalizacija() {
	for (int i = 0; i < brojac; i++) {
		for (int j = 0; j < brojac; j++) {
			matrica[i][j].postoji = 0;
			matrica[i][j].tezina = 0;
			matrica[i][j].a = 0;
			matrica[i][j].b = 0;
		}
	}
	return matrica;
}

Graf::~Graf()
{
	delete[] imena;

	for (int i = 0; i < brojac; i++) {
		delete[] matrica[i];
	}
	matrica = nullptr;


}

Graf::Elem** Graf::dodajElement()
{
	Elem** pom;
	pom = new Elem * [brojac];
	for (int i = 0; i < brojac; i++) {
		pom[i] = new Elem[brojac];
	}
	for (int i = 0; i < brojac; i++) {
		for (int j = 0; j < brojac; j++) {
			pom[i][j] = { 0,0,0,0 };
		}
	}

	for (int i = 0; i < brojac - 1; i++) {
		for (int j = 0; j < brojac - 1; j++) {
			pom[i][j].a = matrica[i][j].a;
			pom[i][j].b = matrica[i][j].b;
			pom[i][j].postoji = matrica[i][j].postoji;
			pom[i][j].tezina = matrica[i][j].tezina;
		}
	}


	for (int i = 0; i < brojac - 1; i++) {
		delete[] matrica[i];
	}
	matrica = pom;

	return matrica;
}

Graf::Elem** Graf::ukloniElement(string ime) {
	int i = 0;
	Elem** pom;
	pom = new Elem * [brojac];
	for (int i = 0; i < brojac; i++) {
		pom[i] = new Elem[brojac];
	}

	if (brojac == 1) return matrica = nullptr;

	for (i; i < brojac + 1; i++) {
		if (imena[i] == ime) break;
	}

	int k = 0;
	for (int p = 0; p <= brojac; p++) {
		if (p != i) {
			int j = 0;
			for (int q = 0; q <= brojac; q++) {
				if (q != i) {
					pom[k][j].a = matrica[p][q].a;
					pom[k][j].b = matrica[p][q].b;
					pom[k][j].postoji = matrica[p][q].postoji;
					pom[k][j].tezina = matrica[p][q].tezina;
					j++;
				}
			}
			k++;

		}
	}

	for (int j = 0; j < brojac; j++) {
		delete[] matrica[j];
	}
	matrica = pom;

	return matrica;
}

string* Graf::ukloniIme(string ime)
{
	string* pom;
	int j = 0;
	pom = new string[brojac];
	for (int i = 0; i < brojac + 1; i++) {
		if (imena[i] != ime) {
			pom[j] = imena[i];
			j++;
		}
	}
	delete[] imena;

	imena = pom;

	return imena;
}

string* Graf::dodajIme(string novoIme)
{
	string* pom = new string[brojac];
	for (int i = 0; i < brojac - 1; i++) {
		pom[i] = imena[i];
	}
	pom[brojac - 1] = novoIme;

	delete[] imena;

	imena = pom;

	return imena;
}

void Graf::ispisi(ostream& os) const
{
	if (matrica == nullptr) {
		os << "Matrica ne postoji" << endl;
	}
	else {
		for (int i = 0; i < brojac; i++) {
			os << setw(5) << i << setw(15) << imena[i] << endl;
		}
		os << endl;

		os << "Matrica susednosti:" << endl;
		for (int i = 0; i < brojac; i++) {
			for (int j = 0; j < brojac; j++) {
				os << setw(5) << matrica[i][j].postoji;
			}
			os << endl;
		}

		os << "Matrica tezine grana: " << endl;
		for (int i = 0; i < brojac; i++) {
			for (int j = 0; j < brojac; j++) {
				os << setw(5) << matrica[i][j].tezina;
			}
			os << endl;
		}
	}



}

void Graf::dijkstra(int v)
{
	//skup tezina
	int* nizW = new int[brojac];
	for (int m = 0; m < brojac; m++) nizW[m] = 0;

	//inicijalizacija skupa za proveru
	int* skup = new int[brojac];
	for (int i = 0; i < brojac; i++) {
		if (i == v) { skup[i] = 1; }
		else { skup[i] = 0; }
	}
	//klasa koja mi omogucava sortiranje u PQ
	class cmp {

	public:
		int operator () (const Graf::Elem& e1, const Graf::Elem& e2) {
			return e1.tezina > e2.tezina;
		}
	};

	//deklaracija prioritetnog reda
	priority_queue <Graf::Elem, vector <Graf::Elem>, cmp> PQ;

	// u PQ se ubacuju sve grane u rastucem poretku
	for (int j = 0; j <= brojac; j++) {
		if (matrica[v][j].postoji == 1 && j != v && matrica[v][j].tezina != 0) {
			PQ.push(matrica[v][j]);
		}
	}

	for (int p = 1; p < brojac; p++) {

		Graf::Elem pomocni = PQ.top();
		PQ.pop();

		if (skup[pomocni.b] == 0 && pomocni.b != v) {
			skup[pomocni.b] = 1;
			nizW[pomocni.b] = pomocni.tezina;
		}

		for (int q = 0; q < brojac; q++) {
			if (skup[q] == 0) {
				if ((pomocni.tezina + matrica[p][q].tezina) < matrica[v][q].tezina) {
					PQ.push(matrica[v][q]);
				}
			}
		}
	}

	for (int i = 1; i < brojac; i++) {
		cout << setw(5) << i << setw(10) << nizW[i] << endl;
	}
	return;
}

void kruskal(const Graf& g)
{
	//klasa koja mi omogucava sortiranje u PQ
	class cmp {

	public:
		int operator () (const Graf::Elem& e1, const Graf::Elem& e2) {
			return e1.tezina > e2.tezina;
		}
	};

	//deklaracija prioritetnog reda
	priority_queue <Graf::Elem, vector <Graf::Elem>, cmp> PQ;

	//deklaracija skupa grana
	struct Grana {
		Graf::Elem e;
		Grana* next;
	};
	Grana* head = nullptr;
	Grana* curr = nullptr;

	// u PQ se ubacuju sve grane u rastucem poretku
	for (int i = 0; i < g.brojac; i++) {
		for (int j = 0; j <= i; j++) {
			if (g.matrica[i][j].postoji == 1) {
				PQ.push(g.matrica[i][j]);
			}
		}
	}

	int b = 0;

	// za proveru pripadnosti skupa
	int* skup = new int[g.brojac];
	for (int i = 0; i < g.brojac; i++) {
		skup[i] = i;
	}

	while (b < g.brojac - 1) {

		Graf::Elem pomocni = PQ.top();
		PQ.pop();

		if (skup[pomocni.a] != skup[pomocni.b]) {
			skup[pomocni.a] = skup[pomocni.b] = g.brojac + 1;

			//inkrementiranje brojaca
			b++;

			//stvarnanje noovog covra
			Grana* node = new Grana;

			//dodavanje cvora
			node->next = nullptr;
			node->e = pomocni;

			if (head == nullptr) {
				head = node;
			}
			else {
				curr->next = node;
			}
			curr = node;
		}
	}

	//definicija tezine
	int suma = 0;

	for (curr = head; curr; curr = curr->next) {
		suma += curr->e.tezina;
	}

	//ispis grana i minimalne cene
	cout << "Minimalna cena je: " << suma << endl;

	cout << "Grane su : " << endl;
	for (curr = head; curr; curr = curr->next) {
		cout << setw(5) << curr->e.a << setw(5) << "-" << setw(5) << curr->e.b << endl;
	}
	return;
}

using namespace std;

void ispisiMeni() {
	cout << "Operacije koje mozete da izaberete su:" << endl
		<< "1. Kreiranje mape grada, bez puteva, za uneti broj lokacija. " << endl
		<< "2. Dodavanje jednog lokacije sa zadatim indeksom. " << endl
		<< "3. Uklanjanje jednog lokacije sa zadatim indeksom. " << endl
		<< "4. Dodavanje duzine puta izmedju dva upisana cvora. " << endl
		<< "5. Brisanje duzine puta izmedju dva upisana cvora. " << endl
		<< "6. Ispisivanje mape povezanosti. " << endl
		<< "7. Brisanje mape iz memorije. " << endl
		<< "8. Dodavanje moguce duzine puta cija je izgradnja u planu" << endl
		<< "9. Izracunavanje minimalne cene izgranje puteva koji spajaju sve lokacije." << endl
		<< "10. Minimalno rastojanje unete lokacije od svih ostalih lokacija" << endl
		<< "11. Kraj programa. " << endl;
	return;
}

bool bezbedanCase(int izbor, Graf* g) {

	if (g == nullptr) {
		cout << "Izabrali ste operaciju koja nije moguca" << endl;
		return false;
	}
	return true;
}


int main() {

	bool krajPrograma = false;
	int izbor;
	Graf* g = nullptr;
	int brojac;

	ispisiMeni();

	while (krajPrograma == false) {

		cout << "Unesite Vas izbor operacije: " << endl;
		cin >> izbor;

		if (izbor < 1 || izbor > 11) {
			cout << "Uneli ste opciju koja nije moguca, unesite ponovo: " << endl;
		}

		switch (izbor)
		{
			case 1: {

				cout << "Unesite broj lokacija: ";
				cin >> brojac;
				g = new Graf(brojac);

			}break;
			case 2: {

				if (bool i = bezbedanCase(izbor, g) == false) break;

				string novoIme;
				cout << "Unesite ime nove lokacije: ";
				cin >> novoIme;
				g->inc();
				g->dodajElement();
				g->dodajIme(novoIme);

			}break;
			case 3: {

				if (bool i = bezbedanCase(izbor, g) == false) break;
				string ime;
				g->dec();
				cout << "Unesite ime lokacije koju zelite da izbacite: ";
				cin >> ime;
				g->ukloniElement(ime);
				g->ukloniIme(ime);

			}break;
			case 4: {

				if (bool i = bezbedanCase(izbor, g) == false) break;

				int a, b, tezina;

				cout << "Unesite prvu lokaciju: " << endl;
				cin >> a;

				cout << "Unesite drugu lokaciju: " << endl;
				cin >> b;

				cout << "Unesite duzinu puta izmedju dve lokacije: " << endl;
				cin >> tezina;

				g->dodajGranu(a, b, tezina);

			}break;
			case 5: {

				if (bool i = bezbedanCase(izbor, g) == false) break;

				int a, b;

				cout << "Unesite dve lokacije izmedju kojih zelite da uklonite put: " << endl;
				cin >> a >> b;

				g->brisiGranu(a, b);

			}break;
			case 6: {

				if (bool i = bezbedanCase(izbor, g) == false) break;

				g->ispisi(cout);

			}break;
			case 7: {

				if (bool i = bezbedanCase(izbor, g) == false) break;

				g->brisiObjekat(*g);

				cout << "Vasa mapa je obrisan." << endl;

			}break;
			case 8: {
			
				if (bool i = bezbedanCase(izbor, g) == false) break;

				int a, b, tezina;
				cout << "Unesite indeks prve lokacije: " << endl;
				cin >> a;
				cout << "Unesite indeks druge lokacije: " << endl;
				cin >> b;
				cout << "Unesite duzinu puta koji moze da se napravi: " << endl;
				cin >> tezina;

				g->dodajTezinu(tezina, a, b);
			
			}break;
			case 9: {
			
				if (bool i = bezbedanCase(izbor, g) == false) break;

				kruskal(*g);
			
			}break;
			case 10: {
			
				if (bool i = bezbedanCase(izbor, g) == false) break;

				int v;

				cout << "Unesite referentnu lokaciju: " << endl;
				cin >> v;

				g->dijkstra(v);
			
			}break;
			case 11: {
			
				krajPrograma = true;
				g->brisiObjekat(*g);

			}break;
		}
	}
	return 0;
}