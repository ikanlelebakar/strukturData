/*
 * File: search_sort.cpp
 * Deskripsi: Fungsi utilitas pencarian linear dan pengurutan
 *            klasemen berdasarkan poin (linked list).
 */

/*
 * cariTim: Linear search pada linked list, return pointer ke node Tim
 *           yang namaTim-nya cocok, atau nullptr jika tidak ditemukan.
 */
Tim* cariTim(const string& namaTimCari) {
    Tim* curr = headTim;
    while (curr != nullptr) {
        if (curr->namaTim == namaTimCari) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

/*
 * urutkanKlasemen: Bubble sort linked list descending berdasarkan poin.
 *                  Swap hanya nilai data (bukan pointer), sehingga
 *                  struktur linked list tetap utuh.
 */
void urutkanKlasemen() {
    if (headTim == nullptr || headTim->next == nullptr) return;

    bool swapped = true;
    while (swapped) {
        swapped  = false;
        Tim* curr = headTim;
        while (curr->next != nullptr) {
            if (curr->poin < curr->next->poin) {
                // Swap data (bukan pointer)
                swap(curr->namaTim,      curr->next->namaTim);
                swap(curr->password,     curr->next->password);
                swap(curr->jumlahPemain, curr->next->jumlahPemain);
                swap(curr->poin,         curr->next->poin);
                swap(curr->isEliminated, curr->next->isEliminated);
                swapped = true;
            }
            curr = curr->next;
        }
    }
}
