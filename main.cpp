#include "./NewVector/vector.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cmath>
#include <vector>
#include <random>
#include <ctime>
#include <fstream>
#include <chrono>
#include <numeric>
#include <deque>
#include <list>
#include <stdlib.h>
#include <typeinfo>
#include <string.h>
#include <istream>

using std::cout; using std::cin; using std::endl; using std::string; using std::setw; using std::left; using std::setprecision; using std::fixed;
using std::sort; using std::stoi; using std::ifstream; using std::list; using std::deque; using std::istream;

class Timer { // paimta iš https://github.com/objprog/paskaitos2019/wiki/Laiko-matavimas
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
public:
    Timer() : start{std::chrono::high_resolution_clock::now()} {}
    void reset() {
        start = std::chrono::high_resolution_clock::now();
    }
    double elapsed() const {
        return std::chrono::duration<double>
                (std::chrono::high_resolution_clock::now() - start).count();
    }
};

class Human {
protected:
    string name = "Vardenis";
    string surname = "Pavardenis";
    Human(const string inputName, const string inputSurname) : name(inputName), surname(inputSurname) {}
public:
    string getName() const { return name; }
    string getSurname() const { return surname; }
    void setName( istream & stream ) { stream >> name; }
    void setSurname( istream & stream ) { stream >> surname; }
};

// Funkcija, kurios reikia klasėje esančioms funkcijoms, taigi įdėta čia
void wasStringGivenInsteadInt(int &param);

class Student : public Human {
private:
    vector<int> grades;
    int exam=0;
    double galutinis=0; // Galutinis studento pažymys
    double galutinisMedian = 0;
    int numberOfGrades=0;
    bool vargsiukas=false;

public:
    Student() : Human("Vardenis", "Pavardenis"), exam(0), galutinis(0), galutinisMedian(0), numberOfGrades(0), vargsiukas(false) {}
    Student(const Student& stud) : Human(stud.name, stud.surname), grades(stud.grades), exam(stud.exam),
                                   galutinis(stud.galutinis), galutinisMedian(stud.galutinisMedian), numberOfGrades(stud.numberOfGrades), vargsiukas(stud.vargsiukas) {}
    Student(Student&& stud) noexcept : Human(stud.name, stud.surname), grades(stud.grades), exam(stud.exam),
                                       galutinis(stud.galutinis), galutinisMedian(stud.galutinisMedian), numberOfGrades(stud.numberOfGrades), vargsiukas(stud.vargsiukas) {}
    ~Student() { grades.clear(); }
    // getters
    double getGalutinis() const {return galutinis; }
    double getGalutinisMedian() const {return galutinisMedian; }
    int getNumberOfGrades() const {return numberOfGrades; }
    bool isVargsiukas() const { return vargsiukas; }
    vector<int> getGrades() const { return grades; }
    int getExam() const { return exam; }
    // setters
    void setExam( istream & stream );
    void setExam( const int& sk ) { exam = sk; }
    void setName(const string & name) { this->name = name; }
    void setSurname(const string & surname) { this->surname = surname; }
    void setVargsiukas(const bool & vargsiukasState) { vargsiukas = vargsiukasState; }
    void reserveGrades( int & number) { grades.reserve(number); }
    void pushBackGrades( int & grade ) { grades.push_back(grade); }

// Nustatomas egzamino pažymys, panaikinant
    void setExamFromGrades();

// Ar pažymių užtenka, nes paskutinis pažymys visada bus egzaminas
    void checkGradesCount();

// Per konsolę įrašomi pažymiai
    void setGrades();
    void setGrades(std::initializer_list<int> list) { grades = list; }

// Apskaičiuoja vidurkį
    float setAverage();

// Apskaičiuoja medianą
    float setMedian();

// Apskaičiuoja abu galutinius pažymius
    void setGalutinis();
    void setGalutinis(const double & paz) { galutinis = paz; }
    void setGalutinisMedian(const double & paz) { galutinisMedian = paz; }

// Pažymių generavimas studentui
    void generateGrades();

// Operatorių persidengimas
    bool operator>(const Student& stud);
    bool operator<(const Student& stud);
    bool operator==(const Student& stud);
    bool operator!=(const Student& stud);
    bool operator>=(const Student& stud);
    bool operator<=(const Student& stud);
    Student& operator=(const Student& stud);
    Student& operator=(Student&& stud) noexcept;
};

void analyseInt() {
    Timer t;// Pradėti v1 užpildymo laiko matavimą
    std::vector<int> v1;
    vector<int> v2;
    // unsigned int sz = 100000;  // 100000, 1000000, 10000000, 100000000
    for (int sz=100000; sz <=100000000; sz*=10) {
        std::cout << "DYDIS: " << sz << std::endl;
        for (int i = 0; i <= sz; ++i)
            v1.push_back(i);
        std::cout << "STD::VECTOR: " << t.elapsed() << std::endl; // Baigti v1 užpildymo laiko matavimą
        v1.clear();

        t.reset(); // Pradėti v2 užpildymo laiko matavimą
        for (int i = 0; i <= sz; ++i)
            v2.push_back(i);
        std::cout << "CUSTOM VECTOR: " << t.elapsed() << std::endl; // Baigti v2 užpildymo laiko matavimą
        v2.clear();
    }
}

Student generateStudent() {
    Student stud = Student();
    stud.setName("Jonas");
    stud.setSurname("Jonaitis");
    stud.setGrades({10, 9, 9, 10, 8, 7, 9, 10});
    stud.setExam(10);
    stud.setGalutinis(9.8);
    stud.setGalutinisMedian(9);
    stud.setVargsiukas(false);
    return stud;
}

void analyseStudent() {
    Student stud = generateStudent();

    Timer t;// Pradėti v1 užpildymo laiko matavimą
    std::vector<Student> v1;
    vector<Student> v2;
    // unsigned int sz = 100000;  // 100000, 1000000, 10000000, 100000000
    for (int sz=100000; sz <=1000000; sz*=10) {
        std::cout << "DYDIS: " << sz << std::endl;
        for (int i = 0; i <= sz; ++i)
            v1.push_back(stud);
        std::cout << "STD::VECTOR: " << t.elapsed() << std::endl; // Baigti v1 užpildymo laiko matavimą
        v1.clear();

        t.reset(); // Pradėti v2 užpildymo laiko matavimą
        for (int i = 0; i <= sz; ++i)
            v2.push_back(stud);
        std::cout << "CUSTOM VECTOR: " << t.elapsed() << std::endl; // Baigti v2 užpildymo laiko matavimą
        v2.clear();
    }
}

void analyseMemory() {
    std::vector<int> v1;
    vector<int> v2;
    int stdTimes = 0, customTimes = 0;
    for (int sz=10000; sz<=100000000; sz*=10) {
        std::cout << "DYDIS: " << sz << std::endl;
        for (int i = 0; i <= sz; ++i) {
            if (v1.capacity() == v1.size())
                stdTimes++;
            v1.push_back(i);
        }
        std::cout << "STD::VECTOR: " << stdTimes << std::endl;
        v1.clear();
        stdTimes = 0;

        for (int i = 0; i <= sz; ++i) {
            if (v2.capacity() == v2.size()) customTimes++;
            v2.push_back(i);
        }
        std::cout << "CUSTOM VECTOR: " << customTimes << std::endl;
        v2.clear();
        customTimes = 0;
    }
}

int main() {
    cout << "vector<int>" << endl;
    analyseInt();
    cout << endl << "vector<Student>" << endl;
    analyseStudent();
    cout << endl << "memory allocation analysis..." << endl;
    analyseMemory();
}