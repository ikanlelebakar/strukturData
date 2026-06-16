// =============================================================================
// File   : buat_jadwal.cpp
// Tujuan : Membuat jadwal pertandingan Ronde 1 (atau Semifinal jika hanya 4 tim).
//          Memasangkan tim [0] vs [n-1], [1] vs [n-2], dst. dan menambahkan
//          setiap pertandingan ke antrian.
//
// Library tambahan yang dibutuhkan:
  #include <ctime>    // untuk struct tm dan mktime()
  #include <sstream>  // untuk ostringstream
  #include <iomanip>  // untuk setw() dan setfill()
//
// Variabel global yang DIPAKAI dari models.cpp:
  - bool   pendaftaranDitutup
  - bool   jadwalSudahDibuat  (set jadi true setelah jadwal dibuat)
  - int    jumlahTim
  - int    MAX_TIM
  - int    rondeSekarang      (set jadi 1 setelah jadwal dibuat)
  - string tanggalTerakhir    (simpan tanggal pertandingan terakhir di ronde ini)
  - Tim   *kepala
  - tambahAntrian()           (dari models.cpp)
  - catatPertandingan()       (dari models.cpp)
  - adalahPangkatDua()        (dari models.cpp)

Fungsi yang harus kamu buat di file ini:
  1. tambahHari(const string& tanggal, int hari) -> string   [helper]
  2. validasiTanggal(const string& tgl) -> bool              [helper]
  3. buatJadwal()
=============================================================================


-----------------------------------------------------------------------------
Fungsi: tambahHari(const string& tanggal, int hari) -> string
Tujuan: Menambahkan sejumlah hari ke tanggal format "YYYY-MM-DD" dan
        mengembalikan tanggal baru dalam format yang sama.

Variabel yang dibutuhkan:
  struct tm t = {}  // Struktur waktu dari library <ctime>
  ostringstream oss // Untuk memformat hasil ke string

Hint algoritma:
  1. Isi struct tm t:
     t.tm_year = stoi(tanggal.substr(0, 4)) - 1900  // tahun (dari 1900)
     t.tm_mon  = stoi(tanggal.substr(5, 2)) - 1     // bulan (0-based)
     t.tm_mday = stoi(tanggal.substr(8, 2))         // hari
  2. Tambah hari: t.tm_mday += hari
  3. Normalisasi tanggal (handle overflow bulan/tahun): mktime(&t)
  4. Format kembali ke string "YYYY-MM-DD" menggunakan ostringstream:
     oss << setfill('0') << (t.tm_year+1900) << "-" << setw(2) << (t.tm_mon+1)
         << "-" << setw(2) << t.tm_mday
  5. return oss.str()


-----------------------------------------------------------------------------
Fungsi: validasiTanggal(const string& tgl) -> bool
Tujuan: Mengecek apakah string tgl memiliki format yang valid: "YYYY-MM-DD"
        (10 karakter, tanda '-' di posisi 4 dan 7, sisanya angka)

Hint algoritma:
  1. Jika tgl.size() != 10, return false
  2. Jika tgl[4] != '-' || tgl[7] != '-', return false
  3. Loop i dari 0 sampai 9:
     - Skip jika i == 4 atau i == 7
     - Jika !isdigit(tgl[i]), return false
  4. return true


-----------------------------------------------------------------------------
Fungsi: buatJadwal()
Tujuan: Membuat pasangan pertandingan Ronde 1 dan memasukkannya ke antrian.
        Menggunakan pola: tim[0] vs tim[n-1], tim[1] vs tim[n-2], dst.

Variabel yang dibutuhkan:
  string  tanggalMulai        // Input tanggal awal dari admin
  Tim   **arrTim              // Array pointer sementara untuk menampung semua tim
  int     n                   // Jumlah tim yang terdaftar
  Tim    *curr                // Pointer traversal linked list
  string  labelRonde          // "Semifinal" jika n==4, atau "Ronde 1"

Hint algoritma:
  1. Guard checks (jika gagal, cetak pesan dan return):
     - Jika !pendaftaranDitutup -> "Admin harus menutup pendaftaran dulu"
     - Jika jumlahTim < 2      -> "Minimal 2 tim"
     - Jika !adalahPangkatDua(jumlahTim) -> "Jumlah tim harus pangkat 2"
     - Jika jadwalSudahDibuat  -> "Braket sudah dibuat"

  2. Loop DO-WHILE untuk input tanggal yang valid:
     Ulangi minta input sampai validasiTanggal(tanggalMulai) == true

  3. Salin semua pointer tim dari linked list ke arrTim:
     Tim **arrTim = new Tim*[MAX_TIM]
     Traversal linked list dengan curr, isi arrTim[n++] = curr

  4. Tentukan labelRonde: jika n == 4 -> "Semifinal", selain itu -> "Ronde 1"

  5. Loop for i dari 0 sampai n/2:
     a. Hitung tanggal: tgl = tambahHari(tanggalMulai, i)
     b. tambahAntrian(arrTim[i], arrTim[n-1-i], tgl, labelRonde)
     c. catatPertandingan(arrTim[i], arrTim[n-1-i], labelRonde)
     d. Cetak pasangan pertandingan ke layar

  6. Simpan tanggalTerakhir = tambahHari(tanggalMulai, n/2 - 1)
  7. Set rondeSekarang = 1, jadwalSudahDibuat = true
  8. delete[] arrTim (bebaskan memori array sementara)
