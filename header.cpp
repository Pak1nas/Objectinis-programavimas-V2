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

Student::Student ( const string& v, const string& p, const vector<double>& nd, double egz ) : vardas_ ( v ), pavarde_ ( p ), nd_ ( nd ), egz_ ( egz ), vid_ ( 0 ), med_ ( 0 ) {}

Student::Student ( const Student& other ) : vardas_ ( other.vardas_ ), pavarde_ ( other.pavarde_ ), nd_ ( other.nd_ ), egz_ ( other.egz_ ), vid_ ( other.vid_ ), med_ ( other.med_ ) {}

Student::Student ( Student&& other ) noexcept : vardas_ ( move ( other.vardas_ ) ), pavarde_ ( move ( other.pavarde_ ) ), nd_ ( move ( other.nd_ ) ), egz_ ( other.egz_ ), vid_ ( other.vid_ ), med_ ( other.med_ ) {}

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

ostream& operator<< ( ostream& os, const Student& s )
{
    os << left << setw ( 15 ) << s.pavarde_ << left << setw ( 15 ) << s.vardas_ << right << setw ( 10 ) << fixed << setprecision ( 2 ) << s.vid_ << right << setw ( 10 ) << fixed << setprecision ( 2 ) << s.med_;
    return os;
}

istream& operator>> ( istream& is, Student& s )
{
    int ndk;
    is >> s.vardas_ >> s.pavarde_ >> ndk;

    s.nd_.clear();

    for ( int i = 0; i < ndk; i++ )
    {
        double x;
        is >> x;
        s.nd_.push_back ( x );
    }

    is >> s.egz_;
    s.skaiciuoti();
    return is;
}
