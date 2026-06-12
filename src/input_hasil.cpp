/*
 * File: input_hasil.cpp
 * Deskripsi: Input hasil skor pertandingan, update poin, eliminasi tim yang kalah,
 *            dan handle logika khusus semifinal + perebutan juara ke-3.
 *
 * Aturan poin:
 *   - Tim yang menang mendapat +1 poin (jumlah kemenangan)
 *   - Tim yang kalah: isEliminated = true
 *
 * Logika semifinal & juara ke-3:
 *   - Saat ronde semifinal (tersisa 4 tim, match menghasilkan 2 pemenang):
 *     * Dua semifinalis yang kalah disimpan di semifinalisKalah1/2
 *     * Mereka BELUM di-eliminate sampai pertandingan juara ke-3 selesai
 *   - Setelah dua semifinal selesai, otomatis enqueue pertandingan juara ke-3
 *   - Setelah match juara ke-3 selesai, barulah keduanya di-eliminate
 */

/*
 * hitungTimAktif: Hitung berapa tim yang belum tereliminasi di linked list.
 */
int hitungTimAktif() {
    int count = 0;
    Tim* curr = headTim;
    while (curr != nullptr) {
        if (!curr->isEliminated) count++;
        curr = curr->next;
    }
    return count;
}

/*
 * inputSkorPertandingan: Proses pertandingan terdepan di antrian.
 */
void inputSkorPertandingan() {
    if (isAntrianKosong()) {
        if (!bracketSudahDibuat) {
            cout << "[INFO] Braket belum dibuat. Silakan buat jadwal terlebih dahulu." << endl;
        } else {
            cout << "[INFO] Tidak ada pertandingan yang tersisa. Turnamen selesai!" << endl;
        }
        return;
    }

    NodeAntrian* match = frontAntrian;
    Tim* timA = match->timA;
    Tim* timB = match->timB;

    cout << "\n=== INPUT HASIL PERTANDINGAN ===" << endl;
    cout << "Ronde    : " << match->ronde << endl;
    cout << "Tanggal  : " << match->tanggalTanding << endl;
    cout << string(40, '-') << endl;
    cout << "Tim A    : " << timA->namaTim << endl;
    cout << "Tim B    : " << timB->namaTim << endl;
    cout << string(40, '-') << endl;

    int skorA, skorB;
    bool inputValid = false;
    while (!inputValid) {
        cout << "Skor " << timA->namaTim << ": ";
        cin >> skorA;
        cout << "Skor " << timB->namaTim << ": ";
        cin >> skorB;
        cin.ignore(10000, '\n');

        if (skorA < 0 || skorB < 0) {
            cout << "[ERROR] Skor tidak boleh negatif." << endl;
        } else if (skorA == skorB) {
            cout << "[ERROR] Skor tidak boleh seri dalam sistem eliminasi. Masukkan ulang." << endl;
        } else {
            inputValid = true;
        }
    }

    Tim* pemenang = (skorA > skorB) ? timA : timB;
    Tim* kalah    = (skorA > skorB) ? timB : timA;

    bool iniMatchKetiga = matchKetiga;  // snapshot sebelum pop

    // Logika match perebutan juara ke-3
    if (iniMatchKetiga) {
        // Match ke-3 selesai: baru sekarang keduanya di-eliminate
        kalah->isEliminated    = true;
        pemenang->isEliminated = true; // eliminasi agar tidak masuk pool finalis
        pemenang->poin        += 1;
        matchKetiga            = false;
        updatePemenangMatch(timA, timB, pemenang);  // catat pemenang ke riwayat bracket

        cout << "\n[HASIL] " << pemenang->namaTim << " menang " << skorA
             << "-" << skorB << " dan meraih JUARA KE-3!" << endl;
        cout << "[ELIMINASI] " << kalah->namaTim << " tereliminasi." << endl;

        popAntrian();

        // Cek apakah final sudah ada di antrian
        if (!isAntrianKosong()) {
            cout << "[INFO] Pertandingan Final siap dimulai!" << endl;
        }
        return;
    }

    // Pertandingan normal (bukan match ketiga)
    pemenang->poin += 1;
    updatePemenangMatch(timA, timB, pemenang);  // catat pemenang ke riwayat bracket
    string tanggalMatch = match->tanggalTanding;
    string rondeMatch   = match->ronde;
    popAntrian();

    // Update tanggal terakhir untuk menghitung tanggal ronde berikutnya
    tanggalTerakhir = tanggalMatch;

    // Cek apakah ini pertandingan semifinal (tersisa 4 tim aktif sebelum match ini)

    // Logika deteksi semifinal: jika kalah adalah semifinalis
    // Semifinal terjadi ketika tersisa 4 tim dan match menghasilkan 2 finalis
    // Kita deteksi: jika setelah pop antrian masih ada match lagi di ronde yang sama
    // dan setelah match ini tersisa 3 tim (2 aktif + 1 yang akan kalah di match berikutnya)
    // Pendekatan sederhana: cek apakah frontAntrian->ronde == "Semifinal"
    bool iniSemifinal = (rondeMatch == "Semifinal");

    if (iniSemifinal) {
        // Semifinalis yang kalah belum di-eliminate
        if (semifinalisKalah1 == nullptr) {
            semifinalisKalah1 = kalah;
            cout << "[INFO] Semifinalis pertama yang kalah: " << kalah->namaTim
                 << " (menunggu pertandingan juara ke-3)" << endl;
        } else {
            semifinalisKalah2 = kalah;

            // Kedua semifinal selesai: buat pertandingan juara ke-3
            // Tanggal juara ke-3 = Hari Final - 1
            // Final = +5 hari dari tanggalTerakhir semifinal
            string tanggalFinal   = tambahHari(tanggalTerakhir, 5);
            string tanggalJuara3  = tambahHari(tanggalFinal, -1);

            pushAntrian(semifinalisKalah1, semifinalisKalah2, tanggalJuara3, "Perebutan Juara ke-3");
            daftarkanMatch(semifinalisKalah1, semifinalisKalah2, "Perebutan Juara ke-3");
            matchKetiga = true;

            // Enqueue Final setelah match ke-3 (akan diproses setelah match ke-3 selesai)
            // Final = +5 hari dari tanggal pertandingan semifinal terakhir
            // Cari dua pemenang semifinal untuk final
            // Pemenang sudah ada di antrian berikutnya (diatur oleh enqueue berikutnya)

            cout << "[INFO] Semifinalis kedua yang kalah: " << kalah->namaTim
                 << " (akan bertanding perebutan juara ke-3 pada " << tanggalJuara3 << ")" << endl;
            cout << "[INFO] Pertandingan Perebutan Juara ke-3 otomatis terjadwal!" << endl;
        }
    } else {
        // Match normal: langsung eliminate yang kalah
        kalah->isEliminated = true;
        cout << "[ELIMINASI] " << kalah->namaTim << " tereliminasi." << endl;
    }

    cout << "\n[HASIL] " << pemenang->namaTim << " menang (" << skorA << "-" << skorB << ")!"
         << " Poin: " << pemenang->poin << endl;



    // Deteksi jika antrian saat ini kosong: mungkin perlu enqueue ronde berikutnya
    // Logika: setelah ronde beres (antrian kosong tapi masih ada tim aktif > 1),
    // admin harus menjalankan buatJadwalBerikutnya (akan di-handle dari main.cpp)
    if (isAntrianKosong()) {
        int timMasihAktif = hitungTimAktif();
        // Tambah semifinalis yang belum di-eliminate ke hitungan jika ada
        if (semifinalisKalah1 != nullptr && !semifinalisKalah1->isEliminated) timMasihAktif++;
        if (semifinalisKalah2 != nullptr && !semifinalisKalah2->isEliminated) timMasihAktif++;

        if (timMasihAktif > 1) {
            cout << "\n[RONDE SELESAI] Semua pertandingan ronde ini selesai." << endl;
            cout << "[INFO] Tim aktif tersisa: " << hitungTimAktif() << endl;
            cout << "[INFO] Admin: Gunakan menu 'Buat Jadwal Ronde Berikutnya' untuk lanjut." << endl;
        } else {
            cout << "\n=== TURNAMEN SELESAI! ===" << endl;
            cout << "Lihat Klasemen untuk melihat Juara 1, 2, dan 3." << endl;
        }
    }
}

/*
 * buatJadwalBerikutnya: Enqueue pertandingan ronde berikutnya
 *                        berdasarkan pemenang ronde sebelumnya.
 *                        Dipanggil dari main setelah satu ronde selesai.
 */
void buatJadwalBerikutnya() {
    if (!bracketSudahDibuat) {
        cout << "[ERROR] Braket belum dibuat." << endl;
        return;
    }

    if (!isAntrianKosong()) {
        cout << "[INFO] Masih ada pertandingan yang belum selesai di ronde ini." << endl;
        return;
    }

    // Kumpulkan tim yang masih aktif (belum eliminate)
    Tim** timAktif = new Tim*[MAX_TIM];
    int  n = 0;
    Tim* curr = headTim;
    while (curr != nullptr) {
        if (!curr->isEliminated) {
            timAktif[n++] = curr;
        }
        curr = curr->next;
    }

    if (n < 2) {
        cout << "[INFO] Tidak cukup tim aktif untuk ronde berikutnya." << endl;
        return;
    }

    rondeSekarang++;

    // Tentukan nama ronde dan offset hari
    string namaRonde;
    int    offsetHari;

    if (n == 4) {
        namaRonde  = "Semifinal";
        offsetHari = 4;
    } else if (n == 2) {
        namaRonde  = "Final";
        offsetHari = 5;
    } else {
        namaRonde  = "Ronde " + to_string(rondeSekarang);
        offsetHari = 3;
    }

    string tanggalRonde = tambahHari(tanggalTerakhir, offsetHari);

    cout << "\n=== JADWAL " << namaRonde << " ===" << endl;
    for (int i = 0; i < n / 2; i++) {
        pushAntrian(timAktif[i], timAktif[n-1-i], tanggalRonde, namaRonde);
        daftarkanMatch(timAktif[i], timAktif[n-1-i], namaRonde);
        cout << "  " << timAktif[i]->namaTim << " vs " << timAktif[n-1-i]->namaTim
             << " (" << tanggalRonde << ")" << endl;
    }

    cout << "[SUKSES] Jadwal " << namaRonde << " berhasil dibuat!" << endl;
    delete[] timAktif;
}
