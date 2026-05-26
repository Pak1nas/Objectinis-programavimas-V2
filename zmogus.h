#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

class zmogus {
protected:
    std::string vardas_;
    std::string pavarde_;

public:
    zmogus () = default;
    zmogus(const std::string& v, const std::string& p): vardas_(v), pavarde_(p) {}

    virtual ~zmogus() = default;

    const std::string& vardas() const { return vardas_; }
    const std::string& pavarde() const { return pavarde_; }

    virtual void printInfo() const = 0;
};

#endif
