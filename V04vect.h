#include "lib.h"

struct Student {
    string name; // vardas
    string surn; // pavarde
    vector<int> nd; // nd rezultatai 
    int egz; // egzaminu rez
    double vid; // galutinis vidurkis
};



std::chrono::duration<double> generationTime; // generavimo laikas
std::chrono::duration<double> readTime; // skaitymo laikas
std::chrono::duration<double> sortTime; // rusiavimo laikas
std::chrono::duration<double> writeTime; // rasymo laikas


//random skaiciu generavimas
using hrClock = std::chrono::high_resolution_clock;
std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
std::uniform_int_distribution<int> dist(1, 10);



vector<Student> BadStudents;
vector<Student> GoodStudents;

string A[] = {"","Jonas", "Petras", "Antanas", "Kazys", "Juozas", "Tomas", "Mantas", "Marius", "Mindaugas", "Gintaras"};
string B[] = {"","Jonaitis", "Petraitis", "Antanaitis", "Kazaitis", "Ugninis", "Trumpulis", "Galiunas", "Gajusis", "Gandras", "Malūnas"};


void skaitom(int pasirinkimas);
void vidurkis();
void mediana();
void spausdinam(char a);
void generuojam(string b, int n);
void rusiuojam();
bool compareByName(const Student& a, const Student& b) {
    return a.name < b.name;
}
bool compareBySurname(const Student& a, const Student& b) {
    return a.surn < b.surn;
}
bool compareByVid(const Student& a, const Student& b) {
    return a.vid < b.vid;
}


void rusiuojam(){
    // surusiuojam studentus pagal galutini bala
    sort(BadStudents.begin(), BadStudents.end(), compareByVid);



    auto startSort = std::chrono::high_resolution_clock::now();
    // iteruojam nuo galo
    while(BadStudents.back().vid >= 5) {
        GoodStudents.push_back({BadStudents.back().name, BadStudents.back().surn, {}, 0, BadStudents.back().vid});
        BadStudents.pop_back(); // istrinam paskutini studenta~
    }
    auto endSort = std::chrono::high_resolution_clock::now();
    sortTime = endSort - startSort;
}


void generuojam(string b, int n){

    ostringstream oss;
    oss << left << setw(20) << "Vardas" << setw(20) << "Pavardė";
    for(int i = 1; i <= 15; i++){
        oss << "ND" << setw(5) << i;
    }
    oss << "Egz." << endl;

    for(int i = 0; i < n; i++){
        oss << left << "Vardas" << setw(14) << i+1 << "Pavardė" << setw(12) << i+1;
        for(int j = 0; j < 15; j++){
            oss << setw(7) << dist(mt);
        }
        oss << dist(mt)<< endl;
    }
    ofstream fr(b);
    fr << oss.str();
    fr.close();  // Close file
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
            temp.name = A[dist(mt)];
            temp.surn = B[dist(mt)];
        }


        temp.nd.clear();

        //nd rezultatai
        bool testi2 = true;
        int j = 0;
        while(testi2){
            char teesti2;
            int nd_result;
            if(pasirinkimas == 1){
                while (true){
                    try{
                        cout << "įveskite " << j+1 << " namų darbo rezultatą: ";
                        cin >> nd_result;
                        if(nd_result < 0 || nd_result > 10){
                            throw std::invalid_argument ("klaida, įveskite skaičių nuo 0 iki 10");
                        }
                        break;
                    }
                    catch(const std::invalid_argument& e){
                    cout << e.what() << endl;
                    cin.clear();
                    cin.ignore(123, '\n');
                    }
                }
            }else if(pasirinkimas == 2 || pasirinkimas == 3) nd_result = dist(mt);
            temp.nd.push_back(nd_result);

            while(true){
                try{
                    cout << "ar norite pridėti daugiau namų darbų rezultatų? (t/n): ";
                    cin >> teesti2; 
                    if(!(teesti2 == 't' || teesti2 == 'n')){
                        throw std::invalid_argument("klaida, pasirinkite taip(t) arba ne(n)");
                    }
                    break;
                }
                catch(const std::invalid_argument& e){
                    cout << e.what() << endl;
                    cin.clear();
                    cin.ignore(123, '\n');
                }
            }

            if(teesti2 == 'n'){
                testi2 = false;
            } else testi2 = true;
            j++;
            if(j == 20) break;
        }


        //egzamino rezultatas
        if(pasirinkimas == 1){
            while (true){
                try{
                    cout << "įveskite egzamino rezultatą: ";
                    cin >> temp.egz;
                    if(temp.egz < 0 || temp.egz > 10){
                        throw std::invalid_argument ("klaida, įveskite skaičių nuo 0 iki 10");
                    }
                    break;
                }
                catch(const std::invalid_argument& e){
                    cout << e.what() << endl;
                    cin.clear();
                    cin.ignore(123, '\n');
                }
            }
        }else if(pasirinkimas == 2 || pasirinkimas == 3) temp.egz = dist(mt);
        BadStudents.push_back(temp);

        
        
        while(true){
            try{
                cout << "ar norite pridėti daugiau mokinių? (t/n): ";
                cin >> teesti;
                if(!(teesti == 't' || teesti == 'n')){
                    throw std::invalid_argument("klaida, pasirinkite taip(t) arba ne(n)");
                }
                break;
            }
            catch(const std::invalid_argument& e){
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(123, '\n');
            }
        }

        if(teesti == 'n'){
            testi = false;
        }
        i++;
        if(i == 15) break;
    }
}


void vidurkis(){
    for(int i = 0; i < BadStudents.size(); i++){
        double sum = 0;
        for(int j = 0; j < BadStudents[i].nd.size(); j++){
            sum += BadStudents[i].nd[j];
        }
        BadStudents[i].vid = (sum / BadStudents[i].nd.size())*0.4 + (BadStudents[i].egz*0.6);
    }
}


void mediana(){

    //nd rezultatu rikiavimas didejimo tvarka
    for (int i = 0; i < BadStudents.size(); i++) {
        sort(BadStudents[i].nd.begin(), BadStudents[i].nd.end()); 
    }

    //medianos skaiciavimas
    for(int i = 0; i < BadStudents.size(); i++){
        if(BadStudents[i].nd.size() % 2 == 0){
            BadStudents[i].vid = ((BadStudents[i].nd[BadStudents[i].nd.size()/2] + BadStudents[i].nd[BadStudents[i].nd.size()/2 - 1]) / 2.0)*0.4 + (BadStudents[i].egz*0.6);
        } 
        else {
            BadStudents[i].vid = BadStudents[i].nd[BadStudents[i].nd.size()/2]*0.4 + (BadStudents[i].egz*0.6);
        }
    }
}


void spausdinam(char a) {

    int pasirinkimas;
    while(true){
        try{
            cout << "Kur norite matyti rezultatus?" << endl;
            cout << "1 - ekrane" << endl;
            cout << "2 - faile" << endl;
            cin >> pasirinkimas;
            if(pasirinkimas != 1 && pasirinkimas != 2){
                throw std::invalid_argument("klaida, įveskite skaičių 1 arba 2");
            }
            break;
        }
        catch(const std::invalid_argument& e){
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(123, '\n');
        }
    }

    int rusiavimas;
    while(true){
        try{
            cout << "Kaip norite surūšiuoti rezultatus?" << endl;
            cout << "1 - pagal vardą" << endl;
            cout << "2 - pagal pavardę" << endl;
            cout << "3 - pagal galutinį balą" << endl;
            cin >> rusiavimas;
            if(rusiavimas != 1 && rusiavimas != 2 && rusiavimas != 3){
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

    if(rusiavimas == 1){
        sort(BadStudents.begin(), BadStudents.end(), compareByName);
        sort(GoodStudents.begin(), GoodStudents.end(), compareByName);
    } else if(rusiavimas == 2){
        sort(BadStudents.begin(), BadStudents.end(), compareBySurname);
        sort(GoodStudents.begin(), GoodStudents.end(), compareBySurname);
    } else{
        sort(BadStudents.begin(), BadStudents.end(), compareByVid);
        sort(GoodStudents.begin(), GoodStudents.end(), compareByVid);
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

        for (int i = 0; i < BadStudents.size(); i++) {
            cout << left << setw(20) << BadStudents[i].surn << setw(14) << BadStudents[i].name << setw(20) << BadStudents[i].vid << endl;
        }
    } else {

        // geri mokiniai

        auto startWrite = std::chrono::high_resolution_clock::now();        
        ostringstream oss;
        oss << left << setw(20) << "Vardas" << setw(15) << "Pavardė" << setw(20);

        if (a == 'v') {
            oss << "Galutinis (Vid.)" << endl;
        } else {
            oss << "Galutinis (Med.)" << endl;
        }

        oss << "-------------------------------------------------------------" << endl;
        oss << fixed << setprecision(2);
        for (int i = 0; i < BadStudents.size(); i++) {
            oss << left << setw(20) << BadStudents[i].name << setw(16) << BadStudents[i].surn << BadStudents[i].vid << endl;
        }
        ofstream file2("susmukeliai.txt");
        file2 << oss.str();
        file2.close();

        oss.str("");
        oss.clear();

        //blogi mokiniai
        oss << left << setw(20) << "Vardas" << setw(15) << "Pavardė" << setw(20);

        if (a == 'v') {
            oss << "Galutinis (Vid.)" << endl;
        } else {
            oss << "Galutinis (Med.)" << endl;
        }

        oss << "-------------------------------------------------------------" << endl;

        oss << fixed << setprecision(2);
        for (int i = 0; i < GoodStudents.size(); i++) {
            oss << left << setw(20) << GoodStudents[i].name << setw(16) << GoodStudents[i].surn << GoodStudents[i].vid << endl;
        }
        ofstream file3("alfos.txt");
        file3 << oss.str();
        file3.close();
        auto endWrite = std::chrono::high_resolution_clock::now();
        writeTime = endWrite - startWrite;
    }
}
