## RC4 stream cipher encryption implementation

The RC4 encryption algorithm works by generating a stream of pseudorandom bytes using a key scheduler and a pseudorandom number generator. 

![Flowchart-of-RC4-Algorithm](https://github.com/0xAbby/RC4/assets/147592615/c3983075-5dea-43db-97c7-e98109653c7e)

[source of the image: https://www.researchgate.net/figure/Flowchart-of-RC4-Algorithm_fig1_323783954]


These bytes are then XORed with the plaintext to create the ciphertext. 

The key scheduler generates a key stream based on the user-provided secret key, while the pseudorandom number generator generates a sequence of pseudorandom bytes used to shuffle the elements of the key stream. 



to build it:
```
$ git clone https://github.com/0xAbby/RC4
$ cd RC4
$ g++ -Wall RC4.cpp -o RC4
$ ./RC4

After encryption: 
0x50 0x25 0x66 0x4f 0xb6 0x7b 0xf3 0xdd 0x25 0x9f 0xd 0xdc 0xb5 0xe8 0x8c 0x9f 0xf8 0x23 0x58 0xa8 0xdb 0x3a 0xb3 0xd 0x6 
After dencryption: 
May the force be with you

```

Encrypted input is printed as hex, while decrypted input is printed as a string.

