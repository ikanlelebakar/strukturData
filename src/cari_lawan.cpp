// File: cari_lawan.cpp
// Deskripsi: Fungsi untuk mencari profil tim berdasarkan nama

// Fungsi cari profil tim lawan
void cariTim() {
    if (kepala == NULL) {
        cout << "Belum ada tim yang terdaftar." << endl;
        return;
    }

    string namaCari;
    cout << "\n=== CARI PROFIL TIM LAWAN ===" << endl;
    cout << "Masukkan nama tim yang dicari: ";
    getline(cin, namaCari);

    Tim *hasil = cariTim(namaCari);

    if (hasil == NULL) {
        cout << "Tim \"" << namaCari << "\" tidak ditemukan dalam sistem." << endl;
        return;
    }

    cout << "\n--- Profil Tim ---" << endl;
    cout << "Nama Tim       : " << hasil->nama << endl;
    cout << "Jumlah Pemain  : " << hasil->jumlahPemain << endl;
    cout << "Poin           : " << hasil->poin << endl;
    cout << "Status         : " << (hasil->tereleminasi ? "Tereliminasi" : "Aktif") << endl;
    cout << string(30, '-') << endl;
}
