#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

long long modular_exponentiation(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

long long find_modular_inverse(long long a, long long m) {
    long long original_modulus = m, temp, quotient;
    long long previous_x = 0, current_x = 1;
    while (a > 1) {
        quotient = a / m;
        temp = m;
        m = a % m, a = temp;
        temp = previous_x;
        previous_x = current_x - quotient * previous_x;
        current_x = temp;
    }
    if (current_x < 0) current_x += original_modulus;
    return current_x;
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

    if (p == 0 || q == 0) {
        cout << "Public key is not valid!" ;
        return 0;
    }

    long long phi = (p - 1) * (q - 1);
    if (gcd(e, phi) != 1) {
        cout << "Public key is not valid!" ;
        return 0;
    }

    long long d = find_modular_inverse(e, phi);
    cout << p << " " << q << " " << phi << " " << d ;

    vector<long long> decodedMessage;
    for (long long cipher_num : ciphertext) {
        decodedMessage.push_back(modular_exponentiation(cipher_num, d, n));
    }

    for (long long num : decodedMessage) {
        cout << num << " ";
    }

    map<long long, char> number_to_char_mapping;
    for (char i = 'A'; i <= 'Z'; i++) {
        number_to_char_mapping[5 + (i - 'A')] = i;
    }
    number_to_char_mapping[31] = ' ';
    number_to_char_mapping[32] = '"';
    number_to_char_mapping[33] = ',';
    number_to_char_mapping[34] = '.';
    number_to_char_mapping[35] = '\'';

    for (long long num : decodedMessage) {
        cout << number_to_char_mapping[num];
    }
    cout << endl;

    return 0;
}
