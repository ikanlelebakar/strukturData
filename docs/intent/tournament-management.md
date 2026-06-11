# Intent: Tournament Management CLI (C++)
> Confirmed: 2026-06-11 | Updated: 2026-06-11 (post-grill)

## Outcome
Program CLI C++ manajemen turnamen game dengan sistem **single elimination + perebutan juara ke-3**, di mana Admin mengontrol jalannya turnamen dan memasukkan pemenang setiap pertandingan secara manual.

## User
3 jenis aktor:
- **Admin** — full control (registrasi pertama kali, tutup pendaftaran, buat braket, tentukan pemenang)
- **Tim** — login pakai username (nama tim) + password; bisa lihat & edit tim sendiri, lihat jadwal & braket, lihat tim lawan
- **Penonton** — hanya lihat jadwal, braket, ranking (tanpa login)

## Why Now
Project/tugas yang harus diselesaikan, dengan struktur file sudah ada di `/src/`.

## Success
Program berjalan penuh dari registrasi admin → pendaftaran tim → admin tutup pendaftaran → braket terbentuk → pertandingan berjalan ronde per ronde → juara 1, 2, 3 ditentukan — semua via CLI, data in-memory.

## Constraint
- Jumlah tim harus **pangkat 2** (4, 8, 16, 32...)
- **Tidak ada file persistence** — data hilang saat program ditutup
- Setiap fitur = **file `.cpp` tersendiri**, tanpa file `.h`
- **Singly linked list** sebagai struktur data utama untuk daftar tim
- Setiap perubahan = commit ke branch saat ini

## Struktur Data: Struct Tim
```
struct Tim (node linked list) {
  string namaTim        // juga berfungsi sebagai username login
  string password       // untuk autentikasi login tim
  int jumlahPemain      // input dari tim saat registrasi, valid: 1–7
  int poin              // jumlah kemenangan, untuk sorting klasemen
  bool isEliminated     // status eliminasi
  Tim* next             // pointer ke node berikutnya (singly linked list)
}
```

## File `.cpp` yang Diperlukan
| File | Status | Keterangan |
|---|---|---|
| `models.cpp` | Ada (perlu diupdate) | Struct + linked list head node |
| `login_admin.cpp` | Ada | Login admin |
| `login_tim.cpp` | **Belum ada — perlu dibuat** | Login tim pakai nama tim + password |
| `registrasi_tim.cpp` | Ada | Input nama tim, password, jumlahPemain (1–7) |
| `edit_tim.cpp` | Ada | Edit data tim (hanya oleh tim yang login) |
| `hapus_tim.cpp` | Ada | Hapus tim (admin only) |
| `buat_jadwal.cpp` | Ada | Prasyarat: pendaftaran sudah ditutup admin |
| `input_hasil.cpp` | Ada | Input hasil + handle logika juara ke-3 |
| `lihat_bracket.cpp` | Ada | Tampilkan bracket |
| `lihat_jadwal.cpp` | Ada | Tampilkan jadwal antrian |
| `lihat_klasemen.cpp` | Ada | Tampilkan ranking berdasarkan poin |
| `lihat_tim.cpp` | Ada | Lihat daftar tim |
| `cari_lawan.cpp` | Ada | Cari detail tim lawan |
| `search_sort.cpp` | Ada | Utilitas sort linked list berdasarkan poin |

## Alur Fase Program
1. **Fase Registrasi** — Tim bisa daftar selama pendaftaran belum ditutup admin
2. **Tutup Pendaftaran** — Admin menutup; setelah ini registrasi baru ditolak
3. **Buat Braket** — Hanya bisa setelah pendaftaran ditutup; jumlah tim harus pangkat 2
4. **Fase Pertandingan** — Admin input hasil ronde per ronde
5. **Juara ke-3** — Auto-pair dua semifinalis yang kalah; kedua tim baru benar-benar di-eliminate setelah match ini selesai

## Aturan Jadwal
| Ronde | Jadwal |
|---|---|
| Ronde 1 | Admin input manual |
| Babak biasa berikutnya | +3 hari dari pertandingan terakhir ronde sebelumnya |
| Semi-final | +4 hari dari pertandingan terakhir ronde sebelumnya |
| **Perebutan Juara ke-3** | **Hari Final − 1** |
| Final | +5 hari dari pertandingan terakhir ronde sebelumnya |

Bracket: pemenang A vs pemenang B dipasangkan otomatis oleh sistem.

## Poin & Ranking
- Poin = jumlah kemenangan → dipakai untuk sorting
- Ranking 1 (juara final), 2 (runner-up final), 3 (pemenang perebutan ke-3)
- Semifinalis yang kalah **belum di-eliminate** sampai pertandingan juara ke-3 selesai

## Out of Scope
- File persistence (tidak ada simpan ke disk)
- Sistem "bye" untuk jumlah tim non-pangkat-2
- Visualisasi ASCII tree braket
- Header file (`.h`)
- Input nama per anggota tim (hanya input jumlah pemain: 1–7)
