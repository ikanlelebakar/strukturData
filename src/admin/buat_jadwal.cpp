// File: buat_jadwal.cpp
// Deskripsi: Fungsi untuk membuat jadwal pertandingan ronde pertama

#include <ctime>
#include <sstream>
#include <iomanip>

// Fungsi validasi format jam HH:MM
bool validasiJam(const string& jm) {
    if (jm.size() != 5) return false;
    if (jm[2] != ':') return false;
    for (int i = 0; i < 5; i++) {
        if (i == 2) continue;
        if (!isdigit(jm[i])) return false;
    }
    int jamVal = stoi(jm.substr(0, 2));
    int menitVal = stoi(jm.substr(3, 2));
    if (jamVal < 0 || jamVal > 23) return false;
    if (menitVal < 0 || menitVal > 59) return false;
    return true;
}

// Fungsi validasi format tanggal YYYY-MM-DD
bool validasiTanggal(const string& tgl) {
    if (tgl.size() != 10) return false;
    if (tgl[4] != '-' || tgl[7] != '-') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(tgl[i])) return false;
    }
    return true;
}

// Fungsi buat jadwal pertandingan Ronde 1
void buatJadwal() {
    if (!pendaftaranDitutup) {
        cout << "Admin harus menutup pendaftaran terlebih dahulu." << endl;
        return;
    }

    if (jumlahTim < 2) {
        cout << "Minimal 2 tim dibutuhkan untuk membuat jadwal." << endl;
        return;
    }

    if (!adalahPangkatDua(jumlahTim)) {
        cout << "Jumlah tim (" << jumlahTim << ") harus pangkat 2 (4, 8, 16...)." << endl;
        return;
    }

    if (jadwalSudahDibuat) {
        cout << "Braket sudah pernah dibuat sebelumnya." << endl;
        return;
    }

    // Kumpulkan tim ke array sementara untuk pairing
    Tim **arrTim = new Tim*[MAX_TIM];
    int n = 0;
    Tim *curr = kepala;
    while (curr != NULL) {
        arrTim[n++] = curr;
        curr = curr->berikutnya;
    }

    string labelRonde = (n == 4) ? "Semifinal" : "Ronde 1";

    cout << "\n=== JADWAL " << labelRonde << " ==="  << endl;
    for (int i = 0; i < n / 2; i++) {
        cout << "\nMatch " << i + 1 << ": " << arrTim[i]->nama << " vs " << arrTim[n - 1 - i]->nama << endl;

        string tgl, jam;
        do {
            cout << "  Masukkan Tanggal (format YYYY-MM-DD): ";
            cin >> tgl;
            cin.ignore(10000, '\n');
            if (!validasiTanggal(tgl)) {
                cout << "  [ERROR] Format tanggal tidak valid. Gunakan YYYY-MM-DD." << endl;
            }
        } while (!validasiTanggal(tgl));

        do {
            cout << "  Masukkan Jam (format HH:MM): ";
            cin >> jam;
            cin.ignore(10000, '\n');
            if (!validasiJam(jam)) {
                cout << "  [ERROR] Format jam tidak valid. Gunakan HH:MM." << endl;
            }
        } while (!validasiJam(jam));

        tambahAntrian(arrTim[i], arrTim[n - 1 - i], tgl, jam, labelRonde);
        catatPertandingan(arrTim[i], arrTim[n - 1 - i], labelRonde);
    }

    rondeSekarang = 1;
    jadwalSudahDibuat = true;

    cout << "\nJadwal " << labelRonde << " berhasil dibuat. Braket siap!" << endl;
    delete[] arrTim;
}
