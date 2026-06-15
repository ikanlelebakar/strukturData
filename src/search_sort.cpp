// File: search_sort.cpp
// Deskripsi: Fungsi utilitas pencarian linear dan pengurutan tim

// Fungsi untuk mencari tim berdasarkan nama (Linear Search)
Tim *cariTim(const string& namaTimCari) {
    Tim *curr = kepala;
    while (curr != NULL) {
        if (curr->nama == namaTimCari) {
            return curr;
        }
        curr = curr->berikutnya;
    }
    return NULL;
}

// Fungsi untuk mengurutkan klasemen tim berdasarkan poin (Bubble Sort)
void urutkanKlasemen() {
    if (kepala == NULL || kepala->berikutnya == NULL) return;

    bool swapped = true;
    while (swapped) {
        swapped = false;
        Tim *curr = kepala;
        while (curr->berikutnya != NULL) {
            if (curr->poin < curr->berikutnya->poin) {
                // Swap data tim (bukan pointernya)
                swap(curr->nama, curr->berikutnya->nama);
                swap(curr->password, curr->berikutnya->password);
                swap(curr->jumlahPemain, curr->berikutnya->jumlahPemain);
                swap(curr->poin, curr->berikutnya->poin);
                swap(curr->tereleminasi, curr->berikutnya->tereleminasi);
                swapped = true;
            }
            curr = curr->berikutnya;
        }
    }
}
