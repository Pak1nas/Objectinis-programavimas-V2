programa: main.cpp header.cpp
    g++ -std=c++17 main.cpp header.cpp -o programa

tests: tests.cpp header.cpp
    g++ -std=c++17 tests.cpp header.cpp -o tests

clean:
    rm -f programa tests
