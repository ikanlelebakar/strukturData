// =============================================================================
// File   : lihat_bracket.cpp
// Tujuan : Menampilkan bagan turnamen (bracket) secara visual di terminal,
//          berbentuk tabel horizontal dari kiri (ronde awal) ke kanan (final).
//
// Variabel global yang DIPAKAI dari models.cpp:
//   - bool jadwalSudahDibuat
//   - int  jumlahHasil
//   - MatchResult matchResults[]
//   - NodeAntrian *depanAntrian
//   - antrianKosong()
//
// Library tambahan yang dibutuhkan (sudah ada di main.cpp, tidak perlu #include lagi):
//   - <vector>   untuk menyimpan daftar ronde dan match per ronde
//   - <map>      untuk mengecek duplikat nama ronde
//   - <iomanip>  untuk setw() (format tabel)
//
// Fungsi yang harus kamu buat di file ini:
//   1. left_pad_str(const string& s, int w) -> string   [fungsi helper]
//   2. tampilBracket()
// =============================================================================


// -----------------------------------------------------------------------------
// Fungsi: left_pad_str(const string& s, int w) -> string
// Tujuan: Mengembalikan string s yang sudah dipadding spasi di kanan sampai
//         lebar total w karakter (digunakan untuk merapikan tampilan grid bracket).
//
// Variabel yang dibutuhkan: tidak ada variabel tambahan
//
// Hint algoritma:
//   - Jika panjang s >= w, potong s sampai w karakter: return s.substr(0, w)
//   - Jika panjang s < w, tambahkan spasi di belakang:
//     return s + string(w - s.size(), ' ')


// -----------------------------------------------------------------------------
// Fungsi: tampilBracket()
// Tujuan: Menampilkan bagan turnamen secara visual di terminal.
//         Bagan dibuat dalam bentuk "grid" 2D, lalu dicetak baris per baris.
//
// Variabel yang dibutuhkan:
//   vector<string>         urutanRonde      // Semua nama ronde unik sesuai urutan
//   map<string, bool>      sudahAda         // Untuk cek nama ronde sudah masuk atau belum
//   vector<string>         rondeUtama       // Ronde utama (tanpa "Perebutan Juara ke-3")
//   bool                   adaJuara3        // Flag: apakah ada pertandingan juara ke-3?
//   int                    jumlahRondeUtama // Berapa ronde utama yang ada
//   vector<vector<int>>    matchPerRonde    // Index match di matchResults per ronde
//   const int              LEBAR = 28       // Lebar setiap kolom dalam grid
//   int                    totalBaris       // Total baris grid = jumlahMatchR0 * 4
//   vector<vector<string>> grid             // Grid 2D: grid[baris][kolom_ronde]
//
// Hint algoritma — ada beberapa tahap besar:
//
//   TAHAP 1 — Guard check:
//     Jika !jadwalSudahDibuat, cetak pesan dan return
//     Jika jumlahHasil == 0, cetak pesan dan return
//
//   TAHAP 2 — Kumpulkan nama ronde secara unik dan berurutan:
//     Loop matchResults[0..jumlahHasil]:
//       Jika ronde belum ada di map sudahAda, tambahkan ke urutanRonde
//     Pisahkan "Perebutan Juara ke-3" ke flag adaJuara3, sisanya ke rondeUtama
//
//   TAHAP 3 — Cetak header nama ronde:
//     Loop rondeUtama, cetak setiap nama dengan setw(28)
//
//   TAHAP 4 — Kumpulkan index match per ronde:
//     matchPerRonde adalah vector 2D berukuran [jumlahRondeUtama]
//     Loop semua matchResults, masukkan index ke matchPerRonde[ri] yang sesuai
//
//   TAHAP 5 — Buat grid kosong dan isi:
//     totalBaris = matchPerRonde[0].size() * 4
//     grid berukuran [totalBaris][jumlahRondeUtama], diisi string spasi selebar LEBAR
//
//     Untuk setiap ronde ri dan setiap match mi:
//       Hitung posisi baris:
//         jarak       = totalBaris / jumlahMatchRi
//         offset      = 1 << ri   (pangkat 2 berdasarkan nomor ronde)
//         barisCenter = mi * jarak + jarak/2 - 1
//         barisA      = barisCenter - offset
//         barisB      = barisCenter + offset
//
//       Isi grid[barisA][ri] = status+namaTimA + " ---\"
//       Isi grid[barisB][ri] = status+namaTimB + " ---/"
//       Isi grid[barisCenter][ri] = spasi + "  |-->"
//       Jika ini kolom Final (ri == jumlahRondeUtama-1): tambahkan nama pemenang
//
//   TAHAP 6 — Cetak grid baris per baris
//
//   TAHAP 7 — Jika adaJuara3, cetak bagian Perebutan Juara ke-3 secara terpisah
//
// Keterangan status tim:
//   "[O] " = tim masih Aktif
//   "[X] " = tim sudah Tereliminasi
