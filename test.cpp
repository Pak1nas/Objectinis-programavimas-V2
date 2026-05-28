#include <gtest/gtest.h>
#include "header.h"
#include <sstream>
#include <fstream>
#include <cmath>

bool approx(double a, double b, double eps = 0.001) {
    return fabs(a - b) < eps;
}

TEST(StudentTest, Skaiciuoti) {
    std::vector<double> nd = {10, 8, 6};
    Student s("Jonas", "Jonaitis", nd, 9);
    s.skaiciuoti();

    EXPECT_TRUE(approx(s.vid(), 8.25));
    EXPECT_TRUE(approx(s.med(), 8));
}

TEST(StudentTest, OperatorIvedimo) {
    std::stringstream ss("Jonas Jonaitis 10 9 8 7\n");
    Student s;
    ss >> s;

    EXPECT_EQ(s.vardas(), "Jonas");
    EXPECT_EQ(s.pavarde(), "Jonaitis");
    EXPECT_GT(s.vid(), 0);
}

TEST(StudentTest, OperatorIsvedimo) {
    std::vector<double> nd = {10, 9, 8};
    Student s("Jonas", "Jonaitis", nd, 7);
    s.skaiciuoti();

    std::stringstream ss;
    ss << s;

    std::string out = ss.str();
    EXPECT_NE(out.find("Jonaitis"), std::string::npos);
}

TEST(StudentTest, CopyConstructor) {
    Student a("A", "B", {1,2,3}, 5);
    a.skaiciuoti();

    Student b = a;

    EXPECT_EQ(b.vardas(), "A");
    EXPECT_TRUE(approx(b.vid(), a.vid()));
}

TEST(StudentTest, MoveConstructor) {
    Student a("A", "B", {1,2,3}, 5);
    a.skaiciuoti();

    Student b = std::move(a);

    SUCCEED();
}

TEST(StudentTest, CopyAssignment) {
    Student a("A", "B", {1,2,3}, 5);
    Student b("X", "Y", {9}, 1);

    b = a;

    EXPECT_EQ(b.vardas(), "A");
}

TEST(StudentTest, MoveAssignment) {
    std::ofstream f("test.txt");
    f << "Vardas Pavarde ND1 ND2 ND3 Egz.\n";
    f << "Jonas Jonaitis 10 9 8 7\n";
    f.close();

    std::ifstream in("test.txt");
    Student s;
    in >> s;

    EXPECT_EQ(s.vardas(), "Jonas");
}
