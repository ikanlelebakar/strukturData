// File: lihat_tim.cpp
// Deskripsi: Fungsi untuk menampilkan seluruh tim yang terdaftar

// Fungsi tampilkan daftar tim
void tampilkanTim() {
    cout << "\n=== DAFTAR TIM TERDAFTAR ===" << endl;

    if (kepala == NULL) {
        cout << "(Belum ada tim yang terdaftar)" << endl;
        return;
    }

    cout << "Total tim: " << jumlahTim << endl;
    cout << string(50, '-') << endl;

    int no = 1;
    Tim *curr = kepala;
    while (curr != NULL) {
        cout << no << ". " << curr->nama << endl;
        cout << "   Jumlah Pemain : " << curr->jumlahPemain << endl;
        cout << "   Poin          : " << curr->poin << endl;
        cout << "   Status        : " << (curr->tereleminasi ? "Tereliminasi" : "Aktif") << endl;
        cout << string(50, '-') << endl;
        curr = curr->berikutnya;
        no++;
    }
}
