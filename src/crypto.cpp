#include "../headers/crypto.h"
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/filters.h>
#include <cryptopp/queue.h>

void Save(const string& filename, const BufferedTransformation& bt) {
    FileSink file(filename.c_str());
    bt.CopyTo(file);
    file.MessageEnd();
}

void SaveKey(const string& filename, const RSA::PublicKey& key) {
    ByteQueue queue;
    key.Save(queue);
    Save(filename, queue);
}

void Load(const string& filename, BufferedTransformation& bt) {
    FileSource file(filename.c_str(), true /*pumpAll*/);
    file.TransferTo(bt);
    bt.MessageEnd();
}

void LoadPublicKey(const string& filename, RSA::PublicKey& key) {
    ByteQueue queue;
    Load(filename, queue);
    key.Load(queue);
}
void LoadKey(const string& filename, RSA::PublicKey& key) {
    ByteQueue queue;
    Load(filename, queue);
    key.Load(queue);
}

void LoadPrivateKey(const string& filename, RSA::PrivateKey& key) {
    ByteQueue queue;
    Load(filename, queue);
    key.Load(queue);
}

void GenerateKeys(RSA::PrivateKey& privateKey, RSA::PublicKey& publicKey, const string& privateKeyFile, const string& publicKeyFile, int keySize) {
    AutoSeededRandomPool prng;

    privateKey.GenerateRandomWithKeySize(prng, keySize);
    publicKey = RSA::PublicKey(privateKey);

    SaveKey(privateKeyFile, privateKey);
    SaveKey(publicKeyFile, publicKey);
}

string RSAEncryptString(const RSA::PublicKey& publicKey, const string& message) {
    AutoSeededRandomPool rng;
    RSAES_OAEP_SHA_Encryptor encryptor(publicKey);

    string cipher;
    StringSource(message, true, 
        new PK_EncryptorFilter(rng, encryptor, 
            new StringSink(cipher)
        )
    );
    return cipher;
}

string RSADecryptString(const RSA::PrivateKey& privateKey, const string& cipher) {
    AutoSeededRandomPool rng;
    RSAES_OAEP_SHA_Decryptor decryptor(privateKey);

    string recovered;
    StringSource(cipher, true, 
        new PK_DecryptorFilter(rng, decryptor, 
            new StringSink(recovered)
        )
    );
    return recovered;
}
