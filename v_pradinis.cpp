#include "lib.h"
#include "v_pradinis.h"

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
