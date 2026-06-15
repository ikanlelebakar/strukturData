// File: hapus_tim.cpp
// Deskripsi: Fungsi untuk menghapus tim dari linked list (Admin)

// Fungsi hapus data tim
void hapusTim() {
    if (kepala == NULL) {
        cout << "Belum ada tim yang terdaftar." << endl;
        return;
    }

    if (jadwalSudahDibuat) {
        cout << "Tidak bisa hapus tim setelah braket dibuat." << endl;
        return;
    }

    string namaCari;
    cout << "\nMasukkan nama tim yang ingin dihapus: ";
    getline(cin, namaCari);

    Tim *curr = kepala;
    Tim *prev = NULL;

    while (curr != NULL) {
        if (curr->nama == namaCari) {
            // Sambungkan pointer node sebelum ke node sesudah
            if (prev == NULL) {
                kepala = curr->berikutnya;
            } else {
                prev->berikutnya = curr->berikutnya;
            }
            delete curr;
            jumlahTim--;
            cout << "[SUKSES] Tim \"" << namaCari << "\" berhasil dihapus. "
                 << "Sisa tim: " << jumlahTim << endl;
            return;
        }
        prev = curr;
        curr = curr->berikutnya;
    }

    cout << "Tim \"" << namaCari << "\" tidak ditemukan." << endl;
}
