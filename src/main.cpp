// File: main.cpp
// Deskripsi: Driver utama program sistem turnamen game

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Hubungkan berkas modul lainnya
#include "umum/models.cpp"
#include "umum/input_helper.cpp"
#include "hapus_terminal/utils.cpp"
#include "umum/search_sort.cpp"
#include "tampilan/pesan.cpp"
#include "tampilan/tabel.cpp"
#include "tampilan/header.cpp"
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
    tampilHeader();
}

// Fungsi menu Admin
void menuAdmin() {
    if (!masukAdmin()) { // Asal: admin/login_admin.cpp
        tampilPromptKembali();
        return;
    }

    bool exitAdmin = false;
    while (!exitAdmin) {
        tampilkanHeader();

        bool turnamenSelesai = jadwalSudahDibuat && antrianKosong() && (hitungTimAktif() <= 1); // Asal antrianKosong: umum/models.cpp, hitungTimAktif: admin/input_hasil.cpp
        bool antarRonde = jadwalSudahDibuat && antrianKosong() && !turnamenSelesai; // Asal antrianKosong: umum/models.cpp
        bool fasePertandingan = jadwalSudahDibuat && !antrianKosong(); // Asal antrianKosong: umum/models.cpp
        bool pendaftaranDitutupBelumBraket = pendaftaranDitutup && !jadwalSudahDibuat;

        if (turnamenSelesai) {
            tampilSubjudul("MENU ADMIN (TURNAMEN SELESAI)");
            tampilPilihanMenu("1. Lihat Daftar Tim");
            tampilPilihanMenu("2. Lihat Klasemen");
            tampilPilihanMenu("3. Lihat Bracket/Bagan");
            tampilPilihanMenu("0. Logout Admin");
            tampilMenuBottom();
            cout << "Pilihan: ";

            int pilihan = ambilInputInt();
            switch (pilihan) {
                case 1: tampilkanTim(); break; // Asal: tim/lihat_tim.cpp
                case 2: tampilKlasemen(); break; // Asal: umum/lihat_klasemen.cpp
                case 3: tampilBracket(); break; // Asal: umum/lihat_bracket.cpp
                case 0:
                    pesanInfo("Logout admin. Kembali ke menu utama.");
                    exitAdmin = true;
                    break;
                default:
                    pesanError("Pilihan tidak valid.");
            }
        } else if (antarRonde) {
            tampilSubjudul("MENU ADMIN (ANTAR RONDE)");
            tampilPilihanMenu("1. Lihat Daftar Tim");
            tampilPilihanMenu("2. Buat Jadwal Ronde Berikutnya");
            tampilPilihanMenu("3. Lihat Klasemen");
            tampilPilihanMenu("4. Lihat Bracket/Bagan");
            tampilPilihanMenu("5. Edit Data Tim");
            tampilPilihanMenu("0. Logout Admin");
            tampilMenuBottom();
            cout << "Pilihan: ";

            int pilihan = ambilInputInt();
            switch (pilihan) {
                case 1: tampilkanTim(); break; // Asal: tim/lihat_tim.cpp
                case 2: buatJadwalBerikutnya(); break; // Asal: admin/input_hasil.cpp
                case 3: tampilKlasemen(); break; // Asal: umum/lihat_klasemen.cpp
                case 4: tampilBracket(); break; // Asal: umum/lihat_bracket.cpp
                case 5: menuEditTim(); break; // Asal: tim/edit_tim.cpp
                case 0:
                    pesanInfo("Logout admin. Kembali ke menu utama.");
                    exitAdmin = true;
                    break;
                default:
                    pesanError("Pilihan tidak valid.");
            }
        } else if (fasePertandingan) {
            tampilSubjudul("MENU ADMIN (FASE PERTANDINGAN)");
            tampilPilihanMenu("1. Lihat Daftar Tim");
            tampilPilihanMenu("2. Input Hasil Pertandingan");
            tampilPilihanMenu("3. Lihat Klasemen");
            tampilPilihanMenu("4. Lihat Bracket/Bagan");
            tampilPilihanMenu("5. Edit Data Tim");
            tampilPilihanMenu("0. Logout Admin");
            tampilMenuBottom();
            cout << "Pilihan: ";

            int pilihan = ambilInputInt();
            switch (pilihan) {
                case 1: tampilkanTim(); break; // Asal: tim/lihat_tim.cpp
                case 2: inputHasil(); break; // Asal: admin/input_hasil.cpp
                case 3: tampilKlasemen(); break; // Asal: umum/lihat_klasemen.cpp
                case 4: tampilBracket(); break; // Asal: umum/lihat_bracket.cpp
                case 5: menuEditTim(); break; // Asal: tim/edit_tim.cpp
                case 0:
                    pesanInfo("Logout admin. Kembali ke menu utama.");
                    exitAdmin = true;
                    break;
                default:
                    pesanError("Pilihan tidak valid.");
            }
        } else if (pendaftaranDitutupBelumBraket) {
            tampilSubjudul("MENU ADMIN (PENDAFTARAN DITUTUP)");
            tampilPilihanMenu("1. Lihat Daftar Tim");
            tampilPilihanMenu("2. Buat Jadwal Pertandingan");
            tampilPilihanMenu("3. Edit Data Tim");
            tampilPilihanMenu("0. Logout Admin");
            tampilMenuBottom();
            cout << "Pilihan: ";

            int pilihan = ambilInputInt();
            switch (pilihan) {
                case 1: tampilkanTim(); break; // Asal: tim/lihat_tim.cpp
                case 2: buatJadwal(); break; // Asal: admin/buat_jadwal.cpp
                case 3: menuEditTim(); break; // Asal: tim/edit_tim.cpp
                case 0:
                    pesanInfo("Logout admin. Kembali ke menu utama.");
                    exitAdmin = true;
                    break;
                default:
                    pesanError("Pilihan tidak valid.");
            }
        } else {
            tampilSubjudul("MENU ADMIN");
            tampilPilihanMenu("1. Lihat Daftar Tim");
            tampilPilihanMenu("2. Edit Data Tim");
            tampilPilihanMenu("3. Hapus Tim");
            tampilPilihanMenu("4. Tutup Pendaftaran");
            tampilPilihanMenu("0. Logout Admin");
            tampilMenuBottom();
            cout << "Pilihan: ";

            int pilihan = ambilInputInt();
            switch (pilihan) {
                case 1: tampilkanTim(); break; // Asal: tim/lihat_tim.cpp
                case 2: menuEditTim(); break; // Asal: tim/edit_tim.cpp
                case 3: hapusTim(); break; // Asal: admin/hapus_tim.cpp
                case 4:
                    if (pendaftaranDitutup) {
                        pesanWarning("Pendaftaran sudah ditutup sebelumnya.");
                    } else if (jumlahTim < 2) {
                        pesanError("Minimal 2 tim harus terdaftar sebelum menutup pendaftaran.");
                    } else if (!adalahPangkatDua(jumlahTim)) { // Asal: umum/models.cpp
                        pesanError("Jumlah tim saat ini: " + to_string(jumlahTim) + " (bukan pangkat 2). Pastikan jumlah tim pangkat 2 sebelum menutup pendaftaran.");
                    } else {
                        pendaftaranDitutup = true;
                        pesanOK("Pendaftaran ditutup! Total " + to_string(jumlahTim) + " tim terdaftar.");
                    }
                    break;
                case 0:
                    pesanInfo("Logout admin. Kembali ke menu utama.");
                    exitAdmin = true;
                    break;
                default:
                    pesanError("Pilihan tidak valid.");
            }
        }

        if (!exitAdmin) {
            tampilPromptLanjut();
        }
    }
}

// Fungsi menu Tim
void menuTim() {
    Tim *timLogin = masukTim(); // Asal: tim/login_tim.cpp
    if (timLogin == NULL) {
        tampilPromptKembali();
        return;
    }

    int pilihan;
    bool exitTim = false;
    while (!exitTim) {
        tampilkanHeader();
        
        if (!jadwalSudahDibuat) {
            tampilSubjudul("MENU TIM: " + timLogin->nama);
            tampilPilihanMenu("1. Edit Data Tim Saya");
            tampilPilihanMenu("2. Lihat Jadwal Pertandingan");
            tampilPilihanMenu("3. Cari Profil Lawan");
            tampilPilihanMenu("4. Lihat Klasemen");
            tampilPilihanMenu("5. Lihat Bracket");
            tampilPilihanMenu("0. Logout (Kembali ke Menu Utama)");
            tampilMenuBottom();
            cout << "Pilihan: ";
            pilihan = ambilInputInt();

            switch (pilihan) {
                case 1:
                    if (timLogin->tereleminasi) {
                        pesanError("Tim sudah tereliminasi, tidak bisa edit data.");
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
                    pesanInfo("Logout tim. Kembali ke menu utama.");
                    exitTim = true;
                    break;
                default:
                    pesanError("Pilihan tidak valid.");
            }
        } else {
            tampilSubjudul("MENU TIM: " + timLogin->nama);
            tampilPilihanMenu("1. Lihat Jadwal Pertandingan");
            tampilPilihanMenu("2. Cari Profil Lawan");
            tampilPilihanMenu("3. Lihat Klasemen");
            tampilPilihanMenu("4. Lihat Bracket");
            tampilPilihanMenu("0. Logout (Kembali ke Menu Utama)");
            tampilMenuBottom();
            cout << "Pilihan: ";
            pilihan = ambilInputInt();

            switch (pilihan) {
                case 1:
                    tampilJadwal(); // Asal: umum/lihat_jadwal.cpp
                    break;
                case 2:
                    cariTim(timLogin); // Asal: tim/cari_lawan.cpp
                    break;
                case 3:
                    tampilKlasemen(); // Asal: umum/lihat_klasemen.cpp
                    break;
                case 4:
                    tampilBracket(); // Asal: umum/lihat_bracket.cpp
                    break;
                case 0:
                    pesanInfo("Logout tim. Kembali ke menu utama.");
                    exitTim = true;
                    break;
                default:
                    pesanError("Pilihan tidak valid.");
            }
        }

        if (!exitTim) {
            tampilPromptLanjut();
        }
    }
}

// Fungsi menu Penonton
void menuPenonton() {
    int pilihan;
    bool exitPenonton = false;
    while (!exitPenonton) {
        tampilkanHeader();
        tampilSubjudul("MENU PENONTON (Tanpa Login)");
        tampilPilihanMenu("1. Lihat Jadwal Pertandingan");
        tampilPilihanMenu("2. Lihat Bracket/Bagan");
        tampilPilihanMenu("3. Lihat Klasemen");
        tampilPilihanMenu("0. Kembali ke Menu Utama");
        tampilMenuBottom();
        cout << "Pilihan: ";
        pilihan = ambilInputInt();

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
                pesanError("Pilihan tidak valid.");
        }

        if (!exitPenonton) {
            tampilPromptLanjut();
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
        
        bool registrasiTutupAtauPenuh = pendaftaranDitutup || (jumlahTim >= MAX_TIM);
        if (!registrasiTutupAtauPenuh) {
            tampilSubjudul("MENU UTAMA");
            tampilPilihanMenu("1. Registrasi Tim");
            tampilPilihanMenu("2. Login Tim");
            tampilPilihanMenu("3. Login Admin");
            tampilPilihanMenu("0. Keluar Program");
            tampilMenuBottom();
            cout << "Pilihan: ";
            pilihan = ambilInputInt();

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
                    pesanOK("Terima kasih! Program selesai.");
                    running = false;
                    break;
                default:
                    pesanError("Pilihan tidak valid. Masukkan angka 0-3.");
                    tampilPromptKembali();
            }
        } else {
            tampilSubjudul("MENU UTAMA");
            tampilPilihanMenu("1. Login Tim");
            tampilPilihanMenu("2. Penonton");
            tampilPilihanMenu("3. Login Admin");
            tampilPilihanMenu("0. Keluar Program");
            tampilMenuBottom();
            cout << "Pilihan: ";
            pilihan = ambilInputInt();

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
                    pesanOK("Terima kasih! Program selesai.");
                    running = false;
                    break;
                default:
                    pesanError("Pilihan tidak valid. Masukkan angka 0-3.");
                    tampilPromptKembali();
            }
        }
    }

    return 0;
}
