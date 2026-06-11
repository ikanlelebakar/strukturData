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

Akun Admin: `username=admin` | `password=turnamen2026`

---

# Alur Penggunaan Program

## 1. Menu Utama (Tanpa Login)
Saat program pertama kali dijalankan, langsung muncul **Menu Utama** dengan 3 pilihan:
```
1. Masuk Sebagai Admin
2. Masuk Sebagai Tim / Registrasi Tim
3. Lihat Sebagai Penonton
0. Keluar Program
```

## 2. Fase Registrasi Tim
- Pilih **2 → Registrasi Tim Baru**
- Input: nama tim (sekaligus username login), password, jumlah pemain (1–7)
- Pendaftaran terbuka selama Admin belum menutup dan kuota belum penuh (MAX: 8 tim)
- Duplikat nama tim otomatis ditolak

## 3. Admin Tutup Pendaftaran
- Pilih **1 (Admin)** → login → pilih **4. Tutup Pendaftaran**
- Sistem validasi: jumlah tim **harus pangkat 2** (4, 8, 16...)
- Setelah ditutup, registrasi baru tidak bisa dilakukan

## 4. Buat Braket Ronde 1
- Admin → pilih **5. Buat Jadwal Pertandingan**
- Admin input tanggal mulai Ronde 1 (format: `YYYY-MM-DD`)
- Sistem otomatis pasangkan tim (head vs tail) dan masukkan ke antrian (Queue)

## 5. Input Hasil Pertandingan (Ronde per Ronde)
- Admin → pilih **7. Input Hasil Pertandingan**
- Input skor Tim A dan Tim B (tidak boleh seri, tidak boleh negatif)
- Sistem otomatis tentukan pemenang (+1 poin) dan eliminasi yang kalah
- Ulangi sampai semua match di ronde selesai (antrian kosong)

## 6. Buat Jadwal Ronde Berikutnya
- Admin → pilih **6. Buat Jadwal Ronde Berikutnya**
- Tanggal otomatis dihitung:
  - Ronde biasa        : +3 hari dari match terakhir
  - Semifinal          : +4 hari dari match terakhir
  - Final              : +5 hari dari match terakhir
  - Perebutan Juara ke-3: Hari Final − 1 (otomatis di-enqueue setelah 2 semifinal selesai)

## 7. Logika Semifinal & Juara ke-3
- Setelah 2 match Semifinal selesai:
  - Dua semifinalis yang kalah **belum di-eliminate**
  - Sistem otomatis enqueue **Pertandingan Perebutan Juara ke-3**
- Setelah match ke-3 selesai, keduanya baru di-eliminate
- Final diproses setelah match ke-3 rampung

## 8. Turnamen Selesai
- Semua antrian kosong → lihat **Klasemen** untuk melihat Juara 1, 2, 3

---

# Hak Akses

## Admin
Login dengan `admin` / `turnamen2026`. Memiliki akses penuh:
- Lihat daftar tim
- Edit data tim (semua tim)
- Hapus tim (hanya sebelum braket dibuat)
- Tutup pendaftaran
- Buat jadwal pertandingan (Ronde 1)
- Buat jadwal ronde berikutnya
- Input hasil pertandingan
- Lihat klasemen
- Lihat bracket/bagan

## Tim
Login menggunakan nama tim (username) + password. Memiliki akses:
- Registrasi tim baru
- Edit data tim sendiri (hanya jika belum tereliminasi)
- Lihat jadwal pertandingan
- Cari profil tim lawan
- Lihat klasemen
- Lihat bracket

## Penonton
Tanpa login. Hanya bisa melihat:
- Jadwal pertandingan
- Bracket/bagan turnamen
- Klasemen

---

# Struktur File

| File | Fungsi |
|------|--------|
| `main.cpp` | Driver utama — menu Admin/Tim/Penonton |
| `models.cpp` | Struct `Tim`, `NodeAntrian`, variabel global, queue |
| `utils.cpp` | `clearScreen()` lintas platform (Windows/Linux/macOS) |
| `search_sort.cpp` | `cariTim()` linear search, `urutkanKlasemen()` bubble sort |
| `login_admin.cpp` | `loginAdmin()` |
| `login_tim.cpp` | `loginTim()` → return `Tim*` |
| `registrasi_tim.cpp` | `registrasiTimBaru()` |
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
6. Jumlah tim harus selalu pangkat 2 (4, 8, 16, 32...)