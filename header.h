#ifndef HEADER_H
#define HEADER_H

#include "zmogus.h"
#include <string>
#include "vector.h"

class Student : public zmogus {
private:
    Vector<double> nd_;
    double egz_;
    double vid_;
    double med_;

public:
    Student();
    Student(const std::string& v, const std::string& p, const Vector<double>& nd, double egz);

    //Rule of five
    Student(const Student& other);
    Student(Student&& other) noexcept;

    Student& operator=(const Student& other);
    Student& operator=(Student&& other) noexcept;

    ~Student();

    void skaiciuoti();

    double vid() const;
    double med() const;

    void printInfo() const override;

    friend std::ostream& operator<<(std::ostream& os, const Student& s);
    friend std::istream& operator>>(std::istream& is, Student& s);
};

int s_int();
double s_double();
int atsitiktinis();

void spausdinti_lentele(const Vector<Student>& A, int pas);
void generuoti_studentus(int kiekismok, int kiekpaz);

#endif
