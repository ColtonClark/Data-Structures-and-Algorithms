#include <iostream>
using namespace std;

class Entry {
    string key;
    int value;
    double GPA;
    int age;
    string name;
    Entry* next;

public:
    Entry(string key, string name, int age, double GPA) {
        this->key = key;
        this->name = name;
        this->age = age;
        this->GPA = GPA;
    }
    string getKey() { return key; } 
    string getname() { return name; }
    int getage() { return age; }
    double getGPA() { return GPA; }
    Entry* getnext()
    {
        return next;
    }
};

class HashMap {
    class Overflow {};
    Entry** table;
    int size;

public:

    unsigned long hash(string str) {
        const char* cstr = str.c_str();
        unsigned long hash = 5381;
        int c;
        while (c = *cstr++)
            hash = hash * 33 + c;
        return hash;
    }

    int getSize()
    {
        return size;
    }

    HashMap(int size) {
        this->size = size;
        table = new Entry*[size];
        for (int i = 0; i < size; i++)
            table[i] = NULL;
    }


    void display()
    {
        for (int i = 0; i < size; i++)
        {
            Entry* Student = table[i];
            if (Student!= NULL)
            {
                cout << "Index: " << i << "\n";
                while (Student != NULL)
                {
                    cout << Student->getKey() << " name:" << Student->getname() << " age:" << Student->getage() << " GPA:" << Student->getGPA() << endl << endl;
                    Student = Student->getnext();
                }
            }
        }
    }

    void put(Entry* e) {
        string key = e->getKey();
        int index = hash(key) % size;
        int startIndex = index;
        while (table[index] != NULL && table[index]->getKey() != key && table[index]->getKey() != "empty") {
            index = (index + 1) % size;
            if (index == startIndex) throw Overflow();
        }
        table[index] = e;
    }

    Entry* get(string key) {
        int index = hash(key) % size;
        int startIndex = index;
        while (table[index] != NULL && table[index]->getKey() != key) {
            index = (index + 1) % size;
            if (index == startIndex)    return NULL;
        }
        return table[index];
    }

    ~HashMap() {
        for (int i = 0; i < size; i++)
            if (table[i] != NULL)
                delete table[i];
        delete[] table;
    }
};

int main()
{
    HashMap Students(23);
    Entry* Student1 = new Entry("4546845689", "Bob", 69, 3.5);
    Entry* Student2 = new Entry("6845627895", "Colton", 24, 4.0);
    Entry* Student3 = new Entry("5478231569", "Boris", 40, 2.7);
    Entry* Student4 = new Entry("1235869845", "Bill", 19, 3.1);
    Entry* Student5 = new Entry("6583956785", "Yongjie", 25, 5.0);
    Entry* Student6 = new Entry("9998564565", "Edward", 21, 3.0);
    Entry* Student7 = new Entry("7788554569", "Robert", 29, 3.8);
    Students.put(Student1);
    Students.put(Student2);
    Students.put(Student3);
    Students.put(Student4);
    Students.put(Student5);
    Students.put(Student6);
    Students.put(Student7);
    Students.display();
}
