#include <iostream>
#define MAX 2

using namespace std;

struct Student
{
    string id;
    string name;
    int age;
    char gender;
    double gpa;
};


int main()
{
    Student s[MAX];
    for(int i=0; i<MAX; i++) {
        cout << "Enter student " << i+1 << " Id: ";
        cin >> s[i].id;
        cout << "Enter student " << i+1 << " name: ";
        cin >> s[i].name;
        cout << "Enter student " << i+1 << " age: ";
        cin >> s[i].age;
        cout << "Enter student " << i+1 << " gender: ";
        cin >> s[i].gender;
        cout << "Enter student " << i+1 << " gpa: ";
        cin >> s[i].gpa;
    }

    for(int i=0; i<MAX; i++) {
        cout << "Student " << i+1 << " Id: " << s[i].id << endl; 
        cout << "Student " << i+1 << " Name: " << s[i].name << endl; 
        cout << "Student " << i+1 << " Age: " << s[i].age << endl; 
        cout << "Student " << i+1 << " Gender: " << s[i].gender << endl; 
        cout << "Student " << i+1 << " Gpa: " << s[i].gpa << endl; 
    }

    return 0;
}