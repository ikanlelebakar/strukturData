/*
 * File: cari_lawan.cpp
 * Deskripsi: Mencari profil tim berdasarkan nama (linear search via cariTim).
 *            Bisa digunakan oleh tim untuk melihat profil lawan.
 */

/*
 * cariLawan: Input nama tim, cari di linked list, tampilkan detail profil.
 */
void cariLawan() {
    if (headTim == nullptr) {
        cout << "[INFO] Belum ada tim yang terdaftar." << endl;
        return;
    }

    string namaCari;
    cout << "\n=== CARI PROFIL TIM LAWAN ===" << endl;
    cout << "Masukkan nama tim yang dicari: ";
    getline(cin, namaCari);

    Tim* hasil = cariTim(namaCari);  // linear search via pointer

    if (hasil == nullptr) {
        cout << "[INFO] Tim \"" << namaCari << "\" tidak ditemukan dalam sistem." << endl;
        return;
    }

    cout << "\n--- Profil Tim ---" << endl;
    cout << "Nama Tim       : " << hasil->namaTim << endl;
    cout << "Jumlah Pemain  : " << hasil->jumlahPemain << endl;
    cout << "Poin           : " << hasil->poin << endl;
    cout << "Status         : " << (hasil->isEliminated ? "Tereliminasi" : "Aktif") << endl;
    cout << string(30, '-') << endl;
}
