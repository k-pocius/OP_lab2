#ifndef V1_5VECT_H
#define V1_5VECT_H

#include "lib.h"

extern std::chrono::duration<double> generationTime; // generavimo laikas
extern std::chrono::duration<double> readTime; // skaitymo laikas
extern std::chrono::duration<double> sortTime; // skirstymo laikas
extern std::chrono::duration<double> writeTime; // rasymo laikas
extern std::chrono::duration<double> rusiavimoLaikas; // rusiavimo laikas

template <typename T>
class Vector{
    private:
        T* data; // duomenu masyvas
        size_t size; // masyvo dydis
        size_t capacity; // talpa

    public:
        Vector() : data(nullptr), size(0), capacity(0) {} // konstruktorius;

        ~Vector(){
            delete[] data;
        }

        //index operator
        T& operator[](size_t index) {
            return data[index];
        }

        const T& operator[](size_t index) const {
            return data[index];
        }


        //back function
        T& back() {
            return data[size - 1];
        }

        const T& back() const {
            return data[size - 1];
        }

        //empty function
        bool empty() const {
            return size == 0;
        }

        //clear function
        void clear() {
            size = 0;
        }


        // begin, end function
        T* begin() {
            return data;
        }

        const T* begin() const {
            return data;
        }


        T* end() {
            return data + size;
        }

        const T* end() const {
            return data + size;
        }

            
        // push_back funkcija
        void push_back(const T& value) {
            if (size == capacity) {
                size_t new_capacity = (capacity == 0) ? 1 : capacity * 2;
                T* new_data = new T[new_capacity];

                for (size_t i = 0; i < size; ++i) {
                    new_data[i] = data[i];
                }

                delete[] data;
                data = new_data;
                capacity = new_capacity;
            }

            data[size++] = value;
        }


        //pop_back
        void pop_back() {
            if (size == 0) {
                // Vector is already empty
                return;
            }
            --size;
        }

        void resize(size_t newSize) {
            if (newSize < size) {
                // Shrink: just reduce size, data remains
                size = newSize;
            } 
            else if (newSize > size) {
                if (newSize > capacity) {
                    // Need to grow
                    size_t new_capacity = newSize;
                    T* new_data = new T[new_capacity];

                    for (size_t i = 0; i < size; ++i) {
                        new_data[i] = data[i];
                    }

                    delete[] data;
                    data = new_data;
                    capacity = new_capacity;
                }

                // Default-initialize new elements
                for (size_t i = size; i < newSize; ++i) {
                    data[i] = T();
                }

                size = newSize;
            }
        }

        // getteriai
        size_t getSize() const {
            return size;
        }

        size_t getCapacity() const {
            return capacity;
        }
};


class Zmogus{
    protected:
        string name; // vardas
        string surn; // pavarde
    public:
        Zmogus() : name(""), surn("") {} // konstruktorius
        virtual ~Zmogus(){}

        void setName(const string& Name) {
            name = Name;
        }

        void setSurn(const string& Surn) {
            surn = Surn;
        }

        string getName() const {
            return name;
        }

        string getSurn() const {
            return surn;
        }
        virtual void test() = 0;
};


class Student : public Zmogus {
    private:
        Vector<int> nd; // nd rezultatai 
        int egz; // egzaminu rez
        double vid; // galutinis vidurkis

    public:

        void test(){}

        Student() : egz(0), vid(0) {} // konstruktorius

        ~Student(){} // destruktorius

        // copy constructor dada
        Student(const Student& other)
        : Zmogus(other), nd(other.nd), egz(other.egz), vid(other.vid){}

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
            : Zmogus(std::move(other)),
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

        void setNd(const Vector<int>& Nd) {
            nd = Nd;
        }


        //geteriai
        double getVid() const {
            return vid;
        }

        int getEgz() const {
            return egz;
        }

        Vector<int>& getNd(){
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

extern Vector<Student> BadStudents;
extern Vector<Student> GoodStudents;

void skaitom(int pasirinkimas, string A[], string B[]);
void vidurkis();
void mediana();
void spausdinam(char a);
void generuojam(string b, int n);
void rusiuojam2(); // skaidymas per puse
void rusiuojam1(); // skaidymas is vieno konteinerio i du
bool compareByName(const Student& a, const Student& b);
bool compareBySurname(const Student& a, const Student& b);
bool compareByVid(const Student& a, const Student& b);
void testas();

#endif