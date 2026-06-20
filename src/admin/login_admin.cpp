// File: login_admin.cpp
// Deskripsi: Fungsi login/autentikasi administrator

// Fungsi masuk admin
bool masukAdmin() {
    string username, password;

    tampilSubjudul("LOGIN ADMIN");
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == adminUsername && password == adminPassword) {
        pesanOK("Login admin berhasil. Selamat datang, Admin!");
        return true;
    }

    pesanError("Username atau password salah.");
    return false;
}
