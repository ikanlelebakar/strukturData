// File: cari_lawan.cpp
// Deskripsi: Fungsi untuk mencari profil tim berdasarkan nama

// Fungsi cari profil tim lawan
void cariTim(Tim *timLogin) {
    if (kepala == NULL) {
        pesanWarning("Belum ada tim yang terdaftar.");
        return;
    }

    tampilSubjudul("DAFTAR TIM LAWAN");
    Tim *curr = kepala;
    int idx = 1;
    bool adaLawan = false;
    while (curr != NULL) {
        if (curr != timLogin) {
            cout << "  " << idx++ << ". " << curr->nama << endl;
            adaLawan = true;
        }
        curr = curr->berikutnya;
    }
    tampilMenuBottom();

    if (!adaLawan) {
        pesanInfo("Tidak ada tim lawan yang tersedia.");
        return;
    }

    string namaCari;
    tampilSubjudul("CARI PROFIL TIM LAWAN");
    cout << "Masukkan nama tim yang dicari: ";
    getline(cin, namaCari);

    if (timLogin != NULL && namaCari == timLogin->nama) {
        pesanError("Anda tidak dapat mencari profil tim Anda sendiri sebagai lawan.");
        return;
    }

    Tim *hasil = cariTim(namaCari);

    if (hasil == NULL) {
        pesanError("Tim \"" + namaCari + "\" tidak ditemukan dalam sistem.");
        return;
    }

    tampilSubjudul("PROFIL TIM: " + hasil->nama);
    cout << "  Jumlah Pemain  : " << hasil->jumlahPemain << endl;
    cout << "  Daftar Pemain  : ";
    for (int i = 0; i < hasil->jumlahPemain; i++) {
        cout << hasil->pemain[i];
        if (i < hasil->jumlahPemain - 1) cout << ", ";
    }
    cout << endl;
    cout << "  Poin           : " << hasil->poin << endl;
    cout << "  Status         : " << (hasil->tereleminasi ? "Tereliminasi" : "Aktif") << endl;
    tampilMenuBottom();
}
