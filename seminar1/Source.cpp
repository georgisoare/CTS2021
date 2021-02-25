//domeniul medical

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
#include <set>
#include <map>
#include <fstream>
using namespace std;

//SUGESTII
//1. Foarte mult cod comentat
//2. Mult cod care se repeta
//3. Variabila "nr" din clasa Medicament nu este foarte sugestiva
//4. Cod redundant (la getteri si setteri; nu sunt apelati)
//5. Atributul "salariu" al clasei Doctor nu este neaparat folositor.


class Doctor {
private:
	string nume;
	string prenume;
	string specializare;
	float salariu;
	int nrPacienti;
	string* pacienti;
	static int nrDoctori;
	const int id;

public:
	//constructor fara parametri
	Doctor() :id(1) { 
		this->nume = "Soare";
		this->prenume = "Nicolla";
		this->specializare = "Chirurg";
		this->salariu = 3000;
		this->nrPacienti = 5;
		this->pacienti = new string[this->nrPacienti];
		for (int i = 0; i < this->nrPacienti; i++)
		{
			this->pacienti[i] = "Pacientul " + to_string(i + 5);
		}
		
		this->nrDoctori++;
	}

	//constructor cu parametri
	Doctor(string numeD, string prenumeD, string specializareD, float salariuD, int nrPacientiD, string* pacientiD) :id(2)
	{
		this->nume = numeD;
		this->prenume = prenumeD;
		this->specializare = specializareD;
		this->salariu = salariuD;
		this->nrPacienti = nrPacientiD;
		this->pacienti = new string[this->nrPacienti];
		for (int i = 0; i < this->nrPacienti; i++)
		{
			this->pacienti[i] = pacientiD[i];
		}
		
		this->nrDoctori++;

	}

	//constructor de copiere
	Doctor(const Doctor& doctor) :id(3) {
		this->nume = doctor.nume;
		this->prenume = doctor.prenume;;
		this->specializare = doctor.specializare;
		this->salariu = doctor.salariu;
		this->nrPacienti = doctor.nrPacienti;
		this->pacienti = new string[this->nrPacienti];
		for (int i = 0; i < this->nrPacienti; i++)
		{
			this->pacienti[i] = doctor.pacienti[i];
		}
		this->nrDoctori++;
	}

	//supraincarcarea operatorului =
	Doctor& operator=(const Doctor& doctor) {
		this->nume = doctor.nume;
		this->prenume = doctor.prenume;;
		this->specializare = doctor.specializare;
		this->salariu = doctor.salariu;
		this->nrPacienti = doctor.nrPacienti;
		this->pacienti = new string[this->nrPacienti];
		for (int i = 0; i < this->nrPacienti; i++)
		{
			this->pacienti[i] = doctor.pacienti[i];
		}
		return *this;

	}

	//supraincarcare operator <<
	friend ostream& operator<<(ostream& out, Doctor& d) {
		out << "Nume: " << d.nume << endl;
		out << "Prenume: " << d.prenume << endl;
		out << "Specializare: " << d.specializare << endl;
		out << "Salariu: " << d.salariu << endl;
		out << "Numarul pacientilor: " << d.nrPacienti << endl;
		out << "Pacienti:" << endl;
		for (int i = 0; i < d.nrPacienti; i++)
		{
			out << d.pacienti[i] << endl;
		}
		out << "Id: " << d.id << endl;
		out << "Numarul doctorilor: " << d.nrDoctori << endl;
		return out;
	}

	//supraincarcare operator >>
	friend istream& operator>>(istream& in, Doctor& d) {
		cout << "Numele doctorului: " << endl;
		in >> d.nume;
		cout << "Prenumele doctorului: " << endl;
		in >> d.prenume;
		cout << "Specializare: " << endl;
		in >> d.specializare;
		cout << "Salariul: " << endl;
		in >> d.salariu;
		cout << "Nr pacienti: " << endl;
		in >> d.nrPacienti;
		if (d.pacienti != NULL)
			delete[] d.pacienti;
		d.pacienti = new string[d.nrPacienti];
		for (int i = 0; i < d.nrPacienti; i++)
		{
			cout << "Pacientul " << i + 1 << endl;
			in >> d.pacienti[i];
		}
		return in;
	}

	//supraincarcare operator ==
	bool operator==(Doctor d) {
		if (this->nume == d.nume && this->prenume == d.prenume && this->specializare == d.specializare && this->salariu==d.salariu)
			return true;
		else return false;
	}

	//supraincarcare operator <=
	bool operator<=(Doctor d) {
		if (this->salariu <= d.salariu)
			return true;
		else return false;
	}

	//supraincarcare operator index  []
	string& operator[](int index) { 
		if (index < 0 || index > this->nrPacienti) {
			cout << "Index in afara limitelor";
			throw new exception("Exceptie");
		}
		else {
			return this->pacienti[index];
		}
	}

	//supraincarcare operator ++ prefixat
	Doctor& operator++() {
		string* pacientiNoi = new string[this->nrPacienti + 1];
		for (int i = 0; i < this->nrPacienti; i++) {
			pacientiNoi[i] = this->pacienti[i];
		}
		pacientiNoi[this->nrPacienti] = "Pacient Nou Adaugat";
		this->nrPacienti++;
		if (this->pacienti != NULL) {
			delete[] this->pacienti;
		}
		this->pacienti = pacientiNoi;
		return *this;
	}

	//supraincarcarea ++ sufixat
	Doctor operator++(int) { 
		Doctor copie = *this;
		string* pacientiNoi = new string[this->nrPacienti + 1];
		for (int i = 0; i < this->nrPacienti; i++) {
			pacientiNoi[i] = this->pacienti[i];
		}
		pacientiNoi[this->nrPacienti] = "Pacient Nou Adaugat";
		this->nrPacienti++;
		if (this->pacienti != NULL) {
			delete[] this->pacienti;
		}
		this->pacienti = pacientiNoi;
		return copie;
	}



	//destructor
	~Doctor()
	{
		if (this->pacienti != NULL)
		{
			delete[] this->pacienti;
		}
		this->nrDoctori--;
	}

	void afisare() {
		cout << "Numele doctorului: " << this->nume << endl;
		cout << "Prenume doctorului: " << this->prenume << endl;
		cout << "Specializare: " << this->specializare << endl;
		cout << "Salariu: " << this->salariu << endl;
		cout << "Nr pacienti: " << this->nrPacienti << endl;
		cout << "Pacienti: " << endl;
		for (int i = 0; i < this->nrPacienti; i++)
		{
			cout << this->pacienti[i] << endl;
		}
		cout << endl;

	}

	void modificare() {
		if (this->salariu < 4000)
			this->salariu=this->salariu+1000;
	}



	//getter si setter atribut salariu
	float getSalariu() {
		return this->salariu;
	}
	void setSalariu(float salariuNou)
	{
		this->salariu = salariuNou;
	}

	//getteri si setteri pacienti
	string* getPacienti() {
		return this->pacienti;
	}

	void setPacienti(string pacientiNoi, int nrPacientNou)
	{
		if (this->pacienti != NULL)
			delete[]this->pacienti;

		this->nrPacienti = nrPacientNou;
		this->pacienti = new string[this->nrPacienti];
		for (int i = 0; i < nrPacienti; i++)
		{
			this->pacienti[i] = pacientiNoi[i];
		}
	}

	//getter atribut nume
	string getNume() {
		return this->nume;
	}

	//getter atribut prenume
	string getPrenume() {
		return this->prenume;
	}

	//getter atribut specializare
	string getSpecializare() {
		return this->specializare;
	}

	//getter atribut nrPacienti
	int getNrPacienti() {
		return this->nrPacienti;
	}

	//getter atribut constant
	int getId()
	{
		return this->id;
	}

	//getter atribut static
	static int getNrDoctori() {
		return nrDoctori;
	}

	//setter atribut static
	static void setNrDoctori(int nrDoctoriNou) {
		Doctor::nrDoctori = nrDoctoriNou;
	}


};

//initializare atribut static
int Doctor::nrDoctori = 0;


class Operatie {
private:
	string data;
	int oraIncepere;
	int nrChirurgi;
	string* chirurgi;
	int durata;
	float pretOperatie;
	const int serie;
	static int nrOperatii;


public:
	//constructor fara parametri
	Operatie() : serie(1){
		this->data = "12.10.2019";
		this->oraIncepere = 12;
		this->durata = 5;
		this->pretOperatie = 1200;
		this->nrChirurgi = 5;
		this->chirurgi = new string[this->nrChirurgi];
		for (int i = 0; i < this->nrChirurgi; i++)
		{
			this->chirurgi[i] = "Chirurgul " + to_string(i + 2);
		}
		//incrementare atribut static
		this->nrOperatii++;
	}

	//constructor cu parametri
	Operatie(string dataO, int oraIncepereO,int durataO, float pretOperatieO, int nrChirurgiO, string* chirurgiO) : serie(2){
		this->data = dataO;
		this->oraIncepere = oraIncepereO;
		this->durata = durataO;
		this->pretOperatie = pretOperatieO;
		this->nrChirurgi = nrChirurgiO;
		this->chirurgi = new string[this->nrChirurgi];
		for (int i = 0; i < this->nrChirurgi; i++)
		{
			this->chirurgi[i] = chirurgiO[i];
		}
		//incrementare atribut static
		this->nrOperatii++;
	}

	//constructor de copiere
	Operatie(const Operatie& operatie) : serie(3) {
		this->data = operatie.data;
		this->oraIncepere = operatie.oraIncepere;
		this->durata = operatie.durata;
		this->pretOperatie = operatie.pretOperatie;
		this->nrChirurgi = operatie.nrChirurgi;
		this->chirurgi = new string[this->nrChirurgi];
		for (int i = 0; i < this->nrChirurgi; i++)
		{
			this->chirurgi[i] = operatie.chirurgi[i];
		}
	}

	void afisare2() {
		cout << "Data operatiei este: " << this->data << endl;
		cout << "Ora la care incepe operatia este: " << this->oraIncepere << endl;
		cout << "Operatia dureaza " << this->durata << " ore" << endl;
		cout << "Pretul operatiei este de " << this->pretOperatie << " lei" << endl;
		cout << "Numarul chirurgilor disponibili este: " << this->nrChirurgi << endl;
		cout << "Acestia sunt: " << endl;
		for (int i = 0; i < this->nrChirurgi; i++)
		{
			cout << this->chirurgi[i] << endl;
		}
		cout << endl;

	}

	//supraincarcare operator =
	Operatie& operator=(const Operatie& operatie) {
		this->data = operatie.data;
		this->oraIncepere = operatie.oraIncepere;
		this->durata = operatie.durata;
		this->pretOperatie = operatie.pretOperatie;
		this->nrChirurgi = operatie.nrChirurgi;
		this->chirurgi = new string[this->nrChirurgi];
		for (int i = 0; i < this->nrChirurgi; i++)
			this->chirurgi[i] = operatie.chirurgi[i];
		return *this;
	}

	//supraincarcare operator <<
	friend ostream& operator<<(ostream& out, Operatie& o) {
		out << "Data operatiei: " << o.data << endl;
		out << "Ora la care incepe operatia: " << o.oraIncepere << endl;
		out << "Durata operatiei (ore):" << o.durata << endl;
		out << "Pretul operatiei: " << o.pretOperatie << endl;
		out << "Numarul chirurgilor disponibili: " << o.nrChirurgi << endl;
		for (int i = 0; i < o.nrChirurgi; i++)
			out << "Acestia sunt: " << o.chirurgi[i] << endl;
		out << "Serie: " << o.serie << endl;
		out << "Numar operatii: " << o.nrOperatii << endl;
		return out;
	}

	//supraincarcare operator >>
	friend istream& operator>>(istream& in, Operatie& o) {
		cout << "Data operatiei este: " << endl;
		in >> o.data;
		cout << "Ora la care incepe operatia: " << endl;
		in >> o.oraIncepere;
		cout << "Durata operatiei (ore): " << endl;
		in >> o.durata;
		cout << "Pretul operatiei: " << endl;
		in >> o.pretOperatie;
		cout << "Numarul chirurgilor: " << endl;
		in >> o.nrChirurgi;
		if (o.chirurgi != NULL)
		{
			delete[] o.chirurgi;
		}
		o.chirurgi = new string[o.nrChirurgi];
		for (int i = 0; i < o.nrChirurgi; i++)
		{
			cout << "Chirurgul " << i + 1 << endl;
			in >> o.chirurgi[i];
		}
		return in;
	}

	//supraincarcare operator ==
	bool operator==(Operatie o) {
		if (this->data == o.data && this->oraIncepere == o.oraIncepere && this->durata == o.durata)
			return true;
		else return false;
	}

	//supraincarcare operator !
	bool operator!() {
		if (this->chirurgi != NULL)
			return false;
		else return true;
	}

	//supraincarcare operator cast
	explicit operator float() {
		return this->pretOperatie;
	}

	//supraincarcare operator+ pentru apel o1+5
	Operatie operator+(int valoare) {
		Operatie copie = *this;
		copie.durata = copie.durata + valoare;
		return copie;
	}

	//supraincarcare operator+ pentru apel 5+o1
	friend Operatie operator+(int valoare, Operatie m) {
		Operatie copie = m;
		copie.durata = copie.durata + valoare;
		return copie;
	}

	//supraincarcare operator += pt apel o1+=7
	Operatie operator+=(int valoare) {
		this->durata += valoare;
		return *this;
	}


	//destructor
	~Operatie() {
		if (this->chirurgi != NULL)
			delete[] this->chirurgi;
		this->nrOperatii--;
	}

	//getter si setter atribut pret
	float getPret() {
		return this->pretOperatie;
	}
	void setPret(float pretNou)
	{
		this->pretOperatie = pretNou;
	}

	//getter data
	string getData() {
		return this->data;
	}

	//getter oraIncepere
	int getOraIncepere() {
		return this->oraIncepere;
	}

	//getter nrChirurgi
	int getNrChirurgi() {
		return this->nrChirurgi;
	}

	//getteri si setteri chirurgi
	string* getChirurgi() {
		return this->chirurgi;
	}

	void setChirurgi(string chirurgiNoi, int nrChirurgNou)
	{
		if (this->chirurgi != NULL)
			delete[]this->chirurgi;

		this->nrChirurgi = nrChirurgNou;
		this->chirurgi = new string[this->nrChirurgi];
		for (int i = 0; i < nrChirurgi; i++)
		{
			this->chirurgi[i] = chirurgiNoi[i];
		}
	}

	//getter atribut constant
	int getSerie()
	{
		return this->serie;
	}

	int getDurata()
	{
		return this->durata;
	}

	//getter atribut static
	static int getNrOperatii() {
		return nrOperatii;
	}

	//setter atribut static
	static void setNrOperatii(int nrOperatieNou) {
		Operatie::nrOperatii = nrOperatieNou;
	}

};

//initializare atribut static
int Operatie::nrOperatii = 0;



class Medicament {
private: 
	string denumireMedicament;
	float pretMedicament;
	string administrare;
	int nrComprimate;
	string* comprimate;
	const int nr;
	static int nrMedicamente;

public:
	//constructor fara parametri
	Medicament() :nr(1) {
		this->denumireMedicament = "Nurofen";
		this->pretMedicament = 25;
		this->administrare = "Orala";
		this->nrComprimate = 3;
		this->comprimate = new string[this->nrComprimate];
		for (int i = 0; i < this->nrComprimate; i++)
			this->comprimate[i] = "Comprimatul " + to_string(i + 1);
		this->nrMedicamente++;

	}

	//constructor cu parametri
	Medicament(string denumireMedicamentM, float pretMedicamentM, string administrareM, int nrComprimateM, string* comprimateM) :nr(2) {
		this->denumireMedicament = denumireMedicamentM;
		this->pretMedicament = pretMedicamentM;
		this->administrare = administrareM;
		this->nrComprimate = nrComprimateM;
		this->comprimate = new string[this->nrComprimate];
		for (int i = 0; i < this->nrComprimate; i++)
			this->comprimate[i]= comprimateM[i];
		this->nrMedicamente++;

	}

	//constructor de copiere
	Medicament(const Medicament& medicament) :nr(3) {
		this->denumireMedicament = medicament.denumireMedicament;
		this->pretMedicament = medicament.pretMedicament;
		this->administrare = medicament.administrare;
		this->nrComprimate = medicament.nrComprimate;
		this->comprimate = new string[this->nrComprimate];
		for (int i = 0; i < this->nrComprimate; i++)
			this->comprimate[i] = medicament.comprimate[i];
		this->nrMedicamente++;
	}

	void afisare3()
	{
		cout << "Denumire medicament: " << this->denumireMedicament << endl;
		cout << "Pretul medicamentului(lei): " << this->pretMedicament << endl;
		cout << "Administrare medicament: " << this->administrare << endl;
		cout << "Nr comprimatelor: " << this->nrComprimate << endl;
		cout << "Comprimate: " << endl;
		for (int i = 0; i < this->nrComprimate; i++)
			cout << this->comprimate[i] << endl;
		cout << endl;
	}

	void modif() {
		if (this->pretMedicament > 20)
			this->nrComprimate--;
	}

	//supraincarcare operator =
	Medicament& operator=(const Medicament& medicament) {
		this->denumireMedicament = medicament.denumireMedicament;
		this->pretMedicament = medicament.pretMedicament;
		this->administrare = medicament.administrare;
		this->nrComprimate = medicament.nrComprimate;
		this->comprimate = new string[this->nrComprimate];
		for (int i = 0; i < this->nrComprimate; i++)
			this->comprimate[i] = medicament.comprimate[i];
		return *this;
	}

	//supraincarcare operator <<
	friend ostream& operator<<(ostream& out, Medicament& m) {
		out << "Denumire medicament: " << m.denumireMedicament<<endl;
		out << "Pretul medicamentului: " << m.pretMedicament<<endl;
		out << "Administrare medicament: " << m.administrare<<endl;
		out << "Nr comprimate: " << m.nrComprimate<<endl;
		out << "Comprimate: " << endl;
		for (int i = 0; i < m.nrComprimate; i++)
			out << m.comprimate[i] << endl;
		out << "NR: " << m.nr<<endl;
		out << "Nr medicamente: " << m.nrMedicamente<<endl;
		return out;
	}

	//supraincarcare operator >>
	friend istream& operator>>(istream& in, Medicament& m) {
		cout << "Denumirea medicamentului: " << endl;
		in >> m.denumireMedicament;
		cout << "Pretul medicamentului: " << endl;
		in >> m.pretMedicament;
		cout << "Administrare: " << endl;
		in >> m.administrare;
		cout << "Nr comprimate: " << endl;
		in >> m.nrComprimate;
		if (m.comprimate != NULL)
			delete[] m.comprimate;
		m.comprimate = new string[m.nrComprimate];
		for (int i = 0; i < m.nrComprimate; i++)
		{
			cout << "Comprimatul " << i + 1 << endl;
			in >> m.comprimate[i];
		}
		return in;
	}

	//supraincarcare operator ==
	bool operator==(Medicament m) {
		if (this->denumireMedicament == m.denumireMedicament && this->pretMedicament == m.pretMedicament && this->administrare == m.administrare)
			return true;
		else return false;
	}

	//supraincarcare operator >=
	bool operator>=(Medicament m) {
		if (this->pretMedicament >= m.pretMedicament)
			return true;
		else return false;
	}




	//destructor
	~Medicament() {
		if (this->comprimate != NULL)
			delete[] this->comprimate;
		this->nrMedicamente++;
	}

	//getter atribut denumire
	string getDenumireMedicament() {
		return this->denumireMedicament;
	}

	//setter atribut denumire
	void setDenumireMedicament(string denumireMedicamentNou) {
		this->denumireMedicament = denumireMedicamentNou;
	}

	//getter atribut constant
	int getNr() {
		return this->nr;
	}

	//getter atribut static
	static int getNrMedicamente() {
		return nrMedicamente;
	}

	//setter atribut static
	static void setNrMedicamente(int nrMedicamenteNou) {
		Medicament::nrMedicamente = nrMedicamenteNou;
	}
};

	//initializare atribut static
	int Medicament::nrMedicamente = 0;


	//mostenire
	class Chirurg :public Doctor { 
	protected:
		int nrOreLucrate;
		int varsta;

	public:
		Chirurg() :Doctor() {
			cout << "Constructor fara parametri clasa Chirurg" << endl;
			this->nrOreLucrate = 10;
			this->varsta = 35;
		}

		Chirurg(string numeP, string prenumeP, string specializareP, float salariuP, int nrPacientiP, string* pacientiP, int nrOreLucrateP, int varstaP ) :Doctor(numeP, prenumeP, specializareP, salariuP, nrPacientiP, pacientiP) {
			cout << "Constructor cu parametri clasa Chirurg" << endl;
			this->nrOreLucrate = nrOreLucrateP;
			this->varsta = varstaP;
		}

		Chirurg(const Chirurg& p) :Doctor(p) {
			this->nrOreLucrate = p.nrOreLucrate;
			this->varsta = p.varsta;
		}

		int getNrOreLucrate() {
			return this->nrOreLucrate;
		}

		void setNrOreLucrate(int nrOreLucrateN) {
			this->nrOreLucrate = nrOreLucrateN;
		}

		int getVarsta() {
			return this->varsta;
		}

		void setVarsta(int varstaN) {
			this->varsta = varstaN;
		}

		~Chirurg() {
			cout << "Destructor clasa Chirurg" << endl;
		}

		void afisareChirurg() {
			cout << "Nume: " << this->getNume() << endl;   
			cout << "Prenume: " << this->getPrenume() << endl;
			cout << "Specializare: " << this->getSpecializare() << endl;
			cout << "Salariu: " << this->getSalariu() << endl;
			cout << "Nr pacienti: " << this->getNrPacienti() << endl;
			for (int i = 0; i < this->getNrPacienti(); i++)
				cout << "Pacientul " << this->getPacienti()[i] << endl;
			cout << "Nr ore lucrate: " << this->getNrOreLucrate() << endl;
			cout << "Varsta: " << this->getVarsta() << endl;
		}
	};

	class Apendicita :public Operatie {
	protected:
		string gravitate;

	public:
		Apendicita() :Operatie() {
			cout << "Constructor fara parametri clasa Apendicita" << endl;
			this->gravitate = "Foarte grav" ; 
		}

	//	Apendicita(string dataP, int oraIncepereP, int nrChirurgiP, string* chirurgiP, int durataP, float pretOperatieP, string gravitateP) :Operatie (dataP, oraIncepereP, nrChirurgiP, chirurgiP, durataP, pretOperatieP) {
	//		cout << "Constructor cu parametri clasa Apendicita" << endl;
	//		this->gravitate = gravitateP;
	//	}

		Apendicita(const Apendicita& p) :Operatie(p) {
				this->gravitate = p.gravitate;
		}

		string getGravitate() {
				return this->gravitate;
		}




		~Apendicita() {
			cout << "Destructor clasa Apendicita" << endl;
		}

		void afisareApendicita() {
			cout << "Data: " << this->getData() << endl;  
			cout << "Ora incepere: " << this->getOraIncepere() << endl;
			cout << "Pretul operatiei: " << this->getPret() << endl;
			cout << "Durata: " << this->getDurata() << endl;
			cout << "Nr chirurgi: " << this->getNrChirurgi() << endl;
			for (int i = 0; i < this->getNrChirurgi(); i++)
				cout << "Chirurgul " << this->getChirurgi()[i] << endl;
			cout << "Gravitate: " << this->getGravitate() << endl;
		}

		void verifPret() {
			if (this->getPret() > 1000) cout << "Operatie scumpa" << endl;
			else cout << "Operatie ieftina" << endl;
		}
	};


	class Asistent { //clasa abstracta
	protected:
		string nume;
		float salariul;

	public:
		Asistent() {
			this->nume = "Ionescu Alexandru";
			this->salariul = 2000;
		}

		Asistent(string numeP, float salariulP) {
			this->nume = numeP;
			this->salariul = salariulP;
		}

		virtual void afisare() { //functie virtuala
			cout << "Asistentul " << this->nume << " are un salariu de " << this->salariul << " lei.\n";
		}

		virtual void getSalAsist() {  //functie virtual pura
			if (this->salariul < 1000) cout << "Salariu mic" << endl;
			else cout << "Salariu mare" << endl;
		}
	};


	class IMarireSalariu {
		virtual void maresteSalariu(int procent) = 0;
		virtual float getSalariu() = 0;
	};

	class Femeie : public Asistent, public IMarireSalariu {
	private:
		int varsta;

	public:
		Femeie() :Asistent() {
			this->varsta = 30;
		}

		Femeie(int varstaP, string numeP, float salariuP) :Asistent(numeP, salariuP) {
			this->varsta = varstaP;
		}

		void afisare() override {
			cout << "Asistentul " << this->nume << " are un salariu de " << this->salariul << " lei si varsta de " << this->varsta << " ani.\n";
		}

		void afisare(string mesaj) {
			cout << mesaj << endl;
		}

		void getSalAsist() {
			this->afisare();
		}

		float getSalariu() {
			return this->salariul;
		}

		void maresteSalariu(int procent) {
			this->salariul = (3 + (float)procent / 100) + this->salariul;
		}
	};


	class IndexOutOfBoundsException : public exception {
	public:
		virtual char* what() {
			char* iob = new char[strlen("Index in afara limitelor") + 1];
			strcpy(iob, "Index in afara limitelor");
			return iob;
		}
	};

	class NullPointerException : public exception {
	public:
		char* what() {
			char* np = new char[strlen("NullPointer - vectorul este gol") + 1];
			strcpy(np, "NullPointer - vectorul este gol");
			return np;
		}
	};

	class Spital {
	private:
		string denumire;
		int nrSali;
		string* sali;

	public:
		Spital() {
			this->denumire = "Floreasca";
			this->nrSali = 0;
			this->sali = NULL;
		}

		Spital(string denumireP, int nrSaliP, string* saliP) {
			this->denumire = denumireP;
			this->nrSali = nrSaliP;
			this->sali = new string[this->nrSali];
			for (int i = 0; i < this->nrSali; i++) {
				this->sali[i] = saliP[i];
			}
		}

		string& operator[](int index) {
			if (index < 0 || index >this->nrSali) {
				throw new IndexOutOfBoundsException();
			}
			else if (this->sali == NULL) {
				throw new NullPointerException();
			}
			else {
				return this->sali[index];
			}
		}

		friend ostream& operator<<(ostream& out, Spital& s) {
			out << s.denumire << " cu " << s.nrSali <<" sali "<< endl;
			for (int i = 0; i < s.nrSali; i++) {
				out << s.sali[i] << endl;
			}
			return out;
		}
	};



int main()
{
	
	/*
	Doctor d1;
	cout << "Apel constructor fara parametri" << endl;
	d1.afisare();

	cout << endl;
	cout << "Modificare salariu:" << endl;
	Doctor mo1;
	mo1.modificare();
	mo1.afisare();
	cout << endl;


	Doctor* d2;
	d2 = &d1;
	d2->afisare();

	Doctor* d3 = new Doctor();
	d3->afisare();

	
	//apel constructor cu parametri
	cout << "Apel constructor cu parametri" << endl;
	string nume = "Popescu";
	string prenume = "Alina";
	float salariu = 3000;
	string specializare = "Endocrinolog";
	int nrPacienti = 2;
	string* pacienti = new string[nrPacienti];
	for (int i = 0; i < nrPacienti; i++)
	{
		pacienti[i] = "Pacient " + to_string(i+10);
	}

	
	Doctor* d4 = new Doctor(nume, prenume, specializare, salariu, nrPacienti, pacienti);
	d4->afisare();

	//Doctor d5 (nume, prenume, salariu, specializare, nrPacienti, pacienti);
	//d5.afisare();

	delete d3;


	//apel setter vector pacienti
	cout << "Apel setter vector pacienti:" << endl;
	Doctor d5;
	int nrPacientiN = 4;
	string* vectorNouPacienti = new string[nrPacientiN];
	for (int i = 0; i < nrPacientiN; i++)
	{
		vectorNouPacienti[i] = "Pacient nou" + to_string(i + 100);
	}
	d5.setPacienti(vectorNouPacienti[1], nrPacientiN);
	d5.afisare();
	



	cout << "Id ul este: " << d1.getId() << endl;

	cout << "Numarul initial al doctorilor este: " << Doctor::getNrDoctori() << endl;
	
	Doctor::setNrDoctori(5);
	cout << "Numarul doctorilor este: " << Doctor::getNrDoctori() << endl;
	cout << endl;

	//apel 1 constructor de copiere
	Doctor d6 = d1;
	cout << "Apel constructor de copiere:" << endl;
	d6.afisare();

	//apel 2 costructor de copiere
	//Doctor d7(d6);
	//d7.afisare();

	

	//apel supraincarcare operator '='
	Doctor d8;
	cout << "Apel supraincarcare = " << endl;
	d8 = d1;
	d8.afisare();

	//apel supraincarcare <<
	Doctor d9;
	cout << "Apel supraincarcare '<<' : " << endl;
	cout << d9;
	cout << endl;

	//apel supraincarcare >>
	Doctor d10;
	cout << "Apel supraincarcare '>>' : " << endl;
	cin >> d10;
	cout << d10;
	cout << endl;

	//apel supraincarcare ==
	cout << "Apel supraincarcare ==" << endl;
	if (d1 == mo1)
		cout << "True";
	else cout << "False";
	cout << endl;

	//apel supraincarcare <=
	cout << "Apel supraincarcare <=" << endl;
	if (d1 <= d6)
		cout << "True";
	else cout << "False";
	cout << endl;








	Operatie o1;
	cout << "Apel constructor fara parametri:" <<endl;
	o1.afisare2();

	//apel supraincarcare =
	Operatie o2;
	cout << "Apel supraincarcare =" << endl;
	o2 = o1;
	o2.afisare2();

	//apel supraincarcare <<
	Operatie o3;
	cout << "Apel supraincarcare <<" << endl;
	cout << o3;
	cout << endl;

	//apel supraincarcare >>
	Operatie o4;
	cout << "Apel supraincarcare >>"<<endl;
	cin >> o4;
	cout << o4;
	cout << endl;

	//apel supraincarcare ==
	cout << "Apel supraincarcare ==" << endl;
	if (o1 == o2)
		cout << "True";
	else cout << "False";
	cout << endl;

	//apel supraincarcare !
	cout << "Apel supraincarcare operator !" << endl;
	if (!o1)
		cout << "True";
	else cout << "False";
	cout << endl;

	


	//Apel constructor fara parametri
	Medicament m1;
	m1.afisare3();

	//Apel constructor cu parametri
	cout << "Apel constructor cu parametri:" << endl;
	string denumireMedicament = "Nospa";
	float pretMedicament = 50;
	string administrare = "Intravenos";
	int nrComprimate = 3;
	string* comprimate = new string[nrComprimate];
	for (int i = 0; i < nrComprimate; i++)
		comprimate[i] = "Comprimatul " + to_string(i + 1);
	Medicament* m2 = new Medicament(denumireMedicament, pretMedicament, administrare, nrComprimate, comprimate);
	m2->afisare3();
	cout << endl;


	//Apel constructor de copiere
	Medicament m3 = m1;
	m3.afisare3();

	Medicament m4;
	m4.modif();
	cout << "Afisare dupa modificare:" << endl;
	m4.afisare3();

	//apel getter si setter
	cout << "Denumirea medicamentului m1 este: " << m1.getDenumireMedicament() << endl;
	string denumireMedicamentN = "Ibuprofen";
	m1.setDenumireMedicament(denumireMedicamentN);
	cout << "Noua denumire a medicamentului m1 este: " << m1.getDenumireMedicament() << endl;
	cout << endl;

	//apel supraincarcare =
	Medicament m5;
	cout << "Apel supraincarcare =" << endl;
	m5 = m1;
	m5.afisare3();
	cout << endl;

	//apel supraincarcare <<
	Medicament m6;
	cout << "Apel supraincarcare <<" << endl;
	cout << m6;
	cout << endl;

	//apel supraincarcare >>
	Medicament m7;
	cout << "Apel supraincarcare >>" << endl;
	cin >> m7;
	cout << m7;
	cout << endl;

	//apel supraincarcare ==
	cout << "Apel supraincarcare ==" << endl;
	if (m1 == m3)
		cout << "True";
	else cout << "False";
	cout << endl;

	//apel operator >=
	cout << "Apel operator >=" << endl;
	if (m1 >= m3)
		cout << "True";
	else cout << "False";
	cout << endl;

	//apel supraincarcare []
	try {
		cout << d1[5];
	}
	catch (exception * e) {
		cout << e->what() << endl;
		cout << "Exceptie prinsa 1" << endl;
	}
	catch (...) {
		cout << "Exceptie prinsa 2" << endl;
	}

	//apel operator cast
	cout << "Pretul este " << (float)o1 << endl;

	//apel operator +
	o1 = o1 + 5;
	cout << o1.getDurata() << endl;
	o1 = 6 + o1;
	cout << o1.getDurata() << endl;

	//apel operator+=
	o1 += 7;
	cout << o1.getDurata() << endl;

	//apel ++ 
	++d1;
	cout << m1;
	d1++;
	cout << m1;

	

	
	cout << "======================" << endl;
	Doctor d11;
	d11.afisare();

	cout << "======================" << endl;
	Chirurg c;
	c.afisareChirurg();

	cout << "======================" << endl;
	Operatie o5;
	o5.afisare2();

	cout << "======================" << endl;
	Apendicita ap;
	ap.afisareApendicita();

	cout << "======================" << endl;
	ap.verifPret();
	
	
	Asistent* as;

	Femeie f1;
	f1.afisare();
	f1.afisare("Afisare 2");
	Femeie f2(30, "Popescu", 3000);
	f2.afisare();
	f2.maresteSalariu(10);
	f2.afisare();

	string sali1[] = { "Sala de operatie","Terapie intensiva","Camera de garda" };
	string sali2[] = { "Sala de mese", "Camere" };

	Spital s1("Floreasca", 3, sali1);
	Spital s2;
	Spital s3("Sanador", 2, sali2);
	try {
		cout << s1[4];
		cout << s3[1];
		cout << s2[0];
	}
	catch (IndexOutOfBoundsException * ex1) {
		cout << ex1->what() << endl;
	}
	catch (NullPointerException * ex2) {
		cout << ex2->what() << endl;
	}
	catch (...) {
		cout << "Exceptie necunoscuta" << endl;
	}
	
	cout << "----------STL------string--------" << endl;
	string denumire = "Regina Maria";
	denumire = denumire + " etaj 2 ";
	cout << denumire << endl;

	denumire.append("... urmeaza etajul 3");
	cout << denumire << endl;
	cout << "Lungimea sirului este " << denumire.length() << " caractere" << endl;

	denumire = "Floreasca";
	cout << "nume.at(2)=" << denumire.at(2) << endl;
	cout << "nume.find('n')=" << denumire.find('a') << endl;
	cout << "nume.substr(0, 3)=" << denumire.substr(0, 3) << endl;

	cout << "----------STL------VECTOR--------" << endl;
	vector<string> saliNoi;
	saliNoi.push_back("Terapie intensiva");
	saliNoi.push_back("Sala de mese");
	saliNoi.push_back("Baie");
	for (int i = 0; i < saliNoi.size(); i++) {
		cout << saliNoi[i] << endl;
	}
	sort(saliNoi.begin(), saliNoi.end());
	cout << "iterator 1" << endl;

	vector<string>::iterator it;
	for (it = saliNoi.begin(); it != saliNoi.end(); it++) {
		cout << *it << endl;
	}
	cout << "iterator 2" << endl;
	saliNoi.pop_back();
	for (it = saliNoi.begin(); it != saliNoi.end(); it++) {
		cout << *it << endl;
	}

	cout << "----------STL------LISTA--------" << endl;
	list<float> lista; 
	lista.push_back(1.0f);
	lista.push_front(123.5f);
	lista.push_back(33.3f);
	lista.push_front(1.01f);

	cout << endl << "Afisare lista:" << endl;
	list<float>::iterator it2;
	for (it2 = lista.begin(); it2 != lista.end(); it2++) {
		cout << *it2 << endl;
	}
	cout << "Afisare lista dupa apel pop_front: " << endl;
	lista.pop_front();
	for (it2 = lista.begin(); it2 != lista.end(); it2++) {
		cout << *it2 << endl;
	}

	cout << "\nAfisare lista sortata: \n";
	lista.sort();
	for (it2 = lista.begin(); it2 != lista.end(); it2++) {
		cout << *it2 << endl;
	}

	cout << "\nAfisare lista invers: \n";
	lista.reverse();
	for (it2 = lista.begin(); it2 != lista.end(); it2++) {
		cout << *it2 << endl;
	}

	cout << "----------STL------SET--------" << endl;
	set<string> angajati;
	angajati.insert("Ion");
	angajati.insert("Vasile");
	angajati.insert("Irina");
	angajati.insert("Maria");
	cout << "Afisare angajati din set: " << endl;
	set<string>::iterator it3;
	for (it3 = angajati.begin(); it3 != angajati.end(); it3++) {
		cout << *it3 << endl;
	}
	cout << endl;
	it3 = angajati.find("Vasile");
	if (it3 != angajati.end()) {
		cout << "S-a gasit angajatul.\n";
	}
	else {
		cout << "Nu s-a gasit angajatul.\n";
	}

	cout << "----------STL------MAP--------" << endl;
	map<int, Spital> sp;
	sp.insert(make_pair(2017, s1));
	sp.insert(make_pair(2018, s2));
	sp.insert(make_pair(2019, s3));

	map<int, Spital>::iterator itMap;
	for (itMap = sp.begin(); itMap != sp.end(); itMap++) {
		cout << "In anul " << itMap->first << " s-a construit spitalul " << itMap->second << endl;
	}

	cout << "Apel map dupa cheie sp[2019] = " << endl << sp[2019];
	

	Doctor doc;
	cout << doc;

	//fisier text

	ofstream fileWrite;
	fileWrite.open("doc.txt", ios::out);
	fileWrite << doc;
	fileWrite.close();

	ifstream fileRead;
	fileRead.open("doc.txt", ios::in);
	Doctor doc1;
	fileRead >> doc1;
	cout << doc1;
	fileRead.close();

	//fisier binar

	ofstream fileWriteBin;
	fileWriteBin.open("doc_binar.dat", ios::binary | ios::out);
	fileWriteBin << doc;
	fileWriteBin.close();

	ifstream fileReadBin;
	fileReadBin.open("doc_binar.dat", ios::binary | ios::in);
	Doctor doc2;
	fileReadBin >> doc2;
	cout << doc2;
	fileReadBin.close();
	
	*/

	//MENIU
	
	Medicament med1;
	Medicament med2;
	

	int t = 100;
	while (t != 0) {
		cout << "Tasta= ";
		cin >> t;
		if (t == 1)
			cout << med1 << endl;
		if (t == 2) {
			cin >> med2;
			cout << med2 << endl;
		}
		if (t == 3) {
			break;
		}
	}


	return 0;
}