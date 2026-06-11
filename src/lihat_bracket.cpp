/*
 * File: lihat_bracket.cpp
 * Deskripsi: Menampilkan representasi teks bracket/bagan turnamen.
 *            Menampilkan seluruh tim yang terdaftar dalam format bracket
 *            berdasarkan urutan pairing yang dibuat saat buat_jadwal.
 */

/*
 * lihatBracketTree: Tampilkan bracket dalam format teks CLI.
 *                   Menggunakan simbol garis untuk menunjukkan pairing.
 */
void lihatBracketTree() {
    cout << "\n=== BAGAN TURNAMEN (BRACKET) ===" << endl;

    if (!bracketSudahDibuat) {
        cout << "(Bracket belum dibuat. Admin perlu menutup pendaftaran dan membuat jadwal)" << endl;
        return;
    }

    // Kumpulkan semua tim ke array untuk menampilkan bracket
    Tim** arrTim = new Tim*[MAX_TIM];
    int  n = 0;
    Tim* curr = headTim;
    while (curr != nullptr) {
        arrTim[n++] = curr;
        curr = curr->next;
    }

    cout << string(60, '=') << endl;

    // Tampilkan pairing bracket awal (head vs tail)
    for (int i = 0; i < n / 2; i++) {
        string statusA = arrTim[i]->isEliminated         ? "[X]" : "[O]";
        string statusB = arrTim[n-1-i]->isEliminated     ? "[X]" : "[O]";

        // Menampilkan pasangan dalam format bracket teks
        cout << "  " << left << setw(20) << (statusA + " " + arrTim[i]->namaTim)
             << " ---\\" << endl;
        cout << "  " << string(24, ' ') << "    |---> [Pemenang]" << endl;
        cout << "  " << left << setw(20) << (statusB + " " + arrTim[n-1-i]->namaTim)
             << " ---/" << endl;
        if (i < n / 2 - 1) cout << endl;
    }

    cout << string(60, '=') << endl;
    cout << "Keterangan: [O] = Aktif  |  [X] = Tereliminasi" << endl;

    // Tampilkan info ronde saat ini
    if (!isAntrianKosong()) {
        cout << "\nPertandingan berikutnya: " << frontAntrian->timA->namaTim
             << " vs " << frontAntrian->timB->namaTim
             << " (" << frontAntrian->ronde << ")" << endl;
    } else {
        cout << "\nTurnamen selesai! Lihat klasemen untuk melihat juara." << endl;
    }

    delete[] arrTim;
}
