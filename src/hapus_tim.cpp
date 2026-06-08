/*
 * File: hapus_tim.cpp
 * Deskripsi: File ini berisi fungsi untuk menghapus tim dari daftar turnamen dan merapatkan kembali indeks array.
 * 
 * Tugas Tim/Mahasiswa:
 * 1. Implementasikan fungsi hapus tim:
 *    - Nama Fungsi: hapusTim
 *    - Parameter: tidak ada (mengakses langsung array global 'daftarTim' dan 'jumlahTimAktif')
 *    - Return: void
 *    - Kebutuhan Teknis:
 *      * Meminta input nama tim yang ingin dihapus.
 *      * Cari indeks tim menggunakan fungsi 'cariIndeksTim'.
 *      * Jika ditemukan:
 *        - Lakukan perulangan (loop) untuk menggeser elemen-elemen array ke arah kiri (indeks i diisi oleh indeks i+1) mulai dari indeks yang ditemukan hingga indeks 'jumlahTimAktif - 2'.
 *        - Kurangi nilai variabel global 'jumlahTimAktif' sebanyak 1 (jumlahTimAktif--).
 *        - Tampilkan pesan sukses bahwa tim berhasil dihapus.
 *      * Jika tidak ditemukan, tampilkan pesan bahwa tim tidak ada di dalam daftar.
 */
