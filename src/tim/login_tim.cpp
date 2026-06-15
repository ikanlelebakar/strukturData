// =============================================================================
// File   : login_tim.cpp
// Tujuan : Fungsi autentikasi untuk tim peserta. Mencari tim berdasarkan nama,
//          lalu mencocokkan password. Mengembalikan pointer ke tim jika berhasil.
//
// Variabel global yang DIPAKAI dari models.cpp:
//   - Tim *kepala  (untuk traversal linked list mencari nama tim)
//
// Fungsi yang harus kamu buat di file ini:
//   1. masukTim() -> Tim*
// =============================================================================


// -----------------------------------------------------------------------------
// Fungsi: masukTim() -> Tim*
// Tujuan: Meminta nama tim dan password, mencari tim dengan nama tersebut
//         di linked list, lalu memverifikasi password-nya.
//         Mengembalikan pointer ke Tim jika berhasil, NULL jika gagal.
//
// Variabel yang dibutuhkan:
//   string  nama      // Input nama tim (username)
//   string  password  // Input password
//   Tim    *curr      // Pointer traversal linked list
//
// Hint algoritma:
//   1. Cetak header "=== LOGIN TIM ==="
//   2. Input nama: getline(cin, nama)
//   3. Input password: getline(cin, password)
//   4. Set curr = kepala
//   5. Loop WHILE (curr != NULL):
//      a. Jika curr->nama == nama -> nama tim ditemukan:
//         - Jika curr->password == password:
//           * Cetak "Login berhasil. Selamat datang, Tim [nama]!"
//           * return curr  (kembalikan pointer ke tim yang login)
//         - Jika password salah:
//           * Cetak "Password salah."
//           * return NULL
//      b. Geser curr ke curr->berikutnya
//   6. Jika loop selesai tanpa menemukan nama:
//      Cetak "Tim tidak ditemukan", return NULL
//
// CATATAN: Fungsi ini mengembalikan pointer Tim* bukan bool.
//          Pointer ini dipakai di menu tim untuk tahu "siapa yang sedang login".
