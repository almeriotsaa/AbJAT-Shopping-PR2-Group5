#include <conio.h>
#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 5
#define MAX_CART 10
#define DISCOUNT_THRESHOLD 10000000 // Diskon diberikan jika belanja di atas Rp 10.000.000
#define DISCOUNT_RATE 0.10          // Diskon 10%

// Struktur untuk menyimpan informasi produk
struct Product {
    char name[30];
    float price;
    int stock;
};

// Fungsi untuk memformat angka menjadi string dalam format Rupiah
void formatRupiah(float amount, char *formattedAmount) {
    char temp[50];
    sprintf(temp, "%.0f", amount);  // Mengonversi float ke string tanpa desimal

    int len = strlen(temp);
    int insertPosition = len % 3;
    int count = 0;
    int j = 0;

    // Menambahkan "Rp " di awal
    formattedAmount[j++] = 'R';
    formattedAmount[j++] = 'p';
    formattedAmount[j++] = ' ';

    // Menambahkan karakter ke string yang diformat
    for (int i = 0; i < len; i++) {
        if (i != 0 && (i - insertPosition) % 3 == 0) {
            formattedAmount[j++] = '.';  // Menambahkan titik setiap 3 digit
        }
        formattedAmount[j++] = temp[i];
    }

    formattedAmount[j] = '\0';  // Menutup string dengan null character
}

// Fungsi untuk menampilkan daftar produk
void displayProducts(struct Product products[], int size) {
    char formattedPrice[50];
    printf("\nList Product:\n");
    for (int i = 0; i < size; i++) {
        formatRupiah(products[i].price, formattedPrice);
        printf("%d. %s - %s (Stock: %d)\n", i + 1, products[i].name, formattedPrice, products[i].stock);
    }
}

// Fungsi untuk menghitung total harga belanjaan
float calculateTotal(struct Product cart[], int cartSize) {
    float total = 0;
    for (int i = 0; i < cartSize; i++) {
        total += cart[i].price;
    }
    return total;
}

// Fungsi untuk menampilkan keranjang belanja
void displayCart(struct Product cart[], int cartSize) {
    char formattedPrice[50];
    if (cartSize == 0) {
        printf("\nCart is empty.\n");
    } else {
        printf("\nCart:\n");
        for (int i = 0; i < cartSize; i++) {
            formatRupiah(cart[i].price, formattedPrice);
            printf("%d. %s - %s\n", i + 1, cart[i].name, formattedPrice);
        }
    }
}

// Fungsi untuk menambah stok produk (khusus admin)
void addStock(struct Product products[], int size) {
    int choice, newStock;
    displayProducts(products, size);
    printf("\nChoose product to add stock (1-%d): ", size);
    scanf("%d", &choice);
    
    if (choice > 0 && choice <= size) {
        printf("Input new stock for %s: ", products[choice - 1].name);
        scanf("%d", &newStock);
        if (newStock > 0) {
            products[choice - 1].stock += newStock;
            printf("Stock updated! %s now has %d in stock.\n", products[choice - 1].name, products[choice - 1].stock);
        } else {
            printf("Invalid stock quantity.\n");
        }
    } else {
        printf("Invalid choice.\n");
    }
}

int main() {
    // Deklarasi variabel untuk username dan password
    char username[20], password[20];
    
    // Username dan password yang valid (disimpan di dalam program)
    char adminUsername[] = "admin";
    char adminPassword[] = "admin123";
    char userUsername[] = "user";
    char userPassword[] = "123";

    // Daftar produk
    struct Product products[MAX_PRODUCTS] = {
        {"Laptop", 8500000, 5},
        {"Smartphone", 3000000, 10},
        {"Headphone", 150000, 20},
        {"Smartwatch", 800000, 8},
        {"Camera", 5000000, 3}
    };

    // Meminta input username dan password dari pengguna
    printf("==========================\n");
    printf("WELCOME TO AbJAT SHOPPING!\n");
    printf("==========================\n");
    printf("\n");
    printf("Input Username: ");
    scanf("%s", username);

    printf("Input Password: ");
    scanf("%s", password);

    // Membandingkan input dengan username dan password yang valid
    if (strcmp(username, adminUsername) == 0 && strcmp(password, adminPassword) == 0) {
    printf("Login as Admin successful!!\n");
    int adminChoice;
    char arrayMenu[5][100] =  {
        "\nAdmin Menu:", 
        "\n1. View Products", 
        "\n2. Add Stock", 
        "\n3. Exit", 
        "\nChoose an option: "
    };
    
    while (1) {
        // Tampilkan menu
        for (int i = 0; i < 5; i++) {
            printf("%s", arrayMenu[i]);
        }

        // Ambil input pilihan admin
        scanf("%d", &adminChoice);

        if (adminChoice == 1) {
            displayProducts(products, MAX_PRODUCTS);
        } else if (adminChoice == 2) {
            addStock(products, MAX_PRODUCTS);
        } else if (adminChoice == 3) {
            printf("Exiting admin menu.\n");
            break;
        } else {
            printf("Invalid choice, please try again.\n");
        }
    };

    } else if (strcmp(username, userUsername) == 0 && strcmp(password, userPassword) == 0) {
        printf("\nLogin as User successful!\n");
        
        // Array untuk menyimpan produk yang dibeli (keranjang belanja)
        struct Product cart[MAX_CART];
        int cartSize = 0;
        int choice, quantity;

        printf("Welcome to E-Commerce AbJAT!\n");

        while (1) {
            // Menampilkan daftar produk
            displayProducts(products, MAX_PRODUCTS);
            
            // Meminta pengguna untuk memilih produk atau checkout
            printf("\nChoose the product you want to buy (1-%d), Press 0 to checkout, or press -1 to delete product from cart: ", MAX_PRODUCTS);
            scanf("%d", &choice);

            if (choice == 0) {
                // Checkout, hitung total dan diskon jika berlaku
                float total = calculateTotal(cart, cartSize);
                if (total > DISCOUNT_THRESHOLD) {
                    float discount = total * DISCOUNT_RATE;
                    total -= discount;
                    printf("\nDiscount 10%% has been applied! Total Discount: Rp %.2f\n", discount);
                }
                char formattedTotal[50];
                formatRupiah(total, formattedTotal);
                printf("\nTotal shopping: %s\n", formattedTotal);
                printf("Thank you!\n");
                break;
            
            } else if (choice == -1) {
                // Menghapus produk dari keranjang
                displayCart(cart, cartSize);
                if (cartSize > 0) {
                    printf("\nChoose product number you want to delete from cart: ");
                    scanf("%d", &choice);
                    if (choice > 0 && choice <= cartSize) {
                        printf("%s Deleted from cart.\n", cart[choice - 1].name);
                        for (int i = choice - 1; i < cartSize - 1; i++) {
                            cart[i] = cart[i + 1];
                        }
                        cartSize--;
                    } else {
                        printf("Invalid Choice\n");
                    }
                }
            
            } else if (choice > 0 && choice <= MAX_PRODUCTS) {
                // Meminta jumlah barang yang ingin dibeli
                printf("How many %s do you want to buy? (Max: %d): ", products[choice - 1].name, products[choice - 1].stock);
                scanf("%d", &quantity);

                // Cek apakah stok cukup
                if (quantity > 0 && quantity <= products[choice - 1].stock) {
                    // Tambahkan produk ke keranjang sesuai dengan kuantitas yang dipilih
                    for (int i = 0; i < quantity; i++) {
                        if (cartSize < MAX_CART) {
                            cart[cartSize] = products[choice - 1];
                            cartSize++;
                        } else {
                            printf("Cart is full, can not add more product.\n");
                            break;
                        }
                    }
                    // Kurangi stok produk
                    products[choice - 1].stock -= quantity;
                    printf("%d %s added to cart.\n\n", quantity, products[choice - 1].name);
                } else {
                    printf("Invalid total or stock is not enough.\n\n");
                }
            
            } else {
                printf("Invalid choice. Please try again!.\n\n");
            }
        }
    } else {
        printf("Login failed! Wrong username or password.\n");
    }

    return 0;
}
