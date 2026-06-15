// =============================================================================
// File   : cari_lawan.cpp
// Tujuan : Fungsi untuk tim mencari dan melihat profil tim lain (sebagai lawan).
//          Tim tidak bisa mencari profilnya sendiri.
//
// Variabel global yang DIPAKAI dari models.cpp:
//   - Tim *kepala  (untuk menampilkan daftar tim lawan yang tersedia)
//
// Fungsi dari search_sort.cpp yang dipakai:
//   - cariTim(const string& nama)  -> Tim*
//
// PERHATIAN: Ada dua fungsi bernama "cariTim" dalam project ini!
//   - cariTim(string) di search_sort.cpp  -> mencari berdasarkan nama, return Tim*
//   - cariTim(Tim*)   di file INI         -> menu cari profil lawan, return void
//   Ini disebut "function overloading" — C++ memilih fungsi yang tepat
//   berdasarkan parameter yang diberikan.
//
// Fungsi yang harus kamu buat di file ini:
//   1. cariTim(Tim *timLogin)  — dengan parameter pointer Tim (bukan string!)
// =============================================================================


// -----------------------------------------------------------------------------
// Fungsi: cariTim(Tim *timLogin)
// Tujuan: Menampilkan daftar tim lain (lawan), lalu meminta nama tim yang
//         ingin dilihat profilnya dan menampilkan info tim tersebut.
//
// Variabel yang dibutuhkan:
//   Tim    *curr      // Pointer traversal linked list untuk tampil daftar
//   int     idx       // Nomor urut daftar tim lawan
//   bool    adaLawan  // Flag apakah ada tim lain selain timLogin
//   string  namaCari  // Nama tim yang ingin dicari profilnya
//   Tim    *hasil     // Hasil pencarian dari cariTim(namaCari)
//
// Hint algoritma:
//   1. Jika kepala == NULL, cetak "Belum ada tim" lalu return
//
//   2. Tampilkan daftar tim lawan:
//      Loop linked list, tampilkan nama tim yang curr != timLogin
//      Jika tidak ada satu pun tim lain, cetak "Tidak ada lawan" lalu return
//
//   3. Minta input nama tim yang dicari:
//      cout << "Masukkan nama tim yang dicari: "
//      getline(cin, namaCari)
//
//   4. Cek apakah yang dicari adalah tim sendiri:
//      Jika timLogin != NULL && namaCari == timLogin->nama:
//        Cetak "[ERROR] Anda tidak bisa mencari profil sendiri", return
//
//   5. Cari tim: Tim *hasil = cariTim(namaCari)  // panggil versi string dari search_sort.cpp
//      Jika hasil == NULL -> "Tim tidak ditemukan", return
//
//   6. Tampilkan profil tim:
//      - hasil->nama
//      - hasil->jumlahPemain
//      - hasil->poin
//      - status: hasil->tereleminasi ? "Tereliminasi" : "Aktif"
