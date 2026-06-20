// File: cari_lawan.cpp
// Deskripsi: Fungsi untuk mencari profil tim berdasarkan nama

// Fungsi cari profil tim lawan
void cariTim(Tim *timLogin) {
    if (kepala == NULL) {
        cout << "Belum ada tim yang terdaftar." << endl;
        return;
    }

    cout << "\nDaftar Tim Lawan yang Tersedia:" << endl;
    Tim *curr = kepala;
    int idx = 1;
    bool adaLawan = false;
    while (curr != NULL) {
        if (curr != timLogin) {
            cout << idx++ << ". " << curr->nama << endl;
            adaLawan = true;
        }
        curr = curr->berikutnya;
    }

    if (!adaLawan) {
        cout << "Tidak ada tim lawan yang tersedia." << endl;
        return;
    }

    string namaCari;
    cout << "\n=== CARI PROFIL TIM LAWAN ===" << endl;
    cout << "Masukkan nama tim yang dicari: ";
    getline(cin, namaCari);

    if (timLogin != NULL && namaCari == timLogin->nama) {
        cout << "[ERROR] Anda tidak dapat mencari profil tim Anda sendiri sebagai lawan." << endl;
        return;
    }

    Tim *hasil = cariTim(namaCari);

    if (hasil == NULL) {
        cout << "Tim \"" << namaCari << "\" tidak ditemukan dalam sistem." << endl;
        return;
    }

    cout << "\n--- Profil Tim ---" << endl;
    cout << "Nama Tim       : " << hasil->nama << endl;
    cout << "Jumlah Pemain  : " << hasil->jumlahPemain << endl;
    cout << "Daftar Pemain  : ";
    for (int i = 0; i < hasil->jumlahPemain; i++) {
        cout << hasil->pemain[i];
        if (i < hasil->jumlahPemain - 1) cout << ", ";
    }
    cout << endl;
    cout << "Poin           : " << hasil->poin << endl;
    cout << "Status         : " << (hasil->tereleminasi ? "Tereliminasi" : "Aktif") << endl;
    cout << string(30, '-') << endl;
}
