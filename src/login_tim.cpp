/*
 * File: login_tim.cpp
 * Deskripsi: Autentikasi login tim menggunakan nama tim (username) + password.
 *            Traverse linked list untuk mencari tim yang cocok.
 */

/*
 * loginTim: Minta input nama tim + password, cari di linked list.
 *           Return pointer ke node Tim jika sukses, nullptr jika gagal.
 *
 * Catatan: Tim yang sudah tereliminasi tetap bisa login untuk melihat data,
 *          pembatasan operasi edit dilakukan di level menu.
 */
Tim* loginTim() {
    string namaTim, password;

    cout << "\n=== LOGIN TIM ===" << endl;
    cout << "Nama Tim (Username): ";
    getline(cin, namaTim);
    cout << "Password          : ";
    getline(cin, password);

    Tim* curr = headTim;
    while (curr != nullptr) {
        if (curr->namaTim == namaTim) {
            if (curr->password == password) {
                cout << "[OK] Login berhasil. Selamat datang, Tim " << namaTim << "!" << endl;
                return curr;
            } else {
                cout << "[GAGAL] Password salah." << endl;
                return nullptr;
            }
        }
        curr = curr->next;
    }

    cout << "[GAGAL] Tim dengan nama \"" << namaTim << "\" tidak ditemukan." << endl;
    return nullptr;
}
