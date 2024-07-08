#ifndef CRYPTO_H
#define CRYPTO_H

#include <cryptopp/rsa.h>
#include <string>

using namespace CryptoPP;
using namespace std;

void Save(const string& filename, const BufferedTransformation& bt);
void SaveKey(const string& filename, const RSA::PublicKey& key);
void Load(const string& filename, BufferedTransformation& bt);
void LoadKey(const string& filename, RSA::PublicKey& key);
void LoadPublicKey(const string& filename, RSA::PublicKey& key);
void LoadPrivateKey(const string& filename, RSA::PrivateKey& key);
void GenerateKeys(RSA::PrivateKey& privateKey, RSA::PublicKey& publicKey, const string& privateKeyFile, const string& publicKeyFile, int keySize = 3072);
string RSAEncryptString(const RSA::PublicKey& publicKey, const string& message);
string RSADecryptString(const RSA::PrivateKey& privateKey, const string& cipher);


#endif // CRYPTO_H
