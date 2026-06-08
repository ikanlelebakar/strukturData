/*
 * File: registrasi_tim.cpp
 * Deskripsi: File ini berisi fungsi untuk mendaftarkan tim baru beserta anggotanya ke sistem oleh pemain/peserta.
 * 
 * Tugas Tim/Mahasiswa:
 * 1. Implementasikan fungsi registrasi tim baru:
 *    - Nama Fungsi: registrasiTimBaru
 *    - Parameter: tidak ada (mengakses langsung array global 'daftarTim' dan 'jumlahTimAktif')
 *    - Return: void
 *    - Kebutuhan Teknis:
 *      * Cek terlebih dahulu apakah kuota tim sudah penuh menggunakan 'jumlahTimAktif >= MAX_TIM'. Jika penuh, tolak pendaftaran.
 *      * Minta input Nama Tim dari pengguna.
 *      * Minta input nama-nama anggota tim (5 orang) secara bertahap dan masukkan ke dalam array 'anggota' di struct Tim.
 *      * Set nilai awal poin tim menjadi 0 (poin = 0) dan status eliminasi menjadi false (isEliminated = false).
 *      * Masukkan data baru tersebut ke indeks ke-'jumlahTimAktif' pada array 'daftarTim'.
 *      * Tambahkan variabel global jumlahTimAktif sebanyak 1 (jumlahTimAktif++).
 *      * Berikan notifikasi sukses bahwa tim berhasil terdaftar.
 */
