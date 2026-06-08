/*
 * File: lihat_jadwal.cpp
 * Deskripsi: File ini berisi fungsi bagi pemain untuk melihat daftar antrian jadwal pertandingan turnamen saat ini.
 * 
 * Tugas Tim/Mahasiswa:
 * 1. Implementasikan fungsi untuk melihat antrian jadwal pertandingan:
 *    - Nama Fungsi: lihatJadwalAntrian
 *    - Parameter: tidak ada (mengakses langsung objek global queue 'antrian' atau array pendukung)
 *    - Return: void
 *    - Kebutuhan Teknis:
 *      * Cek terlebih dahulu apakah antrian tanding kosong menggunakan 'isEmpty()'. Jika kosong, tampilkan pesan bahwa belum ada jadwal yang dibuat.
 *      * Lakukan penelusuran (introspeksi/traversal) di dalam struktur Queue dari indeks terdepan ('depan') hingga terbelakang ('belakang').
 *      * Tampilkan pertandingan satu per satu secara berurutan (misal: "Pertandingan 1: Tim A vs Tim B", "Pertandingan 2: Tim C vs Tim D").
 *      * Informasikan pertandingan mana yang sedang berjalan saat ini (yaitu yang berada di posisi paling depan queue).
 */
