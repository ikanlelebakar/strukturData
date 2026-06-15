// File: utils.cpp
// Deskripsi: Fungsi utilitas untuk membersihkan layar terminal

#include <cstdlib>
#include <iostream>
using namespace std;

// Fungsi untuk membersihkan layar terminal
void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#elif defined(__APPLE__) || defined(__linux__) || defined(__unix__)
    system("clear");
#else
    // Fallback menggunakan ANSI escape code
    cout << "\033[2J\033[H";
#endif
}
