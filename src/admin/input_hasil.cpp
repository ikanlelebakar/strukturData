// =============================================================================
File   : input_hasil.cpp
Tujuan : Menginput skor pertandingan, menentukan pemenang/yang kalah,
         mengelola eliminasi, dan membuat jadwal ronde berikutnya.
         File ini adalah yang paling kompleks — baca baik-baik!

// Variabel global yang DIPAKAI dari models.cpp:
//   - NodeAntrian *depanAntrian
//   - bool jadwalSudahDibuat
//   - bool matchKetiga         (true saat pertandingan Juara ke-3 berlangsung)
//   - int  rondeSekarang       (increment saat buat jadwal ronde baru)
//   - int  MAX_TIM
//   - string tanggalTerakhir
//   - Tim *semifinalisKalah1   (menyimpan tim semifinal pertama yang kalah)
//   - Tim *semifinalisKalah2   (menyimpan tim semifinal kedua yang kalah)
//   - Tim *kepala
//   - antrianKosong(), hapusAntrian(), tambahAntrian(), catatPertandingan(), updatePemenang()
//
// Fungsi dari buat_jadwal.cpp yang dipakai:
//   - tambahHari()
//
// Fungsi yang harus kamu buat di file ini:
//   1. hitungTimAktif() -> int
//   2. inputHasil()
//   3. buatJadwalBerikutnya()
// =============================================================================


// -----------------------------------------------------------------------------
// Fungsi: hitungTimAktif() -> int
// Tujuan: Menghitung berapa tim yang belum tereliminasi (masih aktif).
//
// Variabel yang dibutuhkan:
//   int  count   // Penghitung tim aktif
//   Tim *curr    // Pointer traversal linked list
//
// Hint algoritma:
//   1. Set count = 0, curr = kepala
//   2. Loop WHILE (curr != NULL):
//      - Jika !curr->tereleminasi, increment count
//      - Geser curr
//   3. return count


// -----------------------------------------------------------------------------
// Fungsi: inputHasil()
// Tujuan: Memproses pertandingan di depan antrian. Admin menginput skor kedua
//         tim, sistem menentukan pemenang, memberi poin, dan mengeliminasi
//         tim yang kalah. Menangani kasus khusus Semifinal dan Juara ke-3.
//
// Variabel yang dibutuhkan:
//   NodeAntrian *match      // Node antrian di depan (yang sedang dimainkan)
//   Tim *timA, *timB        // Dua tim yang bertanding
//   int  skorA, skorB       // Skor dari masing-masing tim
//   bool inputValid         // Flag untuk validasi input skor
//   Tim *pemenang, *kalah   // Pointer ke tim pemenang dan yang kalah
//   bool iniMatchKetiga     // Salinan flag matchKetiga sebelum diproses
//   string rondeMatch       // Nama ronde pertandingan ini
//   int tambahPoin          // Berapa poin yang diberikan ke pemenang
//
// Hint algoritma:
//   1. Guard check: jika antrianKosong(), cetak pesan sesuai kondisi lalu return
//
//   2. Ambil data dari depan antrian:
//      match = depanAntrian; timA = match->timA; timB = match->timB
//
//   3. Tampilkan info pertandingan (ronde, tanggal, nama tim)
//
//   4. Loop DO-WHILE untuk input skor yang valid:
//      - Minta cin >> skorA dan cin >> skorB
//      - Validasi: skor tidak boleh negatif, tidak boleh > 3, tidak boleh seri
//
//   5. Tentukan pemenang dan kalah:
//      pemenang = (skorA > skorB) ? timA : timB
//      kalah    = (skorA > skorB) ? timB : timA
//
//   6. Hitung tambahPoin berdasarkan ronde:
//      - "Perebutan Juara ke-3" -> 5 poin
//      - "Final"                -> 20 poin
//      - "Semifinal"            -> 10 poin
//      - Ronde lain             -> 1 << (rondeSekarang - 1)  [bit shift = pangkat 2]
//
//   7. Jika iniMatchKetiga == true (pertandingan Juara ke-3):
//      - Set KEDUA tim tereleminasi = true (keduanya tidak lanjut)
//      - Beri pemenang tambahPoin
//      - matchKetiga = false
//      - updatePemenang(), hapusAntrian(), cetak hasil, return
//
//   8. Jika bukan matchKetiga:
//      - Beri pemenang tambahPoin
//      - updatePemenang()
//      - Simpan tanggalMatch dari match->tanggalTanding
//      - hapusAntrian()
//      - tanggalTerakhir = tanggalMatch
//
//   9. Logika khusus Semifinal (iniSemifinal = rondeMatch == "Semifinal"):
//      - Jika true: tim yang kalah TIDAK langsung dieliminasi (bisa main Juara ke-3)
//        * Jika semifinalisKalah1 == NULL -> simpan ke semifinalisKalah1
//        * Jika sudah ada -> simpan ke semifinalisKalah2, buat jadwal Perebutan Juara ke-3:
//          tanggalJuara3 = tambahHari(tanggalFinal, -1)
//          tambahAntrian(semifinalisKalah1, semifinalisKalah2, tanggalJuara3, "Perebutan Juara ke-3")
//          catatPertandingan(...), matchKetiga = true
//      - Jika false: kalah->tereleminasi = true
//
//  10. Setelah hapusAntrian(), cek apakah antrian sudah kosong:
//      - Jika kosong dan masih ada >1 tim aktif: info admin untuk buat ronde berikutnya
//      - Jika kosong dan hanya <=1 tim aktif: cetak "TURNAMEN SELESAI!"


// -----------------------------------------------------------------------------
// Fungsi: buatJadwalBerikutnya()
// Tujuan: Setelah semua pertandingan ronde sekarang selesai, membuat jadwal
//         untuk ronde berikutnya menggunakan tim yang masih aktif.
//
// Variabel yang dibutuhkan:
//   Tim  **timAktif    // Array sementara untuk menampung tim yang masih aktif
//   int    n           // Jumlah tim aktif
//   Tim   *curr        // Pointer traversal linked list
//   string namaRonde   // Nama ronde berikutnya
//   int    offsetHari  // Jeda hari dari pertandingan terakhir
//   string tanggalRonde// Tanggal ronde berikutnya
//
// Hint algoritma:
//   1. Guard checks:
//      - Jika !jadwalSudahDibuat -> "Braket belum dibuat"
//      - Jika !antrianKosong() -> "Masih ada pertandingan yang belum selesai"
//
//   2. Kumpulkan tim aktif:
//      Tim **timAktif = new Tim*[MAX_TIM]
//      Loop linked list: jika !curr->tereleminasi, tambahkan ke timAktif[n++]
//
//   3. Jika n < 2, tidak bisa buat ronde baru -> return
//
//   4. Increment rondeSekarang++
//
//   5. Tentukan nama ronde dan offset hari:
//      - n == 4 -> namaRonde = "Semifinal",  offsetHari = 4
//      - n == 2 -> namaRonde = "Final",       offsetHari = 5
//      - lainnya-> namaRonde = "Ronde " + to_string(rondeSekarang), offsetHari = 3
//
//   6. Hitung tanggal ronde: tanggalRonde = tambahHari(tanggalTerakhir, offsetHari)
//
//   7. Loop for i dari 0 sampai n/2:
//      - tambahAntrian(timAktif[i], timAktif[n-1-i], tanggalRonde, namaRonde)
//      - catatPertandingan(timAktif[i], timAktif[n-1-i], namaRonde)
//      - Cetak pasangan ke layar
//
//   8. delete[] timAktif
