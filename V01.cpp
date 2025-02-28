#include "lib.h"
#include "V01.h"

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