// =============================================================================
// File   : lihat_klasemen.cpp
// Tujuan : Menampilkan papan klasemen semua tim, diurutkan berdasarkan poin
//          dari yang terbesar. Menggunakan linked list sementara agar linked
//          list asli tidak berubah urutannya.
//
// Variabel global yang DIPAKAI dari models.cpp:
//   - Tim *kepala           (kepala linked list tim asli)
//   - bool jadwalSudahDibuat
//   - int  MAX_TIM
//   - antrianKosong()       (dari models.cpp)
//   - hitungTimAktif()      (dari input_hasil.cpp — pastikan di-include duluan)
//
// Fungsi yang harus kamu buat di file ini:
//   1. tampilKlasemen()
//
// CATATAN: Karena linked list asli tidak boleh dirusak, kamu perlu membuat
//          salinan sementara (temporary linked list) lalu sort salinan itu.
// =============================================================================


// -----------------------------------------------------------------------------
// Fungsi: tampilKlasemen()
// Tujuan: Menampilkan tabel klasemen semua tim yang sudah diurutkan berdasarkan
//         poin. Jika turnamen sudah selesai, tampilkan peringkat (Juara 1, 2, dst).
//         Jika belum selesai, tampilkan status (Aktif / Tereliminasi).
//
// Variabel yang dibutuhkan:
//   bool turnamenSelesai         // true jika turnamen sudah berakhir
//
//   // Struct LOKAL untuk salinan sementara (definisikan DI DALAM fungsi ini):
//   struct NodeTemp {
//     string   nama;
//     int      poin;
//     bool     tereleminasi;
//     NodeTemp *next;
//   };
//
//   NodeTemp *headTemp  // Kepala linked list sementara
//   NodeTemp *tailTemp  // Ekor linked list sementara (untuk tail insertion)
//   Tim      *curr      // Pointer traversal linked list asli
//   NodeTemp *baru      // Node sementara baru yang dibuat saat menyalin data
//
// Hint algoritma — ada 4 tahap besar:
//
//   TAHAP 1 — Cek apakah turnamen sudah selesai:
//     turnamenSelesai = jadwalSudahDibuat && antrianKosong() && (hitungTimAktif() <= 1)
//
//   TAHAP 2 — Salin data dari linked list asli ke linked list sementara:
//     Loop WHILE (curr != NULL):
//       a. Buat NodeTemp baru dengan "new NodeTemp"
//       b. Salin: baru->nama, baru->poin, baru->tereleminasi dari curr
//       c. Set baru->next = NULL
//       d. Tambahkan ke linked list sementara (tail insertion dengan headTemp & tailTemp)
//       e. Geser curr ke curr->berikutnya
//
//   TAHAP 3 — Urutkan linked list sementara dengan Bubble Sort (descending by poin):
//     Loop WHILE (swapped == true):
//       Jika poin node saat ini LEBIH KECIL dari node berikutnya -> swap DATA
//       (Swap: nama, poin, tereleminasi)
//
//   TAHAP 4 — Cetak tabel klasemen:
//     Cetak header: "No", "Nama Tim", "Poin", "Status" atau "Peringkat"
//     Loop melalui linked list sementara, cetak setiap baris:
//       - Jika turnamenSelesai: tampilkan "Juara 1", "Juara 2", "Juara 3", "Juara 4", dll.
//       - Jika belum: tampilkan "Aktif" atau "Tereliminasi"
//
//   TAHAP 5 — Bebaskan memori linked list sementara (jangan sampai memory leak!):
//     Loop WHILE (del != NULL):
//       Simpan del->next ke tempNext
//       delete del
//       del = tempNext
//
// Contoh output (turnamen belum selesai):
//   === KLASEMEN TURNAMEN ===
//   No   Nama Tim            Poin    Status
//   --------------------------------------------------
//   1    Tim Garuda          10      Aktif
//   2    Tim Elang           5       Aktif
//   3    Tim Harimau         1       Tereliminasi
