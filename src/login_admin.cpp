/*
 * File: login_admin.cpp
 * Deskripsi: Autentikasi administrator.
 *            Username: "admin" | Password: "turnamen2026"
 */

/*
 * loginAdmin: Minta username + password, cocokkan dengan kredensial statis.
 *             Return true jika berhasil, false jika gagal/dibatalkan.
 */
bool loginAdmin() {
    string username, password;

    cout << "\n=== LOGIN ADMIN ===" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == "admin" && password == "turnamen2026") {
        cout << "[OK] Login admin berhasil. Selamat datang, Admin!" << endl;
        return true;
    }

    cout << "[GAGAL] Username atau password salah." << endl;
    return false;
}
