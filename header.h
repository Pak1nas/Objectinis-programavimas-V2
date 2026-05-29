#pragma once
#include <iostream>
#include <deque>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cctype>
#include <iomanip>
#include <bits/stdc++.h>


using namespace std;

int s_int();
double s_double();

struct stud {
    string vardas;
    string pavarde;
    deque<double> tarp;
    double egz;
    double vid;
    double med;
};

double atsitiktinis();
void skaiciuoti(stud &s);
void skaidymas(deque<stud>& A, deque<stud>& varg, deque<stud>& kiet, int pass);
void spausdinti_lentele(const deque<stud>& A, int pas, int pass);
void generuoti_studentus(int kiekismok, int kiekpaz);
void spausdinti_lentele(deque<stud>& A, deque<stud>& varg, deque<stud>& kiet);
