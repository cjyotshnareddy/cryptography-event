#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Function to find modular inverse of 'a' under modulo 'm'
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // No modular inverse exists
}

// Function to encrypt plaintext using Affine Cipher
string affineEncrypt(string plaintext, int a, int b) {
    string ciphertext = "";
    int m = 26; // Number of letters in English alphabet

    for (char ch : plaintext) {
        if (isalpha(ch)) {
            bool isUpper = isupper(ch);
            ch = tolower(ch);
            char encryptedChar = ((a * (ch - 'a') + b) % m) + 'a';
            ciphertext += isUpper ? toupper(encryptedChar) : encryptedChar;
        } else {
            ciphertext += ch; // Keep non-alphabet characters unchanged
        }
    }

    return ciphertext;
}

// Function to decrypt ciphertext using Affine Cipher
string affineDecrypt(string ciphertext, int a, int b) {
    string plaintext = "";
    int m = 26; // Number of letters in English alphabet
    int a_inv = modInverse(a, m);

    if (a_inv == -1) {
        cerr << "Error: 'a' must be coprime with 26 for decryption to work.\n";
        return "";
    }

    for (char ch : ciphertext) {
        if (isalpha(ch)) {
            bool isUpper = isupper(ch);
            ch = tolower(ch);
            char decryptedChar = ((a_inv * (ch - 'a' - b + m)) % m) + 'a';
            plaintext += isUpper ? toupper(decryptedChar) : decryptedChar;
        } else {
            plaintext += ch; // Keep non-alphabet characters unchanged
        }
    }

    return plaintext;
}

// Main function for user input
int main() {
    string plaintext;
    int a, b;

    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    cout << "Enter key 'a' (must be coprime with 26): ";
    cin >> a;

    cout << "Enter key 'b': ";
    cin >> b;

    // Check if 'a' is coprime with 26
    if (modInverse(a, 26) == -1) {
        cerr << "Error: 'a' must be coprime with 26.\n";
        return 1;
    }

    string encryptedText = affineEncrypt(plaintext, a, b);
    cout << "Encrypted Text: " << encryptedText << endl;

    string decryptedText = affineDecrypt(encryptedText, a, b);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
