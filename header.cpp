#include "header.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

//sukuriamas tuscias studentas
Student::Student() : zmogus("", ""), egz_ ( 0 ), vid_ ( 0 ), med_ ( 0 ) {}
//inicializuojami paveldeti zmogus ir studentas laukai
Student::Student ( const string& v, const string& p, const Vector<double>& nd, double egz ) : zmogus(v, p), nd_ ( nd ), egz_ ( egz ), vid_ ( 0 ), med_ ( 0 ) {}
//copy konstruktorius
Student::Student ( const Student& other ) : zmogus(other.vardas_, other.pavarde_), nd_ ( other.nd_ ), egz_ ( other.egz_ ), vid_ ( other.vid_ ), med_ ( other.med_ ) {}
//move konstruktorius
Student::Student ( Student&& other ) noexcept : zmogus(other.vardas_, other.pavarde_), nd_ ( move ( other.nd_ ) ), egz_ ( other.egz_ ), vid_ ( other.vid_ ), med_ ( other.med_ ) {}

void Student::printInfo() const {
    std::cout << pavarde_ << " " << vardas_ << " Vid: " << vid_ << " Med: " << med_ << std::endl;
}

//Kopijuoja visus laukus
Student& Student::operator= ( const Student& other )
{
    if ( this != &other )
    {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        nd_ = other.nd_;
        egz_ = other.egz_;
        vid_ = other.vid_;
        med_ = other.med_;
    }

    return *this;
}
//Perkeliamas nd vektorius
Student& Student::operator= ( Student&& other ) noexcept
{
    if ( this != &other )
    {
        vardas_ = move ( other.vardas_ );
        pavarde_ = move ( other.pavarde_ );
        nd_ = move ( other.nd_ );
        egz_ = other.egz_;
        vid_ = other.vid_;
        med_ = other.med_;
    }

    return *this;
}

Student::~Student() {}


//vidurkio/medianos skaiciavimas
void Student::skaiciuoti()
{
    double sum = egz_;

    for ( double x : nd_ ) sum += x;

    vid_ = sum / ( nd_.size() + 1 );

    sort ( nd_.begin(), nd_.end() );
    int d = nd_.size();

    if ( d % 2 == 0 )
        med_ = ( nd_[d / 2] + nd_[d / 2 - 1] ) / 2.0;
    else
        med_ = nd_[d / 2];
}

double Student::vid() const{return vid_;}
double Student::med() const{return med_;}

//suformuoja lentele isvesties operatoriui
std::ostream& operator<<(std::ostream& os, const Student& s)
{
    os << std::left << std::setw(15) << s.pavarde_<< std::left << std::setw(15) << s.vardas_<< std::right << std::setw(20) << std::fixed << std::setprecision(2) << s.vid_<< std::right << std::setw(20) << std::fixed << std::setprecision(2) << s.med_;
    return os;
}
//skaito varda pavarde nd ir egzamina
std::istream& operator>>(std::istream& is, Student& s){
    s.nd_.clear();

    std::string v, p;

    if(!(is>>v>>p))
        return is;

    if(v=="Vardas" && p=="Pavarde"){
        string siuksle;
        getline(is, siuksle);
        return operator>>(is, s);
    }

    s.vardas_=v;
    s.pavarde_=p;

    string line;
    getline(is, line);

    istringstream ss(line);
    Vector<double>temp;
    double x;

    while (ss>>x)
        temp.push_back(x);

    if(temp.empty())
        return is;

    s.egz_=temp.back();
    temp.pop_back();

    s.nd_=temp;

    s.skaiciuoti();

    return is;
}

//saugus ivedimas int ir double
int s_int()
{
    while ( true )
    {
        try
        {
            int x;
            cin >> x;
            return x;
        }
        catch ( ... )
        {
            cin.clear();
            string k;
            getline ( cin, k );
            cout << "Klaida: iveskite skaiciu" << endl;
        }
    }
}

double s_double()
{
    while ( true )
    {
        try
        {
            double x;
            cin >> x;
            return x;
        }
        catch ( ... )
        {
            cin.clear();
            string k;
            getline ( cin, k );
            cout << "Klaida: iveskite skaiciu" << endl;
        }
    }
}
//pazymiu generavimas
int atsitiktinis()
{
    return rand() % 11;
}
//Spausdinimas i fila / ekrana
void spausdinti_lentele ( const Vector<Student>& A, int pas )
{
    ofstream kiet ( "kietekai.txt" );
    ofstream varg ( "vargsiukai.txt" );

    if ( pas == 1 || pas == 3 )
    {
        cout << left << setw(15) << "Pavarde" << left << setw(15) << "Vardas"<< right << setw(15) << "Vidurkis" << right << setw(15) << "Mediana" << endl;
        cout << string ( 70, '-' ) << endl;
    }

    if ( pas == 2 || pas == 3 )
    {
        kiet << left << setw(15) << "Pavarde" << left << setw(15) << "Vardas"<< right << setw(15) << "Vidurkis" << right << setw(15) << "Mediana" << endl;
        varg << left << setw(15) << "Pavarde" << left << setw(15) << "Vardas"<< right << setw(15) << "Vidurkis" << right << setw(15) << "Mediana" << endl;
    }

    for ( const auto& s : A )
    {
        if ( pas == 1 || pas == 3 )
        {
            cout << s << endl;
        }

        if ( s.vid() >= 5 )
            kiet << s << endl;
        else
            varg << s << endl;
    }
}

//Duomenu generavimas
void generuoti_studentus ( int kiekismok, int kiekpaz )
{
    ofstream is ( "kursiokai.txt" );

    is << "Vardas Pavarde";

    for ( int i = 1; i <= kiekpaz; i++ )
        is << " ND" << i;

    is << " Egz." << endl;

    for ( int i = 1; i <= kiekismok; ++i )
    {
        is << "Vardas" << i << " Pavarde" << i;

        for ( int j = 0; j < kiekpaz; ++j )
            is << " " << atsitiktinis();

        is << " " << atsitiktinis() << endl;
    }
}
