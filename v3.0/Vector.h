#pragma once
#include <initializer_list>
#include <stdexcept>
#include <algorithm>
#include <memory>
#include <cstddef> // std::size_t
#include <utility> // std::move, std::swap

template <typename T>
class Vector {
private:

    T* data_;               // Dinaminis masyvas, kuriame saugomi elementai
    std::size_t size_;      // Kiek elementų siuo metu yra masyve
    std::size_t capacity_;  // Kiek vietos masyve is viso yra rezervuota (talpa)

    // Funkcija, kuri atlieka masyvo perlokavima, jei reikia didesnės talpos
    void reallocate(std::size_t new_cap) {
        // Jeigu nauja talpa mazesne nei esamas elementu kiekis, nustatome ja kaip esama elementu skaiciu, kad neprarastume duomenu
        if (new_cap < size_)
            new_cap = size_;

        // Sukuriame nauja masyva su nauja talpa
        T* new_data = new T[new_cap];
        // Perkeliame (move) esamus elementus is seno masyvo i nauja
        for (std::size_t i = 0; i < size_; ++i)
            new_data[i] = std::move(data_[i]);

       
        delete[] data_;           // Istriname sena masyva
        data_ = new_data;         // Pakeiciame rodykle i nauja masyva
        capacity_ = new_cap;      // Atnaujiname talpos reiksme
    }


public:
    // KONSTRUKTORIAI IR DESTRUKTORIUS
    Vector() : data_(nullptr), size_(0), capacity_(0) {}

    // Konstruktorius, kuris sukuria vektoriu su n elementu
    explicit Vector(std::size_t n) : data_(new T[n]), size_(n), capacity_(n) {} 

    // Konstruktorius is initializer_list, leidzia kurti taip: Vector<int> v = {1, 2, 3};
    Vector(std::initializer_list<T> init)
        : data_(new T[init.size()]), size_(init.size()), capacity_(init.size()) {
        std::copy(init.begin(), init.end(), data_);
    }
    // Kopijavimo konstruktorius - sukuria nauja vektoriu kopijuodamas kita
    Vector(const Vector& other) : data_(new T[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
        std::copy(other.data_, other.data_ + size_, data_);
    }

    // Kopijavimo priskyrimo operatorius
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] data_;
            data_ = new T[other.capacity_];
            size_ = other.size_;
            capacity_ = other.capacity_;
            std::copy(other.data_, other.data_ + size_, data_);
        }
        return *this;
    }

    // Perkelimo konstruktorius (move) - greitas resursu peremimas
    Vector(Vector&& other) noexcept : data_(nullptr), size_(0), capacity_(0) {
        *this = std::move(other);
    }

    // Perkelimo priskyrimo operatorius
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    // Destruktorius 
    ~Vector() {
        delete[] data_;
    }

    // Elementu prieiga su indeksu
    T& operator[](std::size_t index) {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    const T& operator[](std::size_t index) const {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    // Funkcija at(), kuri taip pat patikrina indeksa ir ismeta isimti jei neteisingas
    T& at(std::size_t index) {
        if (index >= size_)
            throw std::out_of_range("Index out of range");
        return data_[index];
    }

    const T& at(std::size_t index) const {
        if (index >= size_)
            throw std::out_of_range("Index out of range");
        return data_[index];
    }

    // Iteratoriai leidzia naudoti range-based for ir algoritmus is <algorithm>
    T* begin() { return data_; }
    T* end() { return data_ + size_; }

    const T* begin() const { return data_; }
    const T* end() const { return data_ + size_; }

    // Vektoriaus dydzio keitimas (elementu sk.)
    void resize(std::size_t new_size) {// Jei naujas dydis didesnis uz talpa - perlokuojame vieta       
        if (new_size > capacity_)
            reallocate(new_size);

        if (new_size > size_) {// Jei didiname dydi, nauji elementai yra sukuriami numatytuoju budu
            for (std::size_t i = size_; i < new_size; ++i)
                data_[i] = T();  // cia kvieciamas numatytas konstruktorius
        }
        else if (new_size < size_) { // Jei maziname dydi, sunaikiname nereikalingus elementus
            for (std::size_t i = new_size; i < size_; ++i)
                data_[i].~T();  // kvieciame destruktoriu
        }
        size_ = new_size;
    }

    // Rezervuoja vieta masyve, jei reikia didesnes talpos
    void reserve(std::size_t new_cap) {
        if (new_cap > capacity_)
            reallocate(new_cap);
    }

    // Prideda nauja elementa i pabaiga (kopijuodamas)
    void push_back(const T& value) {
        if (size_ >= capacity_)
            reallocate(capacity_ == 0 ? 1 : capacity_ * 2); // talpos didinimas (dvigubinimas)
        data_[size_++] = value;
    }

    // Prideda nauja elementa i pabaiga (perkeliamas)
    void push_back(T&& value) {
        if (size_ >= capacity_)
            reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_++] = std::move(value);
    }

    // Isvalo vektoriu - sunaikina visus elementus
    void clear() {
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i].~T();  // kviecia destruktoriu kiekvienam elementui
        }
        size_ = 0;
    }


    std::size_t size() const { return size_; }          // Gražina vektoriaus dydi (elementu skaiciu)
    std::size_t capacity() const { return capacity_; }  // Gražina vektoriaus talpa (kiek vietos yra rezervuota)
    bool empty() const { return size_ == 0; }           // Patikrina, ar vektorius yra tuscias

    // Elementu salinimas
    void pop_back() {
        if (size_ > 0) --size_;
        data_[size_].~T();  // sunaikina paskutini elementa
    }

    T& front() { return data_[0]; }           // Gražina pirma elementa
    T& back() { return data_[size_ - 1]; }    // Gražina paskutini elementa

    const T& front() const { return data_[0]; }
    const T& back() const { return data_[size_ - 1]; }

    // Lygina du vektorius - ar jie yra vienodi elementais
    bool operator==(const Vector& other) const {
        if (size_ != other.size_) return false;
        for (std::size_t i = 0; i < size_; ++i)
            if (!(data_[i] == other.data_[i])) return false;
        return true;
    }

    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }

    // Iterpia elementa nurodytoje pozicijoje
    void insert(std::size_t pos, const T& value) {
        if (pos > size_) throw std::out_of_range("Iterpimo pozicija yra uz leistinu ribu");
        if (size_ >= capacity_) reallocate(capacity_ == 0 ? 1 : capacity_ * 2);
        // Pastumiame elementus i desine, kad butu vietos naujam
        for (std::size_t i = size_; i > pos; --i) {
            data_[i] = std::move(data_[i - 1]);
        }
        data_[pos] = value;
        ++size_;
    }

    // Iterpia intervala elementu, nurodyta iteratoriais
    template <typename InputIt>
    void insert(T* pos, InputIt first, InputIt last) {
        std::size_t index = pos - data_;  // pozicija kur iterpti
        std::size_t count = std::distance(first, last);  // kiek elementu iterpti

        if (size_ + count > capacity_)
            reallocate(std::max(capacity_ * 2, size_ + count));  // padidinti talpa jei reikia

        // Pastumti esamus elementus i desine
        for (std::size_t i = size_; i-- > index; )
            data_[i + count] = std::move(data_[i]);


        // Nukopijuoti naujus elementus
        for (std::size_t i = 0; i < count; ++i)
            data_[index + i] = *(first + i);

        size_ += count;
    }

    // Iterpia `count` kartu ta pati elementa `value` i nurodyta pozicija
    void insert(T* pos, std::size_t count, const T& value) {
        std::size_t index = pos - data_;

        if (size_ + count > capacity_)
            reallocate(std::max(capacity_ * 2, size_ + count));

        // Perstumiam esamus elementus i desine
        for (std::size_t i = size_; i-- > index; )
            data_[i + count] = std::move(data_[i]);

        // Iterpiam naujus elementus, `count` kartu `value`
        for (std::size_t i = 0; i < count; ++i)
            data_[index + i] = value;

        size_ += count;
    }
};

