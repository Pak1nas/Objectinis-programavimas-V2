#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include "header.h"

using namespace std;

bool approx(double a, double b, double eps = 0.001) {
    return fabs(a - b) < eps;
}

void test_skaiciuoti() {
    vector<double> nd = {10, 8, 6};
    Student s("Jonas", "Jonaitis", nd, 9);
    s.skaiciuoti();

    cout << "\n[TEST] skaiciuoti()\n";

    if (approx(s.vid(), 8.25))
        cout << "  Vidurkis OK\n";
    else
        cout << "  Vidurkis FAIL: " << s.vid() << endl;

    if (approx(s.med(), 8))
        cout << "  Mediana OK\n";
    else
        cout << "  Mediana FAIL: " << s.med() << endl;
}

void test_operator_ivedimo() {
    cout << "\n[TEST] operator>>\n";

    string data = "Jonas Jonaitis 10 9 8 7\n";
    stringstream ss(data);

    Student s;
    ss >> s;

    if (s.vardas() == "Jonas" && s.pavarde() == "Jonaitis")
        cout << "  Vardas/pavarde OK\n";
    else
        cout << "  Vardas/pavarde FAIL\n";

    if (s.vid() > 0)
        cout << "  ND + egz skaitymas OK\n";
    else
        cout << "  ND skaitymas FAIL\n";
}

void test_operator_isvedimo() {
    cout << "\n[TEST] operator<<\n";

    vector<double> nd = {10, 9, 8};
    Student s("Jonas", "Jonaitis", nd, 7);
    s.skaiciuoti();

    stringstream ss;
    ss << s;

    string out = ss.str();
    cout << "  Išvedimas:\n" << out << endl;

    if (out.find("Jonaitis") != string::npos)
        cout << "  Pavarde OK\n";
    else
        cout << "  Pavarde FAIL\n";
}

void test_copy_constructor() {
    cout << "\n[TEST] Copy constructor\n";

    Student a("A", "B", {1,2,3}, 5);
    a.skaiciuoti();

    Student b = a;

    if (b.vardas() == "A" && approx(b.vid(), a.vid()))
        cout << "  Copy constructor OK\n";
    else
        cout << "  Copy constructor FAIL\n";
}

void test_move_constructor() {
    cout << "\n[TEST] Move constructor\n";

    Student a("A", "B", {1,2,3}, 5);
    a.skaiciuoti();

    Student b = std::move(a);

    cout << "  Move constructor OK (jei nesukrito)\n";
}

void test_copy_assignment() {
    cout << "\n[TEST] Copy assignment\n";

    Student a("A", "B", {1,2,3}, 5);
    Student b("X", "Y", {9}, 1);

    b = a;

    if (b.vardas() == "A")
        cout << "  Copy assignment OK\n";
    else
        cout << "  Copy assignment FAIL\n";
}

void test_move_assignment() {
    cout << "\n[TEST] Move assignment\n";
 ofstream f("test.txt");
    f << "Vardas Pavarde ND1 ND2 ND3 Egz.\n";
    f << "Jonas Jonaitis 10 9 8 7\n";
    f.close();

    ifstream in("test.txt");
    Student s;
    in >> s;

    if (s.vardas() == "Jonas")
        cout << "  Failo skaitymas OK\n";
    else
        cout << "  Failo skaitymas FAIL\n";
}
