// =============================================================================
// File   : lihat_tim.cpp
// Tujuan : Menampilkan daftar seluruh tim yang terdaftar beserta info mereka.
//
// Variabel global yang DIPAKAI dari models.cpp:
//   - Tim *kepala    (kepala linked list)
//   - int  jumlahTim (untuk menampilkan total)
//
// Fungsi yang harus kamu buat di file ini:
//   1. tampilkanTim()
// =============================================================================


// -----------------------------------------------------------------------------
// Fungsi: tampilkanTim()
// Tujuan: Menelusuri seluruh linked list tim dan mencetak informasi setiap tim.
//
// Variabel yang dibutuhkan:
//   int   no    // Nomor urut, mulai dari 1
//   Tim *curr   // Pointer traversal linked list, mulai dari kepala
//
// Hint algoritma:
//   1. Cetak judul "=== DAFTAR TIM TERDAFTAR ==="
//   2. Jika kepala == NULL: cetak "(Belum ada tim yang terdaftar)" lalu return
//   3. Cetak "Total tim: [jumlahTim]"
//   4. Set no = 1, curr = kepala
//   5. Loop WHILE (curr != NULL):
//      a. Cetak: no, curr->nama
//      b. Cetak: curr->jumlahPemain
//      c. Cetak: curr->poin
//      d. Cetak status: jika curr->tereleminasi -> "Tereliminasi", jika tidak -> "Aktif"
//      e. Cetak garis pemisah
//      f. Geser curr ke curr->berikutnya, increment no
