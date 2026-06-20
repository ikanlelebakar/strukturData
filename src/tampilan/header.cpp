// File: header.cpp
// Deskripsi: Helper untuk menampilkan header utama, subjudul, dan prompt turnamen

#include <iostream>
#include <string>

// Helper untuk mencetak karakter Unicode multi-byte berulang kali
static void printHorizontalLine(int count, const std::string& pattern = "─") {
    for (int i = 0; i < count; ++i) {
        std::cout << pattern;
    }
}

void tampilHeader() {
    clearScreen(); // Asal: hapus_terminal/utils.cpp
    
    // Baris 1: Border Atas
    std::cout << "╔";
    printHorizontalLine(78, "═");
    std::cout << "╗" << std::endl;
    
    // Baris 2: Judul Utama
    std::string judul = "SISTEM MANAJEMEN TURNAMEN GAME";
    if (adminSudahDibuat && !namaTurnamen.empty()) {
        judul = "TURNAMEN: " + namaTurnamen;
    }
    
    int titleLen = (int)judul.length();
    int padLeft = (78 - titleLen) / 2;
    int padRight = 78 - titleLen - padLeft;
    if (padLeft < 0) padLeft = 0;
    if (padRight < 0) padRight = 0;
    
    std::cout << "║" << std::string(padLeft, ' ') << judul << std::string(padRight, ' ') << "║" << std::endl;
    
    // Baris 3: Pembatas Tengah
    std::cout << "╠";
    printHorizontalLine(78, "═");
    std::cout << "╣" << std::endl;
    
    // Baris 4: Status Fase
    std::string statusStr = "";
    if (!pendaftaranDitutup) {
        statusStr = " Status : [FASE REGISTRASI] Pendaftaran masih terbuka";
    } else if (!jadwalSudahDibuat) {
        statusStr = " Status : [PENDAFTARAN DITUTUP] Siap buat braket";
    } else if (!antrianKosong()) {
        statusStr = " Status : [FASE PERTANDINGAN] Turnamen sedang berjalan";
    } else {
        statusStr = " Status : [TURNAMEN SELESAI]";
    }
    int statusLen = (int)statusStr.length();
    int statusPad = 78 - statusLen;
    if (statusPad < 0) statusPad = 0;
    std::cout << "║" << statusStr << std::string(statusPad, ' ') << "║" << std::endl;
    
    // Baris 5: Tim Terdaftar
    std::string timStr = " Tim    : " + std::to_string(jumlahTim) + "/" + std::to_string(MAX_TIM);
    int timLen = (int)timStr.length();
    int timPad = 78 - timLen;
    if (timPad < 0) timPad = 0;
    std::cout << "║" << timStr << std::string(timPad, ' ') << "║" << std::endl;
    
    // Baris 6: Border Bawah
    std::cout << "╚";
    printHorizontalLine(78, "═");
    std::cout << "╝" << std::endl;
}

void tampilSubjudul(const std::string& judul) {
    std::cout << "\n┌─── " << judul << " ";
    int used = 6 + (int)judul.length();
    int remaining = 78 - used;
    if (remaining < 0) remaining = 0;
    printHorizontalLine(remaining, "─");
    std::cout << "┐" << std::endl;
}

void tampilPilihanMenu(const std::string& opt) {
    int len = (int)opt.length();
    int pad = 74 - len; // 78 - 4 spaces padding (2 left, 2 right)
    if (pad < 0) pad = 0;
    std::cout << "│  " << opt << std::string(pad, ' ') << "  │" << std::endl;
}

void tampilMenuBottom() {
    std::cout << "└";
    printHorizontalLine(78, "─");
    std::cout << "┘" << std::endl;
}

void tampilPromptKembali() {
    std::cout << "\nTekan ENTER untuk kembali...";
    std::cin.get();
}

void tampilPromptLanjut() {
    std::cout << "\nTekan ENTER untuk lanjut...";
    std::cin.get();
}
