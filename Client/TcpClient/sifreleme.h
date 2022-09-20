#ifndef SIFRELEME_H
#define SIFRELEME_H
#include <iostream>
#include "hex.h"
#include "cryptlib.h"
#include "modes.h"
#include "osrng.h"
#include "aes.h"
#include "cryptopp/files.h"
#include <string>
using namespace std;
using namespace CryptoPP;
struct Key
{
    string iv;
    string key;
};

class sifreleme
{
public:
    sifreleme();
    string convert_to_hex(string& input);
    Key generate_key();
    string encrypt_aes(Key& key, string& plaintext);
    string sifre(string& sifre);
};

#endif // SIFRELEME_H
