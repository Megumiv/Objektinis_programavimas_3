#pragma once
//#include <vector>
#include <string>
#include <iostream>
#include <utility> // std::move
#include <algorithm>

#include "Vector.h"
template<typename T>
using Vec = Vector<T>;

using std::string;

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
    Vec<int> pazymiai;
    int egzaminas;
    double galutinisVid;
    double galutinisMed;

public:
    // Ivesties / Isvesties operatoriai
    friend std::ostream& operator<<(std::ostream& out, const Student& s);   // isvesties
    friend std::istream& operator>>(std::istream& in, Student& s);          // ivesties

    // Konstruktoriai
    Student() : Zmogus(), egzaminas(0), galutinisVid(0.0), galutinisMed(0.0) {} // default
    explicit Student(const string& v, const string& p, const Vec<int>& paz, int egz); // pilnas

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
    static bool nuskaitytiIsFailo(const string& filename, Vec<Student>& grupe, bool naudotiVidurki);

    // Isvedimas
    static void Isvedimas(const Vec<Student>& grupe);

    // Get'ai
    double getGalutinisVid() const { return galutinisVid; }
    double getGalutinisMed() const { return galutinisMed; }
    int getEgzaminas() const { return egzaminas; }
    const Vec<int>& getPazymiai() const { return pazymiai; }

    // Nustatymai
    void setEgzaminas(int e) { egzaminas = e; }
    void addNd(int nd) { pazymiai.push_back(nd); }
};



/*template <typename T>
class Vec {
public:
    // Member types (pagal std::Vec)
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = T*;
    using const_iterator = const T*;

private:
    pointer data_;       // rodyklė į masyvą
    size_type size_;     // elementų skaičius
    size_type capacity_; // talpa (rezervuota atmintis)

public:
    // Konstruktoriai / destruktorius
    Vec();
    explicit Vec(size_type n, const T& val = T());
    Vec(const Vec& other);
    Vec(Vec&& other) noexcept;
    ~Vec();

    // Operatoriai
    Vec& operator=(const Vec& other);
    Vec& operator=(Vec&& other) noexcept;

    // Elementų prieiga
    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;
    reference at(size_type pos);
    const_reference at(size_type pos) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;

    // Iteratorių funkcijos
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;

    // Talpos funkcijos
    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type capacity() const noexcept;
    void reserve(size_type new_cap);
    void shrink_to_fit();

    // Modifikavimo funkcijos
    void clear() noexcept;
    void push_back(const T& value);
    void push_back(T&& value);
    template <class... Args>
    void emplace_back(Args&&... args);
    void pop_back();

    iterator insert(const_iterator pos, const T& value);
    iterator erase(const_iterator pos);
    iterator erase(const_iterator first, const_iterator last);

    void resize(size_type count, T value = T());

    // Swap
    void swap(Vec& other) noexcept;

    // ... kitos funkcijos (assign, emplace, insert su iteratoriais ir kt.)

};*/