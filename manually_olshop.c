#include <stdio.h>
#include <string.h>

int main() {
    // Deklarasi variabel untuk username dan password
    char username[20], password[20];
    
    // Username dan password yang valid (disimpan di dalam program)
    char validUsername[] = "admin";
    char validPassword[] = "1234";

    // Meminta input username dan password dari pengguna
    printf("Masukkan Username: ");
    scanf("%s", username);

    printf("Masukkan Password: ");
    scanf("%s", password);

    // Membandingkan input dengan username dan password yang valid
    if (strcmp(username, validUsername) == 0 && strcmp(password, validPassword) == 0) {
        printf("Login berhasil! Selamat datang, %s.\n", username);
    } else {
        printf("Login gagal! Username atau password salah.\n");
    }

    return 0;
}
