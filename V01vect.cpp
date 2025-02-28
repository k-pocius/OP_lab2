#include "lib.h"


int main() {
    srand(time(NULL));
    char a;

    cout << "Ar norite duomenis skaityti iš failo? (t/n): ";
    cin >> a;
    while (!(a == 't' || a == 'n')) {
        cout << "klaida, įveskite t arba n: ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> a;
    }
    auto start = std::chrono::high_resolution_clock::now(); // Start timing
    int pasirinkimas;
    if (a == 't') {
        int file;
        cout << "pasirinkite failą: " << endl;
        cout << "1 - kursiokai10000.txt" << endl;
        cout << "2 - kursiokai100000.txt" << endl;
        cout << "3 - kursiokai1000000.txt" << endl;
        cin >> file;
        while (file != 1 && file != 2 && file != 3) {
            cout << "klaida, įveskite skaičių 1, 2 arba 3: ";
            cin.clear();
            cin.ignore(123, '\n');
            cin >> file;
        }

        string filename;
        if(file == 1){
            filename = "kursiokai10000.txt";
        } else if(file == 2){
            filename = "kursiokai100000.txt";
        } else filename = "kursiokai1000000.txt";
        
        ifstream file1(filename);
        string line;
        getline(file1, line); // Skip the header line

        while (getline(file1, line)) {
            istringstream iss(line);
            Student student;
            iss >> student.name >> student.surn;
            int score;
            while (iss >> score) {
                student.nd.push_back(score);
            }
            student.egz = student.nd.back();
            student.nd.pop_back();
            students.push_back(student);
        }
        file1.close();

    } else {
        cout << "Pasirinkite duomenų įvedimo būdą:" << endl;
        cout << "1 - Įvesti visus duomenis ranka" << endl;
        cout << "2 - Įvesti pažymių duomenis automatiškai" << endl;
        cout << "3 - Įvesti visus duomenis automatiškai" << endl;
        cin >> pasirinkimas;

        while (pasirinkimas != 1 && pasirinkimas != 2 && pasirinkimas != 3) {
            cout << "klaida, įveskite skaičių 1, 2 arba 3: ";
            cin.clear();
            cin.ignore(123, '\n');
            cin >> pasirinkimas;
        }

        skaitom(pasirinkimas);
    }
    auto end = std::chrono::high_resolution_clock::now(); // End timing

    cout << "pasirinkite skaičiavimo būdą vidurkis(v)/mediana(m): ";
    cin >> a;
    while (!(a == 'v' || a == 'm')) {
        cout << "klaida, pasirinkite v arba m: ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> a;
    }
    if (a == 'v') {
        vidurkis();
    } else {
        mediana();
    }
    spausdinam(a);

    std::chrono::duration<double> duration = end - start;
    cout << "Program execution time: " << duration.count() << " seconds" << endl;

    return 0;
}