#include "lib.h"

using namespace std;


struct Homework {
    int score; //nd rezultatai
    Homework* next;
};

struct Student {
    string name; //vardas
    string surn; //pavarde
    int egz; //egzaminu rez
    double vid; //galutinis vidurkis
    Homework* homeworkHead;
    Student* next;
};

string A[] = {"Jonas", "Petras", "Antanas", "Kazys", "Juozas", "Tomas", "Mantas", "Marius", "Mindaugas", "Gintaras"};
string B[] = {"Jonaitis", "Petraitis", "Antanaitis", "Kazaitis", "Ugninis", "Trumpulis", "Galiunas", "Gajusis", "Gandras", "Malūnas"};

void skaitom(Student*& studentHead, int pasirinkimas);
void vidurkis(Student*& studentHead);
void mediana(Student*& studentHead);
void insertStudent(Student*& studentHead, string name, string surn, int egz);
void insertHomework(Homework*& homeworkHead, int score);
void spausdinam(Student*& studentHead, char a);

void sortHomework(Homework*& head) {
    if (head == nullptr) return;

    bool swapped;
    Homework* ptr1;
    Homework* lptr = nullptr;

    do {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->score > ptr1->next->score) {
                swap(ptr1->score, ptr1->next->score);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}


int main(){

    srand(time(NULL)); 
    Student* studentHead = nullptr;

    char a;
    cout << "Pasirinkite duomenų įvedimo būdą:" << endl;            
    cout << "1 - Įvesti visus duomenis ranka" << endl;
    cout << "2 - Įvesti pažymių duomenis automatiškai" << endl;
    cout << "3 - Įvesti visus duomenis automatiškai" << endl; 
    int pasirinkimas; // pasirinkimas kaip įvesti duomenis
    cin >> pasirinkimas;

    // patikrinimas ar įvestas tinkamas skaičius
    while(pasirinkimas != 1 && pasirinkimas != 2 && pasirinkimas != 3){
        cout << "klaida, įveskite skaičių 1, 2 arba 3: ";
        cin.clear();
        cin.ignore(123, '\n');
        cin >> pasirinkimas;
    }

    skaitom(studentHead, pasirinkimas); 

    cout << "pasirinkite skaičiavimo būdą vidurkis(v)/mediana(m): ";
    cin >> a;
    while(!(a == 'v' || a == 'm')){
        cout << "klaida, pasirinkite v arba m: ";
        cin.clear();
        cin >> a;
        cin.ignore(123, '\n');
    }
    if(a == 'v'){
        vidurkis(studentHead);
    }else mediana(studentHead);

    spausdinam(studentHead, a);

    //atlaisvinama dinaminė atmintis
    while (studentHead != nullptr) {
        Student* tempStudent = studentHead;
        while (studentHead->homeworkHead != nullptr) {
            Homework* tempHomework = studentHead->homeworkHead;
            studentHead->homeworkHead = studentHead->homeworkHead->next;
            delete tempHomework; // atlaisvinama dabartinio studento namu darbu atmintis
        }
        studentHead = studentHead->next;
        delete tempStudent; // atlaisvinama dabartinio studento atmintis
    }

    return 0;
}

void skaitom(Student*& studentHead, int pasirinkimas) {
    string tempName; //vardas
    string tempSurn;// pavarde
    int tempEgz;//egz rez
    int tempNd;//namu darbu rez

    bool testi = true; // mokiniu pridejimo ciklas

    while (testi) {
        char teesti; // ar testi mokiniu pridejima

        if(pasirinkimas == 1 || pasirinkimas == 2){
            cout << "įveskite mokinio vardą: ";
            cin >> tempName;
            cout << "įveskite mokinio pavardę: ";
            cin >> tempSurn; 
        }else if(pasirinkimas == 3){
            tempName = A[rand() % 10];
            tempSurn = B[rand() % 10];
        }


        if(pasirinkimas == 1){
            cout << "įveskite egzamino rezultatą: ";
            while (!(cin >> tempEgz)) {
                cout << "klaida, įveskite skaičių: ";
                cin.clear();
                cin.ignore(123, '\n');
            }
        }else if(pasirinkimas == 2 || pasirinkimas == 3) tempEgz = rand() % 10 + 1;

        //pridedam nauja studenta, su vardu, pavarde ir egzamino rezultatu
        insertStudent(studentHead, tempName, tempSurn, tempEgz);

        // randamas paskutinis studento node'as
        Student* currentStudent = studentHead;
        while (currentStudent->next != nullptr) {
            currentStudent = currentStudent->next;
        }

        bool testi2 = true; // namu darbu ivedimo ciklas
        while (testi2) {
            char teesti2; // ar testi namu darbu ivedima
            if(pasirinkimas == 1){
                cout << "įveskite namų darbo rezultatą: ";
                while (!(cin >> tempNd)) {
                    cout << "klaida, įveskite skaičių: ";
                    cin.clear();
                    cin.ignore(123, '\n');
                }
            }else if(pasirinkimas == 2 || pasirinkimas == 3) tempNd = rand() % 10 + 1;

            //pridedam namu darbus paskutiniam studentui 
            insertHomework(currentStudent->homeworkHead, tempNd);

            cout << "ar norite pridėti daugiau namų darbų rezultatų? (t/n): ";
            cin >> teesti2;
            while (!(teesti2 == 't' || teesti2 == 'n')) {
                cout << "klaida, pasirinkite taip(t) arba ne(n): ";
                cin.clear();
                cin.ignore(123, '\n');
                cin >> teesti2;
            }
            if (teesti2 == 'n') testi2 = false;
        }

        cout << "ar norite pridėti daugiau mokinių? (t/n): ";
        cin >> teesti;
        while (!(teesti == 't' || teesti == 'n')) {
            cout << "klaida, pasirinkite taip(t) arba ne(n): ";
            cin.clear();
            cin.ignore(123, '\n');
            cin >> teesti;
        }
        if (teesti == 'n') testi = false;
    }
}

void insertStudent(Student*& studentHead, string name, string surn, int egz){
    struct Student* newStudent = new Student; // priskiriama vieta naujam studento objektui
    struct Student* temp = studentHead; // laikinas pointeris i studento head node

    // priskiriam naujam studentui reiksmes
    newStudent->name = name;
    newStudent->surn = surn;
    newStudent->egz = egz;

    // jei studentu sarasas tuscias, priskiriam nauja studenta head node'ui
    if(studentHead == nullptr){
        studentHead = newStudent;
        return;
    }

    // einam per visus studentus ir priskiriam nauja studenta prie paskutinio studento
    while(temp->next != nullptr){
        temp = temp->next;
    }
    temp->next = newStudent;
}


void insertHomework(Homework*& homeworkHead, int score){
    Homework* newHomework = new Homework; // priskiriama vieta naujam homework objektui

    newHomework->score = score; // priskiriam naujam homework objektui reiksme

    // jei homework sarasas tuscias, priskiriam nauja nd rez head node'ui
    if (homeworkHead == nullptr) {
        homeworkHead = newHomework;
    } else {
        Homework* temp = homeworkHead;
        // einam per visus nd rezultatus ir priskiriam nauja nd rezultata prie paskutinio nd rezultato
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newHomework;
    }
}


void vidurkis(Student*& studentHead){

    double sum = 0;
    Student* currentStudent = studentHead;
    while(currentStudent != nullptr){
        sum = 0;
        int n = 0;
        Homework* currentHomework = currentStudent->homeworkHead;
        while(currentHomework != nullptr){
            sum += currentHomework->score;
            currentHomework = currentHomework->next;
            n++;
        }
        currentStudent->vid = (sum / n)*0.4 + (currentStudent->egz*0.6);
        currentStudent = currentStudent->next;
    }
}

void mediana(Student*& studentHead) {
    Student* currentStudent = studentHead;
    while (currentStudent != nullptr) {
        // nd rikiavimas
        sortHomework(currentStudent->homeworkHead);

        Homework* currentHomework = currentStudent->homeworkHead;
        int count = 0;
        while (currentHomework != nullptr) {
            count++;
            currentHomework = currentHomework->next;
        }

    //    currentHomework = currentStudent->homeworkHead;
        for (int i = 0; i < count / 2 - 1; i++) {
            currentHomework = currentHomework->next;
        }

        double median;
        if (count % 2 == 0) {
            median = (currentHomework->score + currentHomework->next->score) / 2.0;
        } else {
            median = currentHomework->next->score;
        }

        currentStudent->vid = median * 0.4 + (currentStudent->egz * 0.6);
        currentStudent = currentStudent->next;
    }
}

void spausdinam(Student*& studentHead, char a){

    cout << left << setw(15) << "Pavardė" << setw(15) << "Vardas" << setw(20);

    if(a == 'v'){
        cout << "Galutinis (Vid.)" << endl;
    } else cout << "Galutinis (Med.)" << endl;

    cout << "-------------------------------------------------------------" << endl;

    cout << fixed << setprecision(2);


    Student* currentStudent = studentHead;
    while (currentStudent != nullptr) {
        cout << left << setw(15) << currentStudent->surn << setw(15) << currentStudent->name;
        cout << setw(20) << currentStudent->vid<< endl;

        currentStudent = currentStudent->next;
    }
}