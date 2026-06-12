/*
 * File: edit_tim.cpp
 * Deskripsi: Mengubah data tim menggunakan pointer.
 *            Tim hanya bisa edit data dirinya sendiri.
 */

/*
 * editDataTim: Edit nama tim dan/atau jumlah pemain melalui pointer.
 *              Wajib menggunakan operator -> untuk memanipulasi struct.
 */
void editDataTim(Tim* ptrTim) {
    if (ptrTim == nullptr) {
        cout << "[ERROR] Pointer tim tidak valid." << endl;
        return;
    }

    int pilihan;
    cout << "\n=== EDIT DATA TIM: " << ptrTim->namaTim << " ===" << endl;
    cout << "1. Ubah Nama Tim" << endl;
    cout << "2. Ubah Jumlah Pemain" << endl;
    cout << "3. Ubah Password" << endl;
    cout << "0. Batal" << endl;
    cout << "Pilihan: ";
    cin >> pilihan;
    cin.ignore(10000, '\n');

    switch (pilihan) {
        case 1: {
            string namaBaru;
            cout << "Nama Tim Baru: ";
            getline(cin, namaBaru);

            // Cek duplikat (tidak boleh sama dengan tim lain)
            Tim* existing = cariTim(namaBaru);
            if (existing != nullptr && existing != ptrTim) {
                cout << "[DITOLAK] Nama \"" << namaBaru << "\" sudah dipakai tim lain." << endl;
            } else {
                ptrTim->namaTim = namaBaru;  // operator -> untuk akses via pointer
                cout << "[SUKSES] Nama tim berhasil diubah menjadi \"" << namaBaru << "\"." << endl;
            }
            break;
        }
        case 2: {
            int jumlahBaru;
            do {
                cout << "Jumlah Pemain Baru (" << MIN_PEMAIN << "-" << MAX_PEMAIN << "): ";
                cin >> jumlahBaru;
                cin.ignore(10000, '\n');
                if (jumlahBaru < MIN_PEMAIN || jumlahBaru > MAX_PEMAIN) {
                    cout << "[ERROR] Harus antara " << MIN_PEMAIN << " dan " << MAX_PEMAIN << "." << endl;
                }
            } while (jumlahBaru < MIN_PEMAIN || jumlahBaru > MAX_PEMAIN);

            ptrTim->jumlahPemain = jumlahBaru;  // operator -> untuk akses via pointer
            cout << "[SUKSES] Jumlah pemain berhasil diubah menjadi " << jumlahBaru << "." << endl;
            break;
        }
        case 3: {
            string passBaru;
            cout << "Password Baru: ";
            getline(cin, passBaru);
            ptrTim->password = passBaru;
            cout << "[SUKSES] Password berhasil diubah." << endl;
            break;
        }
        case 0:
            cout << "Edit dibatalkan." << endl;
            break;
        default:
            cout << "[ERROR] Pilihan tidak valid." << endl;
    }
}

/*
 * menuEditTim: Admin memilih tim yang ingin diedit berdasarkan nama.
 *              Dipanggil dari menu admin tanpa tim yang login.
 */
void menuEditTim() {
    if (headTim == nullptr) {
        cout << "[INFO] Belum ada tim yang terdaftar." << endl;
        return;
    }

    string namaCari;
    cout << "\nMasukkan nama tim yang ingin diedit: ";
    getline(cin, namaCari);

    Tim* target = cariTim(namaCari);  // cari via pointer
    if (target == nullptr) {
        cout << "[ERROR] Tim \"" << namaCari << "\" tidak ditemukan." << endl;
        return;
    }

    editDataTim(target);  // kirim pointer langsung (akses ke objek asli)
}

/*
 * editTimSendiri: Tim yang sedang login mengedit data dirinya sendiri.
 *                Dipanggil dari menu tim dengan pointer timLogin.
 */
void editTimSendiri(Tim* timLogin) {
    if (timLogin == nullptr) return;
    editDataTim(timLogin);
}
