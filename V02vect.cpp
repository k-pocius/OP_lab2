#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

struct Student {
    string name; // vardas
    string surn; // pavarde
    vector<int> nd; // nd rezultatai 
    int egz; // egzaminu rez
    double vid; // galutinis vidurkis
};

vector<Student> students;

string A[] = {"Jonas", "Petras", "Antanas", "Kazys", "Juozas", "Tomas", "Mantas", "Marius", "Mindaugas", "Gintaras"};
string B[] = {"Jonaitis", "Petraitis", "Antanaitis", "Kazaitis", "Ugninis", "Trumpulis", "Galiunas", "Gajusis", "Gandras", "Malūnas"};

void skaitom(int pasirinkimas);
void vidurkis();
void mediana();
void spausdinam(char a);

bool compareByName(const Student& a, const Student& b) {
    return a.name < b.name;
}

bool compareBySurname(const Student& a, const Student& b) {
    return a.surn < b.surn;
}

bool compareByVid(const Student& a, const Student& b) {
    return a.vid < b.vid;
}


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
    auto start = chrono::high_resolution_clock::now(); // Start timing
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
    auto end = chrono::high_resolution_clock::now(); // End timing

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

    chrono::duration<double> duration = end - start;
    cout << "Program execution time: " << duration.count() << " seconds" << endl;

    return 0;
}

void skaitom(int pasirinkimas){
    
    bool testi = true;
    int i = 0;    
    Student temp;
    while(testi){
        char teesti;

        //mokinio vardas pavarde
        if(pasirinkimas == 1 || pasirinkimas == 2){
            cout << "įveskite mokinio vardą: ";
            cin >> temp.name;
            cout << "įveskite mokinio pavardę: ";
            cin >> temp.surn; 
        }else if(pasirinkimas == 3){
            temp.name = A[rand() % 10];
            temp.surn = B[rand() % 10];
        }


        temp.nd.clear();

        //nd rezultatai
        bool testi2 = true;
        int j = 0;
        while(testi2){
            char teesti2;
            int nd_result;
            if(pasirinkimas == 1){
                cout << "įveskite " << j+1 << " namų darbo rezultatą: ";
                while(!(cin >> nd_result)){
                    cout << "klaida, įveskite skaičių: ";
                    cin.clear();
                    cin.ignore(123, '\n');
                } 
            }else if(pasirinkimas == 2 || pasirinkimas == 3) nd_result = rand() % 10 + 1;
            temp.nd.push_back(nd_result);

            cout << "ar norite pridėti daugiau namų darbų rezultatų? (t/n): ";
            cin >> teesti2;
            while(!(teesti2 == 't' || teesti2 == 'n')){
                cout << "klaida, pasirinkite taip(t) arba ne(n): ";
                cin.clear();
                cin >> teesti2;
                cin.ignore(123, '\n');
            }
            if(teesti2 == 'n'){
                testi2 = false;
            } else testi2 = true;
            j++;
            if(j == 20) break;
        }


        //egzamino rezultatas
        if(pasirinkimas == 1){
            cout << "įveskite egzamino rezultatą: ";
            while (!(cin >> temp.egz)) {
                cout << "klaida, įveskite skaičių: ";
                cin.clear();
                cin.ignore(123, '\n');
            }
        }else if(pasirinkimas == 2 || pasirinkimas == 3) temp.egz = rand() % 10 + 1;
        students.push_back(temp);

        
        
        cout << "ar norite pridėti daugiau mokinių? (t/n): ";
        cin >> teesti;
        while(!(teesti == 't' || teesti == 'n')){
            cout << "klaida, pasirinkite taip(t) arba ne(n): ";
            cin.clear();
            cin >> teesti;
            cin.ignore(123, '\n');
        }
        if(teesti == 'n'){
            testi = false;
        }
        i++;
        if(i == 15) break;
    }
}

void vidurkis(){
    for(int i = 0; i < students.size(); i++){
        double sum = 0;
        for(int j = 0; j < students[i].nd.size(); j++){
            sum += students[i].nd[j];
        }
        students[i].vid = (sum / students[i].nd.size())*0.4 + (students[i].egz*0.6);
    }
}

void mediana(){

    //nd rezultatu rikiavimas didejimo tvarka
    for (int i = 0; i < students.size(); i++) {
        sort(students[i].nd.begin(), students[i].nd.end()); 
    }

    //medianos skaiciavimas
    for(int i = 0; i < students.size(); i++){
        if(students[i].nd.size() % 2 == 0){
            students[i].vid = ((students[i].nd[students[i].nd.size()/2] + students[i].nd[students[i].nd.size()/2 - 1]) / 2.0)*0.4 + (students[i].egz*0.6);
        } 
        else {
            students[i].vid = students[i].nd[students[i].nd.size()/2]*0.4 + (students[i].egz*0.6);
        }
    }
}

void spausdinam(char a) {

    cout << "Kur norite matyti rezultatus?" << endl;
    cout << "1 - ekrane" << endl;
    cout << "2 - faile" << endl;
    int pasirinkimas;
    cin >> pasirinkimas;
    while (pasirinkimas != 1 && pasirinkimas != 2) {
        cout << "klaida, įveskite skaičių 1 arba 2: ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> pasirinkimas;
    }
    int rusiavimas;
    cout << "Kaip norite surūšiuoti rezultatus?" << endl;
    cout << "1 - pagal vardą" << endl;
    cout << "2 - pagal pavardę" << endl;
    cout << "3 - pagal galutinį balą" << endl;
    cin >> rusiavimas;
    while (rusiavimas != 1 && rusiavimas != 2 && rusiavimas != 3) {
        cout << "klaida, įveskite skaičių 1, 2 arba 3: ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> rusiavimas;
    }

    if(rusiavimas == 1){
        sort(students.begin(), students.end(), compareByName);
    } else if(rusiavimas == 2){
        sort(students.begin(), students.end(), compareBySurname);
    } else{
        sort(students.begin(), students.end(), compareByVid);
    }

    if(pasirinkimas == 1){
        cout << left << setw(20) << "Pavardė" << setw(15) << "Vardas" << setw(20);

        if (a == 'v') {
            cout << "Galutinis (Vid.)" << endl;
        } else {
            cout << "Galutinis (Med.)" << endl;
        }

        cout << "-------------------------------------------------------------" << endl;

        cout << fixed << setprecision(2);

        for (int i = 0; i < students.size(); i++) {
            cout << left << setw(20) << students[i].surn << setw(14) << students[i].name << setw(20) << students[i].vid << endl;
        }
    } else {
        ofstream file2("rezultatai.txt");
        file2 << left << setw(20) << "Vardas" << setw(15) << "Pavardė" << setw(20);

        if (a == 'v') {
            file2 << "Galutinis (Vid.)" << endl;
        } else {
            file2 << "Galutinis (Med.)" << endl;
        }

        file2 << "-------------------------------------------------------------" << endl;

        file2 << fixed << setprecision(2);

        for (int i = 0; i < students.size(); i++) {
            file2 << left << setw(20) << students[i].name << setw(14) << students[i].surn << setw(20) << students[i].vid << endl;
        }
        file2.close();
    }
}