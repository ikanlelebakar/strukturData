// File: login_admin.cpp
// Deskripsi: Fungsi login/autentikasi administrator

// Fungsi masuk admin
bool masukAdmin() {
    string username, password;

    cout << "\n=== LOGIN ADMIN ===" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == adminUsername && password == adminPassword) {
        cout << "Login admin berhasil. Selamat datang, Admin!" << endl;
        return true;
    }

    cout << "Username atau password salah." << endl;
    return false;
}
