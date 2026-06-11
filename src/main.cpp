/*
 * File: main.cpp
 * Deskripsi: Driver utama program. Menghubungkan seluruh modul via #include *.cpp
 *            dan menjalankan menu CLI utama dengan 3 aktor:
 *            Admin, Tim, dan Penonton.
 *
 * Cara Kompilasi:
 *   g++ src/main.cpp -o sistem_turnamen
 *
 * Cara Jalankan:
 *   ./sistem_turnamen
 */

// ==========================================
// BAGIAN 1: Library Imports
// ==========================================
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// ==========================================
// BAGIAN 2: Hubungkan Berkas Modul
// ==========================================
// Urutan include sangat penting (dependency order)

#include "models.cpp"          // Struct, variabel global, fungsi queue (WAJIB PERTAMA)
#include "utils.cpp"           // clearScreen() lintas platform
#include "search_sort.cpp"     // cariTim(), urutkanKlasemen()

// Modul fitur (semua bergantung pada models.cpp)
#include "login_admin.cpp"
#include "login_tim.cpp"
#include "registrasi_tim.cpp"
#include "lihat_tim.cpp"
#include "edit_tim.cpp"
#include "hapus_tim.cpp"
#include "buat_jadwal.cpp"     // berisi tambahHari() — dipakai juga oleh input_hasil.cpp
#include "input_hasil.cpp"
#include "lihat_klasemen.cpp"
#include "lihat_bracket.cpp"
#include "lihat_jadwal.cpp"
#include "cari_lawan.cpp"

// ==========================================
// BAGIAN 3: Helper — Tampilkan Header
// ==========================================
void tampilkanHeader() {
    clearScreen();
    cout << "\n" << string(50, '=') << endl;
    cout << "      SISTEM MANAJEMEN TURNAMEN GAME" << endl;
    cout << string(50, '=') << endl;

    // Tampilkan status fase
    if (!pendaftaranDitutup) {
        cout << "  Status: [FASE REGISTRASI] Pendaftaran masih terbuka" << endl;
    } else if (!bracketSudahDibuat) {
        cout << "  Status: [PENDAFTARAN DITUTUP] Siap buat braket" << endl;
    } else if (!isAntrianKosong()) {
        cout << "  Status: [FASE PERTANDINGAN] Turnamen sedang berjalan" << endl;
    } else {
        cout << "  Status: [TURNAMEN SELESAI]" << endl;
    }
    cout << "  Tim terdaftar: " << jumlahTimAktif << "/" << MAX_TIM << endl;
    cout << string(50, '=') << endl;
}

// ==========================================
// BAGIAN 4: Sub-menu Admin
// ==========================================
void menuAdmin() {
    // Autentikasi admin
    if (!loginAdmin()) return;

    int pilihan;
    bool exitAdmin = false;

    while (!exitAdmin) {
        tampilkanHeader();
        cout << "\n--- MENU ADMIN ---" << endl;
        cout << "1. Lihat Daftar Tim" << endl;
        cout << "2. Edit Data Tim" << endl;
        cout << "3. Hapus Tim" << endl;
        cout << "4. Tutup Pendaftaran" << endl;
        cout << "5. Buat Jadwal Pertandingan" << endl;
        cout << "6. Buat Jadwal Ronde Berikutnya" << endl;
        cout << "7. Input Hasil Pertandingan" << endl;
        cout << "8. Lihat Klasemen" << endl;
        cout << "9. Lihat Bracket/Bagan" << endl;
        cout << "0. Logout Admin" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                lihatDaftarTim();
                break;
            case 2:
                menuEditTim();
                break;
            case 3:
                hapusTim();
                break;
            case 4:
                if (pendaftaranDitutup) {
                    cout << "[INFO] Pendaftaran sudah ditutup sebelumnya." << endl;
                } else if (jumlahTimAktif < 2) {
                    cout << "[DITOLAK] Minimal 2 tim harus terdaftar sebelum menutup pendaftaran." << endl;
                } else if (!isPowerOfTwo(jumlahTimAktif)) {
                    cout << "[PERINGATAN] Jumlah tim saat ini: " << jumlahTimAktif
                         << " (bukan pangkat 2). Pastikan pangkat 2 sebelum tutup!" << endl;
                    cout << "Tetap tutup pendaftaran? (y/n): ";
                    char konfirmasi;
                    cin >> konfirmasi;
                    if (konfirmasi == 'y' || konfirmasi == 'Y') {
                        pendaftaranDitutup = true;
                        cout << "[SUKSES] Pendaftaran ditutup. Tim: " << jumlahTimAktif << endl;
                    }
                } else {
                    pendaftaranDitutup = true;
                    cout << "[SUKSES] Pendaftaran ditutup! Total " << jumlahTimAktif << " tim terdaftar." << endl;
                }
                break;
            case 5:
                buatJadwalPertandingan();
                break;
            case 6:
                buatJadwalBerikutnya();
                break;
            case 7:
                inputSkorPertandingan();
                break;
            case 8:
                lihatKlasemen();
                break;
            case 9:
                lihatBracketTree();
                break;
            case 0:
                cout << "[INFO] Logout admin. Kembali ke menu utama." << endl;
                exitAdmin = true;
                break;
            default:
                cout << "[ERROR] Pilihan tidak valid. Masukkan angka 0-9." << endl;
        }

        if (!exitAdmin) {
            cout << "\nTekan ENTER untuk lanjut...";
            cin.ignore();
            cin.get();
        }
    }
}

// ==========================================
// BAGIAN 5: Sub-menu Tim
// ==========================================
void menuTim() {
    int pilihanAwal;
    cout << "\n--- MENU TIM ---" << endl;
    cout << "1. Login Tim" << endl;
    cout << "2. Registrasi Tim Baru" << endl;
    cout << "0. Kembali ke Menu Utama" << endl;
    cout << "Pilihan: ";
    cin >> pilihanAwal;

    if (pilihanAwal == 0) return;

    if (pilihanAwal == 2) {
        registrasiTimBaru();
        return;
    }

    if (pilihanAwal != 1) {
        cout << "[ERROR] Pilihan tidak valid." << endl;
        return;
    }

    // Login tim
    Tim* timLogin = loginTim();
    if (timLogin == nullptr) return;

    int pilihan;
    bool exitTim = false;

    while (!exitTim) {
        tampilkanHeader();
        cout << "\n--- MENU TIM: " << timLogin->namaTim << " ---" << endl;
        cout << "1. Registrasi Tim Baru" << endl;
        cout << "2. Edit Data Tim Saya" << endl;
        cout << "3. Lihat Jadwal Pertandingan" << endl;
        cout << "4. Cari Profil Lawan" << endl;
        cout << "5. Lihat Klasemen" << endl;
        cout << "6. Lihat Bracket" << endl;
        cout << "0. Logout (Kembali ke Menu Utama)" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                registrasiTimBaru();
                break;
            case 2:
                if (timLogin->isEliminated) {
                    cout << "[INFO] Tim sudah tereliminasi, tidak bisa edit data." << endl;
                } else {
                    editTimSendiri(timLogin);
                }
                break;
            case 3:
                lihatJadwalAntrian();
                break;
            case 4:
                cariLawan();
                break;
            case 5:
                lihatKlasemen();
                break;
            case 6:
                lihatBracketTree();
                break;
            case 0:
                cout << "[INFO] Logout tim. Kembali ke menu utama." << endl;
                exitTim = true;
                break;
            default:
                cout << "[ERROR] Pilihan tidak valid. Masukkan angka 0-6." << endl;
        }

        if (!exitTim) {
            cout << "\nTekan ENTER untuk lanjut...";
            cin.ignore();
            cin.get();
        }
    }
}

// ==========================================
// BAGIAN 6: Sub-menu Penonton
// ==========================================
void menuPenonton() {
    int pilihan;
    bool exitPenonton = false;

    while (!exitPenonton) {
        tampilkanHeader();
        cout << "\n--- MENU PENONTON (Tanpa Login) ---" << endl;
        cout << "1. Lihat Jadwal Pertandingan" << endl;
        cout << "2. Lihat Bracket/Bagan" << endl;
        cout << "3. Lihat Klasemen" << endl;
        cout << "0. Kembali ke Menu Utama" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                lihatJadwalAntrian();
                break;
            case 2:
                lihatBracketTree();
                break;
            case 3:
                lihatKlasemen();
                break;
            case 0:
                exitPenonton = true;
                break;
            default:
                cout << "[ERROR] Pilihan tidak valid." << endl;
        }

        if (!exitPenonton) {
            cout << "\nTekan ENTER untuk lanjut...";
            cin.ignore();
            cin.get();
        }
    }
}

// ==========================================
// BAGIAN 7: Fungsi Main
// ==========================================
int main() {
    int pilihan;
    bool running = true;

    cout << "\nSelamat datang di Sistem Manajemen Turnamen!" << endl;
    cout << "Akun Admin: username=admin | password=turnamen2026" << endl;

    while (running) {
        tampilkanHeader();
        cout << "\n--- MENU UTAMA ---" << endl;
        cout << "1. Masuk Sebagai Admin" << endl;
        cout << "2. Masuk Sebagai Tim / Registrasi Tim" << endl;
        cout << "3. Lihat Sebagai Penonton" << endl;
        cout << "0. Keluar Program" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                menuAdmin();
                break;
            case 2:
                menuTim();
                break;
            case 3:
                menuPenonton();
                break;
            case 0:
                cout << "\nTerima kasih! Program selesai." << endl;
                running = false;
                break;
            default:
                cout << "[ERROR] Pilihan tidak valid. Masukkan angka 0-3." << endl;
        }
    }

    return 0;
}
