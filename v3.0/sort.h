#pragma once
#include "Header.h"
#include "Studentas.h"

// Rikiavimo pasirinkimas
void SortMeniu(char& sortChoice) {

	while (true) {
		cout << "\nPasirinkite pagal ka norite surusiuoti: \n  a) Pavarde \n  b) Varda \n  c) Galutinis pagal vidurki \n  d) Galutinis pagal mediana. \nIveskite tik pasirinkimo raide: ";
		cin >> sortChoice;

		// tikrinama ar ivestis atitinka galimus paasirinkimus
		if (sortChoice == 'a' || sortChoice == 'b' || sortChoice == 'c' || sortChoice == 'd') {
			break;
		}
		else {
			cout << "\nNeteisingas pasirinkimas. Bandykite dar karta.\n";
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignoruoja neteisinga ivesti
		}
	}
}

// Isrenkami tik skaitmenys
int extractNumber(const string& pavarde) { 
	string digits;
	for (char c : pavarde) {
		if (isdigit(c)) digits += c;
	}
	return digits.empty() ? 0 : std::stoi(digits);
}

// Rikiavimas
void Sort(char sortChoice, vector<Student>& grupe) {
	if (sortChoice == 'a') { //pavarde
		sort(grupe.begin(), grupe.end(), [](const Student& a, const Student& b) {
			int numA = extractNumber(a.getPavarde());
			int numB = extractNumber(b.getPavarde());
			if (numA == numB)  return a.getPavarde() < b.getPavarde(); // turi sutapti skaitmenu kiekis
			return numA < numB;
			});
	}
	else if (sortChoice == 'b') { //vardas
		sort(grupe.begin(), grupe.end(), [](const Student& a, const Student& b) {
			int numA = extractNumber(a.getVardas());
			int numB = extractNumber(b.getVardas());
			if (numA == numB)  return a.getVardas() < b.getVardas(); // turi sutapti skaitmenu kiekis
			return numA < numB;
			});
	}
	else if (sortChoice == 'c') { // vidurkio galutinis
		sort(grupe.begin(), grupe.end(), [](const Student& a, const Student& b) {
			return a.getGalutinisVid() < b.getGalutinisVid();
			});
	}
	else if (sortChoice == 'd') { // medianos galutinis
		sort(grupe.begin(), grupe.end(), [](const Student& a, const Student& b) {
			return a.getGalutinisMed() < b.getGalutinisMed();
			});
	}
}


// Isskirstymas i kietiakius ir vargsiukus pagal bala
void Skirstymas(const vector<Student>& grupe) {

    vector<Student> kietiakiai;
    vector<Student> vargsiukai;

    for (const auto& stud : grupe) {
        if (stud.getGalutinisVid() >= 5.0 || stud.getGalutinisMed() >= 5)
            kietiakiai.push_back(stud);
        else
            vargsiukai.push_back(stud);
    }
    std::ofstream outKiet("kietiakiai.txt");
    std::ofstream outVargs("vargsiukai.txt");

    if (!outKiet) {
        std::cout << "Klaida atidarant kietiakiai.txt faila!\n";
        return;
    }
    if (!outVargs) {
        std::cout << "Klaida atidarant vargsiukai.txt faila!\n";
        return;
    }

    // Kietiakiai
    outKiet << left << setw(15) << "\nPavarde" << setw(15) << "Vardas";
    outKiet << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    outKiet << "------------------------------------------------------------------\n";

    for (const auto& s : kietiakiai) {
        outKiet << left << setw(15) << s.getPavarde() << setw(15) << s.getVardas();
        // galutinis pasirinktas pagal vidurki, o prie medianos - x
        if (s.getGalutinisVid() == -1) outKiet << setw(20) << "x.xx";
        else outKiet << setw(20) << fixed << setprecision(2) << s.getGalutinisVid();
        // galutinis pasirinktas pagal mediana, o prie vidurkio - x
        if (s.getGalutinisMed() == -1) outKiet << setw(20) << "x.xx" << endl;
        else outKiet << setw(20) << fixed << setprecision(2) << s.getGalutinisMed() << endl;
    }

    // Vargsiukai
    outVargs << left << setw(15) << "\nPavarde" << setw(15) << "Vardas";
    outVargs << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    outVargs << "------------------------------------------------------------------\n";

    for (const auto& s : vargsiukai) {
        outVargs << left << setw(15) << s.getPavarde() << setw(15) << s.getVardas();
        // galutinis pasirinktas pagal vidurki, o prie medianos - x
        if (s.getGalutinisVid() == -1) outVargs << setw(20) << "x.xx";
        else outVargs << setw(20) << fixed << setprecision(2) << s.getGalutinisVid();
        // galutinis pasirinktas pagal mediana, o prie vidurkio - x
        if (s.getGalutinisMed() == -1) outVargs << setw(20) << "x.xx" << endl;
        else outVargs << setw(20) << fixed << setprecision(2) << s.getGalutinisMed() << endl;
    }
    //failas.close();
    cout << "\nPapildomai surusiuota ir isvesta i failus: \"kietiakiai.txt\" (balas >= 5) ir \"vargsiukai.txt\" (balas < 5).\n";
}