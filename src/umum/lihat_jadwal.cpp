// File: lihat_jadwal.cpp
// Deskripsi: Fungsi untuk menampilkan seluruh antrian jadwal pertandingan

// Fungsi tampilkan jadwal antrian pertandingan
void tampilJadwal() {
    tampilSubjudul("JADWAL ANTRIAN PERTANDINGAN");

    if (antrianKosong()) {
        pesanInfo("Belum ada jadwal pertandingan");
        return;
    }

    vector<int> lebar = {4, 14, 25, 19, 12};
    vector<char> alinyemen = {'C', 'C', 'C', 'C', 'C'};

    tampilGarisTabel(lebar, 'A');
    tampilBarisTabel({"No", "Ronde", "Pertandingan", "Jadwal", "Status"}, lebar, alinyemen);
    tampilGarisTabel(lebar, 'T');

    int no = 1;
    NodeAntrian *curr = depanAntrian;
    while (curr != NULL) {
        string matchStr = curr->timA->nama + " vs " + curr->timB->nama;
        string jadwalStr = curr->tanggalTanding + " " + curr->jam;
        string statusStr = (no == 1) ? "BERLANGSUNG" : "MENUNGGU";
        
        tampilBarisTabel({to_string(no), curr->ronde, matchStr, jadwalStr, statusStr}, lebar, alinyemen);
        
        curr = curr->berikutnya;
        no++;
    }
    tampilGarisTabel(lebar, 'B');
}
