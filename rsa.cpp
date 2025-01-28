#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
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

// Function to compute GCD of a and b using Euclidean algorithm
long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to compute modular inverse of e mod phi(n)
long long mod_inverse(long long e, long long phi) {
    long long t = 0, new_t = 1;
    long long r = phi, new_r = e;
    while (new_r != 0) {
        long long quotient = r / new_r;
        t = new_t;
        new_t = t - quotient * new_t;
        r = new_r;
        new_r = r - quotient * new_r;
    }
    if (r > 1) return -1;  // No inverse if GCD(e, phi) != 1
    if (t < 0) t = t + phi;
    return t;
}

// Function to generate RSA keys with larger primes
void generate_rsa_keys(long long &e, long long &d, long long &n) {
    long long p = 61, q = 53;  // Small primes for simplicity (in real cases, use much larger primes)
    n = p * q;
    long long phi = (p - 1) * (q - 1);

    // Choose e such that 1 < e < phi and gcd(e, phi) = 1
    e = 17;  // Common choice for e

    // Compute d such that (d * e) % phi = 1
    d = mod_inverse(e, phi);
}

// Function to encrypt a message using RSA
long long encrypt(long long m, long long e, long long n) {
    return mod_exp(m, e, n);
}

// Function to decrypt a ciphertext using RSA
long long decrypt(long long c, long long d, long long n) {
    return mod_exp(c, d, n);
}

// Function to convert a character to an integer (ASCII value)
long long char_to_int(char c) {
    return static_cast<long long>(c);
}

// Function to convert an integer back to a character
char int_to_char(long long n) {
    if (n < 0 || n > 255) {
        return '?';  // Invalid range for ASCII characters
    }
    return static_cast<char>(n);
}

int main() {
    long long e, d, n;
    generate_rsa_keys(e, d, n);

    cout << "Public Key: (e=" << e << ", n=" << n << ")\n";
    cout << "Private Key: (d=" << d << ", n=" << n << ")\n";

    string message;
    cout << "Enter a word to encrypt: ";
    cin >> message;

    // Encrypt each character and store the encrypted values as a string
    string encrypted_message = "";
    for (char c : message) {
        long long m = char_to_int(c);
        long long c_encrypted = encrypt(m, e, n);
        encrypted_message += to_string(c_encrypted) + " ";
    }
    cout << "Encrypted message: " << encrypted_message << endl;

    // Decrypt the message back to the original string
    string decrypted_message = "";
    size_t pos = 0;
    while ((pos = encrypted_message.find(" ")) != string::npos) {
        string token = encrypted_message.substr(0, pos);
        long long c = stoll(token);
        long long m_decrypted = decrypt(c, d, n);
        decrypted_message += int_to_char(m_decrypted);
        encrypted_message.erase(0, pos + 1);
    }

    cout << "Decrypted message: " << message << endl;

    return 0;
}
