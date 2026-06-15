// =============================================================================
// File   : registrasi_tim.cpp
// Tujuan : Mendaftarkan tim baru ke dalam sistem (menambahkan node baru di
//          akhir linked list / tail insertion).
//
// Variabel global yang DIPAKAI dari models.cpp:
//   - bool pendaftaranDitutup  (cek apakah masih bisa daftar)
//   - int  jumlahTim           (cek kuota dan increment setelah daftar)
//   - int  MAX_TIM             (batas maksimum tim)
//   - int  MIN_PEMAIN, MAX_PEMAIN (batas jumlah pemain)
//   - Tim *kepala              (pointer ke awal linked list)
//   - cariTim()                (dari search_sort.cpp, untuk cek duplikat nama)
//
// Fungsi yang harus kamu buat di file ini:
//   1. daftarTim()
// =============================================================================


// -----------------------------------------------------------------------------
// Fungsi: daftarTim()
// Tujuan: Meminta input nama, password, dan jumlah pemain dari pengguna,
//         lalu membuat node Tim baru dan menyambungkannya di akhir linked list.
//
// Variabel yang dibutuhkan:
//   string nama          // Nama tim yang diinput
//   string password      // Password tim yang diinput
//   int    jumlahPemain  // Jumlah pemain tim (harus MIN_PEMAIN s/d MAX_PEMAIN)
//   Tim   *baru          // Node Tim baru yang akan dibuat dengan "new Tim"
//   Tim   *curr          // Pointer traversal untuk mencari ekor linked list
//
// Hint algoritma:
//   1. Guard checks (jika gagal, cetak pesan dan return):
//      - Jika pendaftaranDitutup -> "Pendaftaran sudah ditutup"
//      - Jika jumlahTim >= MAX_TIM -> "Batas maksimum tercapai"
//
//   2. Input nama: getline(cin, nama)
//   3. Cek duplikat: if (cariTim(nama) != NULL) -> "Nama sudah dipakai", return
//   4. Input password: getline(cin, password)
//   5. Loop DO-WHILE untuk jumlahPemain yang valid:
//      Ulangi sampai MIN_PEMAIN <= jumlahPemain <= MAX_PEMAIN
//
//   6. Buat node baru:
//      Tim *baru = new Tim
//      Isi: baru->nama, baru->password, baru->jumlahPemain, baru->poin = 0,
//           baru->tereleminasi = false, baru->berikutnya = NULL
//
//   7. Tambahkan ke akhir linked list (Tail Insertion):
//      - Jika kepala == NULL: kepala = baru  (list masih kosong)
//      - Jika tidak: traversal sampai curr->berikutnya == NULL,
//                    lalu curr->berikutnya = baru
//
//   8. jumlahTim++
//   9. Cetak pesan sukses: nama tim dan total tim saat ini
//  10. Jika jumlahTim >= MAX_TIM: set pendaftaranDitutup = true, cetak info
//  11. Cetak "Tekan ENTER untuk kembali..." lalu cin.get()
