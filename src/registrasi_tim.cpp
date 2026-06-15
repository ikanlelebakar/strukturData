// File: registrasi_tim.cpp
// Deskripsi: Fungsi registrasi tim baru (tambah di akhir linked list)

// Fungsi daftar tim baru
void daftarTim() {
    // Cek flag pendaftaran
    if (pendaftaranDitutup) {
        cout << "Pendaftaran sudah ditutup oleh Admin." << endl;
        return;
    }

    // Cek kuota maksimum
    if (jumlahTim >= MAX_TIM) {
        cout << "Jumlah tim sudah mencapai batas maksimum (" << MAX_TIM << " tim)." << endl;
        return;
    }

    string nama, password;
    int jumlahPemain;

    cout << "\n=== REGISTRASI TIM BARU ===" << endl;

    // Input nama tim
    cout << "Nama Tim  : ";
    getline(cin, nama);

    // Cek duplikat nama tim
    if (cariTim(nama) != NULL) {
        cout << "Nama tim \"" << nama << "\" sudah terdaftar. Pilih nama lain." << endl;
        return;
    }

    // Input password
    cout << "Password  : ";
    getline(cin, password);

    // Input jumlah pemain dengan validasi
    do {
        cout << "Jumlah Pemain (" << MIN_PEMAIN << "-" << MAX_PEMAIN << "): ";
        cin >> jumlahPemain;
        cin.ignore(10000, '\n');
        if (jumlahPemain < MIN_PEMAIN || jumlahPemain > MAX_PEMAIN) {
            cout << "Jumlah pemain harus antara " << MIN_PEMAIN << " dan " << MAX_PEMAIN << "." << endl;
        }
    } while (jumlahPemain < MIN_PEMAIN || jumlahPemain > MAX_PEMAIN);

    // Buat node Tim baru
    Tim *baru = new Tim;
    baru->nama = nama;
    baru->password = password;
    baru->jumlahPemain = jumlahPemain;
    baru->poin = 0;
    baru->tereleminasi = false;
    baru->berikutnya = NULL;

    // Tambah data di akhir (tail insertion)
    if (kepala == NULL) {
        kepala = baru;
    } else {
        Tim *curr = kepala;
        while (curr->berikutnya != NULL) {
            curr = curr->berikutnya;
        }
        curr->berikutnya = baru;
    }

    jumlahTim++;
    cout << "Tim \"" << nama << "\" berhasil terdaftar! (Total: "
         << jumlahTim << "/" << MAX_TIM << " tim)" << endl;

    // Otomatis tutup pendaftaran jika kuota penuh
    if (jumlahTim >= MAX_TIM) {
        pendaftaranDitutup = true;
        cout << "Kuota tim sudah penuh. Pendaftaran otomatis ditutup!" << endl;
    }

    cout << "\nTekan ENTER untuk kembali ke Menu Utama...";
    cin.get();
}
