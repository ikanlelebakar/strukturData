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
            pesanError("Braket belum dibuat. Silakan buat jadwal terlebih dahulu.");
        } else {
            pesanInfo("Tidak ada pertandingan yang tersisa. Turnamen selesai!");
        }
        return;
    }

    NodeAntrian *match = depanAntrian;
    Tim *timA = match->timA;
    Tim *timB = match->timB;

    tampilSubjudul("INPUT HASIL PERTANDINGAN");
    cout << "  Ronde    : " << match->ronde << endl;
    cout << "  Tanggal  : " << match->tanggalTanding << endl;
    tampilMenuBottom();
    cout << "  Tim A    : " << timA->nama << endl;
    cout << "  Tim B    : " << timB->nama << endl;
    tampilMenuBottom();

    int skorA, skorB;
    bool inputValid = false;
    while (!inputValid) {
        cout << "Skor " << timA->nama << ": ";
        skorA = ambilInputInt();
        cout << "Skor " << timB->nama << ": ";
        skorB = ambilInputInt();

        if (skorA < 0 || skorB < 0) {
            pesanError("Skor tidak boleh negatif.");
        } else if (skorA > 3 || skorB > 3) {
            pesanError("Skor tidak boleh lebih dari 3.");
        } else if (skorA == skorB) {
            pesanError("Skor tidak boleh seri dalam sistem eliminasi. Masukkan ulang.");
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

        pesanOK(pemenang->nama + " menang " + to_string(skorA) + "-" + to_string(skorB) + " dan meraih JUARA KE-3!");
        pesanInfo(kalah->nama + " tereliminasi.");

        hapusAntrian();

        if (!antrianKosong()) {
            pesanOK("Pertandingan Final siap dimulai!");
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
            pesanInfo("Semifinalis pertama yang kalah: " + kalah->nama + " (menunggu pertandingan juara ke-3)");
        } else {
            semifinalisKalah2 = kalah;

            // Buat pertandingan juara ke-3
            tampilSubjudul("PENJADWALAN PEREBUTAN JUARA KE-3");
            cout << "  " << semifinalisKalah1->nama << " vs " << semifinalisKalah2->nama << endl;
            tampilMenuBottom();
            
            string tgl, jam;
            do {
                cout << "  Masukkan Tanggal (format YYYY-MM-DD): ";
                cin >> tgl;
                cin.ignore(10000, '\n');
                if (!validasiTanggal(tgl)) {
                    pesanError("Format tanggal tidak valid. Gunakan YYYY-MM-DD.");
                }
            } while (!validasiTanggal(tgl));

            do {
                cout << "  Masukkan Jam (format HH:MM): ";
                cin >> jam;
                cin.ignore(10000, '\n');
                if (!validasiJam(jam)) {
                    pesanError("Format jam tidak valid. Gunakan HH:MM.");
                }
            } while (!validasiJam(jam));

            tambahAntrian(semifinalisKalah1, semifinalisKalah2, tgl, jam, "Perebutan Juara ke-3");
            catatPertandingan(semifinalisKalah1, semifinalisKalah2, "Perebutan Juara ke-3");
            matchKetiga = true;

            pesanOK("Pertandingan Perebutan Juara ke-3 berhasil dijadwalkan!");
        }
    } else {
        kalah->tereleminasi = true;
        pesanInfo(kalah->nama + " tereliminasi.");
    }

    pesanOK(pemenang->nama + " menang (" + to_string(skorA) + "-" + to_string(skorB) + ")! Poin: " + to_string(pemenang->poin));

    if (antrianKosong()) {
        int timMasihAktif = hitungTimAktif();
        if (semifinalisKalah1 != NULL && !semifinalisKalah1->tereleminasi) timMasihAktif++;
        if (semifinalisKalah2 != NULL && !semifinalisKalah2->tereleminasi) timMasihAktif++;

        if (timMasihAktif > 1) {
            pesanOK("Semua pertandingan ronde ini selesai.");
            cout << "  Tim aktif tersisa: " << hitungTimAktif() << endl;
            pesanInfo("Admin: Gunakan menu 'Buat Jadwal Ronde Berikutnya' untuk lanjut.");
        } else {
            tampilSubjudul("TURNAMEN SELESAI!");
            pesanOK("Lihat Klasemen untuk melihat Juara 1, 2, dan 3.");
        }
    }
}

// Fungsi buat jadwal ronde berikutnya
void buatJadwalBerikutnya() {
    if (!jadwalSudahDibuat) {
        pesanError("Braket belum dibuat.");
        return;
    }

    if (!antrianKosong()) {
        pesanWarning("Masih ada pertandingan yang belum selesai di ronde ini.");
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
        pesanError("Tidak cukup tim aktif untuk ronde berikutnya.");
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

    tampilSubjudul("JADWAL " + namaRonde);
    for (int i = 0; i < n / 2; i++) {
        tampilSubjudul("MATCH " + to_string(i + 1) + ": " + timAktif[i]->nama + " vs " + timAktif[n - 1 - i]->nama);

        string tgl, jam;
        do {
            cout << "  Masukkan Tanggal (format YYYY-MM-DD): ";
            cin >> tgl;
            cin.ignore(10000, '\n');
            if (!validasiTanggal(tgl)) {
                pesanError("Format tanggal tidak valid. Gunakan YYYY-MM-DD.");
            }
        } while (!validasiTanggal(tgl));

        do {
            cout << "  Masukkan Jam (format HH:MM): ";
            cin >> jam;
            cin.ignore(10000, '\n');
            if (!validasiJam(jam)) {
                pesanError("Format jam tidak valid. Gunakan HH:MM.");
            }
        } while (!validasiJam(jam));

        tambahAntrian(timAktif[i], timAktif[n - 1 - i], tgl, jam, namaRonde);
        catatPertandingan(timAktif[i], timAktif[n - 1 - i], namaRonde);
    }

    pesanOK("Jadwal " + namaRonde + " berhasil dibuat!");
    delete[] timAktif;
}
