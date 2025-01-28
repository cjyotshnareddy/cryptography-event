#include <iostream>
#include <string>
#include <cctype>

using namespace std;

// Function to generate the repeating key sequence based on the plaintext length
string generateKey(string plaintext, string key) {
    int keyLength = key.length();
    int textLength = plaintext.length();
    string newKey = "";

    for (int i = 0, j = 0; i < textLength; i++) {
        if (isalpha(plaintext[i])) {
            newKey += key[j % keyLength];
            j++;
        } else {
            newKey += plaintext[i]; // Preserve spaces and special characters
        }
    }
    return newKey;
}

// Function to encrypt plaintext using Vigenère Cipher
string vigenereEncrypt(string plaintext, string key) {
    string ciphertext = "";
    key = generateKey(plaintext, key);

    for (size_t i = 0; i < plaintext.length(); i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            char keyBase = isupper(key[i]) ? 'A' : 'a';
            char encryptedChar = ((plaintext[i] - base + key[i] - keyBase) % 26) + base;
            ciphertext += encryptedChar;
        } else {
            ciphertext += plaintext[i]; // Keep non-alphabet characters unchanged
        }
    }
    return ciphertext;
}

// Function to decrypt ciphertext using Vigenère Cipher
string vigenereDecrypt(string ciphertext, string key) {
    string plaintext = "";
    key = generateKey(ciphertext, key);

    for (size_t i = 0; i < ciphertext.length(); i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            char keyBase = isupper(key[i]) ? 'A' : 'a';
            char decryptedChar = ((ciphertext[i] - base - (key[i] - keyBase) + 26) % 26) + base;
            plaintext += decryptedChar;
        } else {
            plaintext += ciphertext[i]; // Keep non-alphabet characters unchanged
        }
    }
    return plaintext;
}

// Main function for user input
int main() {
    string plaintext, key;

    cout << "Enter plaintext: ";
    getline(cin, plaintext);

    cout << "Enter keyword: ";
    cin >> key;

    string encryptedText = vigenereEncrypt(plaintext, key);
    cout << "Encrypted Text: " << encryptedText << endl;

    string decryptedText = vigenereDecrypt(encryptedText, key);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
