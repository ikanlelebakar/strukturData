/*
 * File: lihat_jadwal.cpp
 * Deskripsi: Menampilkan seluruh antrian jadwal pertandingan (FIFO traversal).
 */

/*
 * lihatJadwalAntrian: Traverse antrian dari front ke back dan tampilkan tiap match.
 */
void lihatJadwalAntrian() {
    cout << "\n=== JADWAL ANTRIAN PERTANDINGAN ===" << endl;

    if (isAntrianKosong()) {
        cout << "(Belum ada jadwal pertandingan)" << endl;
        return;
    }

    int no = 1;
    NodeAntrian* curr = frontAntrian;
    while (curr != nullptr) {
        cout << no << ". [" << curr->ronde << "] "
             << curr->timA->namaTim << " vs " << curr->timB->namaTim
             << "  |  Tanggal: " << curr->tanggalTanding;
        if (no == 1) cout << "  <-- SEDANG BERLANGSUNG";
        cout << endl;
        curr = curr->next;
        no++;
    }
}
