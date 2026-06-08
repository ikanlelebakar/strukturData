/*
 * File: edit_tim.cpp
 * Deskripsi: File ini berisi fungsi untuk mengubah informasi tim (nama tim / anggota) menggunakan konsep pointer.
 * 
 * Tugas Tim/Mahasiswa:
 * 1. Implementasikan fungsi edit data tim menggunakan pointer:
 *    - Nama Fungsi: editDataTim
 *    - Parameter: Tim* ptrTim (Pointer yang menunjuk ke objek Tim asli pada array global 'daftarTim')
 *    - Return: void
 *    - Kebutuhan Teknis:
 *      * Melalui pointer 'ptrTim', ubah isi atribut 'namaTim' sesuai dengan inputan user baru.
 *      * Melalui pointer 'ptrTim', lakukan perulangan untuk mengupdate/mengubah nama-nama 'anggota[i].namaPemain' jika diinginkan admin.
 *      * Wajib menggunakan operator panah (->) atau operator dereference (*) untuk memanipulasi atribut di dalam struct Tim yang ditunjuk.
 * 
 * 2. Implementasikan fungsi menu pemicu edit:
 *    - Nama Fungsi: menuEditTim
 *    - Parameter: tidak ada
 *    - Return: void
 *    - Kebutuhan Teknis:
 *      * Menerima input nama tim yang ingin diedit.
 *      * Cari indeks tim menggunakan fungsi 'cariIndeksTim'.
 *      * Jika ditemukan, panggil fungsi 'editDataTim' dengan mengirimkan alamat memori asli tim tersebut (menggunakan operator &).
 *      * Jika tidak ditemukan, tampilkan pesan error.
 */
