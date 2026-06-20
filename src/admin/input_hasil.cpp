// File: input_hasil.cpp
// Deskripsi: Fungsi untuk menginput hasil pertandingan dan membuat jadwal ronde berikutnya

// Fungsi menghitung tim yang masih aktif (belum tereliminasi)
int hitungTimAktif() {
    int count = 0;
    Tim *curr = kepala;
    while (curr != NULL) {
        if (!curr->tereleminasi) count++;
        curr = curr->berikutnya;
    }
    return count;
}

// Fungsi input hasil skor pertandingan
void inputHasil() {
    if (antrianKosong()) {
        if (!jadwalSudahDibuat) {
            cout << "Braket belum dibuat. Silakan buat jadwal terlebih dahulu." << endl;
        } else {
            cout << "Tidak ada pertandingan yang tersisa. Turnamen selesai!" << endl;
        }
        return;
    }

    NodeAntrian *match = depanAntrian;
    Tim *timA = match->timA;
    Tim *timB = match->timB;

    cout << "\n=== INPUT HASIL PERTANDINGAN ===" << endl;
    cout << "Ronde    : " << match->ronde << endl;
    cout << "Tanggal  : " << match->tanggalTanding << endl;
    cout << string(40, '-') << endl;
    cout << "Tim A    : " << timA->nama << endl;
    cout << "Tim B    : " << timB->nama << endl;
    cout << string(40, '-') << endl;

    int skorA, skorB;
    bool inputValid = false;
    while (!inputValid) {
        cout << "Skor " << timA->nama << ": ";
        skorA = ambilInputInt();
        cout << "Skor " << timB->nama << ": ";
        skorB = ambilInputInt();

        if (skorA < 0 || skorB < 0) {
            cout << "[ERROR] Skor tidak boleh negatif." << endl;
        } else if (skorA > 3 || skorB > 3) {
            cout << "[ERROR] Skor tidak boleh lebih dari 3." << endl;
        } else if (skorA == skorB) {
            cout << "[ERROR] Skor tidak boleh seri dalam sistem eliminasi. Masukkan ulang." << endl;
        } else {
            inputValid = true;
        }
    }

    Tim *pemenang = (skorA > skorB) ? timA : timB;
    Tim *kalah = (skorA > skorB) ? timB : timA;

    bool iniMatchKetiga = matchKetiga;
    string rondeMatch = match->ronde;

    // Tentukan penambahan poin berdasarkan tipe ronde
    int tambahPoin = 1;
    if (rondeMatch == "Perebutan Juara ke-3") {
        tambahPoin = 5;
    } else if (rondeMatch == "Final") {
        tambahPoin = 20;
    } else if (rondeMatch == "Semifinal") {
        tambahPoin = 10;
    } else {
        tambahPoin = 1 << (rondeSekarang - 1);
    }

    // Logika match perebutan juara ke-3
    if (iniMatchKetiga) {
        kalah->tereleminasi = true;
        pemenang->tereleminasi = true;
        pemenang->poin += tambahPoin;
        matchKetiga = false;
        updatePemenang(timA, timB, pemenang);

        cout << "\n" << pemenang->nama << " menang " << skorA
             << "-" << skorB << " dan meraih JUARA KE-3!" << endl;
        cout << kalah->nama << " tereliminasi." << endl;

        hapusAntrian();

        if (!antrianKosong()) {
            cout << "Pertandingan Final siap dimulai!" << endl;
        }
        return;
    }

    pemenang->poin += tambahPoin;
    updatePemenang(timA, timB, pemenang);
    hapusAntrian();

    bool iniSemifinal = (rondeMatch == "Semifinal");

    if (iniSemifinal) {
        if (semifinalisKalah1 == NULL) {
            semifinalisKalah1 = kalah;
            cout << "Semifinalis pertama yang kalah: " << kalah->nama
                 << " (menunggu pertandingan juara ke-3)" << endl;
        } else {
            semifinalisKalah2 = kalah;

            // Buat pertandingan juara ke-3
            cout << "\n=== PENJADWALAN PEREBUTAN JUARA KE-3 ===" << endl;
            cout << semifinalisKalah1->nama << " vs " << semifinalisKalah2->nama << endl;
            string tgl, jam;
            do {
                cout << "  Masukkan Tanggal (format YYYY-MM-DD): ";
                cin >> tgl;
                cin.ignore(10000, '\n');
                if (!validasiTanggal(tgl)) {
                    cout << "  [ERROR] Format tanggal tidak valid. Gunakan YYYY-MM-DD." << endl;
                }
            } while (!validasiTanggal(tgl));

            do {
                cout << "  Masukkan Jam (format HH:MM): ";
                cin >> jam;
                cin.ignore(10000, '\n');
                if (!validasiJam(jam)) {
                    cout << "  [ERROR] Format jam tidak valid. Gunakan HH:MM." << endl;
                }
            } while (!validasiJam(jam));

            tambahAntrian(semifinalisKalah1, semifinalisKalah2, tgl, jam, "Perebutan Juara ke-3");
            catatPertandingan(semifinalisKalah1, semifinalisKalah2, "Perebutan Juara ke-3");
            matchKetiga = true;

            cout << "Pertandingan Perebutan Juara ke-3 berhasil dijadwalkan!" << endl;
        }
    } else {
        kalah->tereleminasi = true;
        cout << kalah->nama << " tereliminasi." << endl;
    }

    cout << "\n" << pemenang->nama << " menang (" << skorA << "-" << skorB << ")!"
         << " Poin: " << pemenang->poin << endl;

    if (antrianKosong()) {
        int timMasihAktif = hitungTimAktif();
        if (semifinalisKalah1 != NULL && !semifinalisKalah1->tereleminasi) timMasihAktif++;
        if (semifinalisKalah2 != NULL && !semifinalisKalah2->tereleminasi) timMasihAktif++;

        if (timMasihAktif > 1) {
            cout << "\nSemua pertandingan ronde ini selesai." << endl;
            cout << "Tim aktif tersisa: " << hitungTimAktif() << endl;
            cout << "Admin: Gunakan menu 'Buat Jadwal Ronde Berikutnya' untuk lanjut." << endl;
        } else {
            cout << "\n=== TURNAMEN SELESAI! ===" << endl;
            cout << "Lihat Klasemen untuk melihat Juara 1, 2, dan 3." << endl;
        }
    }
}

// Fungsi buat jadwal ronde berikutnya
void buatJadwalBerikutnya() {
    if (!jadwalSudahDibuat) {
        cout << "Braket belum dibuat." << endl;
        return;
    }

    if (!antrianKosong()) {
        cout << "Masih ada pertandingan yang belum selesai di ronde ini." << endl;
        return;
    }

    // Kumpulkan tim yang masih aktif
    Tim **timAktif = new Tim*[MAX_TIM];
    int n = 0;
    Tim *curr = kepala;
    while (curr != NULL) {
        if (!curr->tereleminasi) {
            timAktif[n++] = curr;
        }
        curr = curr->berikutnya;
    }

    if (n < 2) {
        cout << "Tidak cukup tim aktif untuk ronde berikutnya." << endl;
        delete[] timAktif;
        return;
    }

    rondeSekarang++;

    string namaRonde;

    if (n == 4) {
        namaRonde  = "Semifinal";
    } else if (n == 2) {
        namaRonde  = "Final";
    } else {
        namaRonde  = "Ronde " + to_string(rondeSekarang);
    }

    cout << "\n=== JADWAL " << namaRonde << " ===" << endl;
    for (int i = 0; i < n / 2; i++) {
        cout << "\nMatch " << i + 1 << ": " << timAktif[i]->nama << " vs " << timAktif[n - 1 - i]->nama << endl;

        string tgl, jam;
        do {
            cout << "  Masukkan Tanggal (format YYYY-MM-DD): ";
            cin >> tgl;
            cin.ignore(10000, '\n');
            if (!validasiTanggal(tgl)) {
                cout << "  [ERROR] Format tanggal tidak valid. Gunakan YYYY-MM-DD." << endl;
            }
        } while (!validasiTanggal(tgl));

        do {
            cout << "  Masukkan Jam (format HH:MM): ";
            cin >> jam;
            cin.ignore(10000, '\n');
            if (!validasiJam(jam)) {
                cout << "  [ERROR] Format jam tidak valid. Gunakan HH:MM." << endl;
            }
        } while (!validasiJam(jam));

        tambahAntrian(timAktif[i], timAktif[n - 1 - i], tgl, jam, namaRonde);
        catatPertandingan(timAktif[i], timAktif[n - 1 - i], namaRonde);
    }

    cout << "\nJadwal " << namaRonde << " berhasil dibuat!" << endl;
    delete[] timAktif;
}
