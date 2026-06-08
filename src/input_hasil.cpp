/*
 * File: input_hasil.cpp
 * Deskripsi: File ini berisi fungsi untuk menginputkan hasil skor pertandingan terdepan di antrian, memperbarui poin, mengeliminasi tim yang kalah, dan mengeluarkan pertandingan tersebut dari antrian (pop).
 * 
 * Tugas Tim/Mahasiswa:
 * 1. Implementasikan fungsi input hasil pertandingan:
 *    - Nama Fungsi: inputSkorPertandingan
 *    - Parameter: tidak ada
 *    - Return: void
 *    - Kebutuhan Teknis:
 *      * Cek terlebih dahulu apakah antrian tanding kosong menggunakan 'isEmpty()'. Jika kosong, tampilkan pesan bahwa tidak ada jadwal aktif.
 *      * Ambil pertandingan paling depan dari antrian (FIFO).
 *      * Minta input skor untuk Tim A dan Tim B.
 *      * Bandingkan skor untuk menentukan pemenang dan pecundang:
 *        - Tim yang menang mendapat tambahan poin (misal +3 poin).
 *        - Tim yang kalah statusnya diubah menjadi tereliminasi (isEliminated = true).
 *      * Keluarkan pertandingan dari antrian menggunakan fungsi 'pop()'.
 *      * Tampilkan pesan konfirmasi pemenang dan tim yang tereliminasi.
 */
