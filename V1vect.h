#include "lib.h"

class Student {
    private:
        string name; // vardas
        string surn; // pavarde
        vector<int> nd; // nd rezultatai 
        int egz; // egzaminu rez
        double vid; // galutinis vidurkis

    public:
        Student() : name(""), surn(""), egz(0), vid(0) {} // konstruktorius

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

    //seteriai
    void setVid(double Vid) {
        vid = Vid;
    }

    void setEgz(int Egz) {
        egz = Egz;
    }

    void setName(const string& Name) {
        name = Name;
    }

    void setSurn(const string& Surn) {
        surn = Surn;
    }

    void setNd(const vector<int>& Nd) {
        nd = Nd;
    }


    //geteriai
    double getVid() const {
        return vid;
    }

    string getName() const {
        return name;
    }

    string getSurn() const {
        return surn;
    }

    int getEgz() const {
        return egz;
    }

    const vector<int>& getNd() const {
        return nd;
    }
};

std::chrono::duration<double> generationTime; // generavimo laikas
std::chrono::duration<double> readTime; // skaitymo laikas
std::chrono::duration<double> sortTime; // skirstymo laikas
std::chrono::duration<double> writeTime; // rasymo laikas
std::chrono::duration<double> rusiavimoLaikas; // rusiavimo laikas


//random skaiciu generavimas
using hrClock = std::chrono::high_resolution_clock;
std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
std::uniform_int_distribution<int> dist(1, 10);



vector<Student> BadStudents;
vector<Student> GoodStudents;
vector<Student> BadStudents2; // studentai rusiuojam1 funkcijai

string A[] = {"","Jonas", "Petras", "Antanas", "Kazys", "Juozas", "Tomas", "Mantas", "Marius", "Mindaugas", "Gintaras"};
string B[] = {"","Jonaitis", "Petraitis", "Antanaitis", "Kazaitis", "Ugninis", "Trumpulis", "Galiunas", "Gajusis", "Gandras", "Malūnas"};


void skaitom(int pasirinkimas);
void vidurkis();
void mediana();
void spausdinam(char a);
void generuojam(string b, int n);
void rusiuojam2(char a); // skaidymas per puse
void rusiuojam1(char a); // skaidymas is vieno konteinerio i du

bool compareByName(const Student& a, const Student& b) {
    return a.getName() < b.getName();
}
bool compareBySurname(const Student& a, const Student& b) {
    return a.getSurn() < b.getSurn();
}
bool compareByVid(const Student& a, const Student& b) {
    return a.getVid() < b.getVid();
}


void rusiuojam1(char a){
    // nukopijuojam visus elementus i atskira konteineri, kad nereiktu keist toliau esancios programos
    BadStudents2.resize(BadStudents.size());
    copy(BadStudents.begin(), BadStudents.end(), BadStudents2.begin()); 
    BadStudents.clear();


    auto startSort = std::chrono::high_resolution_clock::now();
    sort(BadStudents2.begin(), BadStudents2.end(), compareByVid);
    while(!BadStudents2.empty()){
        if(BadStudents2.back().getVid() >= 5){
            GoodStudents.push_back(BadStudents2.back());
        } else {
            BadStudents.push_back(BadStudents2.back());
        }
    }
    BadStudents2.clear();

    auto endSort = std::chrono::high_resolution_clock::now();
    sortTime = endSort - startSort;  
}

void rusiuojam2(char a){
    // surusiuojam studentus pagal galutini bala
    sort(BadStudents.begin(), BadStudents.end(), compareByVid);


   if(a == 't'){ // jei pasirenkamas spausdinimas faile 
        auto startSort = std::chrono::high_resolution_clock::now();
        // iteruojam nuo galo
        while(BadStudents.back().getVid() >= 5) {
            GoodStudents.push_back(BadStudents.back());
            BadStudents.pop_back(); // istrinam paskutini studenta
        }
        auto endSort = std::chrono::high_resolution_clock::now();
        sortTime = endSort - startSort;  
    }
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


void vidurkis(){
    for(int i = 0; i < BadStudents.size(); i++){
        double sum = 0;
        for(int j = 0; j < BadStudents[i].getNd().size(); j++){
            sum += BadStudents[i].getNd()[j];
        }
        double average;
        average = (sum / BadStudents[i].getNd().size())*0.4 + (BadStudents[i].getEgz()*0.6);
        BadStudents[i].setVid(average);
    }
}


void mediana(){

    //nd rezultatu rikiavimas didejimo tvarka
    for (int i = 0; i < BadStudents.size(); i++) {
        sort(BadStudents[i].getNd().begin(), BadStudents[i].getNd().end()); 
    }

    //medianos skaiciavimas
    for(int i = 0; i < BadStudents.size(); i++){
        double average;
        if(BadStudents[i].getNd().size() % 2 == 0){
            average = ((BadStudents[i].getNd()[BadStudents[i].getNd().size()/2] + BadStudents[i].getNd()[BadStudents[i].getNd().size()/2 - 1]) / 2.0)*0.4 + (BadStudents[i].getEgz()*0.6);
            BadStudents[i].setVid(average);
        } 
        else {
            average = BadStudents[i].getNd()[BadStudents[i].getNd().size()/2]*0.4 + (BadStudents[i].getEgz()*0.6);
            BadStudents[i].setVid(average);
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

    auto startRusiavimas = std::chrono::high_resolution_clock::now();
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
    auto endRusiavimas = std::chrono::high_resolution_clock::now();
    rusiavimoLaikas = endRusiavimas - startRusiavimas;

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
            cout << left << setw(20) << BadStudents[i].getSurn() << setw(14) << BadStudents[i].getName() << setw(20) << BadStudents[i].getVid() << endl;
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
            oss << left << setw(20) << BadStudents[i].getSurn() << setw(16) << BadStudents[i].getName() << BadStudents[i].getVid() << endl;
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
            oss << left << setw(20) << GoodStudents[i].getSurn() << setw(16) << GoodStudents[i].getName() << GoodStudents[i].getVid() << endl;
        }
        ofstream file3("alfos.txt");
        file3 << oss.str();
        file3.close();
        auto endWrite = std::chrono::high_resolution_clock::now();
        writeTime = endWrite - startWrite;
    }
}