// File: login_tim.cpp
// Deskripsi: Fungsi login tim menggunakan nama tim dan password

// Fungsi masuk tim
Tim *masukTim() {
    string nama, password;

    cout << "\n=== LOGIN TIM ===" << endl;
    cout << "Nama Tim (Username): ";
    getline(cin, nama);
    cout << "Password          : ";
    getline(cin, password);

    Tim *curr = kepala;
    while (curr != NULL) {
        if (curr->nama == nama) {
            if (curr->password == password) {
                cout << "Login berhasil. Selamat datang, Tim " << nama << "!" << endl;
                return curr;
            } else {
                cout << "Password salah." << endl;
                return NULL;
            }
        }
        curr = curr->berikutnya;
    }

    cout << "Tim dengan nama \"" << nama << "\" tidak ditemukan." << endl;
    return NULL;
}
