/*
 * File: test_clear_screen.cpp
 * Deskripsi: Test manual untuk memverifikasi fungsi clearScreen().
 *
 * TDD RED Phase:
 *   - File ini dikompilasi SEBELUM clearScreen() diimplementasi di utils.cpp
 *   - Akan gagal kompilasi (fungsi belum ada) — itulah "RED"
 *
 * Cara compile & jalankan:
 *   g++ src/test_clear_screen.cpp -o test_clear && ./test_clear
 *
 * Expected output setelah GREEN:
 *   [PASS] clearScreen() terpanggil tanpa crash di platform ini
 *   [PASS] clearScreen() bisa dipanggil berulang kali
 *   [PASS] clearScreen() berjalan dalam < 1 detik
 */

#include <iostream>
#include <string>
#include <chrono>
using namespace std;

// ================================================================
// INCLUDE: utils.cpp akan berisi clearScreen()
// Baris ini akan menyebabkan compile error di RED phase (belum ada)
// ================================================================
#include "utils.cpp"

// ================================================================
// Test helper sederhana
// ================================================================
int testsRun    = 0;
int testsPassed = 0;
int testsFailed = 0;

void expectTrue(bool kondisi, const string& namaTest) {
    testsRun++;
    if (kondisi) {
        testsPassed++;
        cout << "[PASS] " << namaTest << endl;
    } else {
        testsFailed++;
        cout << "[FAIL] " << namaTest << endl;
    }
}

// ================================================================
// TEST CASES
// ================================================================

/*
 * Test 1: clearScreen() harus bisa dipanggil tanpa crash.
 *         Ini test paling dasar — fungsi harus ada dan tidak throw.
 */
void test_clearScreen_tidak_crash() {
    bool tidakCrash = true;
    try {
        clearScreen();
    } catch (...) {
        tidakCrash = false;
    }
    expectTrue(tidakCrash, "clearScreen() terpanggil tanpa crash di platform ini");
}

/*
 * Test 2: clearScreen() harus bisa dipanggil berulang kali (idempotent).
 */
void test_clearScreen_bisa_dipanggil_berulang() {
    bool berhasil = true;
    try {
        clearScreen();
        clearScreen();
        clearScreen();
    } catch (...) {
        berhasil = false;
    }
    expectTrue(berhasil, "clearScreen() bisa dipanggil berulang kali");
}

/*
 * Test 3: clearScreen() harus selesai dalam < 1 detik (tidak blocking).
 */
void test_clearScreen_tidak_lambat() {
    auto mulai = chrono::steady_clock::now();
    clearScreen();
    auto selesai = chrono::steady_clock::now();

    auto durasiMs = chrono::duration_cast<chrono::milliseconds>(selesai - mulai).count();
    expectTrue(durasiMs < 1000, "clearScreen() berjalan dalam < 1 detik (aktual: "
               + to_string(durasiMs) + "ms)");
}

// ================================================================
// MAIN: Jalankan semua test
// ================================================================
int main() {
    cout << "=== TEST: clearScreen() ===" << endl;
    cout << string(40, '-') << endl;

    test_clearScreen_tidak_crash();
    test_clearScreen_bisa_dipanggil_berulang();
    test_clearScreen_tidak_lambat();

    cout << string(40, '-') << endl;
    cout << "Hasil: " << testsPassed << "/" << testsRun << " test passed";
    if (testsFailed > 0) {
        cout << " (" << testsFailed << " GAGAL)";
    }
    cout << endl;

    return (testsFailed > 0) ? 1 : 0;
}
