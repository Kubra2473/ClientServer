#include "sifreleme.h"

sifreleme::sifreleme()
{

}
string sifreleme::convert_to_hex(string &input)
{
    string output;
        CryptoPP::StringSource(input,true,
                               new CryptoPP::HexEncoder(
                                   new CryptoPP::StringSink(output)));
        return output;

}

Key sifreleme::generate_key()
{
    std::string str = "11111111111111111111111111111111";
       std::string str2 ="0000000000000000";
       SecByteBlock key(reinterpret_cast<const CryptoPP::byte*>(&str[0]),str.size());
       SecByteBlock iv(reinterpret_cast<const CryptoPP::byte*>(&str2[0]),str.size());

       string keystr((const char*) key.BytePtr(), key.size());
       string ivstr((const char*) iv.BytePtr(), iv.size());

       Key keyout;
       keyout.iv=ivstr;
       keyout.key=keystr;
       return keyout;

}

string sifreleme::encrypt_aes(Key &key, string &plaintext)
{


    CBC_Mode< AES >::Encryption enc;
    const CryptoPP::byte* keydata = (const CryptoPP::byte*) &key.key[0];
    const CryptoPP::byte* ivdata = (const CryptoPP::byte*) &key.iv[0];
    enc.SetKeyWithIV(keydata,key.key.size(),ivdata);

    string cipher;
    StringSource(plaintext,true,
                 new StreamTransformationFilter(
                     enc,new HexEncoder(new StringSink(cipher))));
    //cout<<"şifre çözüldü"<<cipher;
    return cipher;

}
string sifreleme::sifre(string &sifre)
{
    Key key= generate_key();
    //cout<<"Key:"<<convert_to_hex(key.key)<<endl;
    string cipher=encrypt_aes(key,sifre);
    //cout<<"Encrypted:"<<convert_to_hex(cipher)<<endl;
    string a=convert_to_hex(cipher);
    //cout<<"a:"<<a;
    //string b=convert_from_hex(a);
    //string decipher=decrypt_aes(key,b);

    return a;

}
