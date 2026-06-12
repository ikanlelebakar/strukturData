/*
 * File: buat_jadwal.cpp
 * Deskripsi: Membuat jadwal pertandingan ronde pertama dan memasukkannya
 *            ke dalam antrian (Queue). Dipanggil hanya setelah pendaftaran
 *            ditutup admin dan jumlah tim adalah pangkat 2.
 *
 * Aturan jadwal:
 *   - Ronde 1        : Admin input manual tanggal mulai
 *   - Ronde berikutnya: +3 hari dari tanggal pertandingan terakhir ronde sebelumnya
 *   - Semifinal      : +4 hari dari tanggal pertandingan terakhir ronde sebelumnya
 *   - Juara ke-3     : Hari Final - 1
 *   - Final          : +5 hari dari tanggal pertandingan terakhir ronde sebelumnya
 */

#include <ctime>
#include <sstream>
#include <iomanip>

/*
 * isPowerOfTwo: Cek apakah n adalah pangkat 2
 */


/*
 * tambahHari: Tambahkan 'hari' hari ke string tanggal "YYYY-MM-DD".
 *             Return string tanggal baru.
 */
string tambahHari(const string& tanggal, int hari) {
    struct tm t = {};
    // Parse YYYY-MM-DD
    t.tm_year = stoi(tanggal.substr(0, 4)) - 1900;
    t.tm_mon  = stoi(tanggal.substr(5, 2)) - 1;
    t.tm_mday = stoi(tanggal.substr(8, 2));

    t.tm_mday += hari;
    mktime(&t);  // normalize (handle overflow hari/bulan)

    ostringstream oss;
    oss << setfill('0')
        << (t.tm_year + 1900) << "-"
        << setw(2) << (t.tm_mon + 1) << "-"
        << setw(2) << t.tm_mday;
    return oss.str();
}

/*
 * validasiTanggal: Return true jika format "YYYY-MM-DD" valid (tidak kosong & 10 char)
 */
bool validasiTanggal(const string& tgl) {
    if (tgl.size() != 10) return false;
    if (tgl[4] != '-' || tgl[7] != '-') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(tgl[i])) return false;
    }
    return true;
}

/*
 * buatJadwalPertandingan: Pasang seluruh tim aktif untuk ronde pertama
 *                         dan enqueue ke antrian pertandingan.
 */
void buatJadwalPertandingan() {
    // Prasyarat: pendaftaran harus sudah ditutup
    if (!pendaftaranDitutup) {
        cout << "[DITOLAK] Admin harus menutup pendaftaran terlebih dahulu." << endl;
        return;
    }

    // Prasyarat: harus ada tim
    if (jumlahTimAktif < 2) {
        cout << "[DITOLAK] Minimal 2 tim dibutuhkan untuk membuat jadwal." << endl;
        return;
    }

    // Prasyarat: jumlah tim harus pangkat 2
    if (!isPowerOfTwo(jumlahTimAktif)) {
        cout << "[DITOLAK] Jumlah tim (" << jumlahTimAktif << ") harus pangkat 2 (4, 8, 16...)." << endl;
        return;
    }

    // Prasyarat: braket belum pernah dibuat
    if (bracketSudahDibuat) {
        cout << "[INFO] Braket sudah pernah dibuat sebelumnya." << endl;
        return;
    }

    // Admin input tanggal mulai Ronde 1
    string tanggalMulai;
    do {
        cout << "Masukkan tanggal mulai Ronde 1 (format YYYY-MM-DD): ";
        cin >> tanggalMulai;
        cin.ignore(10000, '\n');
        if (!validasiTanggal(tanggalMulai)) {
            cout << "[ERROR] Format tanggal tidak valid. Gunakan YYYY-MM-DD." << endl;
        }
    } while (!validasiTanggal(tanggalMulai));

    // Kumpulkan semua tim aktif ke array sementara (untuk pairing)
    Tim** arrTim = new Tim*[MAX_TIM];
    int  n = 0;
    Tim* curr = headTim;
    while (curr != nullptr) {
        arrTim[n++] = curr;
        curr = curr->next;
    }

    // Tentukan label ronde: jika hanya 4 tim, langsung "Semifinal"
    string labelRonde = (n == 4) ? "Semifinal" : "Ronde 1";

    // Pasang tim: [0] vs [n-1], [1] vs [n-2], dst. (pairing head vs tail)
    // Setiap match berjeda 1 hari dari match sebelumnya
    cout << "\n=== JADWAL " << labelRonde << " ==="  << endl;
    for (int i = 0; i < n / 2; i++) {
        string tgl = tambahHari(tanggalMulai, i);  // +i hari per match
        pushAntrian(arrTim[i], arrTim[n - 1 - i], tgl, labelRonde);
        daftarkanMatch(arrTim[i], arrTim[n - 1 - i], labelRonde);
        cout << "  " << arrTim[i]->namaTim << " vs " << arrTim[n-1-i]->namaTim
             << " (" << tgl << ")" << endl;
    }

    // tanggalTerakhir = tanggal match terakhir ronde ini
    tanggalTerakhir    = tambahHari(tanggalMulai, n / 2 - 1);
    rondeSekarang      = 1;
    bracketSudahDibuat = true;

    cout << "[SUKSES] Jadwal " << labelRonde << " berhasil dibuat. Braket siap!" << endl;
    delete[] arrTim;
}
