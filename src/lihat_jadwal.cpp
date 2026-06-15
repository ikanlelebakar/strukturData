// File: lihat_jadwal.cpp
// Deskripsi: Fungsi untuk menampilkan seluruh antrian jadwal pertandingan

// Fungsi tampilkan jadwal antrian pertandingan
void tampilJadwal() {
    cout << "\n=== JADWAL ANTRIAN PERTANDINGAN ===" << endl;

    if (antrianKosong()) {
        cout << "(Belum ada jadwal pertandingan)" << endl;
        return;
    }

    int no = 1;
    NodeAntrian *curr = depanAntrian;
    while (curr != NULL) {
        cout << no << ". [" << curr->ronde << "] "
             << curr->timA->nama << " vs " << curr->timB->nama
             << "  |  Tanggal: " << curr->tanggalTanding;
        if (no == 1) cout << "  <-- SEDANG BERLANGSUNG";
        cout << endl;
        curr = curr->berikutnya;
        no++;
    }
}
