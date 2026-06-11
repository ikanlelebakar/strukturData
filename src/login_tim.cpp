/*
 * File: login_tim.cpp
 * Deskripsi: File ini berisi fungsi untuk autentikasi login tim.
 *            Tim login menggunakan nama tim (sebagai username) dan password.
 *
 * Tugas Tim/Mahasiswa:
 * 1. Implementasikan fungsi login tim:
 *    - Nama Fungsi: loginTim
 *    - Parameter: tidak ada
 *    - Return: Tim* -> pointer ke node Tim yang berhasil login, atau nullptr jika gagal
 *    - Kebutuhan Teknis:
 *      * Minta input username (nama tim) dan password dari pengguna.
 *      * Traverse linked list (mulai dari headTim) untuk mencari tim dengan namaTim yang cocok.
 *      * Jika ditemukan, bandingkan password yang diinput dengan password yang tersimpan.
 *      * Jika cocok, return pointer ke node Tim tersebut (login sukses).
 *      * Jika nama tim tidak ditemukan atau password salah, tampilkan pesan error dan return nullptr.
 *      * Catatan: Tim yang sudah tereliminasi (isEliminated = true) tetap bisa login
 *        untuk melihat data, namun tidak bisa edit (pembatasan dilakukan di menu, bukan di sini).
 */
