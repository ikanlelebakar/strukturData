// File: tabel.cpp
// Deskripsi: Helper untuk menampilkan tabel data dengan border Unicode

#include <iostream>
#include <string>
#include <vector>

// Helper untuk format teks di dalam sel agar rapi dan tidak merusak border
static std::string formatCell(const std::string& text, int width, char align = 'L') {
    std::string s = text;
    int contentWidth = width - 2; // Kurangi 2 untuk padding spasi kiri dan kanan
    if (contentWidth < 1) contentWidth = 1;

    if ((int)s.length() > contentWidth) {
        s = s.substr(0, contentWidth);
    }
    
    int padLeft = 1;
    int padRight = 1;
    
    if (align == 'R') {
        padLeft = contentWidth - (int)s.length() + 1;
    } else if (align == 'C') {
        int totalPad = contentWidth - (int)s.length();
        padLeft = totalPad / 2 + 1;
        padRight = totalPad - (totalPad / 2) + 1;
    } else { // 'L'
        padRight = contentWidth - (int)s.length() + 1;
    }
    
    // Pastikan total karakter yang dikembalikan persis sama dengan width
    std::string res = std::string(padLeft, ' ') + s + std::string(padRight, ' ');
    if ((int)res.length() < width) {
        res += std::string(width - res.length(), ' ');
    } else if ((int)res.length() > width) {
        res = res.substr(0, width);
    }
    return res;
}

void tampilGarisTabel(const std::vector<int>& lebar, char tipe) {
    std::string kiri, tengah, kanan, hubung;
    if (tipe == 'A') { // Atas
        kiri = "┌"; tengah = "┬"; kanan = "┐"; hubung = "─";
    } else if (tipe == 'T') { // Tengah
        kiri = "├"; tengah = "┼"; kanan = "┤"; hubung = "─";
    } else { // Bawah ('B')
        kiri = "└"; tengah = "┴"; kanan = "┘"; hubung = "─";
    }
    
    std::cout << kiri;
    for (size_t i = 0; i < lebar.size(); ++i) {
        for (int j = 0; j < lebar[i]; ++j) {
            std::cout << hubung;
        }
        if (i < lebar.size() - 1) {
            std::cout << tengah;
        }
    }
    std::cout << kanan << std::endl;
}

void tampilBarisTabel(const std::vector<std::string>& data, const std::vector<int>& lebar, const std::vector<char>& alinyemen = {}) {
    std::cout << "│";
    for (size_t i = 0; i < lebar.size(); ++i) {
        std::string teks = "";
        if (i < data.size()) {
            teks = data[i];
        }
        char align = 'L';
        if (i < alinyemen.size()) {
            align = alinyemen[i];
        }
        std::cout << formatCell(teks, lebar[i], align) << "│";
    }
    std::cout << std::endl;
}
