// File: registrasi_admin.cpp
// Deskripsi: Fungsi registrasi admin pertama kali dijalankan

void daftarAdmin() {
    cout << "\n" << string(50, '=') << endl;
    cout << "      REGISTRASI ADMINISTRATOR TURNAMEN" << endl;
    cout << string(50, '=') << endl;
    cout << "Selamat datang! Silakan daftarkan akun Admin dan atur turnamen Anda." << endl;

    cout << "\nUsername Admin: ";
    cin >> adminUsername;

    cout << "Password Admin: ";
    cin >> adminPassword;
    cin.ignore(10000, '\n');

    cout << "Nama Turnamen : ";
    getline(cin, namaTurnamen);

    // Minta input kapasitas tim (harus pangkat 2)
    do {
        cout << "Maksimal Tim (harus pangkat 2, min 2): ";
        cin >> MAX_TIM;
        cin.ignore(10000, '\n');
        if (!adalahPangkatDua(MAX_TIM) || MAX_TIM < 2) {
            cout << "Kapasitas tim harus merupakan angka pangkat 2 (2, 4, 8, 16, 32, dst.)." << endl;
        }
    } while (!adalahPangkatDua(MAX_TIM) || MAX_TIM < 2);

    adminSudahDibuat = true;

    cout << "\nAkun Admin berhasil dibuat!" << endl;
    cout << "Nama Turnamen: " << namaTurnamen << endl;
    cout << "Maksimal Tim : " << MAX_TIM << endl;
    cout << string(50, '=') << endl;
    cout << "Tekan ENTER untuk lanjut ke Menu Utama...";
    cin.get();
}
