// =============================================================================
// File   : search_sort.cpp
// Tujuan : Fungsi utilitas pencarian dan pengurutan tim.
//
// Variabel global yang DIPAKAI dari models.cpp:
//   - Tim *kepala             (kepala linked list tim)
//
// Fungsi yang harus kamu buat di file ini:
//   1. cariTim(const string& namaTimCari) -> Tim*
//   2. urutkanKlasemen()
// =============================================================================


// -----------------------------------------------------------------------------
// Fungsi: cariTim(const string& namaTimCari) -> Tim*
// Tujuan: Mencari node Tim berdasarkan nama menggunakan Linear Search.
//         Jika ditemukan, kembalikan pointer ke node tersebut.
//         Jika tidak ditemukan, kembalikan NULL.
//
// Variabel yang dibutuhkan:
//   Tim *curr  // Pointer untuk traversal linked list, mulai dari kepala
//
// Hint algoritma (Linear Search pada Linked List):
//   1. Mulai dari curr = kepala
//   2. Selama curr tidak NULL:
//      a. Jika curr->nama == namaTimCari, kembalikan curr (ketemu!)
//      b. Geser curr ke curr->berikutnya
//   3. Jika loop selesai tanpa menemukan, kembalikan NULL
//
// Contoh penggunaan:
//   Tim *hasil = cariTim("Tim Garuda");
//   if (hasil != NULL) { /* tim ditemukan */ }


// -----------------------------------------------------------------------------
// Fungsi: urutkanKlasemen()
// Tujuan: Mengurutkan linked list tim berdasarkan poin dari TERBESAR ke TERKECIL
//         menggunakan algoritma Bubble Sort.
//
// Variabel yang dibutuhkan:
//   bool swapped  // Flag apakah ada pertukaran dalam satu putaran
//   Tim *curr     // Pointer untuk traversal selama proses sorting
//
// Hint algoritma (Bubble Sort pada Linked List):
//   1. Jika kepala == NULL atau kepala->berikutnya == NULL, return (tidak perlu sort)
//   2. Set swapped = true, lalu buat loop WHILE (swapped):
//      a. Set swapped = false
//      b. Set curr = kepala
//      c. Loop WHILE (curr->berikutnya != NULL):
//         - Jika curr->poin LEBIH KECIL dari curr->berikutnya->poin:
//           * Tukar isi DATA kedua node (bukan pointer-nya!)
//           * Gunakan swap() untuk: nama, password, jumlahPemain, poin, tereleminasi
//           * Set swapped = true
//         - Geser curr ke curr->berikutnya
//   3. Loop luar akan berhenti jika tidak ada pertukaran sama sekali
//
// PENTING: Yang ditukar adalah DATA di dalam node, BUKAN pointer node-nya!
//          Ini lebih mudah daripada memanipulasi pointer.
