#include <iostream>
#include <iomanip>

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

void skaitom(Student*& studentHead);
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

    Student* studentHead = nullptr;

    char a;

    skaitom(studentHead);

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

    return 0;
}

void skaitom(Student*& studentHead) {
    string tempName;
    string tempSurn;
    int tempEgz;
    int tempNd;

    bool testi = true;

    while (testi) {
        char teesti;

        cout << "įveskite mokinio vardą: ";
        cin >> tempName;
        cout << "įveskite mokinio pavardę: ";
        cin >> tempSurn;

        cout << "įveskite egzamino rezultatą: ";
        while (!(cin >> tempEgz)) {
            cout << "klaida, įveskite skaičių: ";
            cin.clear();
            cin.ignore(123, '\n');
        }

        insertStudent(studentHead, tempName, tempSurn, tempEgz);

        Student* currentStudent = studentHead;
        while (currentStudent->next != nullptr) {
            currentStudent = currentStudent->next;
        }

        bool testi2 = true;
        while (testi2) {
            char teesti2;
            cout << "įveskite namų darbo rezultatą: ";
            while (!(cin >> tempNd)) {
                cout << "klaida, įveskite skaičių: ";
                cin.clear();
                cin.ignore(123, '\n');
            }

            insertHomework(currentStudent->homeworkHead, tempNd);

            cout << "ar norite pridėti daugiau rezultatų? (t/n): ";
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
    struct Student* newStudent = new Student;
    struct Student* temp = studentHead;

    newStudent->name = name;
    newStudent->surn = surn;
    newStudent->egz = egz;

    if(studentHead == nullptr){
        studentHead = newStudent;
        return;
    }

    while(temp->next != nullptr){
        temp = temp->next;
    }
    temp->next = newStudent;
}


void insertHomework(Homework*& homeworkHead, int score){
    Homework* newHomework = new Homework;

    newHomework->score = score;

    if (homeworkHead == nullptr) {
        homeworkHead = newHomework;
    } else {
        Homework* temp = homeworkHead;
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
        // Sort the homework results for the current student
        sortHomework(currentStudent->homeworkHead);

        // Calculate the median
        Homework* currentHomework = currentStudent->homeworkHead;
        int count = 0;
        while (currentHomework != nullptr) {
            count++;
            currentHomework = currentHomework->next;
        }

        currentHomework = currentStudent->homeworkHead;
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