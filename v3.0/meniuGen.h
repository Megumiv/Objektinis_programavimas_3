#pragma once
#include "Header.h"
#include "Studentas.h"

// Meniu
void meniu()
{
	cout << "\n\nMeniu: \n";
	cout << "1 - Rankiniu budu ivesti pazymius\n";
	cout << "2 - Generuoti pazymius\n";
	cout << "3 - Generuoti pazymius ir studentu vardus bei pavardes\n";
	cout << "4 - Duomenis nuskaityti is failo\n";
	cout << "5 - BAIGTI darba ir isvesti rezultatus\n";
	cout << "6 - Sugeneruoti testavimo failus\n";
	cout << "7 - Isvalyti ivestus duomenis\n";
	cout << "8 - 'Rule of five' ir ivesties/ivesties operatoriu veikimo testavimas\n";

	cout << "Pasirinkite (1, 2, 3, 4, 5, 6, 7, 8): ";
	cin >> choice;
}

// Pasirenkamas nuskaitymo failas
string pasirinktiFaila() {
	int nus = 0;
	string filename;

	while (true) {
		cout << "\nPasirinkite koki faila nuskaitysite:\n"
			<< "1 - kursiokai.txt\n"
			<< "2 - studentai10000.txt\n"
			<< "3 - studentai100000.txt\n"
			<< "4 - studentai1000000.txt\n"
			<< "5 - pats ivesiu pavadinima.\n";
		cin >> nus;

		if (nus == 1) return "kursiokai.txt";
		if (nus == 2) return "studentai10000.txt";
		if (nus == 3) return "studentai100000.txt";
		if (nus == 4) return "studentai1000000.txt";
		if (nus == 5) {
			cin >> filename;
			return filename;
		}
		cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
	}
}

// Atsitiktiniam skaiciavimui
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> diss(1, 10); // sugeneruoja random skaicius nuo 0 iki 10 - pazymiams
uniform_int_distribution<> dis(0, 10); // - studentu kiekiui

bool naudotiVidurki = true;
// Tik vidurkis ar mediana pasirenkama
void vidarmed(bool& naudotiVidurki) {
	while (true) {
		cout << "\nPasirinkite skaiciavimo buda (1 - Vidurkis, 2 - Mediana): ";
		cin >> pasirinkimas;
		if (pasirinkimas == 1) {
			naudotiVidurki = true;
			break;
		}
		else if (pasirinkimas == 2) {
			naudotiVidurki = false;
			break;
		}
		else {
			cout << "Netinkama verte. Iveskite skaiciu 1 arba 2.\n";
		}
	}
}

// Generuoja pazymius Student objektui
void pazymiai(Student& a) {
	int ndKiek = diss(gen); // kiekis
	cout << "- Namu darbu rezultatai (atsitiktiniai, 0-10): ";

	// random namu darbu rezultatai
	for (int i = 0; i < ndKiek; ++i) {
		int paz = dis(gen);       
		a.addNd(paz);               
		cout << paz << " ";
	}
	// random egzamino pazymys
	int egz = dis(gen);
	a.setEgzaminas(egz);
	cout << "\n- Egzamino rezultatas (atsitiktinis, 0-10): " << egz << endl;
}


// Duomenu failu generavimas
void generateStudentFile(const std::string& filename, size_t recordCount) {
	std::ofstream out(filename);
	if (!out.is_open()) {
		std::cerr << "Nepavyko atidaryti failo: " << filename << "\n";
		return;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 10);

	for (size_t i = 1; i <= recordCount; ++i) {
		out << "VardasNR" << i << " PavardeNR" << i << " "
			<< dis(gen) << " " << dis(gen) << " "
			<< dis(gen) << " " << dis(gen) << " "
			<< dis(gen) << "\n";
	}

	out.close();
	cout << "\nFailas sukurtas: " << filename << " (" << recordCount << " studentu)";
}
inline void GenFailai() {
	std::vector<std::pair<std::string, size_t>> failai = {
		{"studentai_1k.txt", 1'000},
		{"studentai_10k.txt", 10'000},
		{"studentai_100k.txt", 100'000},
		{"studentai_1m.txt", 1'000'000},
		{"studentai_10m.txt", 10'000'000}
	};

	for (const auto& [filename, count] : failai) {
		auto start = std::chrono::high_resolution_clock::now();
		generateStudentFile(filename, count);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = end - start;
		cout << "Sugeneruota per: " << elapsed.count() << " s\n\n";
	}
}

