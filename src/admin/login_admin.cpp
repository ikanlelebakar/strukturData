// =============================================================================
// File   : login_admin.cpp
// Tujuan : Fungsi autentikasi untuk admin. Membandingkan input username dan
//          password dengan data yang tersimpan di variabel global.
//
// Variabel global yang DIPAKAI dari models.cpp:
//   - string adminUsername  (username yang didaftarkan saat registrasi)
//   - string adminPassword  (password yang didaftarkan saat registrasi)
//
// Fungsi yang harus kamu buat di file ini:
  1. masukAdmin() -> bool
// =============================================================================


// -----------------------------------------------------------------------------
// Fungsi: masukAdmin() -> bool
// Tujuan: Meminta input username dan password, lalu membandingkannya dengan
//         data admin yang tersimpan. Mengembalikan true jika berhasil login,
//         false jika username atau password salah.
//
// Variabel yang dibutuhkan:
//   string username   // Input username dari pengguna
//   string password   // Input password dari pengguna
//
// Hint algoritma:
//   1. Cetak header "=== LOGIN ADMIN ==="
//   2. Minta input: cout << "Username: "; cin >> username
//   3. Minta input: cout << "Password: "; cin >> password
//   4. Cek kondisi: if (username == adminUsername && password == adminPassword)
//      - Jika cocok: cetak pesan sukses, return true
//      - Jika tidak: cetak "Username atau password salah.", return false
