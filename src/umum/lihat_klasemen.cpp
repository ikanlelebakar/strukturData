// File: lihat_klasemen.cpp
// Deskripsi: Fungsi untuk menampilkan klasemen turnamen

// Fungsi tampilkan papan klasemen
void tampilKlasemen() {
    tampilSubjudul("KLASEMEN TURNAMEN");

    if (kepala == NULL) {
        pesanInfo("Belum ada tim yang terdaftar");
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
    vector<int> lebar = {6, 34, 10, 25};
    vector<char> alinyemen = {'C', 'L', 'C', 'L'};
    
    tampilGarisTabel(lebar, 'A');
    string headerStatus = turnamenSelesai ? "Peringkat" : "Status";
    tampilBarisTabel({"No", "Nama Tim", "Poin", headerStatus}, lebar, {'C', 'C', 'C', 'C'});
    tampilGarisTabel(lebar, 'T');

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

        tampilBarisTabel({to_string(no), tCurr->nama, to_string(tCurr->poin), statusStr}, lebar, alinyemen);

        tCurr = tCurr->next;
        no++;
    }
    tampilGarisTabel(lebar, 'B');

    // Bebaskan memori list sementara
    NodeTemp *del = headTemp;
    while (del != NULL) {
        NodeTemp *tempNext = del->next;
        delete del;
        del = tempNext;
    }
}
