#include "Header.h"         
#include "Studentas.h"
#include "meniuGen.h"
#include "test.h"
#include "sort.h"


int main() {
    while (true) {
        meniu();

        if (choice == "1") { //ivedama ranka

            // studentu kiekio ivedimas
            while (true) {
                cout << "Iveskite studentu kieki: ";
                cin >> m;
                if (m > 0) break;
                else cout << "Netinkamas skaicius. Maziausias galimas 1.\n";
            }

			vidarmed(naudotiVidurki); // pasirenkamas vidurkis arba mediana

            // duomenu ivedimas
            for (int i = 0; i < m; i++) {
				Student laik;
				laik.ivestiRanka(); 			
				laik.skaiciuokGalutinis(naudotiVidurki); // galutinis balas
				grupe.push_back(laik); 
            }
        }

        else if (choice == "2") { // sugeneruojami pazymiai, ivedami vardas ir pavarde
            
            vidarmed(naudotiVidurki); // pasirenkamas vidurkis arba mediana

            uniform_int_distribution<> diss(1, 10);
            random_device rd;
            mt19937 gen(rd());

            m = diss(gen);
            cout << "Studentu kiekis (atsitiktinis, 1-10): " << m << endl;

            // ivedama ranka
            for (int i = 0; i < m; i++) {
                cout << "\nIveskite studento varda ir pavarde: ";
                string v, p;
                cin >> v >> p;
                laik.setVardas(v);
                laik.setPavarde(p);

                pazymiai(laik);
				laik.skaiciuokGalutinis(naudotiVidurki);

                grupe.push_back(laik);
            }
        }

        else if (choice == "3") { // Sugeneruojami pazymiai, vardai bei pavardes

            vidarmed(naudotiVidurki); // pasirenkamas vidurkis arba mediana

            uniform_int_distribution<> diss(1, 10);
            random_device rd;
            mt19937 gen(rd());

            m = diss(gen);
            cout << "\nStudentu kiekis (atsitiktinis, 1-10): " << m << endl;

            uniform_int_distribution<> nameDist(0, firstNames.size() - 1);
            uniform_int_distribution<> surnameDist(0, lastNames.size() - 1);

            for (int i = 0; i < m; i++) { // random priskiriami vardai ir pavardes
                laik.setVardas(firstNames[nameDist(gen)]);
                laik.setPavarde(lastNames[surnameDist(gen)]);
                cout << "\n" << laik.getVardas() << " " << laik.getPavarde() << " --- \n";

                pazymiai(laik); // sugeneruojami egzamino ir namu darbu pazymiai
				laik.skaiciuokGalutinis(naudotiVidurki); // galutinis balas

                grupe.push_back(laik);
            }
        }

        else if (choice == "4") { // Nuskaitymas is failo

            vidarmed(naudotiVidurki); // pasirenkamas vidurkis arba mediana
			int nus = 0;

			string filename = pasirinktiFaila(); // pasirenkamas nuskaitymo failas
			
            // testavimo kartojimo pasirinkimas
			while (true) {
				cout << "\nPasirinkite kiek kartu testuosite nuskaityma: ";
				cin >> testnr;
				if (testnr >= 1) break;
				else cout << "Netinkamas skaicius. Maziausias galimas 1.\n";
			}

            // Paleisti testavima
            auto start = std::chrono::high_resolution_clock::now();

			vector<Student> grupe_temp; // kad kiekvienas testas prasidetu nuo tuscios grupes
            // Nuskaitymas
			for (int i = 0; i < testnr; i++) {
				grupe_temp.clear(); // isvalom tarp testu
				if (!Student::nuskaitytiIsFailo(filename, grupe_temp, naudotiVidurki)) {
					cout << "\nNuskaitymas nepavyko.\n";
				}
			}
			// po testu priskiriam paskutinio testo duomenis i pagrindine grupe
            grupe.insert(grupe.end(), grupe_temp.begin(), grupe_temp.end());

            auto end = std::chrono::high_resolution_clock::now(); // stabdyti testavima
            diff = end - start; // skirtumas sekundemis 
            testai.push_back(diff.count());

            if (testnr > 0) {
                cout << "\nVidutinis nuskaitymo vykdymo laikas per " << testnr << " testus: " << accumulate(testai.begin(), testai.end(), 0.0) / testai.size() << " s\n";
            }
        }

        else if (choice == "5") { // Baigiamas darbas - isvestis ir rusiavimas
            
            char sortChoice;
            SortMeniu(sortChoice); 
            Sort(sortChoice, grupe); 
			Student::Isvedimas(grupe);

            if (!grupe.empty()) {
                cout << "\nSuskirstymui pagal bala i kietiaciu ir vargsiuku failus:" << endl;
                SortMeniu(sortChoice);
                Sort(sortChoice, grupe);
                Skirstymas(grupe);
            }
            break;
        }

        else if (choice == "6") { // Generuojami duomenu failai
            GenFailai();
        }

        else if (choice == "7") { // Isvalyti ivestus duomenis
            grupe.clear();
            cout << "\nStudentu sarasas isvalytas.\n";
        }

        else if (choice == "8") { // Testuoja "Rule of Five" ir ivesties/isvesties operatorius
            isTestavimoRezimas = true;
            testRuleOfFive(); 
            testOperatoriai(); 
            isTestavimoRezimas = false;
        }

        else { // meniu neteisingo ivedimo isvestis
            cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
            continue;
        }
    }
    return 0;
}

