#pragma once
#include "Header.h"
#include "Studentas.h"

// testavimui
std::chrono::duration<double> diff; // skirtumas sekundemis
vector<double> testai;
double tvid(const vector<double>& times) {
	if (times.empty()) return 0.0;
	return accumulate(times.begin(), times.end(), 0.0) / times.size();
}

/* testavimo rezultatai VECTOR:
	Vidutinis nuskaitymo vykdymo laikas 10 000 studentu per 5 testus: 3.14733 s
	Vidutinis nuskaitymo vykdymo laikas 100 000 studentu per 5 testus: 40.7781 s
	Vidutinis nuskaitymo vykdymo laikas 1 000 000 studentu per 5 testus: 206.372 s
*/

/* Nauju generuojamu duomenu failu testavimo rezultatai:
	1 000 studentu:  0.0172659 s
	10 000 studentu:  0.145388 s
	100 000 studentu:  1.495 s
	1 000 000 studentu:  15.8693 s
	10 000 000 studentu:   165.408 s
*/

// RULE OF FIVE testavimui
void testRuleOfFive() {
    cout << "\n--- Tikrinamas Rule of Five ---\n";

    // Originalus objektas
    Student s1("Vardas", "Pavarde", { 10, 9, 8 }, 9);
    s1.skaiciuokGalutinis(true);

    //Zmogus z; // Kompiliacijos klaida – negalima sukurti abstrakcios klases objekto

    // Kopijavimo konstruktorius
    Student s2(s1);
    if (s2.getVardas() != s1.getVardas())
        cerr << "Kopijavimo konstruktorius: vardas nesutampa\n";
    if (s2.getPavarde() != s1.getPavarde())
        cerr << "Kopijavimo konstruktorius: pavarde nesutampa\n";
    if (s2.getEgzaminas() != s1.getEgzaminas())
        cerr << "Kopijavimo konstruktorius: egzaminas nesutampa\n";
    if (s2.getPazymiai() != s1.getPazymiai())
        cerr << "Kopijavimo konstruktorius: pazymiai nesutampa\n";
    if (s2.getGalutinisVid() != s1.getGalutinisVid())
        cerr << "Kopijavimo konstruktorius: galutinisVid nesutampa\n";
    if (s2.getGalutinisMed() != s1.getGalutinisMed())
        cerr << "Kopijavimo konstruktorius: galutinisMed nesutampa\n";

    // Kopijavimo priskyrimo operatorius
    Student s3;
    s3 = s1;
    if (s3.getVardas() != s1.getVardas())
        cerr << "Kopijavimo priskyrimo operatorius: vardas nesutampa\n";
    if (s3.getPavarde() != s1.getPavarde())
        cerr << "Kopijavimo priskyrimo operatorius: pavarde nesutampa\n";
    if (s3.getEgzaminas() != s1.getEgzaminas())
        cerr << "Kopijavimo priskyrimo operatorius: egzaminas nesutampa\n";
    if (s3.getPazymiai() != s1.getPazymiai())
        cerr << "Kopijavimo priskyrimo operatorius: pazymiai nesutampa\n";
    if (s3.getGalutinisVid() != s1.getGalutinisVid())
        cerr << "Kopijavimo priskyrimo operatorius: galutinisVid nesutampa\n";
    if (s3.getGalutinisMed() != s1.getGalutinisMed())
        cerr << "Kopijavimo priskyrimo operatorius: galutinisMed nesutampa\n";

    // Perkelimo konstruktorius
    Student s4(std::move(s1));
    if (s4.getVardas() != "Vardas")
        cerr << "Perkelimo konstruktorius: vardas neteisingas po move\n";
    if (s4.getPavarde() != "Pavarde")
        cerr << "Perkelimo konstruktorius: pavarde nesutampa\n";
    if (s4.getEgzaminas() != 9)
        cerr << "Perkelimo konstruktorius: egzaminas nesutampa\n";
    if (s4.getPazymiai() != vector<int>({ 10, 9, 8 }))
        cerr << "Perkelimo konstruktorius: pazymiai nesutampa\n";
    if (s4.getGalutinisVid() <= 0.0)
        cerr << "Perkelimo konstruktorius: galutinisVid neapskaiciuotas\n";

    // Perkelimo priskyrimo operatorius
    Student s5;
    s5 = std::move(s2);
    if (s5.getVardas() != "Vardas")
        cerr << "Perkelimo priskyrimo operatorius: vardas nesutampa\n";
    if (s5.getPavarde() != "Pavarde")
        cerr << "Perkelimo priskyrimo operatorius: pavarde neteisinga po move\n";
    if (s5.getEgzaminas() != 9)
        cerr << "Perkelimo priskyrimo operatorius: egzaminas nesutampa\n";
    if (s5.getPazymiai() != vector<int>({ 10, 9, 8 }))
        cerr << "Perkelimo priskyrimo operatorius: pazymiai nesutampa\n";
    if (s5.getGalutinisVid() <= 0.0)
        cerr << "Perkelimo priskyrimo operatorius: galutinisVid neapskaiciuotas\n";

    cout << "\nRULE OF FIVE TESTAS SEKMINGAI BAIGTAS:\n";
}

// Ivesties ir isvesties operatoriu testavimas
void testOperatoriai() {
    cout << "\n--- Tikrinami ivesties ir isvesties operatoriai ---\n";

    // Sukuriam teksto srauta su studento duomenimis (kaip ivestis)
    std::istringstream input("Vardas\nPavarde\n3\n8 9 10\n9\n");

    Student s;
    // Ivedame duomenis iš teksto srauto
    input >> s;
    if (input.fail()) {
        cerr << "\nKlaida: nepavyko nuskaityti studento duomenu.\n";
    }

    // Patikriname ar teisingai nuskaityta
    assert(s.getVardas() == "Vardas");
    assert(s.getPavarde() == "Pavarde");
    assert(s.getEgzaminas() == 9); 
    vector<int> tiketini = { 8, 9, 10 };
    assert(s.getPazymiai() == tiketini); 

    // Isvedame i tekstini srauta
    std::ostringstream output;
    output << s;

    // Patikriname ar isvestis nera tuscia
    assert(!output.str().empty());

    cout << "\n\nIVESTIES / ISVESTIES OPERATORIU TESTAS SEKMINGAS (su nustatytais duomenimis):\n\n" << output.str() << endl;
}