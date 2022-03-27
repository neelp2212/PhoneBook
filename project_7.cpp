// Assignment - 7  (Write a program to keep record of names, addresses and telephone numbers.)
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdlib>
#include <stdlib.h>
using namespace std;

// Create a structure for Information
struct Information
{
    string name;
    string email;
    string city;
    bool relative;
    int mobile_number;

    friend istream &operator>>(istream &in, Information &person);
    friend ostream &operator<<(ostream &out, const Information &person);
};

// Input operator overload
istream &operator>>(istream &in, Information &person)
{
    in >> person.name;
    in >> person.email;
    in >> person.city;
    in >> person.relative;
    in >> person.mobile_number;
    return in;
}

// output operator overload
ostream &operator<<(ostream &out, const Information &person)
{
    out << person.name << " " << person.email << " " << person.city << " " << person.relative << " " << person.mobile_number << " ";
}

// It is used to update the file after changes
void writeToFile(vector<Information> &phonebook)
{
    ofstream file("data.txt", ios::out);
    for (const auto &person : phonebook)
    {
        file << person;
    }
    file.close();
}

// This function is used to read the data from file
void readFromFile()
{
    cout << "Reading file: " << endl;
    ifstream readFile("data.txt");
    string name;
    while (readFile)
    {
        getline(readFile, name);
        cout << name << endl;
    }
    readFile.close();
}

// It is used to print the data of vector
void printVectorData(vector<Information> &phonebook)
{
    for (auto person : phonebook)
    {
        cout << endl;
        cout << "Name: " << person.name << endl;
        cout << "Email: " << person.email << endl;
        cout << "city: " << person.city << endl;
        cout << "relative: " << person.relative << endl;
        cout << "Mobile number: " << person.mobile_number << endl;
    }
}

// It is used to remove the detail of a person from vector
void removeData(vector<Information> &phonebook, string name)
{
    vector<Information>::iterator it = phonebook.begin();
    while (it != phonebook.end())
    {
        if (it->name == name)
        {
            it = phonebook.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

// It is used to print the data of persons who stay in the same city
void printPersonFromSameCity(vector<Information> &phonebook, string city)
{
    for (auto person : phonebook)
    {
        if (city == person.city)
        {
            cout << "Name: " << person.name << endl;
            cout << "Email: " << person.email << endl;
            cout << "city: " << person.city << endl;
            cout << "relative: " << person.relative << endl;
            cout << "Mobile number: " << person.mobile_number << endl;
        }
    }
}

// It is used to compare a person is relative or not
bool compareRelative(const Information &person1, const Information &person2)
{
    return person1.relative > person2.relative;
}

int main()
{
    // vector of user defined datatype is created to store the data.
    vector<Information> phonebook;
    // File opened in trunc mode to make the changes in file
    ofstream file("data.txt", ios::trunc);
    while (1)
    {
        // Ask user to enter their details for Person
        Information person;
        cout << "Enter your name:" << endl;
        getline(cin, person.name);
        cout << "Enter your email:" << endl;
        getline(cin, person.email);
        cout << "Enter the name of your city:" << endl;
        getline(cin, person.city);
        string check;
        cout << "Is he/she is your relative (yes/no)?" << endl;
        getline(cin, check);
        if (check == "yes")
        {
            person.relative = true;
        }
        else
        {
            person.relative = false;
        }
        cout << "Enter your mobile_number:" << endl;
        cin >> person.mobile_number;
        // It stores the data of a person in a vector named phonebook
        phonebook.push_back(person);
        // Using operator overloading it saves the data directly to the file
        file << person;
        // Ask user if he/she wants to continue to add another person
        cout << "Do you want to add another person (yes/no)?" << endl;
        string ans;
        cin >> ans;
        cin.ignore();
        if (ans != "yes")
        {
            break;
        }
    }
    // Close the file after saving the data
    file.close();
    // Sorting the data stored in phonebook
    sort(phonebook.begin(), phonebook.end(), compareRelative);

    // Open the file to read data
    ifstream readfile("data.txt", ios::in);
    Information person;
    vector<Information> fileRead;
    cout << endl;
    cout << "Reading data from the file" << endl;
    // It reads the file using operator overloading
    while (readfile >> person)
    {
        fileRead.push_back(person);
    }
    readfile.close();
    printVectorData(fileRead);
    cout << endl;

    // Ask user to write which person he/she wants to remove
    cout << "Ask user if he/she wants to delete the data:" << endl;
    string delete_contact;
    cout << "Enter the person name whom you want to remove(no to skip): " << endl;
    cin >> delete_contact;
    cout << endl;
    removeData(phonebook, delete_contact);
    printVectorData(phonebook);
    // Changes to be made in file also
    writeToFile(phonebook);

    cout << endl;
    // Ask user if he/she wants the detail of the person who stays in same city
    cout << "If you want to get the persons details of the same city" << endl;
    string same_city;
    cout << "Enter the name of city to print the persons of that city (no to skip): " << endl;
    cin >> same_city;
    // Print the person details who stays in the same city
    printPersonFromSameCity(phonebook, same_city);

    cout << endl;
    cout << "Printing all the information which stores in Phonebook: " << endl;
    printVectorData(phonebook);
    return 0;
}