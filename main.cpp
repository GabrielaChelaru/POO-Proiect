/*
Cerinte comune tuturor temelor:

tratarea exceptiilor
utilizarea variabilelor și functiilor statice
utilizarea conceptelor de Dynamic_Cast și Static_Cast
utilizarea sabloanelor
citirea informațiilor complete a n obiecte, memorarea și afisarea acestora


cerinte generale aplicate fiecarei teme din acest fisier:
- să se identifice și să se implementeze ierarhia de clase;
- clasele sa conțină constructori, destructori, =, funcție prietena de
citire a datelor;
- clasa de baza sa conțină funcție virtuala de afisare, rescrisa în
clasele derivate;
- clasele derivate trebuie sa contina cel constructori parametrizati
prin care sa se evidentieze transmiterea parametrilor către
constructorul din clasa de baza.


Tema 1. Firma X are un domeniu de business unde este necesar să se urmărească modul în care clientii plătesc (numerar, cec sau card de credit).
 Indiferent de modul de plata, firma X știe în ce data s-a efectuat plata și ce suma a fost primita. Dacă se plătește cu cardul, atunci se cunoaște și numărul cardului de credit.
 Pentru cash, nu e necesara identificarea clientului care a făcut plata.

Cerinta suplimentara:
     - Sa se construiasca clasa template Gestiune care sa conțină numărul total de plati (incrementat  automat la adaugarea unei noi chitante)
      și un vector de pointeri la obiecte de tip Plata, alocat dinamic. Sa se supraincarce operatorul += pentru inserarea
unei plati în lista, indiferent de tipul acesteia.
- Sa se construiasca o specializare pentru tipul char* care sa stocheze numarul de clienti, impreuna cu numele acestora.

structura

-  abstract clasa Plata(data, suma)
-derivata numerar, cec(cnp), card de credit(cod)--fiecare derivata
--clasa templatee trebuie sa contina un vectori de pointeri la clasa Plata//vecator de tip typeid
*/

#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

class Plata {
protected:
    double suma_;
    int data_;
public:
    Plata();
    Plata(const double& suma, const int& data);// mai safe artificiu gasit pe net :)))
    Plata(const Plata& ob);
    ~Plata();

    double getSuma() const;
    void setSuma(const double& suma);

    virtual void afisare() const;

    Plata& operator=(const Plata& ob);

    friend istream& operator>>(istream &in, Plata& ob);
    friend ostream& operator<<(ostream &out, const Plata& ob);
};

Plata::Plata() {
    cout << "Constructor fara parametri pentru clasa Plata" << endl;
    suma_ = 0;
    data_ = 0;
}

Plata::Plata(const double& suma, const int& data) {
    cout << "Constructor cu doi parametri pentru clasa Plata" << endl;
    suma_ = suma;
    data_ = data;
}

Plata::Plata(const Plata& ob) {
    cout << "Constructor de copiere pentru clasa Plata" << endl;
    suma_ = ob.suma_;
    data_ = ob.data_;
}

Plata::~Plata() {
    cout << "Destructor pentru clasa Plata" << endl;
}

Plata& Plata::operator=(const Plata& ob) {
    if (&ob != this) {
        suma_ = ob.suma_;
        data_ = ob.data_;
    }
    return *this;
}

void Plata::setSuma(const double& suma) {
    suma_ = suma;
}

double Plata::getSuma() const {
    return suma_;
}

void Plata::afisare() const {
    cout << suma_ << " " << data_ << endl;
}

istream& operator>>(istream &in, Plata&ob) {
    in >> ob.suma_ >> ob.data_;
    return in;
}

ostream& operator<<(ostream &out, const Plata& ob) {
    ob.afisare();
    return out;
}





class Numerar : public Plata {

public:
    Numerar();
    Numerar(const double& suma, const int& data);
    Numerar(const Numerar& ob);
    ~Numerar();

    Numerar& operator=(const Numerar& ob);

    void afisare() const;// pentru ca sa nu se modifice varbiabilele din funtcite
    void afisareClient() const;
};

Numerar::Numerar() : Plata() {
    cout << "Constructor fara parametri pentru clasa Numerar" << endl;
}

Numerar::Numerar(const double& suma, const int& data) : Plata(suma, data) {
    cout << "Constructor cu parametri pentru clasa Numerar" << endl;
}

Numerar::Numerar(const Numerar& ob) : Plata(ob) {
    cout << "Constructor de copiere pentru clasa Plata" << endl;
}

Numerar::~Numerar() {
    cout << "Destructor pentru clasa Numerar" << endl;
}

Numerar& Numerar::operator=(const Numerar& ob) {
    if (&ob != this) {
        suma_ = ob.suma_;
        data_ = ob.data_;
    }
    return *this;
}

void Numerar::afisare() const {
    cout << suma_ << " " << data_ << endl;
}

void Numerar::afisareClient() const {
    cout << "Pentru plata numerar, clientul nu poate fi identificat" << endl;
}





class Cec : public Plata {
    int cnp_[13];
public:
    Cec();
    Cec(const double& suma, const int& data, int cnp[13]);
    Cec(const Cec& ob);
    ~Cec();

    Cec& operator=(const Cec& ob);

    void afisare() const;
    void afisareClient() const;
};

Cec::Cec() : Plata() {
    cout << "Constructor fara parametri pentru clasa Cec" << endl;
    for (int i = 0; i < 13; i++)
        cnp_[i] = 0;
}

Cec::Cec(const double& suma, const int& data, int* cnp) : Plata(suma, data) {
    cout << "Constructor cu parametri pentru clasa Cec" << endl;
    for(int i = 0; i < 13; i++)
        cnp_[i] = cnp[i];
}

Cec::Cec(const Cec& ob) : Plata(ob) {
    cout << "Constructor de copiere pentru clasa Cec" << endl;
    for (int i = 0; i < 13; i++)
        cnp_[i] = ob.cnp_[i];
}

Cec::~Cec() {
    cout << "Destructor pentru clasa Cec" << endl;
}

Cec& Cec::operator=(const Cec& ob) {
    if (&ob != this) {
        suma_ = ob.suma_;
        data_ = ob.data_;
        for (int i = 0; i < 13; ++i)
            cnp_[i] = ob.cnp_[i];//strcpy
    }
    return *this;
}

void Cec::afisare() const {
    for (int i = 0; i < 13; ++i)
        cout << cnp_[i];
    cout << " " << suma_ << " " << data_ << endl;
}

void Cec::afisareClient() const {
    cout << "Plata prin cec. CNP-ul clientului este: ";
    for (int i = 0; i < 13; ++i)
        cout << cnp_[i];
    cout << endl;
}




class Card : public Plata {
    int cod_[6];
public:
    Card();
    Card(const double& suma, const int& data, int cod[6]);
    Card(const Card& ob);
    ~Card();

    Card& operator=(const Card& ob);

    void afisare() const;
    void afisareClient() const;
};


Card::Card():Plata() {
    cout << "Constructor fara parametri pentru clasa Card" << endl;
    for (int i = 0; i < 6; i++)
        cod_[i] = 0;
}

Card::Card(const double& suma, const int& data, int cod[6]) : Plata(suma, data) {
    cout << "Constructor cu parametri pentru clasa Card" << endl;
    for(int i = 0; i < 6; i++)
        cod_[i] = cod[i];
}

Card::Card(const Card& ob) : Plata(ob) {
    cout << "Constructor de copiere pentru clasa Card" << endl;
    for(int i = 0; i < 6; i++)
        cod_[i] = ob.cod_[i];
}

Card::~Card() {
    cout << "Destructor pentru clasa Card" << endl;

}

Card& Card::operator=(const Card& ob) {
    if (&ob != this) {
        suma_ = ob.suma_;
        data_ = ob.data_;
        for (int i = 0; i < 6; ++i)
            cod_[i] = ob.cod_[i];
    }
    return *this;
}

void Card::afisare() const {
    for (int i = 0; i < 6; ++i)
        cout << cod_[i];
    cout << " " << suma_ << " " << data_ << endl;
}

void Card::afisareClient() const {
    cout << "Plata cu cardul. Codul cardului este: ";
    for (int i = 0; i < 6; ++i)
        cout << cod_[i];
    cout << endl;
}

template <class T>
class Gestiune {
    static int numarPlati_;
    Plata** plati_;
public:
    Gestiune();
    ~Gestiune();

    static int getNumarPlati();

    void operator+=(Plata* ob);

    void afisare() const;
    void afisareClienti() const;
};

template <class T>
Gestiune<T>::Gestiune() {
    plati_ = NULL;
}

template <class T>
Gestiune<T>::~Gestiune() {
    delete[] plati_;//delete la toti pointerii
}

template <class T>
int Gestiune<T>::getNumarPlati() {
    return numarPlati_;
}

template <class T>
void Gestiune<T>::operator+=(Plata* ob) {
    Plata** tempPlati = new Plata*[numarPlati_];
    for (int i = 0; i < numarPlati_; ++i)
        tempPlati[i] = plati_[i];
    delete[] plati_;

    ++numarPlati_;
    plati_ = new Plata*[numarPlati_];
    for (int i = 0; i < numarPlati_ - 1; ++i)
        plati_[i] = tempPlati[i];
    plati_[numarPlati_ - 1] = ob;
}

template <class T>
void Gestiune<T>::afisare() const {
    for (int i = 0; i < numarPlati_; ++i)//afiseaza nume suma data
        cout << *plati_[i];
}

template <class T>
void Gestiune<T>::afisareClienti() const { //afiseaza numai numele sau cnp sau cod
    for (int i = 0; i < numarPlati_; ++i) {
        Numerar* clientNumerar = dynamic_cast<Numerar*>(plati_[i]);// pointer la clasa de baza, converteste catre derivata// daca e numerar returneaza daca nu null
        Cec* clientCec = dynamic_cast<Cec*>(plati_[i]);
        Card* clientCard = dynamic_cast<Card*>(plati_[i]);

        if (clientNumerar)
            clientNumerar->afisareClient();
        if (clientCec)
            clientCec->afisareClient();
        if (clientCard)
            clientCard->afisareClient();
    }
}

template <>
class Gestiune<char*> {
    static int numarClienti_;//numarul ramane acelasi si poate fi modificat in toate instantele
    char** nume_;
public:
    Gestiune();
    ~Gestiune();

    static int getNumarClienti();

    void operator+=(char* nume);

    void afisare() const;
};

Gestiune<char*>::Gestiune() {
    nume_ = NULL;
}

Gestiune<char*>::~Gestiune() {
    for (int i = 0; i < numarClienti_; ++i)
        delete[] nume_[i];
    delete[] nume_;
}
int Gestiune<char*>::getNumarClienti() {
    return numarClienti_;
}

void Gestiune<char*>::operator+=(char* nume) {//coiaza salveaza, realcoca mai mult spatiu si copiaza iar apoi adauga urm elem
    char** tempNume = new char*[numarClienti_];//vector temporar si copiaza in din vectorul nume
    for (int i = 0; i < numarClienti_; ++i) {
        tempNume[i] = new char[strlen(nume_[i])];
        strcpy(tempNume[i], nume_[i]);// il copiaza
        delete[] nume_[i];//il sterge de tot
    }
    delete[] nume_;

    ++numarClienti_;
    nume_ = new char*[numarClienti_];
    for (int i = 0; i < numarClienti_ - 1; ++i) {
        nume_[i] = new char[strlen(tempNume[i])];
        strcpy(nume_[i], tempNume[i]);
    }
    nume_[numarClienti_ - 1] = new char[strlen(nume)];
    strcpy(nume_[numarClienti_ - 1], nume);
    //aloca din nou, salveaza cel sters si adauga numele nou
}

void Gestiune<char*>::afisare() const {
    for (int i = 0; i < numarClienti_; ++i)
        cout << nume_[i] << endl;
}

template<class T>
int Gestiune<T>::numarPlati_ = 0;//intializare valori statice

int Gestiune<char *>::numarClienti_ = 0;//si aici

int main() {
    {
        int n;
        Gestiune<int> gestiune;

        cout << "introduceti numarul de persoane" << endl;
        cin >> n;
        assert(n > 0);

        cout << "alegeti metodat de plata" << endl;
        for (int i = 0; i < n; ++i) {
            Plata *plata;

            cout << "Numerar: 1" << endl;
            cout << "Cec: 2" << endl;
            cout << "Card: 3" << endl;
            int op;
            cin >> op;
            assert(op >= 1 && op <= 3);//verifica conditia daca e fals inchide programul si afiseaza unde e eroarea

            double suma;
            int data;
            char sir[100];
            switch (op) {
                case 1:
                    cout << "introduceti suma" << endl;
                    cin >> suma;
                    cout << "introduceti data" << endl;
                    cin >> data;
                    assert(data > 0 && data <= 31);
                    plata = new Numerar(suma, data);
                    gestiune += plata;
                    break;
                case 2:
                    cout << "introduceti cnp" << endl;
                    cin >> sir;
                    try {
                        if (strlen(sir) != 13)
                            throw -1;
                    }
                    catch (int e) {
                        cout << "CNP-ul dat nu are 13 cifre!" << endl;
                        return 0;
                    }

                    int cnp[13];
                    for (int i = 0; i < 13; ++i)
                        cnp[i] = sir[i] - '0';

                    assert(cnp[0] >= 1 && cnp[0] <= 4);//cnp incepe cu 1 2 3 sau 4

                    cout << "introduceti suma" << endl;
                    cin >> suma;
                    cout << "introduceti data" << endl;
                    cin >> data;
                    assert(data > 0 && data <= 31);
                    plata = new Cec(suma, data, cnp);
                    gestiune += plata;
                    break;
                case 3:
                    cout << "introduceti cod" << endl;
                    cin >> sir;
                    try {
                        if (strlen(sir) != 6) {
                            throw -1;
                        }
                    }
                    catch (int e) {
                        cout << "Codul citit nu are 6 cifre" << endl;
                        return 0;
                    }

                    int cod[6];
                    for (int i = 0; i < 6; ++i) {
                        cod[i] = sir[i] - '0';
                    }

                    cout << "introduceti suma" << endl;
                    cin >> suma;
                    cout << "introduceti data" << endl;
                    cin >> data;
                    assert(data > 0 && data <= 31);
                    plata = new Card(suma, data, cod);
                    gestiune += plata;
                    break;
            }
        }

        cout << gestiune.getNumarPlati() << endl;
        gestiune.afisare();
        gestiune.afisareClienti();
    }



    {
        cout << "urmeaza specializarea in care o sa se aiseaze si numele persoaneleor introduse"<<endl;
        int n;
        Gestiune<char *> gestiune;

        cout << "introduceti numarul de persoane" << endl;
        cin >> n;
        assert(n > 0);

        cout << "alegeti metoda de plata" << endl;
        for (int i = 0; i < n; ++i) {
            Plata *plata;

            cout << "Numerar: 1" << endl;
            cout << "Cec: 2" << endl;
            cout << "Card: 3" << endl;
            int op;
            cin >> op;
            assert(op >= 1 && op <= 3);

            double suma;
            int data;
            char nume[100], sir[100];
            switch (op) {
                case 1:
                    cout << "introduceti nume" << endl;
                    cin >> nume;
                    cout << "introduceti suma" << endl;
                    cin >> suma;
                    cout << "introduceti data" << endl;
                    cin >> data;
                    assert(data > 0 && data <= 31);
                    plata = new Numerar(suma, data);
                    gestiune += nume;
                    break;
                case 2:
                    cout << "introduceti nume" << endl;
                    cin >> nume;
                    cout << "introduceti cnp" << endl;
                    cin >> sir;
                    try {
                        if (strlen(sir) != 13)
                            throw -1;
                    }
                    catch (int e) {
                        cout << "CNP-ul dat nu are 13 cifre!" << endl;
                        return 0;
                    }

                    int cnp[13];
                    for (int i = 0; i < 13; ++i)
                        cnp[i] = sir[i] - '0';

                    assert(cnp[0] >= 1 && cnp[0] <= 4);


                    cout << "introduceti suma" << endl;
                    cin >> suma;
                    cout << "introduceti data" << endl;
                    cin >> data;
                    assert(data > 0 && data <= 31);
                    plata = new Cec(suma, data, cnp);
                    gestiune += nume;
                    break;
                case 3:
                    cout << "introduceti nume" << endl;
                    cin >> nume;
                    cout << "introduceti cod" << endl;
                    cin >> sir;
                    try {
                        if (strlen(sir) != 6) {
                            throw -1;
                        }
                    }
                    catch (int e) {
                        cout << "Codul citit nu are 6 cifre" << endl;
                        return 0;
                    }

                    int cod[6];
                    for (int i = 0; i < 6; ++i) {
                        cod[i] = sir[i] - '0';
                    }

                    cout << "introduceti suma" << endl;
                    cin >> suma;
                    cout << "introduceti data" << endl;
                    cin >> data;
                    assert(data > 0 && data <= 31);
                    plata = new Card(suma, data, cod);
                    gestiune += nume;
                    break;
            }
        }

        cout << gestiune.getNumarClienti() << endl;
        gestiune.afisare();


        return 0;
    }
}
