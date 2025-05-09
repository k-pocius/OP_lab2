#include "lib.h"

//random skaiciu generavimas
using hrClock = std::chrono::high_resolution_clock;
std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
std::uniform_int_distribution<int> dist(1, 10);

class Student {
    private:
        string name; // vardas
        string surn; // pavarde
        vector<int> nd; // nd rezultatai 
        int egz; // egzaminu rez
        double vid; // galutinis vidurkis

    public:
        Student() : name(""), surn(""), egz(0), vid(0) {} // konstruktorius

        ~Student(){} // destruktorius

        // copy constructor 
        Student(const Student& other)
        : name(other.name), surn(other.surn), nd(other.nd), egz(other.egz), vid(other.vid){
        }

        // copy assignment operator
        Student& operator=(const Student& other){
            if(this != &other) {
                name = other.name;
                surn = other.surn;
                nd = other.nd;
                egz = other.egz;
                vid = other.vid;
            }
            return *this;
        }

       // move constructor
        Student(Student&& other)
            : name(std::move(other.name)),
            surn(std::move(other.surn)),
            nd(std::move(other.nd)),
            egz(std::move(other.egz)),
            vid(std::move(other.vid))
        {
            other.egz = 0;
            other.vid = 0.0;
            other.name = ""; 
            other.surn = ""; 
            other.nd.clear();
        }

        // move assignment operator
        Student& operator=(Student&& other) {
            if (this != &other) {
                name = std::move(other.name);
                surn = std::move(other.surn);
                nd = std::move(other.nd);
                egz = std::move(other.egz);
                vid = std::move(other.vid);

                other.egz = 0;
                other.vid = 0.0;
                other.name = ""; 
                other.surn = ""; 
                other.nd.clear();
            }
            return *this;
        }

        //seteriai
        void setVid(double Vid) {
            vid = Vid;
        }

        void setEgz(int Egz) {
            egz = Egz;
        }

        void setName(string& Name) {
            name = Name;
        }

        void setSurn(string& Surn) {
            surn = Surn;
        }

        void setNd(vector<int>& Nd) {
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

        vector<int>& getNd(){
            return nd;
        }

        friend istream& operator>>(std::istream& in, Student& s) {
            std::string name, surname;
            std::vector<int> nd;
            int temp, egz;

            in >> name >> surname;
            s.setName(name);
            s.setSurn(surname);

            while (in >> temp) {
                nd.push_back(temp);
            }

            if (!nd.empty()) {
                egz = nd.back();
                nd.pop_back();  // Remove last element, which is egz
                s.setEgz(egz);
                s.setNd(nd);
            }

            in.clear();  // Clear stream state if end of line or error
            return in;
        }


            // isvesties operatorius 
        friend ostream& operator<<(ostream& os, const Student& s){
            os << left << setw(20) << s.name << setw(16) << s.surn << s.vid << endl;
            return os;
        }
};

std::chrono::duration<double> generationTime; // generavimo laikas
std::chrono::duration<double> readTime; // skaitymo laikas
std::chrono::duration<double> sortTime; // skirstymo laikas
std::chrono::duration<double> writeTime; // rasymo laikas
std::chrono::duration<double> rusiavimoLaikas; // rusiavimo laikas

vector<Student> BadStudents;
vector<Student> GoodStudents;

void skaitom(int pasirinkimas, string A[], string B[]);
void vidurkis();
void mediana();
void spausdinam(char a);
void generuojam(string b, int n);
void rusiuojam2(); // skaidymas per puse
void rusiuojam1(); // skaidymas is vieno konteinerio i du

bool compareByName(const Student& a, const Student& b) {
    return a.getName() < b.getName();
}
bool compareBySurname(const Student& a, const Student& b) {
    return a.getSurn() < b.getSurn();
}
bool compareByVid(const Student& a, const Student& b) {
    return a.getVid() < b.getVid();
}

void testas() {
    string v = "Jonas";
    string p = "Jonaitis";
    Student s1;
    s1.setName(v);
    s1.setSurn(p);
    s1.setEgz(8);
    vector<int> nd = {7, 8, 9};
    s1.setNd(nd);
    s1.setVid(8.2);

    // Test copy constructor
    Student s2(s1);
    cout << "Student 1:\n" << s1;
    cout << "Student 2 (copied from Student 1):\n" << s2;

    // Test copy assignment operator
    Student s3;
    s3 = s1; 
    cout << "Student 1:\n" << s1;
    cout << "Student 3 (assigned from Student 1):\n" << s3;

    // Test move constructor
    cout << "Student 1 before:\n" << s1;    
    Student s4(std::move(s1)); 
    cout << "Student 1 after:\n" << s1;
    cout << "Student 4 (moved from Student 1):\n" << s4;


    // Test move assignment operator
    Student s5;
    cout << "Student 2 before:\n" << s2; 
    s5 = std::move(s2);
    cout << "Student 2 after:\n" << s2; 
    cout << "Student 5 (moved from Student 2):\n" << s5;
}


void rusiuojam1(){
    // nukopijuojam visus elementus i atskira konteineri, kad nereiktu keist toliau esancios programos
    vector<Student> BadStudents2(BadStudents);
    BadStudents.clear();

    auto startSort = std::chrono::high_resolution_clock::now();
    sort(BadStudents2.begin(), BadStudents2.end(), compareByVid);
    while(!BadStudents2.empty()){
        if(BadStudents2.back().getVid() >= 5){
            GoodStudents.push_back(std::move(BadStudents2.back()));
        } else {
            BadStudents.push_back(std::move(BadStudents2.back()));
        }
        BadStudents2.pop_back(); // istrinam paskutini studenta
    }

    auto endSort = std::chrono::high_resolution_clock::now();
    sortTime = endSort - startSort;  
}

void rusiuojam2(){
    // surusiuojam studentus pagal galutini bala
    sort(BadStudents.begin(), BadStudents.end(), compareByVid);
        auto startSort = std::chrono::high_resolution_clock::now();
        // iteruojam nuo galo
        while(BadStudents.back().getVid() >= 5) {
            GoodStudents.push_back(std::move(BadStudents.back()));
            BadStudents.pop_back(); // istrinam paskutini studenta
        }
        auto endSort = std::chrono::high_resolution_clock::now();
        sortTime = endSort - startSort;  
}

void skaitom(int pasirinkimas, string A[], string B[]){
    bool testi = true;
    int i = 0;    
    string name, surn;
    int egz;
    vector <int> ND;
    Student temp;
    while(testi){
        char teesti;

        //mokinio vardas pavarde
        if(pasirinkimas == 1 || pasirinkimas == 2){
            cout << "įveskite mokinio vardą: ";
            cin >> name;
            cout << "įveskite mokinio pavardę: ";
            cin >> surn; 
        }else if(pasirinkimas == 3){
            name = A[dist(mt)];
            surn = B[dist(mt)];
        }

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
            }else if(pasirinkimas == 2 || pasirinkimas == 3) ND.push_back(dist(mt));

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
                    cin >> egz;
                    if(egz < 0 || egz > 10){
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
        }else if(pasirinkimas == 2 || pasirinkimas == 3) egz = dist(mt);   

        temp.setName(name); // Set the name
        temp.setSurn(surn); // Set the surname
        temp.setEgz(egz);   // Set the exam result
        temp.setNd(ND);     // Set the homework results (ND is a vector<int>)

        // Add the Student object to the BadStudents vector
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

        for (const auto& student : BadStudents) {
            cout << student << endl;
        }
        for (const auto& student : GoodStudents) {
            cout << student << endl;
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
        for (const auto& student : BadStudents) {
            oss << student;
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
        for (const auto& student : GoodStudents) {
            oss << student;
        }
        ofstream file3("alfos.txt");
        file3 << oss.str();
        file3.close();
        auto endWrite = std::chrono::high_resolution_clock::now();
        writeTime = endWrite - startWrite;
    }
}