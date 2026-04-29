#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <vector>

class Student {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<double> nd_;
    double egz_;
    double vid_;
    double med_;

public:
    Student();
    Student(const std::string& v, const std::string& p, const std::vector<double>& nd, double egz);

    Student(const Student& other);
    Student(Student&& other) noexcept;

    Student& operator=(const Student& other);
    Student& operator=(Student&& other) noexcept;

    ~Student();

    void setVardas(const std::string& v);
    void setPavarde(const std::string& p);
    void addNd(double x);
    void setEgz(double x);

    const std::string& vardas() const;
    const std::string& pavarde() const;
    double vid() const;
    double med() const;

    void skaiciuoti();
};

int s_int();
double s_double();
int atsitiktinis();

void spausdinti_lentele(const std::vector<Student>& A, int pas);
void generuoti_studentus(int kiekismok, int kiekpaz);

#endif
