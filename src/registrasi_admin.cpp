/*
 * File: registrasi_admin.cpp
 * Deskripsi: Alur registrasi admin pertama kali program dijalankan.
 *            Admin membuat username, password, nama turnamen, dan jumlah maksimal tim.
 */

void registrasiAdmin() {
    cout << "\n" << string(50, '=') << endl;
    cout << "      REGISTRASI ADMINISTRATOR TURNAMEN" << endl;
    cout << string(50, '=') << endl;
    cout << "Selamat datang! Silakan daftarkan akun Admin dan atur turnamen Anda." << endl;

    cout << "\nUsername Admin: ";
    cin >> adminUsername;

    cout << "Password Admin: ";
    cin >> adminPassword;

    cout << "Nama Turnamen : ";
    cin.ignore();
    getline(cin, namaTurnamen);

    // Minta input kapasitas tim (harus pangkat 2)
    do {
        cout << "Maksimal Tim (harus pangkat 2, min 2): ";
        cin >> MAX_TIM;
        if (!isPowerOfTwo(MAX_TIM) || MAX_TIM < 2) {
            cout << "[ERROR] Kapasitas tim harus merupakan angka pangkat 2 (2, 4, 8, 16, 32, dst.)." << endl;
        }
    } while (!isPowerOfTwo(MAX_TIM) || MAX_TIM < 2);

    adminSudahDibuat = true;

    cout << "\n[SUKSES] Akun Admin berhasil dibuat!" << endl;
    cout << "Nama Turnamen: " << namaTurnamen << endl;
    cout << "Maksimal Tim : " << MAX_TIM << endl;
    cout << string(50, '=') << endl;
    cout << "Tekan ENTER untuk lanjut ke Menu Utama...";
    cin.ignore();
    cin.get();
}
