// File: edit_tim.cpp
// Deskripsi: Fungsi untuk mengedit data tim menggunakan pointer

// Fungsi pembantu edit data tim via pointer
void editDataTim(Tim *ptrTim) {
    if (ptrTim == NULL) {
        pesanError("Pointer tim tidak valid.");
        return;
    }

    int pilihan;
    tampilSubjudul("EDIT DATA TIM: " + ptrTim->nama);
    tampilPilihanMenu("1. Ubah Nama Tim");
    tampilPilihanMenu("2. Ubah Jumlah Pemain");
    tampilPilihanMenu("3. Ubah Nama-nama Pemain");
    tampilPilihanMenu("4. Ubah Password");
    tampilPilihanMenu("0. Batal");
    tampilMenuBottom();
    cout << "Pilihan: ";
    pilihan = ambilInputInt();

    switch (pilihan) {
        case 1: {
            string namaBaru;
            cout << "Nama Tim Baru: ";
            getline(cin, namaBaru);

            // Cek duplikat (tidak boleh sama dengan tim lain)
            Tim *existing = cariTim(namaBaru);
            if (existing != NULL && existing != ptrTim) {
                pesanError("Nama \"" + namaBaru + "\" sudah dipakai tim lain.");
            } else {
                ptrTim->nama = namaBaru;
                pesanOK("Nama tim berhasil diubah menjadi \"" + namaBaru + "\".");
            }
            break;
        }
        case 2: {
            int jumlahBaru;
            do {
                cout << "Jumlah Pemain Baru (" << MIN_PEMAIN << "-" << MAX_PEMAIN << "): ";
                jumlahBaru = ambilInputInt();
                if (jumlahBaru < MIN_PEMAIN || jumlahBaru > MAX_PEMAIN) {
                    pesanError("Harus antara " + to_string(MIN_PEMAIN) + " dan " + to_string(MAX_PEMAIN) + ".");
                }
            } while (jumlahBaru < MIN_PEMAIN || jumlahBaru > MAX_PEMAIN);

            ptrTim->jumlahPemain = jumlahBaru;
            tampilSubjudul("Input Nama Pemain Baru");
            for (int i = 0; i < jumlahBaru; i++) {
                cout << "Nama Pemain " << (i + 1) << ": ";
                getline(cin, ptrTim->pemain[i]);
            }
            pesanOK("Jumlah dan nama pemain berhasil diubah.");
            break;
        }
        case 3: {
            tampilSubjudul("Ubah Nama-nama Pemain");
            for (int i = 0; i < ptrTim->jumlahPemain; i++) {
                cout << "Nama Pemain " << (i + 1) << " (" << ptrTim->pemain[i] << "): ";
                string namaBaru;
                getline(cin, namaBaru);
                if (!namaBaru.empty()) {
                    ptrTim->pemain[i] = namaBaru;
                }
            }
            pesanOK("Nama-nama pemain berhasil diperbarui.");
            break;
        }
        case 4: {
            string passBaru;
            cout << "Password Baru: ";
            getline(cin, passBaru);
            ptrTim->password = passBaru;
            pesanOK("Password berhasil diubah.");
            break;
        }
        case 0:
            pesanInfo("Edit dibatalkan.");
            break;
        default:
            pesanError("Pilihan tidak valid.");
    }
}

// Fungsi menu edit tim oleh Admin
void menuEditTim() {
    if (kepala == NULL) {
        pesanWarning("Belum ada tim yang terdaftar.");
        return;
    }

    string namaCari;
    cout << "\nMasukkan nama tim yang ingin diedit: ";
    getline(cin, namaCari);

    Tim *target = cariTim(namaCari);
    if (target == NULL) {
        pesanError("Tim \"" + namaCari + "\" tidak ditemukan.");
        return;
    }

    editDataTim(target);
}

// Fungsi edit tim sendiri (oleh Tim yang login)
void editTim(Tim *timLogin) {
    if (timLogin == NULL) return;
    editDataTim(timLogin);
}
