# Program Manajemen Turnamen Game (CLI C++)

Program CLI C++ untuk manajemen turnamen game dengan sistem **single elimination + perebutan juara ke-3**.
Source code ada di [src/](/src/). Struktur data utama menggunakan **Singly Linked List**.
Referensi teknis lengkap ada di [README](README.md) dan [docs/intent/tournament-management.md](docs/intent/tournament-management.md).

---

# Yang Digunakan

- **Singly Linked List** — menyimpan data tim (`struct Tim`) dan antrian pertandingan (`NodeAntrian`)
- **Queue berbasis Linked List** — antrian jadwal pertandingan (FIFO)
- **Bubble Sort** — mengurutkan klasemen berdasarkan poin secara descending

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
0. Keluar Program
```
- **1. Registrasi Tim**: Memasukkan nama tim (username login), password, dan jumlah pemain (1-7).
- **2. Login Tim**: Masuk ke menu tim menggunakan kredensial tim.
- **3. Login Admin**: Masuk ke menu admin menggunakan kredensial admin dinamis.

### Fase B: Pendaftaran Ditutup / Penuh (Tim >= MAX_TIM atau ditutup secara manual oleh Admin)
```
1. Login Tim
2. Penonton
3. Login Admin
0. Keluar Program
```
- Opsi registrasi tim menghilang dan diganti dengan opsi **2. Penonton** untuk melihat jadwal, braket, dan klasemen tanpa login.

## 3. Admin Menutup Pendaftaran & Membuat Jadwal
- Admin login -> pilih **4. Tutup Pendaftaran** (opsional jika kuota belum penuh).
- Admin -> pilih **5. Buat Jadwal Pertandingan**.
- Admin memasukkan tanggal mulai Ronde 1 (`YYYY-MM-DD`). Sistem otomatis memasangkan tim secara *head-vs-tail* (Tim 1 vs Tim N, dst.) dan memasukkannya ke antrian pertandingan (Queue).

## 4. Input Hasil Pertandingan (Ronde per Ronde)
- Admin -> pilih **7. Input Hasil Pertandingan**.
- Admin memilih tim pemenang pada pertandingan terdepan di antrian. Sistem otomatis menandai tim kalah sebagai tereliminasi dan memberikan +1 poin kemenangan kepada pemenang.
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

# Hak Akses

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

# Struktur File

| File | Fungsi |
|------|--------|
| `main.cpp` | Driver utama — menu Admin/Tim/Penonton |
| `models.cpp` | Struct `Tim`, `NodeAntrian`, variabel global, queue, helper `isPowerOfTwo` |
| `utils.cpp` | `clearScreen()` lintas platform (Windows/Linux/macOS) |
| `search_sort.cpp` | `cariTim()` linear search, `urutkanKlasemen()` bubble sort |
| `registrasi_admin.cpp` | `registrasiAdmin()` — Pendaftaran akun admin dan setelan turnamen pertama kali |
| `login_admin.cpp` | `loginAdmin()` — Autentikasi administrator dinamis |
| `login_tim.cpp` | `loginTim()` → return `Tim*` |
| `registrasi_tim.cpp` | `registrasiTimBaru()` — Pendaftaran tim |
| `lihat_tim.cpp` | `lihatDaftarTim()` |
| `edit_tim.cpp` | `editDataTim()`, `menuEditTim()`, `editTimSendiri()` |
| `hapus_tim.cpp` | `hapusTim()` |
| `buat_jadwal.cpp` | `buatJadwalPertandingan()`, `tambahHari()` |
| `input_hasil.cpp` | `inputSkorPertandingan()`, `buatJadwalBerikutnya()` |
| `lihat_jadwal.cpp` | `lihatJadwalAntrian()` |
| `lihat_bracket.cpp` | `lihatBracketTree()` |
| `lihat_klasemen.cpp` | `lihatKlasemen()` |
| `cari_lawan.cpp` | `cariLawan()` |

---

# Catatan Teknis

1. Setiap fitur baru harus berbeda file `*.cpp`
2. Tidak boleh ada file `*.h` — semua via `#include *.cpp` di `main.cpp`
3. Setiap perubahan harus melakukan commit ke branch saat ini
4. Setelah semua program dan test selesai harus mengupdate `/graphify`
5. Data tidak persisten — semua hilang saat program ditutup (no file I/O)
6. Kapasitas maksimum tim (`MAX_TIM`) di-set secara dinamis oleh admin dan harus merupakan pangkat 2.