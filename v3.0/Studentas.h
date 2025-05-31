#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <utility> // std::move

using std::string;
using std::vector;

class Zmogus {
protected:
    string vardas;
    string pavarde;

public:
    Zmogus() = default;
    Zmogus(const string& v, const string& p) : vardas(v), pavarde(p) {}

    // RULE OF FIVE
    virtual ~Zmogus() = default;                           //destruktorius   
    Zmogus(const Zmogus& other) = default;                // Kopijavimo konstruktorius   
    Zmogus& operator=(const Zmogus& other) = default;     // Kopijavimo priskyrimo operatorius
    Zmogus(Zmogus&& other) noexcept = default;            // Perkelimo konstruktorius
    Zmogus& operator=(Zmogus&& other) noexcept = default; // Perkelimo priskyrimo operatorius


    // Abstraktus metodas, pavyzdziui, galutinis balas, kad klase butu abstrakti
    virtual double skaiciuokGalutinis(bool naudotiVidurki) = 0;

    // Geteriai ir seteriai
    void setVardas(const string& v) { vardas = v; }
    void setPavarde(const string& p) { pavarde = p; }

    string getVardas() const { return vardas; }
    string getPavarde() const { return pavarde; }

    // Ivedimas ranka
    virtual void ivestiRanka() = 0;
};

extern bool isTestavimoRezimas; 

class Student : public Zmogus {
private:
    vector<int> pazymiai;
    int egzaminas;
    double galutinisVid;
    double galutinisMed;

public:
    // Ivesties / Isvesties operatoriai
    friend std::ostream& operator<<(std::ostream& out, const Student& s);   // isvesties
    friend std::istream& operator>>(std::istream& in, Student& s);          // ivesties

    // Konstruktoriai
    Student() : Zmogus(), egzaminas(0), galutinisVid(0.0), galutinisMed(0.0) {} // default
    explicit Student(const string& v, const string& p, const vector<int>& paz, int egz); // pilnas

    // Rule of five
    ~Student() override;// = default; // destruktorius 
    //~Student() = default;
    Student(const Student& other);                  // kopijavimo konstruktorius
    Student& operator=(const Student& other);       // kopijavimo priskyrimo operatorius
    Student(Student&& other) noexcept;              // perkelimo konstruktorius
    Student& operator=(Student&& other) noexcept;   // perkelimo priskyrimo operatorius

    // Implementuoti abstraktu metoda is Zmogus
    double skaiciuokGalutinis(bool naudotiVidurki) override;

    // Ivesties metodai
    void ivestiRanka() override;

    // Nuskaitymas is failo
    static bool nuskaitytiIsFailo(const string& filename, vector<Student>& grupe, bool naudotiVidurki);

    // Isvedimas
    static void Isvedimas(const vector<Student>& grupe);

    // Get'ai
    double getGalutinisVid() const { return galutinisVid; }
    double getGalutinisMed() const { return galutinisMed; }
    int getEgzaminas() const { return egzaminas; }
    const vector<int>& getPazymiai() const { return pazymiai; }

    // Nustatymai
    void setEgzaminas(int e) { egzaminas = e; }
    void addNd(int nd) { pazymiai.push_back(nd); }
};
