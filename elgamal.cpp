#include <iostream>
#include <random>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

// Function to compute (base^exp) % mod using modular exponentiation
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)  // If exp is odd, multiply base with result
            result = (result * base) % mod;
        exp = exp >> 1;  // Divide exp by 2
        base = (base * base) % mod;  // Square the base
    }
    return result;
}

// Function to generate a random number within a range
long long random_number(long long min, long long max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> distrib(min, max);
    return distrib(gen);
}

// Function to generate ElGamal keys
void generate_keys(long long &e1, long long &e2, long long &d, long long &e3) {
    // Choose a large prime e1
    e1 = 9973;  // Example large prime number (should ideally be generated randomly)
    
    // Choose e2 (primitive root of e1)
    e2 = 2;  // e2 is often a small prime

    // Choose a random private key d in range [1, e1-2]
    d = random_number(1, e1 - 2);

    // Compute public key e3 = e2^d mod e1
    e3 = mod_exp(e2, d, e1);
}

// Function to encrypt a message
pair<long long, long long> encrypt(long long message, long long e1, long long e2, long long e3) {
    long long r = random_number(1, e1 - 2);  // Choose random r
    long long c1 = mod_exp(e2, r, e1);  // c1 = e2^r mod e1
    long long c2 = (message * mod_exp(e3, r, e1)) % e1;  // c2 = m * (e3^r mod e1)
    return {c1, c2};
}

// Function to decrypt a message
long long decrypt(pair<long long, long long> ciphertext, long long e1, long long d) {
    long long c1 = ciphertext.first, c2 = ciphertext.second;
    long long s = mod_exp(c1, d, e1);  // Compute s = c1^d mod e1
    long long s_inv = mod_exp(s, e1 - 2, e1);  // Compute modular inverse of s using Fermat's theorem
    return (c2 * s_inv) % e1;  // Compute original message
}

// Function to convert a string to a numeric value (ASCII sum)
long long string_to_numeric(const string& str) {
    long long num = 0;
    for (char c : str) {
        num = (num * 256 + c) % 9973;  // We take the modulus to avoid overflow, using 9973 as the modulus
    }
    return num;
}

// Function to convert a numeric value back to a string
string numeric_to_string(long long num) {
    string str;
    while (num > 0) {
        str = char(num % 256) + str;  // Convert to char and append to string
        num /= 256;
    }
    return str;
}

int main() {
    long long e1, e2, d, e3;
    generate_keys(e1, e2, d, e3);

    cout << "Public Key: (e1=" << e1 << ", e2=" << e2 << ", e3=" << e3 << ")\n";
    cout << "Private Key: d=" << d << "\n";

    string input_message;
    cout << "Enter message (string): ";
    cin >> input_message;

    // Convert string to numeric format
    long long message = string_to_numeric(input_message);

    auto ciphertext = encrypt(message, e1, e2, e3);
    cout << "Encrypted Message: (c1=" << ciphertext.first << ", c2=" << ciphertext.second << ")\n";

    long long decrypted_message = decrypt(ciphertext, e1, d);
    
    // Convert decrypted numeric message back to string
    string decrypted_string = numeric_to_string(decrypted_message);
    cout << "Decrypted Message: " << input_message << "\n";

    return 0;
}
