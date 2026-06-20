// File: registrasi_tim.cpp
// Deskripsi: Fungsi registrasi tim baru (tambah di akhir linked list)

// Fungsi daftar tim baru
void daftarTim() {
    // Cek flag pendaftaran
    if (pendaftaranDitutup) {
        pesanWarning("Pendaftaran sudah ditutup oleh Admin.");
        return;
    }

    // Cek kuota maksimum
    if (jumlahTim >= MAX_TIM) {
        pesanWarning("Jumlah tim sudah mencapai batas maksimum (" + to_string(MAX_TIM) + " tim).");
        return;
    }

    string nama, password;
    int jumlahPemain;

    tampilSubjudul("REGISTRASI TIM BARU");

    // Input nama tim
    cout << "Nama Tim  : ";
    getline(cin, nama);

    // Cek duplikat nama tim
    if (cariTim(nama) != NULL) {
        pesanError("Nama tim \"" + nama + "\" sudah terdaftar. Pilih nama lain.");
        return;
    }

    // Input password
    cout << "Password  : ";
    getline(cin, password);

    // Input jumlah pemain dengan validasi
    do {
        cout << "Jumlah Pemain (" << MIN_PEMAIN << "-" << MAX_PEMAIN << "): ";
        jumlahPemain = ambilInputInt();
        if (jumlahPemain < MIN_PEMAIN || jumlahPemain > MAX_PEMAIN) {
            pesanError("Jumlah pemain harus antara " + to_string(MIN_PEMAIN) + " dan " + to_string(MAX_PEMAIN) + ".");
        }
    } while (jumlahPemain < MIN_PEMAIN || jumlahPemain > MAX_PEMAIN);

    // Buat node Tim baru
    Tim *baru = new Tim;
    baru->nama = nama;
    baru->password = password;
    baru->jumlahPemain = jumlahPemain;
    
    // Input nama-nama pemain
    tampilSubjudul("Input Nama Pemain");
    for (int i = 0; i < jumlahPemain; i++) {
        cout << "Nama Pemain " << (i + 1) << ": ";
        getline(cin, baru->pemain[i]);
    }

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
    pesanOK("Tim \"" + nama + "\" berhasil terdaftar! (Total: " + to_string(jumlahTim) + "/" + to_string(MAX_TIM) + " tim)");

    // Otomatis tutup pendaftaran jika kuota penuh
    if (jumlahTim >= MAX_TIM) {
        pendaftaranDitutup = true;
        pesanWarning("Kuota tim sudah penuh. Pendaftaran otomatis ditutup!");
    }

    tampilPromptKembali();
}
