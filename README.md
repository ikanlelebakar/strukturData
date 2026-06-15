# 🏆 Proyek: Sistem Manajemen & Penjadwalan Turnamen

Proyek ini adalah aplikasi berbasis *Command Line Interface* (CLI) C++ untuk mengelola jalannya turnamen kompetitif menggunakan sistem eliminasi (sistem gugur) tunggal (*single elimination*) ditambah dengan babak perebutan juara ke-3.

Proyek ini dibagi menjadi berkas-berkas `*.cpp` terpisah tanpa file header (`*.h`) untuk mempermudah pengerjaan tim. Keterhubungan antar-berkas diatur melalui `#include` di dalam berkas [main.cpp](file:///home/fais/Documents/strukturData/src/main.cpp).

---

## 📂 Struktur Berkas Proyek

Semua berkas modul modular terorganisir di dalam folder `src/`:

1. **[src/main.cpp](file:///home/fais/Documents/strukturData/src/main.cpp)**: Driver utama program CLI, memuat menu utama untuk Admin, Tim, dan Penonton, serta menyatukan seluruh berkas modul.
2. **[src/umum/models.cpp](file:///home/fais/Documents/strukturData/src/umum/models.cpp)**: Definisi struktur data (struct), antrian pertandingan (Queue berbasis Linked List), variabel global, dan fungsi pembantu (seperti cek pangkat dua).
3. **[src/umum/search_sort.cpp](file:///home/fais/Documents/strukturData/src/umum/search_sort.cpp)**: Implementasi pencarian tim menggunakan *Linear Search* dan pengurutan klasemen menggunakan *Bubble Sort*.
4. **[src/hapus_terminal/utils.cpp](file:///home/fais/Documents/strukturData/src/hapus_terminal/utils.cpp)**: Fungsi utilitas untuk membersihkan layar terminal (`clearScreen()`) secara lintas platform (Windows/Linux/macOS).

### 🛡️ Fitur Menu Admin (Admin Access)
5. **[src/admin/registrasi_admin.cpp](file:///home/fais/Documents/strukturData/src/admin/registrasi_admin.cpp)**: Pendaftaran akun administrator dinamis pertama kali beserta konfigurasi maksimal tim (`MAX_TIM`).
6. **[src/admin/login_admin.cpp](file:///home/fais/Documents/strukturData/src/admin/login_admin.cpp)**: Autentikasi untuk masuk sebagai Admin.
7. **[src/admin/hapus_tim.cpp](file:///home/fais/Documents/strukturData/src/admin/hapus_tim.cpp)**: Menghapus pendaftaran tim sebelum jadwal/braket dibuat.
8. **[src/admin/buat_jadwal.cpp](file:///home/fais/Documents/strukturData/src/admin/buat_jadwal.cpp)**: Logika pengacakan braket awal turnamen (Ronde 1) dengan mempertemukan tim secara *head-vs-tail*.
9. **[src/admin/input_hasil.cpp](file:///home/fais/Documents/strukturData/src/admin/input_hasil.cpp)**: Memasukkan skor pertandingan saat ini, mengeliminasi tim yang kalah, memberikan poin kemenangan (+1), dan menjadwalkan ronde berikutnya (termasuk final dan juara 3).

### 👥 Fitur Menu Tim / Pemain (Restricted Access)
10. **[src/tim/registrasi_tim.cpp](file:///home/fais/Documents/strukturData/src/tim/registrasi_tim.cpp)**: Mendaftarkan tim baru dengan nama, password, dan jumlah pemain (1-7).
11. **[src/tim/login_tim.cpp](file:///home/fais/Documents/strukturData/src/tim/login_tim.cpp)**: Autentikasi bagi tim terdaftar untuk masuk ke Menu Tim.
12. **[src/tim/edit_tim.cpp](file:///home/fais/Documents/strukturData/src/tim/edit_tim.cpp)**: Mengubah nama/password/jumlah pemain dari tim sendiri (selama belum tereliminasi).
13. **[src/tim/lihat_tim.cpp](file:///home/fais/Documents/strukturData/src/tim/lihat_tim.cpp)**: Menampilkan seluruh tim terdaftar beserta info dasarnya.
14. **[src/tim/cari_lawan.cpp](file:///home/fais/Documents/strukturData/src/tim/cari_lawan.cpp)**: Mencari dan melihat detail profil tim lawan.

### 👁️ Fitur Umum & Penonton (Public Access)
15. **[src/umum/lihat_jadwal.cpp](file:///home/fais/Documents/strukturData/src/umum/lihat_jadwal.cpp)**: Menampilkan antrian jadwal tanding saat ini.
16. **[src/umum/lihat_bracket.cpp](file:///home/fais/Documents/strukturData/src/umum/lihat_bracket.cpp)**: Menampilkan visualisasi bagan eliminasi turnamen (Bracket).
17. **[src/umum/lihat_klasemen.cpp](file:///home/fais/Documents/strukturData/src/umum/lihat_klasemen.cpp)**: Menampilkan klasemen tim terurut berdasarkan jumlah kemenangan (poin).

---

## 📝 Detail Spesifikasi Struktur Data & Logika

### 1. `models.cpp`
*   **Struct `Tim` (Node Singly Linked List)**:
    ```cpp
    struct Tim {
        string nama;
        string password;
        int jumlahPemain; // Nilai valid: 1–7
        int poin;         // Poin bertambah +1 per kemenangan
        bool tereleminasi;
        Tim *berikutnya;
    };
    ```
*   **Struct `NodeAntrian` (Node Queue Pertandingan)**:
    ```cpp
    struct NodeAntrian {
        Tim *timA;
        Tim *timB;
        string tanggalTanding;
        string ronde;
        NodeAntrian *berikutnya;
    };
    ```
*   **Fungsi Queue**:
    *   `void tambahAntrian(Tim *timA, Tim *timB, string tanggal, string ronde)` (Enqueue)
    *   `void hapusAntrian()` (Dequeue)
    *   `bool antrianKosong()` (Pengecekan kekosongan antrian)

### 2. Aturan Bisnis Turnamen
*   **Kapasitas Maksimal Tim (`MAX_TIM`)**: Di-set dinamis oleh Admin pertama kali berjalan, dan nilainya harus merupakan pangkat 2 (misal: 2, 4, 8, 16, 32...).
*   **Batas Pemain**: Jumlah pemain minimal 1 dan maksimal 7 orang.
*   **Aturan Penjadwalan Tanggal**:
    *   Ronde 1: Input tanggal manual pertama kali oleh Admin (`YYYY-MM-DD`).
    *   Ronde Biasa Selanjutnya: +3 hari dari pertandingan terakhir ronde sebelumnya.
    *   Semifinal: +4 hari dari pertandingan terakhir.
    *   Perebutan Juara ke-3: Hari Final - 1 hari (dijadwalkan otomatis setelah semifinal berakhir).
    *   Final: +5 hari dari pertandingan terakhir.
*   **Skor & Poin**:
    *   Skor maksimal per tim dalam pertandingan adalah 3 (skor valid: 0-3).
    *   Tidak boleh ada skor negatif atau seri (karena sistem gugur).
    *   Tim pemenang mendapatkan +1 poin ke dalam klasemen.

---

## 🛠️ Cara Kompilasi dan Menjalankan Program

Karena proyek ini menggunakan pendekatan Single-File Architecture yang digabungkan lewat `#include` berkas `.cpp` di `main.cpp`, Anda cukup melakukan kompilasi pada **[src/main.cpp](file:///home/fais/Documents/strukturData/src/main.cpp)** saja.

### Menggunakan g++ (GCC) di Terminal Linux/Windows:

```bash
g++ src/main.cpp -o sistem_turnamen
./sistem_turnamen
```
