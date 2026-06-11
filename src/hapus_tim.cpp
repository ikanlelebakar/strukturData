/*
 * File: hapus_tim.cpp
 * Deskripsi: Menghapus tim dari linked list (admin only).
 *            Hanya bisa dilakukan sebelum braket dibuat.
 */

/*
 * hapusTim: Cari tim berdasarkan nama, lalu hapus node dari linked list.
 *           Menyambung kembali pointer prev->next agar list tetap utuh.
 */
void hapusTim() {
    if (headTim == nullptr) {
        cout << "[INFO] Belum ada tim yang terdaftar." << endl;
        return;
    }

    if (bracketSudahDibuat) {
        cout << "[DITOLAK] Tidak bisa hapus tim setelah braket dibuat." << endl;
        return;
    }

    string namaCari;
    cout << "\nMasukkan nama tim yang ingin dihapus: ";
    cin.ignore();
    getline(cin, namaCari);

    Tim* curr = headTim;
    Tim* prev = nullptr;

    while (curr != nullptr) {
        if (curr->namaTim == namaCari) {
            // Sambungkan prev ke node sesudah curr
            if (prev == nullptr) {
                // Hapus node head
                headTim = curr->next;
            } else {
                prev->next = curr->next;
            }
            delete curr;
            jumlahTimAktif--;
            cout << "[SUKSES] Tim \"" << namaCari << "\" berhasil dihapus. "
                 << "Sisa tim: " << jumlahTimAktif << endl;
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    cout << "[ERROR] Tim \"" << namaCari << "\" tidak ditemukan." << endl;
}
