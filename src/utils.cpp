/*
 * File: utils.cpp
 * Deskripsi: Fungsi utilitas lintas platform untuk program tournament management.
 *
 * Fungsi:
 *   - clearScreen(): Membersihkan terminal di Windows, Linux, dan macOS.
 *
 * Cara kerja cross-platform:
 *   - Windows  : system("cls")
 *   - Linux    : system("clear")
 *   - macOS    : system("clear")
 *
 * Deteksi platform menggunakan preprocessor macro standar C++:
 *   - _WIN32 atau _WIN64 → Windows
 *   - __APPLE__          → macOS
 *   - __linux__          → Linux
 */

#include <cstdlib>   // system()

/*
 * clearScreen: Bersihkan layar terminal sesuai platform yang terdeteksi.
 *              Aman dipanggil berkali-kali (idempotent).
 */
void clearScreen() {
#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#elif defined(__APPLE__) || defined(__linux__) || defined(__unix__)
    system("clear");
#else
    // Fallback: gunakan ANSI escape code untuk membersihkan layar
    // \033[2J  = clear screen
    // \033[H   = move cursor to home position
    cout << "\033[2J\033[H";
#endif
}
