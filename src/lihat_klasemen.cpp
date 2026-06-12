/*
 * File: lihat_klasemen.cpp
 * Deskripsi: Menampilkan papan klasemen berdasarkan poin (descending).
 *            Memanggil urutkanKlasemen() dari search_sort.cpp terlebih dahulu.
 */

/*
 * lihatKlasemen: Sort linked list by poin descending, lalu tampilkan tabel.
 */
void lihatKlasemen() {
    cout << "\n=== KLASEMEN TURNAMEN ===" << endl;

    if (headTim == nullptr) {
        cout << "(Belum ada tim yang terdaftar)" << endl;
        return;
    }

    // Deteksi apakah turnamen sudah selesai secara penuh
    bool turnamenSelesai = bracketSudahDibuat && isAntrianKosong() && (hitungTimAktif() <= 1);

    // Buat struct temporary untuk menampung salinan data tim
    struct NodeTemp {
        string namaTim;
        int poin;
        bool isEliminated;
        NodeTemp* next;
    };

    NodeTemp* headTemp = nullptr;
    NodeTemp* tailTemp = nullptr;

    // Salin data dari linked list asli
    Tim* curr = headTim;
    while (curr != nullptr) {
        NodeTemp* baru = new NodeTemp;
        baru->namaTim = curr->namaTim;
        baru->poin = curr->poin;
        baru->isEliminated = curr->isEliminated;
        baru->next = nullptr;

        if (headTemp == nullptr) {
            headTemp = baru;
            tailTemp = baru;
        } else {
            tailTemp->next = baru;
            tailTemp = baru;
        }
        curr = curr->next;
    }

    // Urutkan salinan sementara (bubble sort descending berdasarkan poin)
    if (headTemp != nullptr && headTemp->next != nullptr) {
        bool swapped = true;
        while (swapped) {
            swapped = false;
            NodeTemp* c = headTemp;
            while (c->next != nullptr) {
                if (c->poin < c->next->poin) {
                    swap(c->namaTim,      c->next->namaTim);
                    swap(c->poin,         c->next->poin);
                    swap(c->isEliminated, c->next->isEliminated);
                    swapped = true;
                }
                c = c->next;
            }
        }
    }

    // Header tabel
    cout << left
         << setw(5)  << "No"
         << setw(20) << "Nama Tim"
         << setw(8)  << "Poin"
         << setw(15) << (turnamenSelesai ? "Peringkat" : "Status")
         << endl;
    cout << string(50, '-') << endl;

    int no = 1;
    NodeTemp* tCurr = headTemp;
    while (tCurr != nullptr) {
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
            statusStr = tCurr->isEliminated ? "Tereliminasi" : "Aktif";
        }

        cout << left
             << setw(5)  << no
             << setw(20) << tCurr->namaTim
             << setw(8)  << tCurr->poin
             << setw(15) << statusStr
             << endl;

        tCurr = tCurr->next;
        no++;
    }
    cout << string(50, '-') << endl;

    // Bebaskan memori linked list salinan sementara
    NodeTemp* del = headTemp;
    while (del != nullptr) {
        NodeTemp* tempNext = del->next;
        delete del;
        del = tempNext;
    }
}
