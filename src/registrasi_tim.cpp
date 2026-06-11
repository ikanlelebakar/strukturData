/*
 * File: registrasi_tim.cpp
 * Deskripsi: Mendaftarkan tim baru ke sistem (tail insertion ke linked list).
 *            Pendaftaran hanya bisa dilakukan selama pendaftaran belum ditutup admin.
 */

/*
 * registrasiTimBaru: Input nama tim, password, jumlah pemain.
 *                    Tambahkan ke akhir linked list.
 */
void registrasiTimBaru() {
    // Cek flag pendaftaran
    if (pendaftaranDitutup) {
        cout << "[DITOLAK] Pendaftaran sudah ditutup oleh Admin." << endl;
        return;
    }

    // Cek kuota maksimum
    if (jumlahTimAktif >= MAX_TIM) {
        cout << "[DITOLAK] Jumlah tim sudah mencapai batas maksimum (" << MAX_TIM << " tim)." << endl;
        return;
    }

    string namaTim, password;
    int    jumlahPemain;

    cout << "\n=== REGISTRASI TIM BARU ===" << endl;

    // Input nama tim
    cout << "Nama Tim  : ";
    cin.ignore();
    getline(cin, namaTim);

    // Cek duplikat nama tim
    if (cariTim(namaTim) != nullptr) {
        cout << "[DITOLAK] Nama tim \"" << namaTim << "\" sudah terdaftar. Pilih nama lain." << endl;
        return;
    }

    // Input password
    cout << "Password  : ";
    getline(cin, password);

    // Input jumlah pemain dengan validasi
    do {
        cout << "Jumlah Pemain (" << MIN_PEMAIN << "-" << MAX_PEMAIN << "): ";
        cin >> jumlahPemain;
        if (jumlahPemain < MIN_PEMAIN || jumlahPemain > MAX_PEMAIN) {
            cout << "[ERROR] Jumlah pemain harus antara " << MIN_PEMAIN << " dan " << MAX_PEMAIN << "." << endl;
        }
    } while (jumlahPemain < MIN_PEMAIN || jumlahPemain > MAX_PEMAIN);

    // Buat node Tim baru
    Tim* baru        = new Tim;
    baru->namaTim    = namaTim;
    baru->password   = password;
    baru->jumlahPemain = jumlahPemain;
    baru->poin       = 0;
    baru->isEliminated = false;
    baru->next       = nullptr;

    // Tail insertion ke linked list
    if (headTim == nullptr) {
        headTim = baru;
    } else {
        Tim* curr = headTim;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = baru;
    }

    jumlahTimAktif++;
    cout << "[SUKSES] Tim \"" << namaTim << "\" berhasil terdaftar! (Total: "
         << jumlahTimAktif << "/" << MAX_TIM << " tim)" << endl;

    cout << "\nTekan ENTER untuk kembali ke Menu Utama...";
    cin.ignore();
    cin.get();
}
