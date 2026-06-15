// =============================================================================
// File   : main.cpp
// Tujuan : Titik masuk (entry point) seluruh program. Berisi semua #include,
//          fungsi-fungsi menu, dan fungsi main().
//
// CARA KERJA PROYEK INI:
//   Project ini TIDAK menggunakan file .h (header file). Sebagai gantinya,
//   setiap file .cpp di-#include langsung ke main.cpp secara berurutan.
//   URUTAN #include SANGAT PENTING karena file berikutnya memakai fungsi/
//   variabel dari file sebelumnya.
//
// Urutan #include yang harus dipertahankan:
//   1.  umum/models.cpp          <- HARUS PERTAMA (semua struct & var global)
//   2.  hapus_terminal/utils.cpp <- Fungsi clearScreen()
//   3.  umum/search_sort.cpp     <- cariTim() & urutkanKlasemen()
//   4.  admin/registrasi_admin.cpp
//   5.  admin/login_admin.cpp
//   6.  tim/login_tim.cpp
//   7.  tim/registrasi_tim.cpp
//   8.  tim/lihat_tim.cpp
//   9.  tim/edit_tim.cpp
//   10. admin/hapus_tim.cpp
//   11. admin/buat_jadwal.cpp    <- tambahHari() dipakai oleh input_hasil.cpp
//   12. admin/input_hasil.cpp    <- hitungTimAktif() dipakai oleh lihat_klasemen.cpp
//   13. umum/lihat_klasemen.cpp
//   14. umum/lihat_bracket.cpp
//   15. umum/lihat_jadwal.cpp
//   16. tim/cari_lawan.cpp
//
// Fungsi yang harus kamu buat di file ini:
//   1. tampilkanHeader()
//   2. menuAdmin()
//   3. menuTim()
//   4. menuPenonton()
//   5. main()
// =============================================================================

// -----------------------------------------------------------------------------
// BAGIAN 1: Include library standar dan semua modul
// -----------------------------------------------------------------------------

// TODO: Tambahkan #include standar:
//   #include <iostream>
//   #include <string>
//   #include <iomanip>
//   using namespace std;

// TODO: Tambahkan semua #include modul sesuai urutan di atas


// -----------------------------------------------------------------------------
// Fungsi: tampilkanHeader()
// Tujuan: Membersihkan layar dan menampilkan banner atas program yang berisi
//         nama turnamen dan status fase turnamen saat ini.
//
// Variabel yang dibutuhkan: tidak ada variabel lokal
//
// Hint algoritma:
//   1. Panggil clearScreen()  // dari hapus_terminal/utils.cpp
//   2. Cetak garis "=== ... ===" sebanyak 50 karakter
//   3. Jika adminSudahDibuat && !namaTurnamen.empty():
//      Cetak "TURNAMEN: [namaTurnamen]"
//      Jika tidak: Cetak "SISTEM MANAJEMEN TURNAMEN GAME"
//   4. Tampilkan STATUS FASE berdasarkan kondisi flag:
//      - !pendaftaranDitutup               -> "[FASE REGISTRASI]"
//      - pendaftaranDitutup && !jadwalSudahDibuat -> "[PENDAFTARAN DITUTUP]"
//      - jadwalSudahDibuat && !antrianKosong()    -> "[FASE PERTANDINGAN]"
//      - else                              -> "[TURNAMEN SELESAI]"
//   5. Cetak "Tim terdaftar: [jumlahTim]/[MAX_TIM]"


// -----------------------------------------------------------------------------
// Fungsi: menuAdmin()
// Tujuan: Menu khusus Admin. Pertama login dulu, lalu tampilkan menu yang
//         berubah-ubah tergantung fase turnamen saat ini.
//         Ada 5 kondisi/fase yang menampilkan menu berbeda.
//
// Variabel yang dibutuhkan:
//   bool exitAdmin          // Flag untuk keluar dari loop menu admin
//   bool turnamenSelesai    // jadwalSudahDibuat && antrianKosong() && hitungTimAktif() <= 1
//   bool antarRonde         // jadwalSudahDibuat && antrianKosong() && !turnamenSelesai
//   bool fasePertandingan   // jadwalSudahDibuat && !antrianKosong()
//   bool pendaftaranDitutupBelumBraket  // pendaftaranDitutup && !jadwalSudahDibuat
//   int  pilihan            // Pilihan menu yang diinput
//
// Hint algoritma:
//   1. Panggil masukAdmin() — jika return false (gagal login), return
//   2. Loop WHILE (!exitAdmin):
//      a. tampilkanHeader()
//      b. Hitung semua flag fase (turnamenSelesai, antarRonde, dst.)
//      c. Gunakan IF-ELSE IF untuk menampilkan menu yang sesuai dengan fase:
//
//      FASE 1 — turnamenSelesai:
//        Menu: Lihat Daftar Tim | Lihat Klasemen | Lihat Bracket | Logout
//        Fungsi: tampilkanTim() | tampilKlasemen() | tampilBracket()
//
//      FASE 2 — antarRonde (antara ronde):
//        Menu: Lihat Daftar Tim | Buat Jadwal Ronde Berikutnya | Klasemen | Bracket | Logout
//        Fungsi: tampilkanTim() | buatJadwalBerikutnya() | tampilKlasemen() | tampilBracket()
//
//      FASE 3 — fasePertandingan (ronde sedang berjalan):
//        Menu: Lihat Daftar Tim | Input Hasil | Klasemen | Bracket | Logout
//        Fungsi: tampilkanTim() | inputHasil() | tampilKlasemen() | tampilBracket()
//
//      FASE 4 — pendaftaranDitutupBelumBraket:
//        Menu: Lihat Daftar Tim | Buat Jadwal Pertandingan | Logout
//        Fungsi: tampilkanTim() | buatJadwal()
//
//      FASE 5 — else (pendaftaran masih terbuka):
//        Menu: Lihat Daftar Tim | Edit Tim | Hapus Tim | Tutup Pendaftaran | Logout
//        Fungsi: tampilkanTim() | menuEditTim() | hapusTim()
//        KHUSUS "Tutup Pendaftaran":
//          - Jika sudah ditutup -> "Sudah ditutup"
//          - Jika jumlahTim < 2 -> "Minimal 2 tim"
//          - Jika !adalahPangkatDua(jumlahTim) -> tanya konfirmasi dulu
//          - Jika valid -> pendaftaranDitutup = true
//
//   3. Setelah setiap aksi (kecuali logout): tampilkan "Tekan ENTER untuk lanjut..."


// -----------------------------------------------------------------------------
// Fungsi: menuTim()
// Tujuan: Menu untuk tim yang sedang login. Pertama login dulu untuk mendapatkan
//         pointer tim, lalu tampilkan menu dengan pilihan yang tersedia.
//
// Variabel yang dibutuhkan:
//   Tim  *timLogin    // Pointer ke tim yang berhasil login (dari masukTim())
//   int   pilihan     // Pilihan menu
//   bool  exitTim     // Flag untuk keluar dari loop menu
//
// Hint algoritma:
//   1. Tim *timLogin = masukTim() — jika NULL (gagal login), return
//   2. Loop WHILE (!exitTim):
//      a. tampilkanHeader()
//      b. Tampilkan nama tim yang login: "--- MENU TIM: [timLogin->nama] ---"
//      c. Menu: Edit Data | Jadwal | Cari Lawan | Klasemen | Bracket | Logout
//      d. Switch-case:
//         case 1 (Edit):
//           Jika timLogin->tereleminasi -> "Tim tereliminasi, tidak bisa edit"
//           Jika tidak -> editTim(timLogin)
//         case 2: tampilJadwal()
//         case 3: cariTim(timLogin)    // Versi dengan parameter Tim* dari cari_lawan.cpp
//         case 4: tampilKlasemen()
//         case 5: tampilBracket()
//         case 0: exitTim = true


// -----------------------------------------------------------------------------
// Fungsi: menuPenonton()
// Tujuan: Menu tanpa login untuk penonton. Hanya bisa melihat jadwal, bracket,
//         dan klasemen. Tidak bisa melakukan perubahan apapun.
//
// Variabel yang dibutuhkan:
//   int  pilihan        // Pilihan menu
//   bool exitPenonton   // Flag untuk keluar
//
// Hint algoritma:
//   Loop WHILE (!exitPenonton):
//     tampilkanHeader()
//     Tampilkan menu: Jadwal | Bracket | Klasemen | Kembali
//     Switch-case:
//       case 1: tampilJadwal()
//       case 2: tampilBracket()
//       case 3: tampilKlasemen()
//       case 0: exitPenonton = true


// -----------------------------------------------------------------------------
// Fungsi: main() -> int
// Tujuan: Titik masuk program. Menjalankan registrasi admin sekali di awal,
//         lalu masuk ke loop menu utama yang berlangsung terus sampai user keluar.
//
// Variabel yang dibutuhkan:
//   int  pilihan   // Pilihan menu utama
//   bool running   // Flag untuk menjalankan/menghentikan loop utama
//
// Variabel kondisi (dihitung di dalam loop):
//   bool registrasiTutupAtauPenuh  // pendaftaranDitutup || (jumlahTim >= MAX_TIM)
//
// Hint algoritma:
//   1. Jika !adminSudahDibuat:
//      clearScreen()
//      daftarAdmin()   // Registrasi admin hanya sekali di awal
//
//   2. Loop WHILE (running):
//      a. tampilkanHeader()
//      b. Hitung: registrasiTutupAtauPenuh = pendaftaranDitutup || jumlahTim >= MAX_TIM
//
//      c. Jika !registrasiTutupAtauPenuh (pendaftaran masih terbuka):
//         Menu: Registrasi Tim | Login Tim | Login Admin | Keluar
//         Switch:
//           case 1: daftarTim()
//           case 2: menuTim()
//           case 3: menuAdmin()
//           case 0: running = false, cetak "Terima kasih!"
//
//      d. Jika registrasiTutupAtauPenuh (pendaftaran sudah tutup/penuh):
//         Menu: Login Tim | Penonton | Login Admin | Keluar
//         Switch:
//           case 1: menuTim()
//           case 2: menuPenonton()
//           case 3: menuAdmin()
//           case 0: running = false, cetak "Terima kasih!"
//
//   3. return 0
