// =============================================================================
// File   : models.cpp
// Tujuan : Pondasi seluruh program — berisi semua struct, variabel global,
//          dan fungsi dasar untuk antrian (queue) pertandingan.
//
// PENTING: File ini harus di-#include PERTAMA di main.cpp karena semua file
//          lain bergantung pada definisi yang ada di sini.
//
// Urutan yang harus kamu buat di file ini:
//   1. #include library yang dibutuhkan (iostream, string)
//   2. using namespace std;
//   3. Konstanta dan variabel global
//   4. Fungsi utilitas: adalahPangkatDua()
//   5. Definisi struct Tim
//   6. Definisi struct NodeAntrian
//   7. Variabel global untuk linked list tim dan antrian pertandingan
//   8. Fungsi queue: tambahAntrian(), hapusAntrian(), antrianKosong()
//   9. Struct MatchResult + array riwayat pertandingan
//  10. Fungsi riwayat: catatPertandingan(), updatePemenang()
// =============================================================================


// -----------------------------------------------------------------------------
// BAGIAN 1: Library & Namespace
// -----------------------------------------------------------------------------
// TODO: Tambahkan #include untuk iostream dan string
// TODO: Tambahkan "using namespace std;"


// -----------------------------------------------------------------------------
// BAGIAN 2: Konstanta dan Variabel Global — Pengaturan Turnamen
// -----------------------------------------------------------------------------

// TODO: Deklarasikan variabel global berikut:
//
//   int MAX_TIM           = 8;    // Kapasitas maks tim, bisa diubah admin (harus pangkat 2)
//   const int MIN_PEMAIN  = 1;    // Minimum pemain dalam satu tim
//   const int MAX_PEMAIN  = 7;    // Maksimum pemain dalam satu tim
//
//   string adminUsername  = "";   // Username admin (diisi saat registrasi)
//   string adminPassword  = "";   // Password admin (diisi saat registrasi)
//   string namaTurnamen   = "";   // Nama turnamen (diisi saat registrasi)
//   bool adminSudahDibuat = false;// Flag: apakah admin sudah dibuat?


// -----------------------------------------------------------------------------
// BAGIAN 3: Fungsi Utilitas
// -----------------------------------------------------------------------------

// Fungsi: adalahPangkatDua(int n) -> bool
// Tujuan: Mengecek apakah angka n adalah pangkat dari 2 (misal: 2, 4, 8, 16...)
//
// Variabel yang dibutuhkan: tidak ada (langsung return ekspresi boolean)
//
// Hint algoritma:
//   - Angka pangkat 2 dalam biner hanya punya SATU bit '1'
//   - Trik bitwise: (n & (n-1)) == 0 akan true jika n adalah pangkat 2
//   - Jangan lupa cek n > 0 agar angka 0 tidak lolos
//
// Contoh:
//   adalahPangkatDua(4)  -> true  (biner: 100)
//   adalahPangkatDua(6)  -> false (biner: 110)
//   adalahPangkatDua(8)  -> true  (biner: 1000)


// -----------------------------------------------------------------------------
// BAGIAN 4: Struct Tim (Node untuk Linked List)
// -----------------------------------------------------------------------------

// TODO: Definisikan struct bernama "Tim" dengan field-field berikut:
//
//   string nama;          // Nama tim (juga berfungsi sebagai username login)
//   string password;      // Password login tim
//   int    jumlahPemain;  // Berapa pemain dalam tim (MIN_PEMAIN s/d MAX_PEMAIN)
//   int    poin;          // Poin yang dikumpulkan tim selama turnamen (awal: 0)
//   bool   tereleminasi;  // true jika tim sudah kalah dan keluar turnamen
//   Tim   *berikutnya;    // Pointer ke node Tim berikutnya (linked list)


// -----------------------------------------------------------------------------
// BAGIAN 5: Struct NodeAntrian (Node untuk Queue Pertandingan)
// -----------------------------------------------------------------------------

// TODO: Definisikan struct bernama "NodeAntrian" dengan field-field berikut:
//
//   Tim         *timA;           // Pointer ke tim pertama yang bertanding
//   Tim         *timB;           // Pointer ke tim kedua yang bertanding
//   string       tanggalTanding; // Tanggal pertandingan format "YYYY-MM-DD"
//   string       ronde;          // Nama ronde, misal: "Ronde 1", "Semifinal", "Final"
//   NodeAntrian *berikutnya;     // Pointer ke node antrian berikutnya


// -----------------------------------------------------------------------------
// BAGIAN 6: Variabel Global — Linked List Tim & Status Turnamen
// -----------------------------------------------------------------------------

// TODO: Deklarasikan variabel global berikut:
//
//   Tim *kepala           = NULL;  // Pointer ke node pertama linked list tim
//   int  jumlahTim        = 0;     // Hitungan tim yang sudah terdaftar
//   bool pendaftaranDitutup = false; // true jika admin sudah tutup pendaftaran
//   bool jadwalSudahDibuat  = false; // true jika bracket sudah dibuat
//
// Untuk antrian pertandingan (Queue):
//   NodeAntrian *depanAntrian    = NULL; // Pointer ke depan antrian (yang akan main)
//   NodeAntrian *belakangAntrian = NULL; // Pointer ke belakang antrian (terakhir masuk)
//
// Untuk status ronde:
//   int    rondeSekarang  = 0;  // Nomor ronde yang sedang berjalan
//   int    matchDiRonde   = 0;  // Jumlah match dalam ronde ini
//   string tanggalTerakhir = ""; // Tanggal pertandingan terakhir (untuk hitung jadwal)
//
// Untuk logika perebutan Juara ke-3:
//   Tim *semifinalisKalah1 = NULL; // Penyimpan tim semifinal pertama yang kalah
//   Tim *semifinalisKalah2 = NULL; // Penyimpan tim semifinal kedua yang kalah
//   bool matchKetiga       = false;// true jika pertandingan Juara ke-3 sedang berjalan


// -----------------------------------------------------------------------------
// BAGIAN 7: Fungsi Queue (Antrian Pertandingan)
// -----------------------------------------------------------------------------

// Fungsi: tambahAntrian(Tim *timA, Tim *timB, string tanggal, string ronde)
// Tujuan: Menambahkan satu pertandingan baru ke BELAKANG antrian (Enqueue)
//
// Variabel yang dibutuhkan:
//   NodeAntrian *baru  // Node antrian baru yang akan dibuat dengan "new"
//
// Hint algoritma:
//   1. Buat NodeAntrian baru dengan "new NodeAntrian"
//   2. Isi semua field-nya (timA, timB, tanggalTanding, ronde, berikutnya = NULL)
//   3. Cek apakah antrian kosong (belakangAntrian == NULL):
//      - Jika kosong: depan dan belakang sama-sama menunjuk ke node baru
//      - Jika tidak kosong: sambungkan node terakhir ke baru, geser belakangAntrian


// Fungsi: hapusAntrian()
// Tujuan: Menghapus satu pertandingan dari DEPAN antrian (Dequeue)
//
// Variabel yang dibutuhkan:
//   NodeAntrian *temp  // Pointer sementara untuk menyimpan node yang akan dihapus
//
// Hint algoritma:
//   1. Jika depanAntrian == NULL, langsung return (antrian sudah kosong)
//   2. Simpan depanAntrian ke variabel temp
//   3. Geser depanAntrian ke node berikutnya
//   4. Jika setelah digeser depanAntrian jadi NULL, set belakangAntrian = NULL juga
//   5. Hapus temp dengan "delete temp" untuk bebaskan memori


// Fungsi: antrianKosong() -> bool
// Tujuan: Mengecek apakah tidak ada pertandingan yang tersisa di antrian
//
// Hint algoritma:
//   - Cukup kembalikan (depanAntrian == NULL)


// -----------------------------------------------------------------------------
// BAGIAN 8: Struct & Array Riwayat Pertandingan
// -----------------------------------------------------------------------------

// TODO: Definisikan struct bernama "MatchResult" dengan field-field berikut:
//   Tim    *timA;     // Pointer ke tim A yang bertanding
//   Tim    *timB;     // Pointer ke tim B yang bertanding
//   Tim    *pemenang; // Pointer ke pemenang (NULL jika belum selesai)
//   string  ronde;    // Nama ronde pertandingan ini
//
// TODO: Deklarasikan konstanta dan array global:
//   const int MAX_MATCHES = 64;             // Maksimum riwayat pertandingan
//   MatchResult matchResults[MAX_MATCHES];  // Array untuk menyimpan semua riwayat
//   int jumlahHasil = 0;                    // Berapa banyak riwayat yang sudah tersimpan


// Fungsi: catatPertandingan(Tim *timA, Tim *timB, string ronde)
// Tujuan: Menyimpan data pertandingan baru ke array matchResults (pemenang = NULL dulu)
//
// Hint algoritma:
//   1. Cek jika jumlahHasil >= MAX_MATCHES, langsung return (array penuh)
//   2. Isi matchResults[jumlahHasil] dengan timA, timB, NULL, dan ronde
//   3. Increment jumlahHasil


// Fungsi: updatePemenang(Tim *timA, Tim *timB, Tim *pemenang)
// Tujuan: Mencari riwayat pertandingan yang cocok dan mengisi field pemenangnya
//
// Variabel yang dibutuhkan:
//   int i      // Counter for loop
//   bool cocok // Apakah match di index i cocok dengan timA dan timB?
//
// Hint algoritma:
//   1. Loop dari i = 0 sampai jumlahHasil
//   2. Cek apakah matchResults[i] cocok: timA dan timB bisa dalam urutan apapun
//      cocok = (timA==A && timB==B) || (timA==B && timB==A)
//   3. Pastikan pemenang di riwayat itu masih NULL (belum diisi)
//   4. Jika cocok dan belum diisi: isi pemenangnya, lalu return
