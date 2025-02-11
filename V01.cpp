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
    double vid; //galutinis vidurkis
    int n; //nd kiekis
}C[100];

int m = 1; //mokiniu sk., namu darbu kiekis

int main(){
    char a;

    skaitom();

    cout << "pasirinkite skaičiavimo būdą vidurkis(v)/mediana(m): ";
    cin >> a;
    while(!(a == 'v' || a == 'm')){
        cout << "klaida, pasirinkite v arba m: ";
        cin.clear();
        cin >> a;
        cin.ignore(123, '\n');
    }
    if(a == 'v'){
        vidurkis();
    } else mediana();

    spausdinam(a);

    return 0;
}

void skaitom(){
    
    bool testi = true;
    int i = 0;    
    while(testi){
        char teesti;

        cout << "įveskite mokinio vardą: ";
        cin >> C[i].name;
        cout << "įveskite mokinio pavardę: ";
        cin >> C[i].surn;

        bool testi2 = true;
        int j = 0;
        while(testi2){
            char teesti2;
            cout << "įveskite " << j+1 << " namų darbo rezultatą: ";
            while(!(cin >> C[i].nd[j])){
                cout << "klaida, įveskite skaičių: ";
                cin.clear();
                cin.ignore(123, '\n');
            }
            cout << "ar norite pridėti daugiau rezultatų? (t/n): ";
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
        C[i].n = j;
        }


        cout << "įveskite egzamino rezultatą: ";
        while(!(cin >> C[i].egz)){
            cout << "klaida, įveskite skaičių: ";
            cin.clear();
            cin.ignore(123, '\n');
        }
        

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
        } else{
            testi = true;
        }
        i++;
        m = i;   
    }
}

void vidurkis(){
    for(int i = 0; i < m; i++){
        double sum = 0;
        for(int j = 0; j < C[i].n; j++){
            sum += C[i].nd[j];
        }
        C[i].vid = (sum / C[i].n)*0.4 + (C[i].egz*0.6);
    }
}

void mediana(){

    //nd rezultatu rikiavimas didejimo tvarka
    for (int i = 0; i < m; i++) {
        sort(C[i].nd, C[i].nd + C[i].n); 
    }

    //medianos skaiciavimas
    for(int i = 0; i < m; i++){
        if(C[i].n % 2 == 0){
            C[i].vid = ((C[i].nd[C[i].n/2] + C[i].nd[(C[i].n/2)-1]) / 2.0)*0.4 + (C[i].egz*0.6);
        } 
        else {
            C[i].vid = C[i].nd[C[i].n/2]*0.4 + (C[i].egz*0.6);
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
        cout << left << setw(15) << C[i].surn << setw(15) << C[i].name << setw(20) << C[i].vid << endl;
    }
}
