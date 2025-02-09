#include <iostream>
#include <iomanip>

using namespace std;

void skaitom();
void vidurkis();
void mediana();
void spausdinam(char a);

struct Student {
    string name; //vardas
    string surn; //pavarde
    int nd[20], egz; //nd, egzaminu rez
    int n; //nd kiekis
    double vid; //galutinis vidurkis
}A[100];

int m; //mokiniu sk.


int main(){
    char a;

    skaitom();

    cout << "pasirinkite skaičiavimo būdą vidurkis(v)/mediana(m): ";
    cin >> a;
    if(a == 'v'){
        vidurkis();
    } else if(a == 'm'){
        mediana();
    } else cout << "klaida, įveskite v arba m";

    spausdinam(a);

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

void mediana(){

    for (int i = 0; i < m; i++) {
        sort(A[i].nd, A[i].nd + A[i].n);
    }

    for(int i = 0; i < m; i++){
        if(A[i].n % 2 == 0){
            A[i].vid = ((A[i].nd[A[i].n/2] + A[i].nd[A[i].n/2-1]) / 2)*0.4 + (A[i].egz*0.6);
        } 
        else {
            A[i].vid = A[i].nd[A[i].n/2]*0.4 + (A[i].egz*0.6);
        }
    }
}

void spausdinam(char a){

    cout << left << setw(15) << "Pavardė" << setw(15) << "Vardas" << setw(20);

    if(a == 'v'){
        cout << "Galutinis (Vid.)" << endl;
    } else cout << "Galutinis (Med.)" << endl;

    cout << "-------------------------------------------------------------" << endl;

    cout << fixed << setprecision(2);

    for(int i = 0; i < m; i++){
        cout << left << setw(15) << A[i].surn << setw(15) << A[i].name << setw(20) << A[i].vid << endl;
    }
}