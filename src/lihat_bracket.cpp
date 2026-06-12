/*
 * File: lihat_bracket.cpp
 * Deskripsi: Menampilkan bracket turnamen multi-ronde secara horizontal (kiri ke kanan).
 *            Setiap ronde ditampilkan sebagai kolom, dengan nama pemenang jika sudah
 *            ada hasil, atau "???" jika belum dimainkan.
 *
 * Format output (contoh 4 tim):
 *
 *  === BAGAN TURNAMEN ===
 *  [Semifinal]              [Final]
 *  wkwk      ---\
 *                 |--> wkwk      ---\
 *  codex     ---/                    |--> wkwk  (JUARA!)
 *  opus      ---\                ---/
 *                 |--> ???
 *  gemini    ---/
 */

#include <vector>
#include <map>

/*
 * left_pad_str: kiri-ratakan string s dalam lebar w (padding dengan spasi kanan)
 */
string left_pad_str(const string& s, int w) {
    if ((int)s.size() >= w) return s.substr(0, w);
    return s + string(w - (int)s.size(), ' ');
}


/*
 * lihatBracketTree: tampilkan bracket multi-ronde horizontal berbasis matchResults[].
 */
void lihatBracketTree() {
    cout << "\n=== BAGAN TURNAMEN (BRACKET) ===" << endl;

    if (!bracketSudahDibuat) {
        cout << "(Bracket belum dibuat. Admin perlu menutup pendaftaran dan membuat jadwal)" << endl;
        return;
    }

    if (jumlahMatchResult == 0) {
        cout << "(Belum ada data match)" << endl;
        return;
    }

    cout << string(70, '=') << endl;

    // 1. Kumpulkan ronde-ronde utama
    vector<string> urutanRonde;
    map<string, bool> sudahAda;
    for (int i = 0; i < jumlahMatchResult; i++) {
        string r = matchResults[i].ronde;
        if (sudahAda.find(r) == sudahAda.end()) {
            urutanRonde.push_back(r);
            sudahAda[r] = true;
        }
    }

    vector<string> rondeUtama;
    bool adaJuara3 = false;
    for (auto& r : urutanRonde) {
        if (r == "Perebutan Juara ke-3") {
            adaJuara3 = true;
        } else {
            rondeUtama.push_back(r);
        }
    }

    int jumlahRondeUtama = (int)rondeUtama.size();

    // Tampilkan header
    for (int ri = 0; ri < jumlahRondeUtama; ri++) {
        cout << left << setw(28) << rondeUtama[ri];
    }
    cout << endl;
    cout << string(jumlahRondeUtama * 28, '-') << endl;

    // Kumpulkan match index per ronde
    vector<vector<int>> matchPerRonde(jumlahRondeUtama);
    for (int i = 0; i < jumlahMatchResult; i++) {
        for (int ri = 0; ri < jumlahRondeUtama; ri++) {
            if (matchResults[i].ronde == rondeUtama[ri]) {
                matchPerRonde[ri].push_back(i);
            }
        }
    }

    // totalBaris ditentukan dari jumlah match di ronde pertama
    int jumlahMatchR0 = (int)matchPerRonde[0].size();
    int totalBaris    = jumlahMatchR0 * 4;

    const int LEBAR = 28;
    vector<vector<string>> grid(totalBaris, vector<string>(jumlahRondeUtama, string(LEBAR, ' ')));

    // Isi grid ronde demi ronde
    for (int ri = 0; ri < jumlahRondeUtama; ri++) {
        int jumlahMatchRi = (int)matchPerRonde[ri].size();
        if (jumlahMatchRi == 0) continue;

        int jarak = totalBaris / jumlahMatchRi;
        int offset = 1 << ri; // 2^ri

        for (int mi = 0; mi < jumlahMatchRi; mi++) {
            int idx = matchPerRonde[ri][mi];
            int barisCenter = mi * jarak + jarak / 2 - 1;
            int barisA = barisCenter - offset;
            int barisB = barisCenter + offset;

            Tim* ptrA = matchResults[idx].timA;
            Tim* ptrB = matchResults[idx].timB;
            Tim* ptrPem = matchResults[idx].pemenang;

            string namaA   = ptrA ? ptrA->namaTim : "???";
            string namaB   = ptrB ? ptrB->namaTim : "???";
            string statusA = (ptrA && ptrA->isEliminated) ? "[X] " : "[O] ";
            string statusB = (ptrB && ptrB->isEliminated) ? "[X] " : "[O] ";

            // Isi Tim A
            string selA = statusA + namaA;
            if ((int)selA.size() > LEBAR - 5) selA = selA.substr(0, LEBAR - 5);
            grid[barisA][ri] = left_pad_str(selA, LEBAR - 5) + " ---\\";

            // Isi Tim B
            string selB = statusB + namaB;
            if ((int)selB.size() > LEBAR - 5) selB = selB.substr(0, LEBAR - 5);
            grid[barisB][ri] = left_pad_str(selB, LEBAR - 5) + " ---/";

            // Isi Konektor di Ronde Saat Ini
            grid[barisCenter][ri] = string(LEBAR - 5, ' ') + "  |-->";

            // Jika ini ronde terakhir (Final), tampilkan pemenang juara di baris center kolom terakhir
            if (ri == jumlahRondeUtama - 1) {
                string labelJuara = ptrPem ? (ptrPem->namaTim + " (JUARA!)") : "???";
                grid[barisCenter][ri] = string(LEBAR - 5, ' ') + "  |--> " + labelJuara;
            }
        }
    }

    // Cetak grid
    for (int baris = 0; baris < totalBaris; baris++) {
        for (int ri = 0; ri < jumlahRondeUtama; ri++) {
            cout << grid[baris][ri];
        }
        cout << endl;
    }

    // Tampilkan Perebutan Juara ke-3 jika ada
    if (adaJuara3) {
        cout << endl;
        cout << string(70, '-') << endl;
        cout << "Perebutan Juara ke-3:" << endl;
        for (int i = 0; i < jumlahMatchResult; i++) {
            if (matchResults[i].ronde == "Perebutan Juara ke-3") {
                string namaA = matchResults[i].timA ? matchResults[i].timA->namaTim : "???";
                string namaB = matchResults[i].timB ? matchResults[i].timB->namaTim : "???";
                string sA    = (matchResults[i].timA && matchResults[i].timA->isEliminated) ? "[X] " : "[O] ";
                string sB    = (matchResults[i].timB && matchResults[i].timB->isEliminated) ? "[X] " : "[O] ";
                string pem   = matchResults[i].pemenang
                               ? matchResults[i].pemenang->namaTim + " (JUARA KE-3!)"
                               : "??? (belum dimainkan)";
                cout << "  " << sA << namaA << " vs " << sB << namaB << endl;
                cout << "  Pemenang: " << pem << endl;
            }
        }
    }

    cout << string(70, '=') << endl;
    cout << "Keterangan: [O] = Aktif  |  [X] = Tereliminasi" << endl;

    if (!isAntrianKosong()) {
        cout << "\nPertandingan berikutnya: " << frontAntrian->timA->namaTim
             << " vs " << frontAntrian->timB->namaTim
             << " (" << frontAntrian->ronde << ")" << endl;
    } else {
        cout << "\nTurnamen selesai! Lihat klasemen untuk melihat juara." << endl;
    }
}
