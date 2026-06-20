// File: input_helper.cpp
// Deskripsi: Fungsi pembantu untuk input yang aman dari terminal

#include <iostream>
using namespace std;

int ambilInputInt() {
    int val;
    cin >> val;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        return -1; // Kembalikan -1 untuk menandakan input tidak valid
    }
    cin.ignore(10000, '\n');
    return val;
}
