// File: lihat_tim.cpp
// Deskripsi: Fungsi untuk menampilkan seluruh tim yang terdaftar

// Fungsi tampilkan daftar tim
void tampilkanTim() {
    tampilSubjudul("DAFTAR TIM TERDAFTAR");

    if (kepala == NULL) {
        pesanInfo("Belum ada tim yang terdaftar");
        return;
    }

    vector<int> lebar = {4, 18, 5, 29, 6, 11};
    vector<char> alinyemen = {'C', 'L', 'C', 'L', 'C', 'C'};

    tampilGarisTabel(lebar, 'A');
    tampilBarisTabel({"No", "Nama Tim", "Jml", "Pemain", "Poin", "Status"}, lebar, {'C', 'C', 'C', 'C', 'C', 'C'});
    tampilGarisTabel(lebar, 'T');

    int no = 1;
    Tim *curr = kepala;
    while (curr != NULL) {
        string pemainStr = "";
        for (int i = 0; i < curr->jumlahPemain; i++) {
            pemainStr += curr->pemain[i];
            if (i < curr->jumlahPemain - 1) {
                pemainStr += ", ";
            }
        }
        string statusStr = curr->tereleminasi ? "Tereliminasi" : "Aktif";
        
        tampilBarisTabel({to_string(no), curr->nama, to_string(curr->jumlahPemain), pemainStr, to_string(curr->poin), statusStr}, lebar, alinyemen);
        
        curr = curr->berikutnya;
        no++;
    }
    tampilGarisTabel(lebar, 'B');
}
