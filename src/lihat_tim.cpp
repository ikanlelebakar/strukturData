/*
 * File: lihat_tim.cpp
 * Deskripsi: Menampilkan seluruh tim yang terdaftar dengan traverse linked list.
 */

/*
 * lihatDaftarTim: Traversal linked list dan tampilkan detail setiap tim.
 */
void lihatDaftarTim() {
    cout << "\n=== DAFTAR TIM TERDAFTAR ===" << endl;

    if (headTim == nullptr) {
        cout << "(Belum ada tim yang terdaftar)" << endl;
        return;
    }

    cout << "Total tim: " << jumlahTimAktif << endl;
    cout << string(50, '-') << endl;

    int no   = 1;
    Tim* curr = headTim;
    while (curr != nullptr) {
        cout << no << ". " << curr->namaTim << endl;
        cout << "   Jumlah Pemain : " << curr->jumlahPemain << endl;
        cout << "   Poin          : " << curr->poin << endl;
        cout << "   Status        : " << (curr->isEliminated ? "Tereliminasi" : "Aktif") << endl;
        cout << string(50, '-') << endl;
        curr = curr->next;
        no++;
    }
}
