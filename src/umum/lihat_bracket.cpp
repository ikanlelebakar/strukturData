// File: lihat_bracket.cpp
// Deskripsi: Fungsi untuk menampilkan bagan turnamen secara horizontal

#include <vector>
#include <map>

// Fungsi pembantu padding teks ke kiri
string left_pad_str(const string& s, int w) {
    if ((int)s.size() >= w) return s.substr(0, w);
    return s + string(w - (int)s.size(), ' ');
}

// Fungsi tampilkan bagan turnamen (bracket)
void tampilBracket() {
    cout << "\n=== BAGAN TURNAMEN (BRACKET) ===" << endl;

    if (!jadwalSudahDibuat) {
        cout << "(Bracket belum dibuat. Admin perlu menutup pendaftaran dan membuat jadwal)" << endl;
        return;
    }

    if (jumlahHasil == 0) {
        cout << "(Belum ada data match)" << endl;
        return;
    }

    cout << string(70, '=') << endl;

    // Kumpulkan ronde-ronde utama
    vector<string> urutanRonde;
    map<string, bool> sudahAda;
    for (int i = 0; i < jumlahHasil; i++) {
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

    // Tampilkan header ronde
    for (int ri = 0; ri < jumlahRondeUtama; ri++) {
        cout << left << setw(28) << rondeUtama[ri];
    }
    cout << endl;
    cout << string(jumlahRondeUtama * 28, '-') << endl;

    // Kumpulkan index match per ronde
    vector<vector<int>> matchPerRonde(jumlahRondeUtama);
    for (int i = 0; i < jumlahHasil; i++) {
        for (int ri = 0; ri < jumlahRondeUtama; ri++) {
            if (matchResults[i].ronde == rondeUtama[ri]) {
                matchPerRonde[ri].push_back(i);
            }
        }
    }

    int jumlahMatchR0 = (int)matchPerRonde[0].size();
    int totalBaris = jumlahMatchR0 * 4;

    const int LEBAR = 28;
    vector<vector<string>> grid(totalBaris, vector<string>(jumlahRondeUtama, string(LEBAR, ' ')));

    // Isi grid
    for (int ri = 0; ri < jumlahRondeUtama; ri++) {
        int jumlahMatchRi = (int)matchPerRonde[ri].size();
        if (jumlahMatchRi == 0) continue;

        int jarak = totalBaris / jumlahMatchRi;
        int offset = 1 << ri;

        for (int mi = 0; mi < jumlahMatchRi; mi++) {
            int idx = matchPerRonde[ri][mi];
            int barisCenter = mi * jarak + jarak / 2 - 1;
            int barisA = barisCenter - offset;
            int barisB = barisCenter + offset;

            Tim *ptrA = matchResults[idx].timA;
            Tim *ptrB = matchResults[idx].timB;
            Tim *ptrPem = matchResults[idx].pemenang;

            string namaA = ptrA ? ptrA->nama : "???";
            string namaB = ptrB ? ptrB->nama : "???";
            string statusA = (ptrA && ptrA->tereleminasi) ? "[X] " : "[O] ";
            string statusB = (ptrB && ptrB->tereleminasi) ? "[X] " : "[O] ";

            // Isi Tim A
            string selA = statusA + namaA;
            if ((int)selA.size() > LEBAR - 5) selA = selA.substr(0, LEBAR - 5);
            grid[barisA][ri] = left_pad_str(selA, LEBAR - 5) + " ---\\";

            // Isi Tim B
            string selB = statusB + namaB;
            if ((int)selB.size() > LEBAR - 5) selB = selB.substr(0, LEBAR - 5);
            grid[barisB][ri] = left_pad_str(selB, LEBAR - 5) + " ---/";

            // Isi konektor
            grid[barisCenter][ri] = string(LEBAR - 5, ' ') + "  |-->";

            // Tampilkan pemenang jika ini Final
            if (ri == jumlahRondeUtama - 1) {
                string labelJuara = ptrPem ? (ptrPem->nama + " (JUARA!)") : "???";
                grid[barisCenter][ri] = string(LEBAR - 5, ' ') + "  |--> " + labelJuara;
            }
        }
    }

    // Tampilkan grid
    for (int baris = 0; baris < totalBaris; baris++) {
        for (int ri = 0; ri < jumlahRondeUtama; ri++) {
            cout << grid[baris][ri];
        }
        cout << endl;
    }

    // Tampilkan Perebutan Juara ke-3
    if (adaJuara3) {
        cout << endl;
        cout << string(70, '-') << endl;
        cout << "Perebutan Juara ke-3:" << endl;
        for (int i = 0; i < jumlahHasil; i++) {
            if (matchResults[i].ronde == "Perebutan Juara ke-3") {
                string namaA = matchResults[i].timA ? matchResults[i].timA->nama : "???";
                string namaB = matchResults[i].timB ? matchResults[i].timB->nama : "???";
                string sA    = (matchResults[i].timA && matchResults[i].timA->tereleminasi) ? "[X] " : "[O] ";
                string sB    = (matchResults[i].timB && matchResults[i].timB->tereleminasi) ? "[X] " : "[O] ";
                string pem   = matchResults[i].pemenang
                               ? matchResults[i].pemenang->nama + " (JUARA KE-3!)"
                               : "??? (belum dimainkan)";
                cout << "  " << sA << namaA << " vs " << sB << namaB << endl;
                cout << "  Pemenang: " << pem << endl;
            }
        }
    }

    cout << string(70, '=') << endl;
    cout << "Keterangan: [O] = Aktif  |  [X] = Tereliminasi" << endl;

    if (!antrianKosong()) {
        cout << "\nPertandingan berikutnya: " << depanAntrian->timA->nama
             << " vs " << depanAntrian->timB->nama
             << " (" << depanAntrian->ronde << ")" << endl;
    } else {
        cout << "\nTurnamen selesai! Lihat klasemen untuk melihat juara." << endl;
    }
}
