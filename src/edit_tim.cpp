// File: edit_tim.cpp
// Deskripsi: Fungsi untuk mengedit data tim menggunakan pointer

// Fungsi pembantu edit data tim via pointer
void editDataTim(Tim *ptrTim) {
    if (ptrTim == NULL) {
        cout << "Pointer tim tidak valid." << endl;
        return;
    }

    int pilihan;
    cout << "\n=== EDIT DATA TIM: " << ptrTim->nama << " ===" << endl;
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
            Tim *existing = cariTim(namaBaru);
            if (existing != NULL && existing != ptrTim) {
                cout << "Nama \"" << namaBaru << "\" sudah dipakai tim lain." << endl;
            } else {
                ptrTim->nama = namaBaru;
                cout << "Nama tim berhasil diubah menjadi \"" << namaBaru << "\"." << endl;
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
                    cout << "Harus antara " << MIN_PEMAIN << " dan " << MAX_PEMAIN << "." << endl;
                }
            } while (jumlahBaru < MIN_PEMAIN || jumlahBaru > MAX_PEMAIN);

            ptrTim->jumlahPemain = jumlahBaru;
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
            cout << "Pilihan tidak valid." << endl;
    }
}

// Fungsi menu edit tim oleh Admin
void menuEditTim() {
    if (kepala == NULL) {
        cout << "Belum ada tim yang terdaftar." << endl;
        return;
    }

    string namaCari;
    cout << "\nMasukkan nama tim yang ingin diedit: ";
    getline(cin, namaCari);

    Tim *target = cariTim(namaCari);
    if (target == NULL) {
        cout << "Tim \"" << namaCari << "\" tidak ditemukan." << endl;
        return;
    }

    editDataTim(target);
}

// Fungsi edit tim sendiri (oleh Tim yang login)
void editTim(Tim *timLogin) {
    if (timLogin == NULL) return;
    editDataTim(timLogin);
}
