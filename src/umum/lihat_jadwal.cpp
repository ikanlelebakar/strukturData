// =============================================================================
// File   : lihat_jadwal.cpp
// Tujuan : Menampilkan seluruh antrian pertandingan yang sudah dijadwalkan,
//          dari pertandingan terdekat (depan antrian) hingga yang paling jauh.
//
// Variabel global yang DIPAKAI dari models.cpp:
//   - NodeAntrian *depanAntrian  (titik awal traversal antrian)
//   - antrianKosong()            (fungsi cek antrian kosong dari models.cpp)
//
// Fungsi yang harus kamu buat di file ini:
//   1. tampilJadwal()
// =============================================================================


// -----------------------------------------------------------------------------
// Fungsi: tampilJadwal()
// Tujuan: Menampilkan semua jadwal pertandingan dalam antrian secara berurutan.
//         Pertandingan di posisi pertama diberi label "<-- SEDANG BERLANGSUNG".
//
// Variabel yang dibutuhkan:
//   int           no    // Nomor urut pertandingan, mulai dari 1
//   NodeAntrian *curr   // Pointer untuk traversal antrian, mulai dari depanAntrian
//
// Hint algoritma:
//   1. Cetak judul "=== JADWAL ANTRIAN PERTANDINGAN ==="
//   2. Cek apakah antrian kosong dengan antrianKosong():
//      - Jika kosong, cetak "(Belum ada jadwal pertandingan)" lalu return
//   3. Set no = 1, set curr = depanAntrian
//   4. Loop WHILE (curr != NULL):
//      a. Cetak: no, curr->ronde, curr->timA->nama, curr->timB->nama, curr->tanggalTanding
//      b. Jika no == 1, tambahkan label "  <-- SEDANG BERLANGSUNG" di baris yang sama
//      c. Cetak endl, geser curr ke curr->berikutnya, increment no
//
// Contoh output yang diharapkan:
//   === JADWAL ANTRIAN PERTANDINGAN ===
//   1. [Semifinal] Tim A vs Tim B  |  Tanggal: 2025-01-10  <-- SEDANG BERLANGSUNG
//   2. [Semifinal] Tim C vs Tim D  |  Tanggal: 2025-01-11
