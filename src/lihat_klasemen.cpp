/*
 * File: lihat_klasemen.cpp
 * Deskripsi: Menampilkan papan klasemen berdasarkan poin (descending).
 *            Memanggil urutkanKlasemen() dari search_sort.cpp terlebih dahulu.
 */

/*
 * lihatKlasemen: Sort linked list by poin descending, lalu tampilkan tabel.
 */
void lihatKlasemen() {
    cout << "\n=== KLASEMEN TURNAMEN ===" << endl;

    if (headTim == nullptr) {
        cout << "(Belum ada tim yang terdaftar)" << endl;
        return;
    }

    // Sort terlebih dahulu (bubble sort descending)
    urutkanKlasemen();

    // Header tabel
    cout << left
         << setw(5)  << "No"
         << setw(20) << "Nama Tim"
         << setw(8)  << "Poin"
         << setw(15) << "Status"
         << endl;
    cout << string(50, '-') << endl;

    int  no   = 1;
    Tim* curr = headTim;
    while (curr != nullptr) {
        string status = curr->isEliminated ? "Tereliminasi" : "Aktif";
        cout << left
             << setw(5)  << no
             << setw(20) << curr->namaTim
             << setw(8)  << curr->poin
             << setw(15) << status
             << endl;
        curr = curr->next;
        no++;
    }
    cout << string(50, '-') << endl;
}
