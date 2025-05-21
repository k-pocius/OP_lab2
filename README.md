Naudojimosi instrukcijos:
Norint paleisti programą, į terminalą įvesti "make run_test"
Norint ištrinti sukompiliuotus failus, į terminalą  įvesti "make clean"

Ši programa leidžia:

Įvesti studentų duomenis rankiniu būdu, automatiškai arba iš failo
Apskaičiuoti galutinį pažymių rezultatą pagal vidurkį arba medianą
Skirstyti studentus į dvi grupes: pažangius ir nepažangius pagal dvi strategijas
Rezultatus išvesti į ekraną arba į failus alfos.txt ir susmukeliai.txt
Rūšiuoti studentus pagal vardą, pavardę arba galutinį rezultatą

Programa naudoja dvi klases. Bazinę Žmogaus klasę, kuri aprašo bendrus žmogaus atributus
(vardas, pavardė). Turi gryną virtualią funckiją test(), todėl iš jos negalima kurti objektų. Ir
klasę Studentas, kuri yra paveldima iš Žmogaus klasės. Joje saugomi Studento pažymiai ir galutinis rezultatas. 
Implementuoja test() metodą, galima kurti Studento tipo objektus.

![alt text](baseClass.png)


Perdengtų metodų paaiškinimas 

-------------------------- Įvesties būdai ---------------------------
| Tipas       | Realizacija                      | Aprašymas                                        |
|-------------|----------------------------------|--------------------------------------------------|
| Rankinis    | pasirinkimas == 1                | Vartotojas suveda vardą, pavardę, ND ir egzaminą |
| Pusiau auto | pasirinkimas == 2                | Automatiškai generuojami tik pažymiai            |
| Automatinis | pasirinkimas == 3                | Visi duomenys sugeneruojami automatiškai         |
| Iš failo    | failo pasirinkimas == 1,2,3,4,5  | Visi duomenys sugeneruojami kursiokai.txt faile  |


-------------------------- Išvesties būdai ---------------------------
| Tipas    | Realizacija                     | Failai                                        |
|----------|---------------------------------|-----------------------------------------------|
| Ekranas  | pasirinkimas == 1, spausdinam() | Duomenys išvedami į ekraną pagal rikiavimą    |
| Į failą  | pasirinkimas == 2, spausdinam() | Sukuriami alfos.txt ir susmukeliai.txt        |



![alt text](image.png)

<br>

![alt text](test.png)

<br>


Vektoriaus funkcijų paaiškinimas:

1. push_back funkcija
Paskirtis: Prideda naują elementą į vektoriaus pabaigą.

Veikimas: Jei nėra pakankamai vietos (t. y. talpa lygi dydžiui), talpa padvigubinama.
Sukuriamas naujas masyvas su didesne talpa, į jį perkopijuojami esami elementai.
Galiausiai pridedamas naujas elementas į galą.


2. pop_back funkcija
Paskirtis: Pašalina paskutinį vektoriaus elementą.

Veikimas: Patikrina, ar vektorius nėra tuščias.
Sumažina dydį vienetu.


3. getSize funkcija
Paskirtis: Grąžina šiuo metu esančių elementų skaičių vektoriuje.
Veikimas: Tiesiogiai grąžina size reikšmę.


4. resize funkcija
Paskirtis: Keičia vektoriaus dydį į nurodytą.

Veikimas: Jei naujas dydis didesnis nei esamas, pridedami numatytieji elementai.
Jei mažesnis – vektoriaus dydis sumažinamas.
Jei reikia – padidinama talpa.


5. Konstruktorius ir destruktorius
Paskirtis: Konstruktorius inicializuoja tuščią vektorių.
Destruktorius atlaisvina užimtą atmintį.

Veikimas: Konstruktorius nustato data = nullptr, size = 0, capacity = 0.
Destruktorius naudoja delete[] atlaisvinti dinamiškai priskirtą atmintį.



==== REZULTATŲ LENTELĖ ====
| Veiksmas                        | V1.0 (1M) | V1.1 (1M) |  V1.0 (10M) |  V1.1 (10M) |
|---------------------------------|-----------|-----------|-------------|-------------|
| Failo kūrimo laikas             |   3.15s   |   3.02s   |   29.61s    |   29.57s    |
| Duomenų nuskaitymo laikas       |   7.54s   |   8.08s   |   76.73s    |   82.71s    |
| Skirstymo laikas                |   0.84s   |   1.14s   |    9.70s    |   12.18s    |
| Rezultatų išvedimo laikas       |   0.40s   |   0.39s   |    3.96s    |    4.25s    |
| Rūšiavimo tvarka laikas         |   0.04s   |   0.18s   |    0.45s    |    1.69s    |
|---------------------------------|-----------|-----------|-------------|-------------|
| Visos programos laikas          |   18.68s  |   21.86s  |   136.59s   |   146.66s   |



==== FLAGŲ PALYGINIMAS ====
| Veiksmas                        |  V1 -O1 |  V1 -O2 |  V1 -O3 |  V1.1 -O1 |  V1.1 -O2 |  V1.1 -O3 |
|---------------------------------|---------|---------|---------|-----------|-----------|-----------|
| Failo kūrimo laikas             |  2.96s  |  2.99s  |  3.00s  |   2.97s   |   3.01s   |   2.97s   |
| Duomenų nuskaitymo laikas       |  7.48s  |  7.51s  |  7.53s  |   8.09s   |   8.09s   |   8.09s   |
| Skirstymo į blogus/gerus laikas |  0.84s  |  0.83s  |  0.83s  |   1.14s   |   1.15s   |   1.15s   |
| Rezultatų išvedimo laikas       |  0.40s  |  0.40s  |  0.40s  |   0.42s   |   0.40s   |   0.45s   |
| Rūšiavimo tvarka laikas         |  0.03s  |  0.03s  |  0.04s  |   0.18s   |   0.18s   |   0.18s   |
|---------------------------------|---------|---------|---------|-----------|-----------|-----------|
| Visos programos laikas          | 19.06s  |  19.32s |  18.03s |   18.01s  |   17.16s  |   17.05s  |


+-------------------+------------------------+---------------------------+
|      File         | Custom Vector (laikas) | STL Vector (laikas)      |
+-------------------+------------------------+---------------------------+
| 1000.txt          | 0.01s                  | 0.01s                     |
| 10000.txt         | 0.03s                  | 0.04s                     |
| 100000.txt        | 0.13s                  | 0.18s                     |
| 1000000.txt       | 1.06s                  | 1.54s                     |
| 10000000.txt      | 11.74s                 | 16.08s                    |
+-------------------+------------------------+---------------------------+
