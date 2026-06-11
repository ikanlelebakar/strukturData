/*
 * File: models.cpp
 * Deskripsi: File ini berisi definisi struktur data (struct) dan variabel global
 *            yang digunakan di seluruh sistem.
 *
 * Struktur data utama: Singly Linked List untuk daftar tim.
 *
 * Tugas Tim/Mahasiswa:
 * 1. Implementasikan struct 'Tim' (node linked list) yang berisi:
 *    - string namaTim;       // nama tim, juga sebagai username login
 *    - string password;      // untuk autentikasi login tim
 *    - int jumlahPemain;     // jumlah anggota tim, valid: 1-7
 *    - int poin;             // jumlah kemenangan, untuk sorting klasemen
 *    - bool isEliminated;    // status eliminasi tim
 *    - Tim* next;            // pointer ke node berikutnya (singly linked list)
 *
 * 2. Tentukan konstanta global:
 *    - const int MAX_TIM = 16;  // harus pangkat 2: 4, 8, 16, 32...
 *    - const int MIN_PEMAIN = 1;
 *    - const int MAX_PEMAIN = 7;
 *
 * 3. Buat variabel global:
 *    - Tim* headTim = nullptr;     // head dari linked list tim
 *    - int jumlahTimAktif = 0;     // counter jumlah tim yang terdaftar
 *    - bool pendaftaranDitutup = false; // flag fase: false = masih bisa daftar
 *    - bool bracketSudahDibuat = false; // flag fase: braket sudah terbentuk
 *
 * 4. Implementasikan struct 'AntrianTanding' (Queue berbasis Linked List) untuk jadwal pertandingan:
 *    - Setiap node antrian menyimpan:
 *      * Tim* timA;   // pointer ke tim pertama
 *      * Tim* timB;   // pointer ke tim kedua
 *      * string tanggalTanding; // format: "YYYY-MM-DD" atau string deskriptif
 *      * NodeAntrian* next;
 *    - Variabel global antrian:
 *      * NodeAntrian* frontAntrian = nullptr;
 *      * NodeAntrian* backAntrian = nullptr;
 *    - Fungsi queue yang dibutuhkan:
 *      * void pushAntrian(Tim* timA, Tim* timB, string tanggal) -> enqueue
 *      * void popAntrian()     -> dequeue pertandingan terdepan
 *      * bool isAntrianKosong() -> cek apakah antrian kosong
 *
 * 5. Variabel global khusus perebutan juara ke-3:
 *    - Tim* semifinalisKalah1 = nullptr;
 *    - Tim* semifinalisKalah2 = nullptr;
 *    // Kedua pointer ini diisi saat dua semifinalis kalah.
 *    // Mereka BELUM di-eliminate sampai match juara ke-3 selesai.
 */
