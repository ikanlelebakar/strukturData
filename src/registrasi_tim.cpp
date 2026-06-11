/*
 * File: registrasi_tim.cpp
 * Deskripsi: File ini berisi fungsi untuk mendaftarkan tim baru ke sistem.
 *            Pendaftaran hanya bisa dilakukan selama Admin belum menutup pendaftaran.
 *
 * Tugas Tim/Mahasiswa:
 * 1. Implementasikan fungsi registrasi tim baru:
 *    - Nama Fungsi: registrasiTimBaru
 *    - Parameter: tidak ada (mengakses langsung variabel global headTim, jumlahTimAktif)
 *    - Return: void
 *    - Kebutuhan Teknis:
 *      * Cek flag 'pendaftaranDitutup'. Jika true, tolak pendaftaran dengan pesan error.
 *      * Cek apakah jumlahTimAktif >= MAX_TIM. Jika penuh, tolak pendaftaran.
 *      * Minta input nama tim (string) -> disimpan sebagai namaTim sekaligus username login.
 *      * Cek apakah nama tim sudah terdaftar (traverse linked list). Jika duplikat, tolak.
 *      * Minta input password (string) untuk login tim.
 *      * Minta input jumlah pemain (int, valid: MIN_PEMAIN s.d. MAX_PEMAIN = 1-7).
 *        Validasi input, tolak jika di luar range.
 *      * Buat node Tim baru dengan:
 *        - namaTim = input nama tim
 *        - password = input password
 *        - jumlahPemain = input jumlah pemain
 *        - poin = 0
 *        - isEliminated = false
 *        - next = nullptr
 *      * Tambahkan node baru ke akhir linked list (tail insertion).
 *      * Increment jumlahTimAktif.
 *      * Tampilkan pesan sukses bahwa tim berhasil terdaftar.
 */
