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



// Fungsi untuk menampilkan daftar produk
void displayProducts(struct Product products[], int size) {
    printf("\nList Product:\n");
    for (int i = 0; i < size; i++) {
        printf("%d. %s - Rp %.2f (Stock: %d)\n", i + 1, products[i].name, products[i].price, products[i].stock);
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
    if (cartSize == 0) {
        printf("\nCart is empty.\n");
    } else {
        printf("\nCart:\n");
        for (int i = 0; i < cartSize; i++) {
            printf("%d. %s - Rp %.2f\n", i + 1, cart[i].name, cart[i].price);
        }
    }
}

int main() {
    // Deklarasi variabel untuk username dan password
    char username[20], password[20];
    
    // Username dan password yang valid (disimpan di dalam program)
    char validUsername[] = "user";
    char validPassword[] = "1234";

    // Meminta input username dan password dari pengguna
    printf("Input Username: ");
    scanf("%s", username);

    printf("Input Password: ");
    scanf("%s", password);

    // Membandingkan input dengan username dan password yang valid
    if (strcmp(username, validUsername) == 0 && strcmp(password, validPassword) == 0) {
        printf("\n");
        printf("Login success! Welcome, %s.\n", username);

        struct Product products[MAX_PRODUCTS] = {
        {"Laptop", 8500000, 5},
        {"Smartphone", 3000000, 10},
        {"Headphone", 150000, 20},
        {"Smartwatch", 800000, 8},
        {"Camera", 5000000, 3}
    };

    // Array untuk menyimpan produk yang dibeli (keranjang belanja)
    struct Product cart[MAX_CART];
    int cartSize = 0;
    int choice, quantity;

    printf("\n");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("\n");
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
            printf("\nTotal shopping: Rp %.2f\n", total);
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
                    printf("Invalide Choice\n");
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
        printf("\n");
        printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
        printf("\n");
        printf("Login failed! Wrong username and password.\n");
    }

    return 0;
}
