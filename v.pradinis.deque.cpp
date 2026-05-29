#include "header.h"
#include <chrono>

int main()
{

    auto start = chrono::high_resolution_clock::now();

    srand ( time ( NULL ) );
    cin.exceptions ( ios::failbit | ios::badbit );

    deque<stud> A;
    deque<stud> varg;
    deque<stud> kiet;

    while ( true )
    {
        cout << "1-Rankinis studentu ivedimas" << endl << "2-Generuoti tik pazymius" << endl << "3-Generuoti vardus, pavardes ir pazymius" << endl << "4-Skaityti is failo" << endl << "5-Baigti darba" << endl << "6-Generuoti mokiniu fila" << endl << "Pasirinkite:" << endl;

        int pasirinkimas = s_int();

        if ( pasirinkimas == 5 ) break;

        if ( pasirinkimas == 1 )
        {
            stud s;
            cout << "Iveskite varda ir pavarde:" << endl;
            cin >> s.vardas >> s.pavarde;

            cout << "Iveskite namu darbus (neigiamas baigia):" << endl;

            while ( true )
            {
                double x = s_double();

                if ( x < 0 ) break;

                s.tarp.push_back ( x );
            }

            cout << "Egzamino rezultatas:" << endl;
            s.egz = s_double();

            skaiciuoti ( s );
            A.push_back ( s );
        }

        else if ( pasirinkimas == 2 )
        {
            stud s;
            cout << "Iveskite varda ir pavarde:" << endl;
            cin >> s.vardas >> s.pavarde;

            cout << "Kiek generuoti namu darbu?" << endl;
            int nd = s_int();

            for ( int i = 0; i < nd; i++ )
                s.tarp.push_back ( atsitiktinis() );

            s.egz = atsitiktinis();
            skaiciuoti ( s );
            A.push_back ( s );
        }

        else if ( pasirinkimas == 3 )
        {
            stud s;

            static deque<string> vardai = {"Mykolas", "Darius", "Motejus", "Nojus", "Jonas"};
            static deque<string> pavardes = {"Matulis", "Navierauskas", "Motejunas", "Stankus", "Mezetis"};

            s.vardas = vardai[rand() % vardai.size()];
            s.pavarde = pavardes[rand() % pavardes.size()];

            int nd = rand() % 7 + 3;

            for ( int i = 0; i < nd; i++ )
                s.tarp.push_back ( atsitiktinis() );

            s.egz = atsitiktinis();
            skaiciuoti ( s );
            A.push_back ( s );
        }

        else if ( pasirinkimas == 4 )
        {
            ifstream duom ( "kursiokai.txt" );

            if ( !duom )
            {
                cout << "Nepavyko atidaryti failo" << endl;
                continue;
            }

            string eil;
            getline ( duom, eil ); // header

            while ( getline ( duom, eil ) )
            {
                if ( eil.empty() ) continue;

                istringstream ars ( eil );
                stud s;

                if ( ! ( ars >> s.vardas >> s.pavarde ) ) continue;

                deque<double> vals;
                double v;

                while ( ars >> v ) vals.push_back ( v );

                if ( !vals.empty() )
                {
                    s.egz = vals.back();
                    vals.pop_back();
                    s.tarp = vals;
                }

                skaiciuoti ( s );
                A.push_back ( s );
            }
        }

        else if ( pasirinkimas == 6 )
        {
            cout << "Kiek mokiniu?" << endl;
            int m = s_int();
            cout << "Kiek pazymiu?" << endl;
            int p = s_int();
            generuoti_studentus ( m, p );
        }
    }

    cout << "Strategija:" << endl << "1-Strategija 1" << endl << "2-Strategija 2" <<endl<<"3-Strategija 3"<< endl<<"Pasirinkite viena"<<endl;

    int pass=s_int();

    cout << "Rusiavimas:" << endl << "1 - pagal varda" << endl << "2 - pagal pavarde" << endl << "3 - pagal vidurki" << endl << "4 - pagal mediana" << endl;

    int rus = s_int();



    switch ( rus )
    {
    case 1:
        sort ( A.begin(), A.end(), [] ( const stud & a, const stud & b )
        {
            return a.vardas < b.vardas;
        } );
        break;

    case 2:
        sort ( A.begin(), A.end(), [] ( const stud & a, const stud & b )
        {
            return a.pavarde < b.pavarde;
        } );
        break;

    case 3:
        sort ( A.begin(), A.end(), [] ( const stud & a, const stud & b )
        {
            return a.vid > b.vid;
        } );
        break;

    case 4:
        sort ( A.begin(), A.end(), [] ( const stud & a, const stud & b )
        {
            return a.med > b.med;
        } );
        break;
    }
    skaidymas(A, varg, kiet, pass);

    cout << "Isvedimas: " << endl<<"1 - tik i ekranas" << endl<<"2 - tik i failas" << endl << "3 - Faila ir ekrana" << endl;
    int pas = s_int();

    spausdinti_lentele ( A, pas, pass);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;

    cout << "Programos veikimo laikas: " << diff.count() << endl;;
}
