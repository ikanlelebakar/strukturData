// File: hapus_tim.cpp
// Deskripsi: Fungsi untuk menghapus tim dari linked list (Admin)

// Fungsi hapus data tim
void hapusTim() {
    if (kepala == NULL) {
        pesanWarning("Belum ada tim yang terdaftar.");
        return;
    }

    if (jadwalSudahDibuat) {
        pesanError("Tidak bisa hapus tim setelah braket dibuat.");
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
            pesanOK("Tim \"" + namaCari + "\" berhasil dihapus. Sisa tim: " + to_string(jumlahTim));
            return;
        }
        prev = curr;
        curr = curr->berikutnya;
    }

    pesanError("Tim \"" + namaCari + "\" tidak ditemukan.");
}
