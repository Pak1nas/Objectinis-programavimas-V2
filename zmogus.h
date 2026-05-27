#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

class zmogus {
//Paveldimi duomenys
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    //konstruktoriai
    zmogus () = default;
    zmogus(const std::string& v, const std::string& p): vardas_(v), pavarde_(p) {}
    //virtualus destruktorius
    virtual ~zmogus() = default;

    const std::string& vardas() const { return vardas_; }
    const std::string& pavarde() const { return pavarde_; }

    //Pure virtual metodas, kad klase taptu abstrakti
    virtual void printInfo() const = 0;
};

#endif
