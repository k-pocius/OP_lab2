#include "lib.h"
#include "V01vect.h"

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
                cout << "1 - kursiokai10000.txt" << endl;
                cout << "2 - kursiokai100000.txt" << endl;
                cout << "3 - kursiokai1000000.txt" << endl; 
                cin >> file;
                if(file != 1 && file != 2 && file != 3){
                    throw std::invalid_argument("klaida, įveskite skaičių 1, 2 arba 3");
                }
                break;
            } catch (const std::invalid_argument& e){
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(123, '\n');
            }
        }
        
        string filename;
        if(file == 1){
            filename = "kursiokai10000.txt";
        } else if(file == 2){
            filename = "kursiokai100000.txt";
        } else filename = "kursiokai1000000.txt";

        try {
            ifstream file1(filename);
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

    return 0;
}