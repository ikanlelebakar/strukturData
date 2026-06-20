// File: registrasi_admin.cpp
// Deskripsi: Fungsi registrasi admin pertama kali dijalankan

void daftarAdmin() {
    tampilSubjudul("REGISTRASI ADMINISTRATOR TURNAMEN");
    pesanInfo("Selamat datang! Silakan daftarkan akun Admin dan atur turnamen Anda.");

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
        MAX_TIM = ambilInputInt();
        if (!adalahPangkatDua(MAX_TIM) || MAX_TIM < 2) {
            pesanError("Kapasitas tim harus merupakan angka pangkat 2 (2, 4, 8, 16, 32, dst.).");
        }
    } while (!adalahPangkatDua(MAX_TIM) || MAX_TIM < 2);

    adminSudahDibuat = true;

    pesanOK("Akun Admin berhasil dibuat!");
    tampilSubjudul("DETAIL TURNAMEN");
    cout << "  Nama Turnamen: " << namaTurnamen << endl;
    cout << "  Maksimal Tim : " << MAX_TIM << endl;
    tampilMenuBottom();
    
    tampilPromptLanjut();
}
