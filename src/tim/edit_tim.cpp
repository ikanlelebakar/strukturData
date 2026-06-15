// =============================================================================
// File   : edit_tim.cpp
// Tujuan : Fungsi untuk mengubah data tim. Ada 3 fungsi di file ini:
//          - editDataTim() : logika utama edit (dipakai oleh fungsi lain)
//          - menuEditTim() : dipanggil oleh Admin (cari tim dulu berdasarkan nama)
//          - editTim()     : dipanggil oleh Tim sendiri (langsung pakai pointer login)
//
// Variabel global yang DIPAKAI dari models.cpp:
//   - int MIN_PEMAIN, MAX_PEMAIN
//   - cariTim()  (dari search_sort.cpp, untuk cek duplikat nama)
//   - Tim *kepala (dipakai cariTim() untuk traversal)
//
// Fungsi yang harus kamu buat di file ini:
//   1. editDataTim(Tim *ptrTim)
//   2. menuEditTim()
//   3. editTim(Tim *timLogin)
// =============================================================================


// -----------------------------------------------------------------------------
// Fungsi: editDataTim(Tim *ptrTim)
// Tujuan: Menampilkan menu pilihan edit dan mengubah data tim yang ditunjuk
//         oleh ptrTim. Ada 3 pilihan: ubah nama, ubah jumlah pemain, ubah password.
//
// Variabel yang dibutuhkan:
//   int pilihan     // Pilihan menu yang diinput pengguna
//
//   // Di dalam case 1 (ubah nama):
//   string  namaBaru    // Nama baru yang diinput
//   Tim    *existing    // Hasil cariTim(namaBaru) untuk cek duplikat
//
//   // Di dalam case 2 (ubah jumlah pemain):
//   int jumlahBaru      // Jumlah pemain baru yang diinput
//
//   // Di dalam case 3 (ubah password):
//   string passBaru     // Password baru yang diinput
//
// Hint algoritma:
//   1. Jika ptrTim == NULL, cetak "Pointer tidak valid" lalu return
//   2. Tampilkan menu:
//      "1. Ubah Nama Tim"
//      "2. Ubah Jumlah Pemain"
//      "3. Ubah Password"
//      "0. Batal"
//   3. cin >> pilihan, cin.ignore()
//   4. Gunakan SWITCH-CASE:
//
//      case 1 — Ubah Nama:
//        getline(cin, namaBaru)
//        Tim *existing = cariTim(namaBaru)
//        Jika existing != NULL && existing != ptrTim -> "Nama sudah dipakai"
//        Jika tidak -> ptrTim->nama = namaBaru, cetak sukses
//
//      case 2 — Ubah Jumlah Pemain:
//        Loop DO-WHILE sampai jumlahBaru valid (MIN_PEMAIN s/d MAX_PEMAIN)
//        ptrTim->jumlahPemain = jumlahBaru
//
//      case 3 — Ubah Password:
//        getline(cin, passBaru)
//        ptrTim->password = passBaru
//
//      case 0 — Batal


// -----------------------------------------------------------------------------
// Fungsi: menuEditTim()
// Tujuan: Versi Admin — mencari tim berdasarkan nama yang diinput dulu,
//         baru memanggil editDataTim() dengan pointer tim yang ditemukan.
//
// Variabel yang dibutuhkan:
//   string  namaCari  // Nama tim yang ingin diedit
//   Tim    *target    // Hasil pencarian menggunakan cariTim()
//
// Hint algoritma:
//   1. Jika kepala == NULL, cetak "Belum ada tim" lalu return
//   2. getline(cin, namaCari)
//   3. Tim *target = cariTim(namaCari)
//   4. Jika target == NULL -> "Tim tidak ditemukan", return
//   5. Panggil editDataTim(target)


// -----------------------------------------------------------------------------
// Fungsi: editTim(Tim *timLogin)
// Tujuan: Versi Tim — tim yang sedang login langsung bisa edit data sendiri
//         tanpa perlu mencari berdasarkan nama.
//
// Hint algoritma:
//   1. Jika timLogin == NULL, langsung return
//   2. Panggil editDataTim(timLogin)
