#include <iostream>
#include <iomanip>

using namespace std;

void skaitom();
void vidurkis();
void spausdinam();

struct Student {
    string name; //vardas
    string surn; //pavarde
    int nd[20], egz; //nd, egzaminu rez
    int n; //nd kiekis
    double vid; //galutinis vidurkis
}A[100];

int m; //mokiniu sk.


int main(){

    skaitom();
    vidurkis();
    spausdinam();

    return 0;
}

void skaitom(){
    
    cout << "įveskite mokinių skaičių: ";
    cin >> m;
    for(int i = 0; i < m; i++){

        cout << "įveskite mokinio vardą: ";
        cin >> A[i].name;
        cout << "įveskite mokinio pavardę: ";
        cin >> A[i].surn;
        cout << "įveskite namų darbų kiekį: ";
        cin >> A[i].n;

        for(int j = 0; j < A[i].n; j++){
            cout << "įveskite " << j+1 << " namų darbo rezultatą: ";
            cin >> A[i].nd[j];
        }
        cout << "įveskite egzamino rezultatą: ";
        cin >> A[i].egz;
    }
}

void vidurkis(){
    for(int i = 0; i < m; i++){
        double sum = 0;
        for(int j = 0; j < A[i].n; j++){
            sum += A[i].nd[j];
        }
        A[i].vid = (sum / A[i].n)*0.4 + (A[i].egz*0.6);
    }
}

void spausdinam(){

    cout << left << setw(15) << "Pavardė" << setw(15) << "Vardas" << setw(20) << "Galutinis (Vid.)" << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << fixed << setprecision(2);

    for(int i = 0; i < m; i++){
        cout << left << setw(15) << A[i].surn << setw(15) << A[i].name << setw(20) << A[i].vid << endl;
    }
}