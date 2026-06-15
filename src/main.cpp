// File: main.cpp
// Deskripsi: Driver utama program sistem turnamen game

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Hubungkan berkas modul lainnya
#include "umum/models.cpp"
#include "hapus_terminal/utils.cpp"
#include "umum/search_sort.cpp"
#include "admin/registrasi_admin.cpp"
#include "admin/login_admin.cpp"
#include "tim/login_tim.cpp"
#include "tim/registrasi_tim.cpp"
#include "tim/lihat_tim.cpp"
#include "tim/edit_tim.cpp"
#include "admin/hapus_tim.cpp"
#include "admin/buat_jadwal.cpp"
#include "admin/input_hasil.cpp"
#include "umum/lihat_klasemen.cpp"
#include "umum/lihat_bracket.cpp"
#include "umum/lihat_jadwal.cpp"
#include "tim/cari_lawan.cpp"

// Fungsi tampilkan header turnamen
void tampilkanHeader() {
    clearScreen(); // Asal: hapus_terminal/utils.cpp
    cout << "\n" << string(50, '=') << endl;
    if (adminSudahDibuat && !namaTurnamen.empty()) {
        cout << "  TURNAMEN: " << namaTurnamen << endl;
    } else {
        cout << "      SISTEM MANAJEMEN TURNAMEN GAME" << endl;
    }
    cout << string(50, '=') << endl;

    // Tampilkan status fase turnamen
    if (!pendaftaranDitutup) {
        cout << "  Status: [FASE REGISTRASI] Pendaftaran masih terbuka" << endl;
    } else if (!jadwalSudahDibuat) {
        cout << "  Status: [PENDAFTARAN DITUTUP] Siap buat braket" << endl;
    } else if (!antrianKosong()) { // Asal: umum/models.cpp
        cout << "  Status: [FASE PERTANDINGAN] Turnamen sedang berjalan" << endl;
    } else {
        cout << "  Status: [TURNAMEN SELESAI]" << endl;
    }
    cout << "  Tim terdaftar: " << jumlahTim << "/" << MAX_TIM << endl;
    cout << string(50, '=') << endl;
}

// Fungsi menu Admin
void menuAdmin() {
    if (!masukAdmin()) { // Asal: admin/login_admin.cpp
        cout << "\nTekan ENTER untuk kembali...";
        cin.get();
        return;
    }

    bool exitAdmin = false;
    while (!exitAdmin) {
        tampilkanHeader();
        cout << "\n--- MENU ADMIN ---" << endl;

        bool turnamenSelesai = jadwalSudahDibuat && antrianKosong() && (hitungTimAktif() <= 1); // Asal antrianKosong: umum/models.cpp, hitungTimAktif: admin/input_hasil.cpp
        bool antarRonde = jadwalSudahDibuat && antrianKosong() && !turnamenSelesai; // Asal antrianKosong: umum/models.cpp
        bool fasePertandingan = jadwalSudahDibuat && !antrianKosong(); // Asal antrianKosong: umum/models.cpp
        bool pendaftaranDitutupBelumBraket = pendaftaranDitutup && !jadwalSudahDibuat;

        if (turnamenSelesai) {
            cout << "1. Lihat Daftar Tim" << endl;
            cout << "2. Lihat Klasemen" << endl;
            cout << "3. Lihat Bracket/Bagan" << endl;
            cout << "0. Logout Admin" << endl;
            cout << "Pilihan: ";

            int pilihan;
            cin >> pilihan;
            cin.ignore(10000, '\n');
            switch (pilihan) {
                case 1: tampilkanTim(); break; // Asal: tim/lihat_tim.cpp
                case 2: tampilKlasemen(); break; // Asal: umum/lihat_klasemen.cpp
                case 3: tampilBracket(); break; // Asal: umum/lihat_bracket.cpp
                case 0:
                    cout << "Logout admin. Kembali ke menu utama." << endl;
                    exitAdmin = true;
                    break;
                default:
                    cout << "Pilihan tidak valid." << endl;
            }
        } else if (antarRonde) {
            cout << "1. Lihat Daftar Tim" << endl;
            cout << "2. Buat Jadwal Ronde Berikutnya" << endl;
            cout << "3. Lihat Klasemen" << endl;
            cout << "4. Lihat Bracket/Bagan" << endl;
            cout << "0. Logout Admin" << endl;
            cout << "Pilihan: ";

            int pilihan;
            cin >> pilihan;
            cin.ignore(10000, '\n');
            switch (pilihan) {
                case 1: tampilkanTim(); break; // Asal: tim/lihat_tim.cpp
                case 2: buatJadwalBerikutnya(); break; // Asal: admin/input_hasil.cpp
                case 3: tampilKlasemen(); break; // Asal: umum/lihat_klasemen.cpp
                case 4: tampilBracket(); break; // Asal: umum/lihat_bracket.cpp
                case 0:
                    cout << "Logout admin. Kembali ke menu utama." << endl;
                    exitAdmin = true;
                    break;
                default:
                    cout << "Pilihan tidak valid." << endl;
            }
        } else if (fasePertandingan) {
            cout << "1. Lihat Daftar Tim" << endl;
            cout << "2. Input Hasil Pertandingan" << endl;
            cout << "3. Lihat Klasemen" << endl;
            cout << "4. Lihat Bracket/Bagan" << endl;
            cout << "0. Logout Admin" << endl;
            cout << "Pilihan: ";

            int pilihan;
            cin >> pilihan;
            cin.ignore(10000, '\n');
            switch (pilihan) {
                case 1: tampilkanTim(); break; // Asal: tim/lihat_tim.cpp
                case 2: inputHasil(); break; // Asal: admin/input_hasil.cpp
                case 3: tampilKlasemen(); break; // Asal: umum/lihat_klasemen.cpp
                case 4: tampilBracket(); break; // Asal: umum/lihat_bracket.cpp
                case 0:
                    cout << "Logout admin. Kembali ke menu utama." << endl;
                    exitAdmin = true;
                    break;
                default:
                    cout << "Pilihan tidak valid." << endl;
            }
        } else if (pendaftaranDitutupBelumBraket) {
            cout << "1. Lihat Daftar Tim" << endl;
            cout << "2. Buat Jadwal Pertandingan" << endl;
            cout << "0. Logout Admin" << endl;
            cout << "Pilihan: ";

            int pilihan;
            cin >> pilihan;
            cin.ignore(10000, '\n');
            switch (pilihan) {
                case 1: tampilkanTim(); break; // Asal: tim/lihat_tim.cpp
                case 2: buatJadwal(); break; // Asal: admin/buat_jadwal.cpp
                case 0:
                    cout << "Logout admin. Kembali ke menu utama." << endl;
                    exitAdmin = true;
                    break;
                default:
                    cout << "Pilihan tidak valid." << endl;
            }
        } else {
            cout << "1. Lihat Daftar Tim" << endl;
            cout << "2. Edit Data Tim" << endl;
            cout << "3. Hapus Tim" << endl;
            cout << "4. Tutup Pendaftaran" << endl;
            cout << "0. Logout Admin" << endl;
            cout << "Pilihan: ";

            int pilihan;
            cin >> pilihan;
            cin.ignore(10000, '\n');
            switch (pilihan) {
                case 1: tampilkanTim(); break; // Asal: tim/lihat_tim.cpp
                case 2: menuEditTim(); break; // Asal: tim/edit_tim.cpp
                case 3: hapusTim(); break; // Asal: admin/hapus_tim.cpp
                case 4:
                    if (pendaftaranDitutup) {
                        cout << "Pendaftaran sudah ditutup sebelumnya." << endl;
                    } else if (jumlahTim < 2) {
                        cout << "Minimal 2 tim harus terdaftar sebelum menutup pendaftaran." << endl;
                    } else if (!adalahPangkatDua(jumlahTim)) { // Asal: umum/models.cpp
                        cout << "Jumlah tim saat ini: " << jumlahTim
                             << " (bukan pangkat 2). Pastikan pangkat 2 sebelum tutup!" << endl;
                        cout << "Tetap tutup pendaftaran? (y/n): ";
                        char konfirmasi;
                        cin >> konfirmasi;
                        cin.ignore(10000, '\n');
                        if (konfirmasi == 'y' || konfirmasi == 'Y') {
                            pendaftaranDitutup = true;
                            cout << "Pendaftaran ditutup. Tim: " << jumlahTim << endl;
                        }
                    } else {
                        pendaftaranDitutup = true;
                        cout << "Pendaftaran ditutup! Total " << jumlahTim << " tim terdaftar." << endl;
                    }
                    break;
                case 0:
                    cout << "Logout admin. Kembali ke menu utama." << endl;
                    exitAdmin = true;
                    break;
                default:
                    cout << "Pilihan tidak valid." << endl;
            }
        }

        if (!exitAdmin) {
            cout << "\nTekan ENTER untuk lanjut...";
            cin.get();
        }
    }
}

// Fungsi menu Tim
void menuTim() {
    Tim *timLogin = masukTim(); // Asal: tim/login_tim.cpp
    if (timLogin == NULL) {
        cout << "\nTekan ENTER untuk kembali...";
        cin.get();
        return;
    }

    int pilihan;
    bool exitTim = false;
    while (!exitTim) {
        tampilkanHeader();
        cout << "\n--- MENU TIM: " << timLogin->nama << " ---" << endl;
        cout << "1. Edit Data Tim Saya" << endl;
        cout << "2. Lihat Jadwal Pertandingan" << endl;
        cout << "3. Cari Profil Lawan" << endl;
        cout << "4. Lihat Klasemen" << endl;
        cout << "5. Lihat Bracket" << endl;
        cout << "0. Logout (Kembali ke Menu Utama)" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore(10000, '\n');

        switch (pilihan) {
            case 1:
                if (timLogin->tereleminasi) {
                    cout << "Tim sudah tereliminasi, tidak bisa edit data." << endl;
                } else {
                    editTim(timLogin); // Asal: tim/edit_tim.cpp
                }
                break;
            case 2:
                tampilJadwal(); // Asal: umum/lihat_jadwal.cpp
                break;
            case 3:
                cariTim(timLogin); // Asal: tim/cari_lawan.cpp
                break;
            case 4:
                tampilKlasemen(); // Asal: umum/lihat_klasemen.cpp
                break;
            case 5:
                tampilBracket(); // Asal: umum/lihat_bracket.cpp
                break;
            case 0:
                cout << "Logout tim. Kembali ke menu utama." << endl;
                exitTim = true;
                break;
            default:
                cout << "Pilihan tidak valid. Masukkan angka 0-5." << endl;
        }

        if (!exitTim) {
            cout << "\nTekan ENTER untuk lanjut...";
            cin.get();
        }
    }
}

// Fungsi menu Penonton
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
        cin.ignore(10000, '\n');

        switch (pilihan) {
            case 1:
                tampilJadwal(); // Asal: umum/lihat_jadwal.cpp
                break;
            case 2:
                tampilBracket(); // Asal: umum/lihat_bracket.cpp
                break;
            case 3:
                tampilKlasemen(); // Asal: umum/lihat_klasemen.cpp
                break;
            case 0:
                exitPenonton = true;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }

        if (!exitPenonton) {
            cout << "\nTekan ENTER untuk lanjut...";
            cin.get();
        }
    }
}

// Fungsi main utama
int main() {
    if (!adminSudahDibuat) {
        clearScreen(); // Asal: hapus_terminal/utils.cpp
        daftarAdmin(); // Asal: admin/registrasi_admin.cpp
    }

    int pilihan;
    bool running = true;
    while (running) {
        tampilkanHeader();
        cout << "\n--- MENU UTAMA ---" << endl;
        
        bool registrasiTutupAtauPenuh = pendaftaranDitutup || (jumlahTim >= MAX_TIM);
        if (!registrasiTutupAtauPenuh) {
            cout << "1. Registrasi Tim" << endl;
            cout << "2. Login Tim" << endl;
            cout << "3. Login Admin" << endl;
            cout << "0. Keluar Program" << endl;
            cout << "Pilihan: ";
            cin >> pilihan;
            cin.ignore(10000, '\n');

            switch (pilihan) {
                case 1:
                    daftarTim(); // Asal: tim/registrasi_tim.cpp
                    break;
                case 2:
                    menuTim();
                    break;
                case 3:
                    menuAdmin();
                    break;
                case 0:
                    cout << "\nTerima kasih! Program selesai." << endl;
                    running = false;
                    break;
                default:
                    cout << "Pilihan tidak valid. Masukkan angka 0-3." << endl;
                    cout << "\nTekan ENTER untuk kembali...";
                    cin.get();
            }
        } else {
            cout << "1. Login Tim" << endl;
            cout << "2. Penonton" << endl;
            cout << "3. Login Admin" << endl;
            cout << "0. Keluar Program" << endl;
            cout << "Pilihan: ";
            cin >> pilihan;
            cin.ignore(10000, '\n');

            switch (pilihan) {
                case 1:
                    menuTim();
                    break;
                case 2:
                    menuPenonton();
                    break;
                case 3:
                    menuAdmin();
                    break;
                case 0:
                    cout << "\nTerima kasih! Program selesai." << endl;
                    running = false;
                    break;
                default:
                    cout << "Pilihan tidak valid. Masukkan angka 0-3." << endl;
                    cout << "\nTekan ENTER untuk kembali...";
                    cin.get();
            }
        }
    }

    return 0;
}
