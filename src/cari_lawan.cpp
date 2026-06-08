/*
 * File: cari_lawan.cpp
 * Deskripsi: File ini berisi fungsi bagi pemain untuk memantau profil tim kompetitor/lawan berdasarkan input nama.
 * 
 * Tugas Tim/Mahasiswa:
 * 1. Implementasikan fungsi cari profil tim lawan:
 *    - Nama Fungsi: cariLawan
 *    - Parameter: tidak ada
 *    - Return: void
 *    - Kebutuhan Teknis:
 *      * Minta input string berupa Nama Tim lawan yang ingin dicari profilnya.
 *      * Panggil fungsi 'cariIndeksTim(namaTimLawan)' dari file 'search_sort.cpp' untuk melakukan pencarian linear.
 *      * Jika indeks yang dikembalikan bernilai >= 0:
 *        - Tampilkan nama tim, poin saat ini, status eliminasi, dan daftar anggota tim tersebut ke layar.
 *      * Jika indeks bernilai -1 (tidak ketemu):
 *        - Tampilkan pesan informatif bahwa tim lawan tersebut tidak ditemukan di dalam sistem turnamen.
 */
