// File: login_tim.cpp
// Deskripsi: Fungsi login tim menggunakan nama tim dan password

// Fungsi masuk tim
Tim *masukTim() {
    string nama, password;

    tampilSubjudul("LOGIN TIM");
    cout << "Nama Tim (Username): ";
    getline(cin, nama);
    cout << "Password          : ";
    getline(cin, password);

    Tim *curr = kepala;
    while (curr != NULL) {
        if (curr->nama == nama) {
            if (curr->password == password) {
                pesanOK("Login berhasil. Selamat datang, Tim " + nama + "!");
                return curr;
            } else {
                pesanError("Password salah.");
                return NULL;
            }
        }
        curr = curr->berikutnya;
    }

    pesanError("Tim dengan nama \"" + nama + "\" tidak ditemukan.");
    return NULL;
}
