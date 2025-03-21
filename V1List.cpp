#include "lib.h"
#include "V1List.h"

int main() {

    auto start = std::chrono::high_resolution_clock::now(); // Start timing

    char b; // ar nori skaityti is failo
    char a; // ar vidurkis ar mediana
    int pasirinkimas;
    int file;

    while (true) {
        try {
            cout << "Ar norite duomenis skaityti iš failo? (t/n): ";
            cin >> b;
            if (b != 't' && b != 'n') {
                throw std::invalid_argument("klaida, įveskite t arba n");
            }
            break; 
        } catch (const std::invalid_argument& e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(123, '\n');
        }
    }

    string filename; // failo pavadinimas
    if(b == 't'){ // skaitymas is failo
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

        switch(file){
            case 1:
                filename = "kursiokai1000.txt";
                n = 1000;
                break;
            case 2:
                filename = "kursiokai10000.txt";
                n = 10000;
                break;
            case 3:
                filename = "kursiokai100000.txt";
                n = 100000;
                break;
            case 4:
                filename = "kursiokai1000000.txt";
                n = 1000000;
                break;
            case 5:
                filename = "kursiokai10000000.txt";
                n = 10000000;   
                break;             
        }

        
        ifstream file1(filename); // bandoma atidaryti failą
        if (!file1) { // jei nepavyksta, sukuriamas failas, ir atidaromas

            auto startt = std::chrono::high_resolution_clock::now();
            generuojam(filename, n); 
            auto endd = std::chrono::high_resolution_clock::now();
            generationTime = endd - startt;


            file1.open(filename);
        }

        try { // tikrinam ar atsidare failas
            if (!file1) {
                throw std::invalid_argument("Failed to open file: " + filename);
            }
        
        
            string line;


            auto startRead = std::chrono::high_resolution_clock::now();
            getline(file1, line); // praleidziam primaja eilute

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
                BadStudents.push_back(student);
            }
            file1.close();
            auto endRead = std::chrono::high_resolution_clock::now();
            readTime = endRead - startRead;

            
        } catch (const std::runtime_error& e) {
            cout << e.what() << endl;
            return 1;
        }


    } else { // duomenu ivedimas ranka, ar automatiskai
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
        skaitom(pasirinkimas); // skaitymas
    }


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
    rusiuojam2(b);
    rusiuojam1(b); // studentu rusiavimas i skirtingus failus
    spausdinam(a); // spausdinimas


    auto end = std::chrono::high_resolution_clock::now(); // End timing
    std::chrono::duration<double> programTime = end - start;
    cout << fixed << setprecision(2);
    cout << "--------------------------------------" << endl;
    cout << endl;
    cout << "failas: " << filename << endl;
    cout << "Failo kūrimo laikas: " << generationTime.count() << "s" << endl;
    cout << "Duomenų nuskaitymo laikas: " << readTime.count() << "s" << endl;     
    cout << "Skirstymo laikas į blogus ir gerus: " << sortTime.count() << "s" << endl;
    cout << "Rezultatų išvedimo laikas: " << writeTime.count() << "s" << endl;
    cout << "Visos programos laikas: " << programTime.count() << "s" << endl;
    cout << endl;
    cout << "--------------------------------------" << endl;

    return 0;
}