import unittest
import os
import sys
import subprocess

# Ensure the tests directory is in the import path
sys.path.append(os.path.dirname(os.path.abspath(__file__)))

from runner import CLIAppRunner

class TestTournament(unittest.TestCase):
    def setUp(self):
        self.success = False
        # Build binary if not exists
        if not os.path.exists("./sistem_turnamen"):
            subprocess.run(["g++", "src/main.cpp", "-o", "sistem_turnamen"], check=True)
        # verbose=True: echoes C++ CLI stream to the console
        # delay=0.4: adds 400ms delay between inputs for screen-clear readability
        self.runner = CLIAppRunner("./sistem_turnamen", verbose=True, delay=0.4)

    def tearDown(self):
        if hasattr(self, 'runner') and self.runner:
            self.runner.close()
            # If the test was not marked successful, print log for debugging
            if not getattr(self, 'success', False):
                print("\n=== RUNNER LOG ON FAILURE ===")
                print(self.runner.get_full_log())
                print("=============================")

    def test_admin_registration_and_validation(self):
        """Tests admin registration and input validation for MAX_TIM (must be power of 2, min 2)."""
        # Wait for admin username prompt
        out = self.runner.read_until("Username Admin: ")
        self.assertIn("REGISTRASI ADMINISTRATOR TURNAMEN", out)
        
        self.runner.write_line("admin")
        
        out = self.runner.read_until("Password Admin: ")
        self.runner.write_line("admin123")
        
        out = self.runner.read_until("Nama Turnamen : ")
        self.runner.write_line("Piala Rektor")
        
        # Test invalid MAX_TIM inputs:
        # 1. Inputting 5 (not power of 2)
        out = self.runner.read_until("Maksimal Tim (harus pangkat 2, min 2): ")
        self.runner.write_line("5")
        
        out = self.runner.read_until("Maksimal Tim (harus pangkat 2, min 2): ")
        self.assertIn("[ERROR]", out)
        
        # 2. Inputting 1 (less than 2)
        self.runner.write_line("1")
        
        out = self.runner.read_until("Maksimal Tim (harus pangkat 2, min 2): ")
        self.assertIn("[ERROR]", out)
        
        # 3. Inputting valid 4 (power of 2)
        self.runner.write_line("4")
        
        out = self.runner.read_until("Tekan ENTER untuk lanjut ke Menu Utama...")
        self.assertIn("[SUKSES] Akun Admin berhasil dibuat!", out)
        self.assertIn("Maksimal Tim : 4", out)
        
        # Advance to Main Menu
        self.runner.write_line("")
        
        out = self.runner.read_until("Pilihan: ")
        self.assertIn("1. Registrasi Tim", out)
        self.assertIn("2. Login Tim", out)
        self.assertIn("3. Login Admin", out)
        self.assertIn("0. Keluar Program", out)
        
        self.success = True

    def test_team_registration_and_validation(self):
        """Tests registering teams, duplicates rejection, invalid player count, and auto-closing registration."""
        # 1. Register Admin first
        self.register_admin("admin", "adminpwd", "Liga C++", "4")
        
        # Register Team 1
        self.register_team("Team Alpha", "alpha123", "5")
        
        # Try registering duplicate Team 1
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("1") # Choose Registration
        out = self.runner.read_until("Nama Tim  : ")
        self.runner.write_line("Team Alpha")
        out = self.runner.read_until("Pilihan: ") # Rejects immediately and returns to main menu
        self.assertIn("[DITOLAK] Nama tim \"Team Alpha\" sudah terdaftar", out)
        
        # Register Team 2 with invalid player count validation (e.g. 0 and 8)
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("1")
        out = self.runner.read_until("Nama Tim  : ")
        self.runner.write_line("Team Beta")
        out = self.runner.read_until("Password  : ")
        self.runner.write_line("beta123")
        
        out = self.runner.read_until("Jumlah Pemain (1-7): ")
        self.runner.write_line("8") # invalid
        out = self.runner.read_until("Jumlah Pemain (1-7): ")
        self.assertIn("[ERROR] Jumlah pemain harus antara 1 dan 7.", out)
        
        self.runner.write_line("0") # invalid
        out = self.runner.read_until("Jumlah Pemain (1-7): ")
        self.assertIn("[ERROR] Jumlah pemain harus antara 1 dan 7.", out)
        
        self.runner.write_line("6") # valid
        out = self.runner.read_until("Tekan ENTER untuk kembali ke Menu Utama...")
        self.assertIn("Tim \"Team Beta\" berhasil terdaftar!", out)
        self.runner.write_line("") # Press ENTER
        
        # ----------------------------------------------------
        # Admin Operations (Pre-bracket: Hapus Tim, Edit Tim, Lihat Daftar Tim)
        # ----------------------------------------------------
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("3") # Login Admin
        out = self.runner.read_until("Username: ")
        self.runner.write_line("admin")
        out = self.runner.read_until("Password: ")
        self.runner.write_line("adminpwd")
        
        # Select 1. Lihat Daftar Tim
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("1")
        out = self.runner.read_until("Tekan ENTER untuk lanjut...")
        self.assertIn("Team Alpha", out)
        self.assertIn("Team Beta", out)
        self.runner.write_line("") # Continue
        
        # Select 2. Edit Data Tim (Admin edits Team Alpha)
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("2")
        out = self.runner.read_until("Masukkan nama tim yang ingin diedit: ")
        self.runner.write_line("Team Alpha")
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("2") # Change Player Count
        out = self.runner.read_until("Jumlah Pemain Baru (1-7): ")
        self.runner.write_line("7")
        out = self.runner.read_until("Tekan ENTER untuk lanjut...")
        self.assertIn("[SUKSES] Jumlah pemain berhasil diubah menjadi 7.", out)
        self.runner.write_line("") # Continue
        
        # Select 3. Hapus Tim (Admin deletes Team Beta)
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("3")
        out = self.runner.read_until("Masukkan nama tim yang ingin dihapus: ")
        self.runner.write_line("Team Beta")
        out = self.runner.read_until("Tekan ENTER untuk lanjut...")
        self.assertIn("[SUKSES] Tim \"Team Beta\" berhasil dihapus.", out)
        self.runner.write_line("") # Continue
        
        # Select 1. Lihat Daftar Tim again to verify changes
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("1")
        out = self.runner.read_until("Tekan ENTER untuk lanjut...")
        self.assertNotIn("Team Beta", out)
        self.assertIn("Team Alpha", out)
        self.assertIn("Jumlah Pemain : 7", out)
        self.runner.write_line("") # Continue
        
        # Select 0. Logout Admin
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("0")
        
        # ----------------------------------------------------
        # Back in Main Menu, complete registration
        # ----------------------------------------------------
        # Register Team Beta again
        self.register_team("Team Beta", "beta123", "6")
        
        # Register Team 3 (Gamma)
        self.register_team("Team Gamma", "gamma123", "5")
        
        # Register Team 4 (Delta) - this should auto-close registration as quota 4 is met
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("1")
        out = self.runner.read_until("Nama Tim  : ")
        self.runner.write_line("Team Delta")
        out = self.runner.read_until("Password  : ")
        self.runner.write_line("delta123")
        out = self.runner.read_until("Jumlah Pemain (1-7): ")
        self.runner.write_line("5")
        
        out = self.runner.read_until("Tekan ENTER untuk kembali ke Menu Utama...")
        self.assertIn("Tim \"Team Delta\" berhasil terdaftar!", out)
        self.assertIn("Kuota tim sudah penuh. Pendaftaran otomatis ditutup!", out)
        self.runner.write_line("") # Press ENTER
        
        # Expecting menu options to change from Fase A to Fase B (No Registration option, Spectator added)
        out = self.runner.read_until("Pilihan: ")
        self.assertNotIn("Registrasi Tim", out)
        self.assertIn("2. Penonton", out)
        
        self.success = True

    def test_full_tournament_flow_4_teams(self):
        """Runs a complete tournament flow with 4 teams: Registration -> Semifinals -> Juara 3 -> Final -> Klasemen verification."""
        # 1. Setup Admin and 4 Teams
        self.register_admin("admin", "adminpwd", "Piala Emas", "4")
        self.register_team("Alpha", "a", "5")
        self.register_team("Beta", "b", "5")
        self.register_team("Gamma", "c", "5")
        self.register_team("Delta", "d", "5")
        
        # 2. Login Admin to Create Bracket
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("3") # Login Admin
        out = self.runner.read_until("Username: ")
        self.runner.write_line("admin")
        out = self.runner.read_until("Password: ")
        self.runner.write_line("adminpwd")
        
        out = self.runner.read_until("Pilihan: ")
        self.assertIn("2. Buat Jadwal Pertandingan", out)
        self.runner.write_line("2") # Buat Jadwal
        
        # Date validation check
        out = self.runner.read_until("Masukkan tanggal mulai Ronde 1 (format YYYY-MM-DD): ")
        self.runner.write_line("2026/06/15") # invalid format
        out = self.runner.read_until("Masukkan tanggal mulai Ronde 1 (format YYYY-MM-DD): ")
        self.assertIn("[ERROR] Format tanggal tidak valid", out)
        
        self.runner.write_line("2026-06-15") # valid format
        out = self.runner.read_until("Tekan ENTER untuk lanjut...")
        self.assertIn("Jadwal Semifinal berhasil dibuat. Braket siap!", out)
        self.runner.write_line("") # Continue
        
        # Logout Admin to verify schedules and brackets as Tim and Penonton
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("0")
        
        # ----------------------------------------------------
        # Verify Schedules & Brackets as Team
        # ----------------------------------------------------
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("1") # Login Tim
        out = self.runner.read_until("Username Tim: ")
        self.runner.write_line("Alpha")
        out = self.runner.read_until("Password Tim: ")
        self.runner.write_line("a")
        
        # Check Schedule
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("2")
        out = self.runner.read_until("Tekan ENTER untuk lanjut...")
        self.assertIn("Alpha vs Delta", out)
        self.assertIn("Beta vs Gamma", out)
        self.runner.write_line("")
        
        # Check Bracket
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("5")
        out = self.runner.read_until("Tekan ENTER untuk lanjut...")
        self.assertIn("BAGAN TURNAMEN", out)
        self.runner.write_line("")
        
        # Logout Tim
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("0")
        
        # ----------------------------------------------------
        # Verify Schedules & Brackets as Spectator
        # ----------------------------------------------------
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("2") # Penonton
        
        # Check Schedule
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("1")
        out = self.runner.read_until("Tekan ENTER untuk lanjut...")
        self.assertIn("Alpha vs Delta", out)
        self.runner.write_line("")
        
        # Check Bracket
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("2")
        out = self.runner.read_until("Tekan ENTER untuk lanjut...")
        self.assertIn("BAGAN TURNAMEN", out)
        self.runner.write_line("")
        
        # Exit Penonton
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("0")
        
        # ----------------------------------------------------
        # Login Admin and Play Tournament Matches
        # ----------------------------------------------------
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("3") # Login Admin
        out = self.runner.read_until("Username: ")
        self.runner.write_line("admin")
        out = self.runner.read_until("Password: ")
        self.runner.write_line("adminpwd")
        
        # 3. Input Semifinal Match 1 (Alpha vs Delta)
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("2") # Input Hasil
        
        # Test negative score validation
        out = self.runner.read_until("Skor Alpha: ")
        self.runner.write_line("-1") 
        out = self.runner.read_until("Skor Delta: ")
        self.runner.write_line("2")
        out = self.runner.read_until("Skor Alpha: ")
        self.assertIn("[ERROR] Skor tidak boleh negatif.", out)
        
        # Test tie score validation
        self.runner.write_line("3")
        out = self.runner.read_until("Skor Delta: ")
        self.runner.write_line("3")
        out = self.runner.read_until("Skor Alpha: ")
        self.assertIn("[ERROR] Skor tidak boleh seri dalam sistem eliminasi.", out)
        
        # Enter valid scores
        self.runner.write_line("3") # Alpha wins
        out = self.runner.read_until("Skor Delta: ")
        self.runner.write_line("1")
        
        out = self.runner.read_until("Tekan ENTER untuk lanjut...")
        self.assertIn("Alpha menang (3-1)!", out)
        self.assertIn("Semifinalis pertama yang kalah: Delta", out)
        self.runner.write_line("")
        
        # 4. Input Semifinal Match 2 (Beta vs Gamma)
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("2") # Input Hasil
        out = self.runner.read_until("Skor Beta: ")
        self.runner.write_line("1")
        out = self.runner.read_until("Skor Gamma: ")
        self.runner.write_line("4") # Gamma wins
        
        out = self.runner.read_until("Tekan ENTER untuk lanjut...")
        self.assertIn("Gamma menang", out)
        self.assertIn("Semifinalis kedua yang kalah: Beta", out)
        self.assertIn("Pertandingan Perebutan Juara ke-3 otomatis terjadwal!", out)
        self.runner.write_line("")
        
        # 5. Input Juara 3 (Delta vs Beta)
        # Note: Match 3 is scheduled automatically. Let's process it.
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("2") # Input Hasil
        out = self.runner.read_until("Skor Delta: ")
        self.runner.write_line("5")
        out = self.runner.read_until("Skor Beta: ")
        self.runner.write_line("2") # Delta wins 3rd place
        
        out = self.runner.read_until("Tekan ENTER untuk lanjut...")
        self.assertIn("Delta menang 5-2 dan meraih JUARA KE-3!", out)
        self.runner.write_line("")
        
        # 6. Admin creates schedule for Final
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("2") # Buat Jadwal Ronde Berikutnya
        out = self.runner.read_until("Tekan ENTER untuk lanjut...")
        self.assertIn("Jadwal Final berhasil dibuat!", out)
        self.runner.write_line("")
        
        # 7. Input Final (Alpha vs Gamma)
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("2") # Input Hasil
        out = self.runner.read_until("Skor Alpha: ")
        self.runner.write_line("10")
        out = self.runner.read_until("Skor Gamma: ")
        self.runner.write_line("8") # Alpha wins 1st place, Gamma 2nd
        
        out = self.runner.read_until("Tekan ENTER untuk lanjut...")
        self.assertIn("Alpha menang", out)
        self.assertIn("=== TURNAMEN SELESAI! ===", out)
        self.runner.write_line("")
        
        # 8. Verify Klasemen
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("2") # Lihat Klasemen
        out = self.runner.read_until("Tekan ENTER untuk lanjut...")
        self.assertIn("Alpha", out)
        self.assertIn("Gamma", out)
        self.assertIn("Delta", out)
        self.assertIn("Beta", out)
        self.runner.write_line("")
        
        # Logout Admin
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("0")
        out = self.runner.read_until("Pilihan: ") # Back to main menu
        self.runner.write_line("0") # Quit program
        
        self.success = True

    def test_team_and_spectator_role_access(self):
        """Tests that Teams can login and edit their own data/search opponents, and Spectators can see brackets/klasemen."""
        self.register_admin("admin", "pwd", "Rektor Cup", "4")
        self.register_team("Warriors", "war123", "5")
        self.register_team("Knights", "kni123", "5")
        self.register_team("Ninjas", "nin123", "5")
        self.register_team("Samurais", "sam123", "5")
        
        # Test 1: Team Login and edit own data
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("1") # Choose Login Tim (fase B)
        out = self.runner.read_until("Username Tim: ")
        self.runner.write_line("Warriors")
        out = self.runner.read_until("Password Tim: ")
        self.runner.write_line("war123")
        
        # In Team Menu
        out = self.runner.read_until("Pilihan: ")
        self.assertIn("MENU TIM: Warriors", out)
        self.runner.write_line("1") # Edit Data Tim Saya
        
        # In Edit Data Tim menu, choose 3. Ubah Password
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("3")
        
        out = self.runner.read_until("Password Baru: ")
        self.runner.write_line("war456")
        
        out = self.runner.read_until("Tekan ENTER untuk lanjut...")
        self.assertIn("[SUKSES] Password berhasil diubah.", out)
        self.runner.write_line("")
        
        # Back in Team Menu, choose Edit Data Tim Saya again
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("1")
        
        # In Edit Data Tim menu, choose 2. Ubah Jumlah Pemain
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("2")
        
        out = self.runner.read_until("Jumlah Pemain Baru (1-7): ")
        self.runner.write_line("7")
        
        out = self.runner.read_until("Tekan ENTER untuk lanjut...")
        self.assertIn("[SUKSES] Jumlah pemain berhasil diubah menjadi 7.", out)
        self.runner.write_line("")
        
        # Search Opponent
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("3") # Cari Profil Lawan
        out = self.runner.read_until("Masukkan nama tim lawan yang dicari: ")
        self.runner.write_line("Ninjas")
        out = self.runner.read_until("Tekan ENTER untuk lanjut...")
        self.assertIn("Nama Tim       : Ninjas", out)
        self.runner.write_line("")
        
        # Logout Team
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("0")
        
        # Test 2: Spectator Menu
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("2") # Penonton
        
        out = self.runner.read_until("Pilihan: ")
        self.assertIn("MENU PENONTON", out)
        self.runner.write_line("3") # Lihat Klasemen
        out = self.runner.read_until("Tekan ENTER untuk lanjut...")
        self.assertIn("Warriors", out)
        self.runner.write_line("")
        
        # Exit Spectator
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("0")
        
        # Exit program
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("0")
        
        self.success = True

    # --- Helper methods ---
    def register_admin(self, username, password, tournament_name, max_teams):
        out = self.runner.read_until("Username Admin: ")
        self.runner.write_line(username)
        out = self.runner.read_until("Password Admin: ")
        self.runner.write_line(password)
        out = self.runner.read_until("Nama Turnamen : ")
        self.runner.write_line(tournament_name)
        out = self.runner.read_until("Maksimal Tim (harus pangkat 2, min 2): ")
        self.runner.write_line(max_teams)
        out = self.runner.read_until("Tekan ENTER untuk lanjut ke Menu Utama...")
        self.runner.write_line("")

    def register_team(self, name, password, members):
        out = self.runner.read_until("Pilihan: ")
        self.runner.write_line("1") # Choose Registrasi Tim
        out = self.runner.read_until("Nama Tim  : ")
        self.runner.write_line(name)
        out = self.runner.read_until("Password  : ")
        self.runner.write_line(password)
        out = self.runner.read_until("Jumlah Pemain (1-7): ")
        self.runner.write_line(members)
        out = self.runner.read_until("Tekan ENTER untuk kembali ke Menu Utama...")
        self.runner.write_line("")

if __name__ == "__main__":
    unittest.main()
