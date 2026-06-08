# 🏆 Proyek: Sistem Manajemen & Penjadwalan Turnamen

Proyek ini adalah aplikasi berbasis *Command Line Interface* (CLI) C++ untuk mengelola jalannya turnamen kompetitif menggunakan sistem eliminasi (sistem gugur). Proyek ini dibagi menjadi berkas-berkas `*.cpp` terpisah tanpa file header (`*.h`) untuk mempermudah pengerjaan tim. Keterhubungan antar-berkas diatur melalui `#include` di dalam berkas [main.cpp](file:///home/fais/Documents/strukturData/src/main.cpp).

---

## 📂 Struktur Berkas Proyek

Semua berkas berada di dalam satu folder dan harus dikerjakan sesuai spesifikasinya:

1. **[models.cpp](file:///home/fais/Documents/strukturData/src/models.cpp)**: Definisi struktur data (struct) dan variabel global.
2. **[search_sort.cpp](file:///home/fais/Documents/strukturData/src/search_sort.cpp)**: Fungsi pencarian tim dan pengurutan klasemen.
3. **[main.cpp](file:///home/fais/Documents/strukturData/src/main.cpp)**: Menu utama program CLI dan penggabung seluruh file.

### 🛡️ Fitur Menu Admin (Admin Access)
4. **[login_admin.cpp](file:///home/fais/Documents/strukturData/src/login_admin.cpp)**: Logika login akses Admin.
5. **[lihat_tim.cpp](file:///home/fais/Documents/strukturData/src/lihat_tim.cpp)**: Menampilkan seluruh tim terdaftar dan anggotanya.
6. **[edit_tim.cpp](file:///home/fais/Documents/strukturData/src/edit_tim.cpp)**: Mengubah nama tim/anggota menggunakan pointer.
7. **[hapus_tim.cpp](file:///home/fais/Documents/strukturData/src/hapus_tim.cpp)**: Menghapus tim dari array (shifting index).
8. **[buat_jadwal.cpp](file:///home/fais/Documents/strukturData/src/buat_jadwal.cpp)**: Mengacak bagan tanding dan memasukkannya ke Queue.
9. **[input_hasil.cpp](file:///home/fais/Documents/strukturData/src/input_hasil.cpp)**: Memasukkan skor, update klasemen (poin), eliminasi tim, dan dequeue (pop).
10. **[lihat_klasemen.cpp](file:///home/fais/Documents/strukturData/src/lihat_klasemen.cpp)**: Menampilkan tabel papan peringkat klasemen.
11. **[lihat_bracket.cpp](file:///home/fais/Documents/strukturData/src/lihat_bracket.cpp)**: Menampilkan visualisasi bagan eliminasi turnamen.

### 👥 Fitur Menu Tim / Pemain (Restricted Access)
12. **[registrasi_tim.cpp](file:///home/fais/Documents/strukturData/src/registrasi_tim.cpp)**: Mendaftarkan nama tim baru beserta 5 anggota.
13. **[lihat_jadwal.cpp](file:///home/fais/Documents/strukturData/src/lihat_jadwal.cpp)**: Melihat antrian jadwal tanding.
14. **[cari_lawan.cpp](file:///home/fais/Documents/strukturData/src/cari_lawan.cpp)**: Mencari profil/anggota tim lain dengan algoritma pencarian.

---

## 📝 Detail Spesifikasi Fitur yang Harus Ditambahkan

Berikut adalah daftar fungsi dan kebutuhan logika yang perlu diisi di dalam masing-masing file `*.cpp`:

### 1. `models.cpp`
*   **Struct `Pemain`**:
    *   `string namaPemain;`
*   **Struct `Tim`**:
    *   `string namaTim;`
    *   `Pemain anggota[5];`
    *   `int poin;`
    *   `bool isEliminated;`
*   **Variabel Global**:
    *   `const int MAX_TIM = 16;`
    *   `Tim daftarTim[MAX_TIM];`
    *   `int jumlahTimAktif = 0;`
*   **Struct `AntrianTanding` (Queue berbasis Array/Linked List)**:
    *   Implementasikan variabel pendukung antrian (`depan`, `belakang`).
    *   Fungsi-fungsi Queue:
        *   `void push(int indexTimA, int indexTimB)`: Memasukkan pasangan tanding ke antrian.
        *   `void pop()`: Mengeluarkan pertandingan terdepan jika sudah selesai.
        *   `bool isEmpty()`: Mengecek apakah antrian kosong.
        *   `bool isFull()`: Mengecek apakah antrian penuh.

### 2. `search_sort.cpp`
*   **Fungsi `int cariIndeksTim(string nama)`**:
    *   Melakukan pencarian linier (*Linear Search*) pada `daftarTim` dari indeks 0 s.d. `jumlahTimAktif - 1`.
    *   Mengembalikan indeks tim jika nama tim cocok, atau `-1` jika tidak ditemukan.
*   **Fungsi `void urutkanKlasemen()`**:
    *   Mengurutkan `daftarTim` menggunakan algoritma *Bubble Sort* atau *Selection Sort* secara *descending* (menurun) berdasarkan nilai `poin`.

### 3. `login_admin.cpp`
*   **Fungsi `bool loginAdmin()`**:
    *   Meminta input username dan password.
    *   Mencocokkan dengan data statis (contoh: admin / 123).
    *   Mengembalikan `true` jika cocok, `false` jika salah.

### 4. `lihat_tim.cpp`
*   **Fungsi `void lihatDaftarTim()`**:
    *   Melakukan iterasi dan menampilkan nama tim, poin, status eliminasi, beserta nama ke-5 anggotanya.

### 5. `edit_tim.cpp`
*   **Fungsi `void editDataTim(Tim* ptrTim)`**:
    *   Menerima pointer ke objek `Tim`.
    *   Mengubah data `namaTim` atau data `anggota` secara langsung pada memori asli menggunakan operator panah (`->`).
*   **Fungsi `void menuEditTim()`**:
    *   Mencari tim dengan `cariIndeksTim()`, jika ketemu panggil `editDataTim(&daftarTim[indeks])`.

### 6. `hapus_tim.cpp`
*   **Fungsi `void hapusTim()`**:
    *   Mencari tim dengan `cariIndeksTim()`.
    *   Jika ketemu, geser (*shift*) semua elemen array di sebelah kanan indeks tersebut ke kiri.
    *   Kurangi `jumlahTimAktif` dengan 1.

### 7. `buat_jadwal.cpp`
*   **Fungsi `void buatJadwalPertandingan()`**:
    *   Memasangkan tim-tim aktif yang belum tereliminasi untuk bertanding.
    *   Memasukkan indeks pasangan tanding tersebut ke dalam queue `antrian` menggunakan `push()`.

### 8. `input_hasil.cpp`
*   **Fungsi `void inputSkorPertandingan()`**:
    *   Mengambil pasangan pertandingan terdepan di queue.
    *   Meminta input skor masing-masing tim.
    *   Menambahkan poin (misal +3) pada tim yang menang.
    *   Mengubah status `isEliminated` menjadi `true` pada tim yang kalah.
    *   Mengeluarkan pertandingan dari antrian menggunakan `pop()`.

### 9. `lihat_klasemen.cpp`
*   **Fungsi `void lihatKlasemen()`**:
    *   Memanggil `urutkanKlasemen()` agar data terurut.
    *   Menampilkan daftar tim terurut beserta poinnya dalam format tabel CLI.

### 10. `lihat_bracket.cpp`
*   **Fungsi `void lihatBracketTree()`**:
    *   Menggambar bagan turnamen sistem gugur secara visual menggunakan karakter teks CLI (seperti `|`, `\`, `---`).

### 11. `registrasi_tim.cpp`
*   **Fungsi `void registrasiTimBaru()`**:
    *   Meminta input nama tim baru dan nama 5 anggotanya.
    *   Memasukkan data ke `daftarTim[jumlahTimAktif]` dan menginkremen `jumlahTimAktif`.

### 12. `lihat_jadwal.cpp`
*   **Fungsi `void lihatJadwalAntrian()`**:
    *   Melakukan traversal queue dari indeks `depan` sampai `belakang` untuk menampilkan daftar antrian tanding.

### 13. `cari_lawan.cpp`
*   **Fungsi `void cariLawan()`**:
    *   Meminta input nama tim lawan.
    *   Mencari menggunakan `cariIndeksTim()`.
    *   Menampilkan profil lengkap tim jika ditemukan.

### 14. `main.cpp`
*   Berisi fungsi `main()`.
*   Menjalankan menu loop utama program:
    *   Akses Admin (memvalidasi dengan `loginAdmin()`, jika berhasil menampilkan sub-menu admin 1-8).
    *   Akses Tim (menampilkan sub-menu tim 1-5).
    *   Keluar program.

---

## 🛠️ Cara Kompilasi dan Menjalankan Program

Karena proyek ini menggunakan pendekatan Single-File Architecture yang digabungkan lewat `#include` berkas `.cpp` di `main.cpp`, Anda **tidak perlu** melakukan kompilasi terhadap semua berkas secara manual. Anda cukup melakukan kompilasi pada **[main.cpp](file:///home/fais/Documents/strukturData/src/main.cpp)** saja.

### Menggunakan g++ (GCC) di Terminal Linux/Windows:

```bash
g++ src/main.cpp -o sistem_turnamen
./sistem_turnamen atau sistem_turnamen.exe
```
