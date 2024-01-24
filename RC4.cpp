//
// RC4.cpp:
//  Rivest Cipher 4 (RC4), stream cipher encryption.
//  References:
//      https://en.wikipedia.org/wiki/RC4
//      https://cypherpunks.venona.com/archive/1994/09/msg00304.html
//
//  https://github.com/0xAbby/RC4
//
// Author:
//  Abdullah Ada
//
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ios>
#include <numeric> // iota()

#define MOD 256
using namespace std;
// key scheduling algorithm
//  https://en.wikipedia.org/wiki/RC4#Key-scheduling_algorithm_(KSA)
//
vector<uint8_t> KSA(string& key) {
  uint32_t length = key.size();
  vector<uint8_t> ksa(MOD);

  iota(ksa.begin(), ksa.end(), 0);  // fill 0,1,2..255

  int j = 0;
  for (uint16_t idx = 0; idx < MOD; idx++) {
    j = (j + ksa[idx] + key[idx % length]) % MOD;

    uint8_t tmp = ksa[idx];  // swap
    ksa[idx] = ksa[j];
    ksa[j] = tmp;
  }

  return ksa;
}

void PRGA(vector<uint8_t>& ksa, string plaintext, vector<uint8_t>& cipher) {
  uint8_t PRGA = 0;
  uint32_t length = plaintext.size();

  int i = 0;
  int j = 0;
  for (uint32_t idx = 0; idx < length; idx++) {
    i = (i + 1) % MOD;
    j = (j + ksa[i]) % MOD;

    int tmp = ksa[i];  // swap
    ksa[i] = ksa[j];
    ksa[j] = tmp;

    PRGA = ksa[(ksa[i] + ksa[j]) % MOD];
    cipher.push_back(PRGA ^ plaintext[idx]);
  }
}

void RC4_encrypt(string key, string plaintext, vector<uint8_t>& output) {
  vector<uint8_t> keystream = KSA(key);
  PRGA(keystream, plaintext, output);

}

vector<uint8_t> RC4_decrypt(string key, vector<uint8_t> cipher) {
  // change cipher from a vector to a string and pass as plaintext to encrypt
  string cipher_text;
  uint32_t length = cipher.size();

  for(uint32_t idx = 0 ; idx < length; idx++) {
   // cout << "Adding " << idx << " byte" << endl;
    cipher_text.push_back( (cipher[idx]));
  }
  RC4_encrypt(key, cipher_text, cipher);

  return cipher;
}

int main(int argc, char* argv[]) {
  string key = "Cool_trick";
  string plaintext = "May the force be with you";
  vector<uint8_t> decrypted;
  vector<uint8_t> ciphertext;

  RC4_encrypt(key, plaintext, ciphertext);

  // print cipher
  printf("After encryption: \n");
  // expectation:
  // ciphertext = 5025664fb67bf3dd259f0ddcb5e88c9ff82358a8db3ab30d06
  for (uint32_t byte = 0; byte < ciphertext.size(); byte++) {
    printf("0x%x ", ciphertext[byte]);
  }

  printf("\n");
  printf("After dencryption: \n");
  decrypted = RC4_decrypt(key, ciphertext);
  for (uint32_t byte = 0; byte < decrypted.size(); byte++) {
    printf("%c", decrypted[byte]);
  }
  printf("\n");

  return 0;
}
