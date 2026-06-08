/*
 * File: main.cpp
 * Deskripsi: File driver utama program yang menghubungkan seluruh modul fitur menggunakan #include *.cpp dan menjalankan menu CLI utama.
 * 
 * Petunjuk Kompilasi:
 * Cukup kompilasi file ini saja (karena file *.cpp lainnya sudah di-include di sini):
 * g++ main.cpp -o sistem_turnamen
 */

// ==========================================
// BAGIAN 1: Library Imports
// ==========================================
#include <iostream>
#include <string>
using namespace std;

// ==========================================
// BAGIAN 2: Hubungkan Berkas Modul
// ==========================================
// Catatan Penting: Urutan include di bawah ini sangat penting karena ketergantungan tipe data dan fungsi.

#include "models.cpp"        // Berisi struct dan variabel global (Wajib paling pertama)
#include "search_sort.cpp"   // Berisi utilitas pencarian dan pengurutan

// Berkas Menu Admin
#include "login_admin.cpp"
#include "lihat_tim.cpp"
#include "edit_tim.cpp"
#include "hapus_tim.cpp"
#include "buat_jadwal.cpp"
#include "input_hasil.cpp"
#include "lihat_klasemen.cpp"
#include "lihat_bracket.cpp"

// Berkas Menu Tim
#include "registrasi_tim.cpp"
#include "lihat_jadwal.cpp"
#include "cari_lawan.cpp"

// ==========================================
// BAGIAN 3: Driver Utama & Controller Menu
// ==========================================
/*
 * Tugas Tim/Mahasiswa:
 * 1. Di dalam fungsi main(), implementasikan perulangan menu utama:
 *    - Pilihan 1: Masuk Sebagai Admin (memicu fungsi 'loginAdmin()' dari login_admin.cpp).
 *      * Jika login sukses (true), masuk ke sub-menu Admin dengan pilihan:
 *        1. Lihat Daftar Tim (panggil 'lihatDaftarTim()')
 *        2. Edit Data Tim (panggil 'menuEditTim()')
 *        3. Hapus Tim (panggil 'hapusTim()')
 *        4. Buat Jadwal Pertandingan (panggil 'buatJadwalPertandingan()')
 *        5. Input Hasil Pertandingan (panggil 'inputSkorPertandingan()')
 *        6. Lihat Klasemen Sementara (panggil 'lihatKlasemen()')
 *        7. Lihat Bracket/Bagan Turnamen (panggil 'lihatBracketTree()')
 *        8. Logout Admin (kembali ke menu utama)
 *    - Pilihan 2: Masuk Sebagai Tim/Pemain, masuk ke sub-menu Tim dengan pilihan:
 *        1. Registrasi Tim Baru (panggil 'registrasiTimBaru()')
 *        2. Lihat Jadwal Antrian Pertandingan (panggil 'lihatJadwalAntrian()')
 *        3. Cari Detail Profil Lawan (panggil 'cariLawan()')
 *        4. Lihat Klasemen Sementara (panggil 'lihatKlasemen()')
 *        5. Keluar Ke Menu Utama
 *    - Pilihan 3: Keluar Program (mengakhiri loop program utama)
 */
int main() {
    // Tulis kerangka loop menu utama Anda di sini
    return 0;
}
