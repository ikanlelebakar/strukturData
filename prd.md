# Bikin
Saya ingin membuat program management turnamen game dengan sistem eliminasi, saya sudah ada file - file yang berguna untuk menyimpan fungi - fungi yang akan digunakan untuk pengembangan programnya letaknya di [src](/src/) . Saya akan jelaskan Alur pengunaan programnya:

# Yang digunakan
linked list -- untuk menagani masalah menyimpan data
dan bisa juga dicek di [README](README.md)

# Alur Penggunaan Program
1. Pertama kali program berjalan yang muncul adalah registrasi sebagai admin, di sini admin akan membuat username dan password untuk login sebagai admin, kemudian admin juga diminta untuk memasukkan nama perlombaannya dan juga maksimal tim yang dapat bermain.
2. Setelah akun admin terbuka maka akan muncul menu: 1. Registrasi Tim 2. Login Tim 3. Login Admin
3. Pada saat pendaftaran tim, dia akan memasukkan nama tim nya yang juga berperan sebagai username untuk login ke akunya, kemudian mendaftarkan password dan jumlah pemainnya.
4. Setelah kuota tim yang bermain telah tercukupi/penuh maka menu 1. registrasi tim akan menghilang dan diganti dengan 1. Login Tim 2. Penonton 3. Login Admin. Tetapi apabila Admin menutup pendaftarannya maka meskipun kuotanya belum habis tetap registrasi nya ditutup.
5. Pada pertandingan pertama untuk setiap tim maka Admin yang menentukan jadwalnya, namun untuk pertandingan selanjutnya maka jadwalnya akan otomatis terbentuk.
6. Setiap kali tim ada yang menang maka dia akan mendapatkan poin, poin ini berguna untuk mengurutkan peringkat nya.


# Hak Akses Admin
Pada saat Admin login dia mempunyai semua akses ke fitur - fitur yang ada, seperti: Membuat braket, Mengedit tim, Menentukan Jadwal permainan.

# Hak Akses Tim
Pada saat Tim login dia mempunyai akses: untuk mengedit timnya, melihat tim lawan, melihat jadwal permainan dan braket.

# Hak Akses Penonton
Pada menu sebagai penonton dia hanya bisa melihat: jadwal permainan, braket dan ranking

# Catatan
1. Setiap fitur baru harus berbeda file *.cpp
2. tidak boleh ada file *.h
3. Setiap perubahan harus melakukan commit ke branch saat ini
4. Setelah semua program dan test setelai maka harus mengupdate /graphify .