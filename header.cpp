#include "header.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

Student::Student() : egz_ ( 0 ), vid_ ( 0 ), med_ ( 0 ) {}

Student::Student ( const string& v, const string& p, const vector<double>& nd, double egz )
    : vardas_ ( v ), pavarde_ ( p ), nd_ ( nd ), egz_ ( egz ), vid_ ( 0 ), med_ ( 0 ) {}

Student::Student ( const Student& other )
    : vardas_ ( other.vardas_ ), pavarde_ ( other.pavarde_ ),
      nd_ ( other.nd_ ), egz_ ( other.egz_ ), vid_ ( other.vid_ ), med_ ( other.med_ ) {}

Student::Student ( Student&& other ) noexcept
    : vardas_ ( move ( other.vardas_ ) ), pavarde_ ( move ( other.pavarde_ ) ),
      nd_ ( move ( other.nd_ ) ), egz_ ( other.egz_ ), vid_ ( other.vid_ ), med_ ( other.med_ ) {}

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

void Student::setVardas ( const string& v )
{
    vardas_ = v;
}
void Student::setPavarde ( const string& p )
{
    pavarde_ = p;
}
void Student::addNd ( double x )
{
    nd_.push_back ( x );
}
void Student::setEgz ( double x )
{
    egz_ = x;
}

const string& Student::vardas() const
{
    return vardas_;
}
const string& Student::pavarde() const
{
    return pavarde_;
}
double Student::vid() const
{
    return vid_;
}
double Student::med() const
{
    return med_;
}

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

int atsitiktinis()
{
    return rand() % 11;
}

void spausdinti_lentele ( const vector<Student>& A, int pas )
{
    ofstream kiet ( "kietekai.txt" );
    ofstream varg ( "vargsiukai.txt" );

    if ( pas == 1 || pas == 3 )
    {
        cout << endl << left << setw ( 15 ) << "Pavarde" << left << setw ( 15 ) << "Vardas" << right << setw ( 20 ) << "Galutinis (Vid.)" << right << setw ( 20 ) << "Galutinis (Med.)" << endl;
        cout << string ( 70, '-' ) << endl;
    }

    if ( pas == 2 || pas == 3 )
    {
        kiet << left << setw ( 15 ) << "Pavarde" << left << setw ( 15 ) << "Vardas" << right << setw ( 20 ) << "Galutinis (Vid.)" << right << setw ( 20 ) << "Galutinis (Med.)" << endl << string ( 70, '-' ) << endl;

        varg << left << setw ( 15 ) << "Pavarde" << left << setw ( 15 ) << "Vardas" << right << setw ( 20 ) << "Galutinis (Vid.)" << right << setw ( 20 ) << "Galutinis (Med.)" << endl << string ( 70, '-' ) << endl;
    }

    for ( const auto& s : A )
    {
        if ( pas == 1 || pas == 3 )
        {
            cout << left << setw ( 15 ) << s.pavarde() << left << setw ( 15 ) << s.vardas() << right << setw ( 20 ) << fixed << setprecision ( 2 ) << s.vid() << right << setw ( 20 ) << fixed << setprecision ( 2 ) << s.med() << endl;
        }

        if ( s.vid() >= 5 )
            kiet << left << setw ( 15 ) << s.pavarde() << left << setw ( 15 ) << s.vardas() << right << setw ( 20 ) << fixed << setprecision ( 2 ) << s.vid() << right << setw ( 20 ) << fixed << setprecision ( 2 ) << s.med() << endl;
        else
            varg << left << setw ( 15 ) << s.pavarde() << left << setw ( 15 ) << s.vardas() << right << setw ( 20 ) << fixed << setprecision ( 2 ) << s.vid() << right << setw ( 20 ) << fixed << setprecision ( 2 ) << s.med() << endl;
    }
}

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
