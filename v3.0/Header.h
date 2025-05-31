#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <random>
#include <cstdlib> 
#include <ctime>
//nuo v0.2
#include <fstream>
#include <limits>
#include <sstream>
#include <chrono> // testavimui
#include <stdexcept> //
#include <filesystem>

//#include <istream>
#include "Studentas.h"
#include <cassert> // for rule of five test

using std::cout;
using std::string;
using std::vector;
using std::endl;
using std::cin;
using std::fixed;
using std::setprecision;
using std::left;
using std::setw;
using std::ifstream;
using std::accumulate; // suma / .size -> vidurkis
using std::ofstream;
using std::cerr; // klaidoms
using std::move;


//std::uniform_int_distribution<> dis(0, 10);  // sugeneruoja random skaicius nuo 0 iki 10 - pazymiams
//std::uniform_int_distribution<> diss(1, 10); // - studentu kiekiui

using std::uniform_int_distribution;
using std::random_device;
using std::mt19937;

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


inline int m = 0; //studentu kiekis
inline int nd = 0; //namu darbu rezultatai
inline int pasirinkimas = 0; // skaiciuoti pagal vidurki ar mediana
inline int isv = 0; 

inline vector<Student> grupe;
inline string choice;
inline vector<int> paz_temp;
inline string sortChoice;
inline Student laik;


// vardu ir pavardziu sarasas
inline const vector<string> firstNames = { "Augustas", "Birute", "Daiva", "Ema", "Fiodoras", "Gabrielius", "Haroldas", "Ieva", "Tomas", "Nija" };
inline const vector<string> lastNames = { "Baravykas", "Kiskis", "Lydeka", "Burokas", "Neris", "Jankauskas", "Kazlauskas", "Urbonas", "Boruta", "Zemaite" };

inline int testnr = 1;

