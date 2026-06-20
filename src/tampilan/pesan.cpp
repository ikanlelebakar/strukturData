// File: pesan.cpp
// Deskripsi: Helper untuk menampilkan pesan status

#include <iostream>
#include <string>

void pesanOK(const std::string& pesan) {
    std::cout << "\n[OK] " << pesan << std::endl;
}

void pesanError(const std::string& pesan) {
    std::cout << "\n[ERROR] " << pesan << std::endl;
}

void pesanWarning(const std::string& pesan) {
    std::cout << "\n[WARNING] " << pesan << std::endl;
}

void pesanInfo(const std::string& pesan) {
    std::cout << "\n[INFO] " << pesan << std::endl;
}
