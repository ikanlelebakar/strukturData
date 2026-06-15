# Program Manajemen Turnamen Game (CLI C++)

Program CLI C++ untuk manajemen turnamen game dengan sistem **single elimination (sistem gugur) + perebutan juara ke-3**.
Source code berada di [src/](/src/). Struktur data utama menggunakan **Singly Linked List** untuk tim dan Queue berbasis Linked List untuk antrian pertandingan.

---

# Struktur Data yang Digunakan

- **Singly Linked List (`Tim`)** — Menyimpan data tim secara dinamis.
- **Queue berbasis Linked List (`NodeAntrian`)** — Mengelola antrian jadwal pertandingan secara First-In-First-Out (FIFO).
- **Bubble Sort** — Mengurutkan klasemen secara *descending* berdasarkan poin (kemenangan) tim.
- **Linear Search** — Mencari keberadaan tim berdasarkan nama di dalam Linked List.

---

# Cara Kompilasi & Jalankan

```bash
g++ src/main.cpp -o sistem_turnamen
./sistem_turnamen
```

---

# Alur Penggunaan Program

## 1. Pertama Kali Dijalankan (Registrasi Admin)
Saat program pertama kali dibuka, pengguna diharuskan mendaftarkan akun Administrator baru. Admin memasukkan:
- Username Admin
- Password Admin
- Nama Turnamen
- Kapasitas Maksimal Tim (`MAX_TIM`): Harus angka pangkat 2 (min 2, contoh: 2, 4, 8, 16, 32...)

## 2. Menu Utama Dinamis (Berdasarkan Status Registrasi)

Setelah registrasi admin selesai, program akan menampilkan Menu Utama. Opsi menu ini berubah secara otomatis berdasarkan kondisi pendaftaran:

### Fase A: Pendaftaran Terbuka (Tim < MAX_TIM & belum ditutup oleh Admin)
```
1. Registrasi Tim
2. Login Tim
3. Login Admin
4. Keluar Program (0)
```
- **1. Registrasi Tim**: Memasukkan nama tim (username login), password, dan jumlah pemain (1-7).
- **2. Login Tim**: Masuk ke menu tim menggunakan kredensial tim.
- **3. Login Admin**: Masuk ke menu admin menggunakan kredensial admin.

### Fase B: Pendaftaran Ditutup / Penuh (Tim >= MAX_TIM atau ditutup secara manual oleh Admin)
```
1. Login Tim
2. Penonton
3. Login Admin
4. Keluar Program (0)
```
- Opsi registrasi tim menghilang dan diganti dengan opsi **2. Penonton** untuk melihat jadwal, braket, dan klasemen tanpa login.

## 3. Admin Menutup Pendaftaran & Membuat Jadwal
- Admin login -> pilih **4. Tutup Pendaftaran** (opsional jika kuota belum penuh).
- Admin -> pilih **2. Buat Jadwal Pertandingan**.
- Admin memasukkan tanggal mulai Ronde 1 (`YYYY-MM-DD`). Sistem otomatis memasangkan tim secara *head-vs-tail* (Tim 1 vs Tim N, dst.) dan memasukkannya ke antrian pertandingan (Queue).

## 4. Input Hasil Pertandingan (Ronde per Ronde)
- Admin -> pilih **2. Input Hasil Pertandingan** (saat turnamen berjalan).
- Admin memilih tim pemenang pada pertandingan terdepan di antrian. Sistem otomatis menandai tim kalah sebagai tereliminasi dan memberikan +1 poin kemenangan kepada pemenang.
- Skor pertandingan valid berkisar antara 0 hingga 3. Skor tidak boleh negatif, seri, atau lebih dari 3.
- Pertandingan dikeluarkan dari antrian (dequeue).

## 5. Buat Jadwal Ronde Berikutnya
- Setelah semua pertandingan pada satu ronde selesai (antrian kosong), Admin membuat jadwal ronde berikutnya via menu admin:
  - Ronde biasa: +3 hari dari pertandingan terakhir.
  - Semifinal: +4 hari dari pertandingan terakhir.
  - Final: +5 hari dari pertandingan terakhir.
  - Perebutan Juara ke-3: Hari Final - 1 (otomatis masuk antrian setelah semifinal selesai).

## 6. Logika Juara ke-3 & Final
- Setelah semifinal selesai, pertandingan perebutan juara ke-3 dimainkan terlebih dahulu sebelum Final.
- Pemenang perebutan juara ke-3 menduduki peringkat ke-3.
- Pemenang Final menjadi Juara 1, dan yang kalah menjadi Juara 2.

---

# Hak Akses Pengguna

## Admin
Login dengan akun admin yang dibuat pada awal program berjalan. Hak akses meliputi:
- Lihat daftar tim
- Edit data tim (semua tim)
- Hapus tim (sebelum braket dibuat)
- Tutup pendaftaran secara manual
- Buat jadwal pertandingan (Ronde 1)
- Buat jadwal ronde berikutnya
- Input hasil pertandingan
- Lihat klasemen
- Lihat bracket/bagan

## Tim
Login menggunakan nama tim (username) + password. Hak akses meliputi:
- Edit data tim sendiri (selama belum tereliminasi)
- Lihat jadwal pertandingan
- Cari profil tim lawan
- Lihat klasemen
- Lihat bracket

## Penonton
Tanpa login. Muncul setelah pendaftaran ditutup/penuh. Hak akses meliputi:
- Lihat jadwal pertandingan
- Lihat bracket/bagan turnamen
- Lihat klasemen

---

# Struktur File Modul

| File | Fungsi |
|------|--------|
| `src/main.cpp` | Driver utama — menu Admin/Tim/Penonton |
| `src/umum/models.cpp` | Struct `Tim`, `NodeAntrian`, variabel global, queue, helper `adalahPangkatDua` |
| `src/hapus_terminal/utils.cpp` | `clearScreen()` lintas platform (Windows/Linux/macOS) |
| `src/umum/search_sort.cpp` | `cariTim()` linear search, `urutkanKlasemen()` bubble sort |
| `src/admin/registrasi_admin.cpp` | `daftarAdmin()` — Pendaftaran akun admin dan setelan turnamen pertama kali |
| `src/admin/login_admin.cpp` | `loginAdmin()` / `masukAdmin()` — Autentikasi administrator dinamis |
| `src/tim/login_tim.cpp` | `masukTim()` → return `Tim*` |
| `src/tim/registrasi_tim.cpp` | `daftarTim()` — Pendaftaran tim |
| `src/tim/lihat_tim.cpp` | `tampilkanTim()` |
| `src/tim/edit_tim.cpp` | `editDataTim()`, `menuEditTim()`, `editTim()` |
| `src/admin/hapus_tim.cpp` | `hapusTim()` |
| `src/admin/buat_jadwal.cpp` | `buatJadwal()`, `tambahHari()` |
| `src/admin/input_hasil.cpp` | `inputHasil()`, `buatJadwalBerikutnya()` |
| `src/umum/lihat_jadwal.cpp` | `tampilJadwal()` |
| `src/umum/lihat_bracket.cpp` | `tampilBracket()` |
| `src/umum/lihat_klasemen.cpp` | `tampilKlasemen()` |
| `src/tim/cari_lawan.cpp` | `cariTim()` |

---
