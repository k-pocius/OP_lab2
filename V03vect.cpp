#include "lib.h"
#include "V03vect.h"

int main() {

    srand(time(NULL));
    char a;
    int pasirinkimas;
    int file;

    while (true) {
        try {
            cout << "Ar norite duomenis skaityti iš failo? (t/n): ";
            cin >> a;
            if (a != 't' && a != 'n') {
                throw std::invalid_argument("klaida, įveskite t arba n");
            }
            break; 
        } catch (const std::invalid_argument& e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(123, '\n');
        }
    }
    auto start = std::chrono::high_resolution_clock::now(); // Start timing

    if(a == 't'){
        while(true){
            try{
                cout << "pasirinkite failą: " << endl;
                cout << "1 - kursiokai1000.txt" << endl;
                cout << "2 - kursiokai10000.txt" << endl;
                cout << "3 - kursiokai100000.txt" << endl; 
                cout << "4 - kursiokai1000000.txt" << endl; 
                cout << "5 - kursiokai10000000.txt" << endl; 
                cin >> file;
                if(file != 1 && file != 2 && file != 3 && file != 4 && file != 5){ 
                    throw std::invalid_argument("klaida, įveskite skaičių 1, 2, 3, 4 arba 5");
                }
                break;
            } catch (const std::invalid_argument& e){
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(123, '\n');
            }
        }
        
        int n = 0; // studentu skaicius
        string filename; // failo pavadinimas
        if(file == 1){
            filename = "kursiokai1000.txt";
            n = 1000;
        } else if(file == 2){
            filename = "kursiokai10000.txt";
            n = 10000;
        } else if(file == 3){
            filename = "kursiokai100000.txt";
            n = 100000;
        } else if(file == 4){
            filename = "kursiokai1000000.txt";
            n = 1000000;
        } else {
            filename = "kursiokai10000000.txt";
            n = 10000000;
        }

        
        ifstream file1(filename);
        if (!file1.is_open()) {
            generuojam(filename, n); 
            file1.open(filename); // Reopen the file after generating it
        }

        try {
            if (!file1.is_open()) {
                throw std::invalid_argument("Failed to open file: " + filename);
            }
        
        
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
        } catch (const std::runtime_error& e) {
            cout << e.what() << endl;
            return 1;
        }

    } else {
        while(true){
            try{
                cout << "Pasirinkite duomenų įvedimo būdą:" << endl;
                cout << "1 - Įvesti visus duomenis ranka" << endl;
                cout << "2 - Įvesti pažymių duomenis automatiškai" << endl;
                cout << "3 - Įvesti visus duomenis automatiškai" << endl;
                cin >> pasirinkimas; 
                if(pasirinkimas != 1 && pasirinkimas != 2 && pasirinkimas != 3){
                    throw std::invalid_argument("klaida, įveskite skaičių 1, 2 arba 3");
                }
                break;
            }
            catch(const std::invalid_argument& e){
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(123, '\n');
            }
        }
        skaitom(pasirinkimas);
    }
    auto end = std::chrono::high_resolution_clock::now(); // End timing

    while(true){
        try{
            cout << "pasirinkite skaičiavimo būdą vidurkis(v)/mediana(m): ";
            cin >> a;
            if(a != 'v' && a != 'm'){
                throw std::invalid_argument("klaida, pasirinkite v arba m");
            }
            break;
        }
        catch(const std::invalid_argument& e){
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(123, '\n');
        }
    }

    if (a == 'v') {
        vidurkis();
    } else {
        mediana();
    }
    spausdinam(a);

    std::chrono::duration<double> duration = end - start;
    cout << "Program execution time: " << duration.count() << " seconds" << endl;
    cout << "File generation time: " << generationTime.count() << " seconds" << endl;

    return 0;
}