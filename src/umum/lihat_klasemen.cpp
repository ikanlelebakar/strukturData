// File: lihat_klasemen.cpp
// Deskripsi: Fungsi untuk menampilkan klasemen turnamen

// Fungsi tampilkan papan klasemen
void tampilKlasemen() {
    cout << "\n=== KLASEMEN TURNAMEN ===" << endl;

    if (kepala == NULL) {
        cout << "(Belum ada tim yang terdaftar)" << endl;
        return;
    }

    // Deteksi apakah turnamen sudah selesai
    bool turnamenSelesai = jadwalSudahDibuat && antrianKosong() && (hitungTimAktif() <= 1);

    // Struktur data sementara untuk salinan linked list (untuk diurutkan)
    struct NodeTemp {
        string nama;
        int poin;
        bool tereleminasi;
        NodeTemp *next;
    };

    NodeTemp *headTemp = NULL;
    NodeTemp *tailTemp = NULL;

    // Salin data ke list sementara
    Tim *curr = kepala;
    while (curr != NULL) {
        NodeTemp *baru = new NodeTemp;
        baru->nama = curr->nama;
        baru->poin = curr->poin;
        baru->tereleminasi = curr->tereleminasi;
        baru->next = NULL;

        if (headTemp == NULL) {
            headTemp = baru;
            tailTemp = baru;
        } else {
            tailTemp->next = baru;
            tailTemp = baru;
        }
        curr = curr->berikutnya;
    }

    // Urutkan list sementara berdasarkan poin descending (Bubble Sort)
    if (headTemp != NULL && headTemp->next != NULL) {
        bool swapped = true;
        while (swapped) {
            swapped = false;
            NodeTemp *c = headTemp;
            while (c->next != NULL) {
                if (c->poin < c->next->poin) {
                    swap(c->nama, c->next->nama);
                    swap(c->poin, c->next->poin);
                    swap(c->tereleminasi, c->next->tereleminasi);
                    swapped = true;
                }
                c = c->next;
            }
        }
    }

    // Cetak klasemen
    cout << left
         << setw(5)  << "No"
         << setw(20) << "Nama Tim"
         << setw(8)  << "Poin"
         << setw(15) << (turnamenSelesai ? "Peringkat" : "Status")
         << endl;
    cout << string(50, '-') << endl;

    int no = 1;
    NodeTemp *tCurr = headTemp;
    while (tCurr != NULL) {
        string statusStr = "";
        if (turnamenSelesai) {
            if (no == 1) {
                statusStr = "Juara 1";
            } else if (no == 2) {
                statusStr = "Juara 2";
            } else if (no == 3 && MAX_TIM >= 4) {
                statusStr = "Juara 3";
            } else if (no == 4 && MAX_TIM >= 4) {
                statusStr = "Juara 4";
            } else {
                statusStr = "Peringkat " + to_string(no);
            }
        } else {
            statusStr = tCurr->tereleminasi ? "Tereliminasi" : "Aktif";
        }

        cout << left
             << setw(5)  << no
             << setw(20) << tCurr->nama
             << setw(8)  << tCurr->poin
             << setw(15) << statusStr
             << endl;

        tCurr = tCurr->next;
        no++;
    }
    cout << string(50, '-') << endl;

    // Bebaskan memori list sementara
    NodeTemp *del = headTemp;
    while (del != NULL) {
        NodeTemp *tempNext = del->next;
        delete del;
        del = tempNext;
    }
}
