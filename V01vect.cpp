#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

void skaitom();
void vidurkis();
void mediana();
void spausdinam(char a);

struct Student {
    string name; //vardas
    string surn; //pavarde
    vector<int> nd; //nd rezultatai 
    int egz; //egzaminu rez
    double vid; //galutinis vidurkis
    int n; //nd kiekis
};

vector<Student> students;

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
    Student temp;
    while(testi){
        char teesti;

        //mokinio vardas pavarde
        cout << "įveskite mokinio vardą: ";
        cin >> temp.name;
        cout << "įveskite mokinio pavardę: ";
        cin >> temp.surn;


        temp.nd.clear();

        //nd rezultatai
        bool testi2 = true;
        int j = 0;
        while(testi2){
            char teesti2;
            int nd_result;
            cout << "įveskite " << j+1 << " namų darbo rezultatą: ";
            while(!(cin >> nd_result)){
                cout << "klaida, įveskite skaičių: ";
                cin.clear();
                cin.ignore(123, '\n');
            }
            temp.nd.push_back(nd_result);

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
            if(j == 20) break;
        }


        //egzamino rezultatas
        cout << "įveskite egzamino rezultatą: ";
        while(!(cin >> temp.egz)){
            cout << "klaida, įveskite skaičių: ";
            cin.clear();
            cin.ignore(123, '\n');
        }
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

void spausdinam(char a){

    cout << left << setw(15) << "Pavardė" << setw(15) << "Vardas" << setw(20);

    if(a == 'v'){
        cout << "Galutinis (Vid.)" << endl;
    } else cout << "Galutinis (Med.)" << endl;

    cout << "-------------------------------------------------------------" << endl;

    cout << fixed << setprecision(2);

    for(int i = 0; i < students.size(); i++){
        cout << left << setw(15) << students[i].surn << setw(15) << students[i].name << setw(20) << students[i].vid << endl;
    }
}
