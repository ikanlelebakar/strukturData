// =============================================================================
// File   : hapus_tim.cpp
// Tujuan : Fungsi untuk menghapus sebuah tim dari linked list berdasarkan nama.
//          Hanya bisa dilakukan sebelum bracket dibuat.
//
// Variabel global yang DIPAKAI dari models.cpp:
//   - Tim  *kepala          (kepala linked list)
//   - int   jumlahTim       (dikurangi 1 jika berhasil hapus)
//   - bool  jadwalSudahDibuat (cek apakah masih boleh hapus)
//
// Fungsi yang harus kamu buat di file ini:
//   1. hapusTim()
// =============================================================================


// -----------------------------------------------------------------------------
// Fungsi: hapusTim()
// Tujuan: Mencari tim berdasarkan nama yang diinput admin, lalu menghapus
//         node tersebut dari linked list dan membebaskan memorinya.
//
// Variabel yang dibutuhkan:
//   string  namaCari  // Nama tim yang ingin dihapus
//   Tim    *curr      // Pointer untuk traversal linked list
//   Tim    *prev      // Pointer ke node SEBELUM curr (untuk menyambung ulang)
//
// Hint algoritma:
//   1. Jika kepala == NULL, cetak "Belum ada tim" lalu return
//   2. Jika jadwalSudahDibuat == true, cetak "Tidak bisa hapus" lalu return
//   3. Minta input namaCari: getline(cin, namaCari)
//   4. Set curr = kepala, prev = NULL
//   5. Loop WHILE (curr != NULL):
//      a. Jika curr->nama == namaCari -> TIM DITEMUKAN:
//         - Sambungkan linked list: jika prev == NULL, kepala = curr->berikutnya
//                                   jika prev != NULL, prev->berikutnya = curr->berikutnya
//         - Hapus curr dengan "delete curr"
//         - Kurangi jumlahTim--
//         - Cetak pesan sukses lalu return
//      b. Geser: prev = curr, curr = curr->berikutnya
//   6. Jika loop selesai tanpa menemukan, cetak "Tim tidak ditemukan"
//
// KONSEP PENTING — Menghapus node dari Linked List:
//   Sebelum hapus:  [prev] -> [curr] -> [curr->berikutnya]
//   Sesudah hapus:  [prev] -> [curr->berikutnya]
//   Caranya: sambungkan prev->berikutnya langsung ke curr->berikutnya,
//            baru kemudian delete curr.
