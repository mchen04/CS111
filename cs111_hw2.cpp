#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

long long modular_exponentiation(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

long long find_modular_inverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    long long i = 5;
    while (i * i <= n) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
        i += 6;
    }
    return true;
}

int main() {
    long long e, n, m;
    cin >> e >> n >> m;
    vector<long long> ciphertext(m);
    for (long long i = 0; i < m; i++) {
        cin >> ciphertext[i];
    }

    long long p = 0, q = 0;
    for (long long i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            p = i;
            q = n / i;
            break;
        }
    }

    if (!is_prime(p) || !is_prime(q) || p == 0 || q == 0 || p == q) {
        cout << "Public key is not valid!";
        return 0;
    }

    long long phi = (p - 1) * (q - 1);
    if (e <= 1 || e >= phi || e == phi || gcd(e, phi) != 1) {
        cout << "Public key is not valid!";
        return 0;
    }

    long long d = find_modular_inverse(e, phi);
    if (d == 0) {
        cout << "Public key is not valid!";
        return 0;
    }

    cout << p << " " << q << " " << phi << " " << d << endl;

    vector<long long> decodedMessage;
    for (long long cipher_num : ciphertext) {
        decodedMessage.push_back(modular_exponentiation(cipher_num, d, n));
    }

    for (long long num : decodedMessage) {
        cout << num << " ";
    }
    cout << endl;

    map<long long, char> number_to_char_mapping;
    for (char i = 'A'; i <= 'Z'; i++) {
        number_to_char_mapping[i - 'A' + 5] = i;
    }
    number_to_char_mapping[31] = ' ';
    number_to_char_mapping[32] = '"';
    number_to_char_mapping[33] = ',';
    number_to_char_mapping[34] = '.';
    number_to_char_mapping[35] = '\'';

    for (long long num : decodedMessage) {
        cout << number_to_char_mapping[num];
    }

    return 0;
}