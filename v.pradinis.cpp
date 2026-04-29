#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <ctime>
#include "header.h"

using namespace std;

int main()
{
    srand ( time ( NULL ) );
    cin.exceptions ( ios::failbit | ios::badbit );

    vector<Student> A;

    while ( true )
    {
        cout << "1 - Rankinis studentu ivedimas" << endl;
        cout << "2 - Generuoti tik pazymius" << endl;
        cout << "3 - Generuoti vardus, pavardes ir pazymius" << endl;
        cout << "4 - Skaityti is failo" << endl;
        cout << "5 - Baigti darba" << endl;
        cout << "6 - Generuoti mokiniu faila" << endl;
        cout << "Pasirinkite: " << endl;

        int pasirinkimas = s_int();

        if ( pasirinkimas == 5 )
        {
            cout << "Programa baigta." << endl;
            break;
        }

        if ( pasirinkimas == 1 )
        {
            string v, p;
            cout << "Iveskite varda ir pavarde: ";
            cin >> v >> p;

            vector<double> nd;
            cout << "Iveskite namu darbu rezultatus (neigiamas skaicius baigia):" << endl;

            while ( true )
            {
                double x = s_double();

                if ( x < 0 ) break;

                nd.push_back ( x );
            }

            cout << "Egzamino rezultatas: ";
            double egz = s_double();

            Student s ( v, p, nd, egz );
            s.skaiciuoti();
            A.push_back ( s );
        }

        else if ( pasirinkimas == 2 )
        {
            string v, p;
            cout << "Iveskite varda ir pavarde: ";
            cin >> v >> p;

            cout << "Kiek generuoti namu darbu? ";
            int ndk = s_int();

            vector<double> nd;

            for ( int i = 0; i < ndk; i++ )
                nd.push_back ( atsitiktinis() );

            double egz = atsitiktinis();

            Student s ( v, p, nd, egz );
            s.skaiciuoti();
            A.push_back ( s );
        }

        else if ( pasirinkimas == 3 )
        {
            static vector<string> vardai = {"Mykolas", "Darius", "Motejus", "Nojus", "Jonas"};
            static vector<string> pavardes = {"Matulis", "Navierauskas", "Motejunas", "Stankus", "Mezetis"};

            string v = vardai[rand() % vardai.size()];
            string p = pavardes[rand() % pavardes.size()];

            int ndk = rand() % 7 + 3;
            vector<double> nd;

            for ( int i = 0; i < ndk; i++ )
                nd.push_back ( atsitiktinis() );

            double egz = atsitiktinis();

            Student s ( v, p, nd, egz );
            s.skaiciuoti();
            A.push_back ( s );
        }

        else if ( pasirinkimas == 4 )
        {
            ifstream duom ( "kursiokai.txt" );

            if ( !duom )
            {
                cout << "Nepavyko atidaryti failo." << endl;
                continue;
            }

            string eil;
            getline ( duom, eil );

            while ( getline ( duom, eil ) )
            {
                if ( eil.find_first_not_of ( " \t\r\n" ) == string::npos ) continue;

                istringstream ars ( eil );
                string v, p;

                if ( ! ( ars >> v >> p ) ) continue;

                vector<double> vals;
                double x;

                while ( ars >> x ) vals.push_back ( x );

                if ( vals.empty() ) continue;

                double egz = vals.back();
                vals.pop_back();

                Student s ( v, p, vals, egz );
                s.skaiciuoti();
                A.push_back ( s );
            }

            cout << "Faile buvo rasta: " << A.size() << " studentu" << endl;
        }

        else if ( pasirinkimas == 6 )
        {
            cout << "Kiek mokiniu norite, kad butu faile? ";
            int mok = s_int();
            cout << "Kiek pazymiu kiekvienam? ";
            int paz = s_int();
            generuoti_studentus ( mok, paz );
        }

        else
        {
            cout << "Neteisingas pasirinkimas." << endl;
        }
    }

    cout << "1 - Rusiavimas pagal varda" << endl;
    cout << "2 - Rusiavimas pagal pavarde" << endl;
    cout << "3 - Rusiavimas pagal galutini (vidurki)" << endl;
    cout << "4 - Rusiavimas pagal galutini (mediana)" << endl;
    cout << "Pasirinkite: " << endl;

    int rus = s_int();

    switch ( rus )
    {
    case 1:
        sort ( A.begin(), A.end(), [] ( const Student & a, const Student & b )
        {
            return a.vardas() < b.vardas();
        } );
        break;

    case 2:
        sort ( A.begin(), A.end(), [] ( const Student & a, const Student & b )
        {
            return a.pavarde() < b.pavarde();
        } );
        break;

    case 3:
        sort ( A.begin(), A.end(), [] ( const Student & a, const Student & b )
        {
            return a.vid() > b.vid();
        } );
        break;

    case 4:
        sort ( A.begin(), A.end(), [] ( const Student & a, const Student & b )
        {
            return a.med() > b.med();
        } );
        break;
    }

    cout << "Kaip norite isvesti duomenis?" << endl;
    cout << "1 - Tik ekrane" << endl;
    cout << "2 - Tik faile" << endl;
    cout << "3 - Ekrane ir faile" << endl;
    cout << "Pasirinkite: " << endl;

    int pas = s_int();
    spausdinti_lentele ( A, pas );

    return 0;
}
