/*
 * File: models.cpp
 * Deskripsi: File ini berisi definisi struktur data (struct) dan variabel global yang digunakan di seluruh sistem.
 * 
 * Tugas Tim/Mahasiswa:
 * 1. Implementasikan struct 'Pemain' yang berisi:
 *    - string namaPemain;
 * 
 * 2. Implementasikan struct 'Tim' yang berisi:
 *    - string namaTim;
 *    - Pemain anggota[5]; // Array of Struct untuk menampung 5 anggota tim
 *    - int poin;          // Poin klasemen tim
 *    - bool isEliminated; // Status apakah tim sudah tereliminasi atau tidak
 * 
 * 3. Tentukan konstanta global:
 *    - const int MAX_TIM = 16;
 * 
 * 4. Buat variabel global untuk data tim:
 *    - Tim daftarTim[MAX_TIM];
 *    - int jumlahTimAktif = 0;
 * 
 * 5. Implementasikan struct 'AntrianTanding' (Queue berbasis Array/Linked List) untuk jadwal pertandingan:
 *    - int depan;
 *    - int belakang;
 *    - (tambahkan variabel array atau pointer node pendukung queue)
 *    - Fungsi queue yang dibutuhkan:
 *      * void push(int indexTimA, int indexTimB) -> Memasukkan pertandingan baru ke antrian
 *      * void pop() -> Mengeluarkan pertandingan terdepan yang sudah selesai
 *      * bool isEmpty() -> Mengecek apakah antrian kosong
 *      * bool isFull() -> Mengecek apakah antrian penuh
 */
