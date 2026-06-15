// =============================================================================
// File   : registrasi_admin.cpp
// Tujuan : Fungsi yang dijalankan PERTAMA KALI saat program dimulai.
//          Admin mendaftarkan akun, nama turnamen, dan kapasitas maksimum tim.
//
// Variabel global yang DIPAKAI dari models.cpp:
//   - string adminUsername    (simpan username admin di sini)
//   - string adminPassword    (simpan password admin di sini)
//   - string namaTurnamen     (simpan nama turnamen di sini)
//   - int    MAX_TIM          (simpan kapasitas maks tim, harus pangkat 2)
//   - bool   adminSudahDibuat (set jadi true setelah registrasi berhasil)
//   - adalahPangkatDua()      (fungsi dari models.cpp untuk validasi)
//
// Fungsi yang harus kamu buat di file ini:
//   1. daftarAdmin()
// =============================================================================


// -----------------------------------------------------------------------------
// Fungsi: daftarAdmin()
// Tujuan: Meminta admin mengisi username, password, nama turnamen, dan kapasitas
//         tim (MAX_TIM). Dipanggil sekali saat program pertama kali dijalankan.
//
// Variabel yang dibutuhkan: tidak ada variabel lokal tambahan
// (semua disimpan langsung ke variabel global)
//
// Hint algoritma:
//   1. Cetak banner "REGISTRASI ADMINISTRATOR TURNAMEN"
//   2. Minta input: cin >> adminUsername
//   3. Minta input: cin >> adminPassword, lalu cin.ignore()
//   4. Minta input nama turnamen: getline(cin, namaTurnamen)
//   5. Loop DO-WHILE untuk input MAX_TIM yang valid:
//      a. Tampilkan prompt "Maksimal Tim (harus pangkat 2, min 2): "
//      b. cin >> MAX_TIM, lalu cin.ignore()
//      c. Kondisi loop: ULANGI jika !adalahPangkatDua(MAX_TIM) || MAX_TIM < 2
//      d. Jika tidak valid, cetak pesan error
//   6. Set adminSudahDibuat = true
//   7. Tampilkan ringkasan: nama turnamen dan MAX_TIM
//   8. Cetak "Tekan ENTER untuk lanjut..." lalu cin.get()
