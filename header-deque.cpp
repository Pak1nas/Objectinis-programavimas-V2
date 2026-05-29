#include "header.h"

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
            string kld;
            getline ( cin, kld );
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
            string kld;
            getline ( cin, kld );
            cout << "Klaida: iveskite skaiciu" << endl;
        }
    }
}

double atsitiktinis()
{
    return rand() % 11;
}

void skaiciuoti ( stud &s )
{
    double sum = s.egz;

    for ( double x : s.tarp ) sum += x;

    s.vid = sum / ( s.tarp.size() + 1 );

    deque<double> kopija = s.tarp;
    sort ( kopija.begin(), kopija.end() );

    int d = kopija.size();

    if ( d % 2 == 1 )
        s.med = kopija[d / 2];
    else
        s.med = ( kopija[d / 2 - 1] + kopija[d / 2] ) / 2.0;
}
void skaidymas(deque<stud>& A, deque<stud>& varg, deque<stud>& kiet, int pass){

    if(pass==1){
            for(const auto &s : A){
                if (s.vid>=5){
                    kiet.push_back(s);
                }
                else
                    varg.push_back(s);
            }

    }
    if(pass==2){
        auto it=A.begin();
        while(it != A.end()){
            if(it->vid < 5){
            varg.push_back(*it);
               it=A.erase(it);
            }
            else{
                ++it;
            }
        }
    }
    if(pass==3){
        auto it=std::partition(A.begin(), A.end(), [](const stud& s){return s.vid<5;});

        varg.insert(varg.end(), A.begin(), it);
        kiet.insert(kiet.end(), it, A.end());
    }
}


void spausdinti_lentele ( const deque<stud>& A, int pas , int pass)
{
    ofstream kieti ( "kietekai.txt" );
    ofstream vargi ( "vargsiukai.txt" );

        if ( pas == 1 || pas == 3 )
        {
            cout << endl << left << setw ( 15 ) << "Pavarde" << setw ( 15 ) << "Vardas" << right << setw ( 20 ) << "Galutinis (Vid.)" << setw ( 20 ) << "Galutinis (Med.)" << endl;
            cout << string ( 70, '-' ) << endl;
        }

        if ( pas == 2 || pas == 3 )
        {
            kieti << left << setw ( 15 ) << "Pavarde" << setw ( 15 ) << "Vardas" << right << setw ( 20 ) << "Galutinis (Vid.)" << setw ( 20 ) << "Galutinis (Med.)" << endl << string ( 70, '-' ) << endl;

            vargi << left << setw ( 15 ) << "Pavarde" << setw ( 15 ) << "Vardas" << right << setw ( 20 ) << "Galutinis (Vid.)" << setw ( 20 ) << "Galutinis (Med.)" << endl << string ( 70, '-' ) << endl;
        }

        for ( const auto &s : A )
        {
            if ( pas == 1 || pas == 3 )
            {
                cout << left << setw ( 15 ) << s.pavarde << setw ( 15 ) << s.vardas << right << setw ( 20 ) << fixed << setprecision ( 2 ) << s.vid << setw ( 20 ) << s.med << endl;
            }

            if ( s.vid >= 5 )
                kieti << s.pavarde << " " << s.vardas << " " << s.vid << " " << s.med << endl;
            else
                vargi << s.pavarde << " " << s.vardas << " " << s.vid << " " << s.med << endl;
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

