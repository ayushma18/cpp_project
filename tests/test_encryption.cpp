#include "../headers/emp.h"

int main() 
{
    RSA::PrivateKey privateKey;
    RSA::PublicKey publicKey;

    RSA::PrivateKey privateKey_loaded;
    RSA::PublicKey publicKey_loaded;

    GenerateKeys(privateKey, publicKey, "tests/sa-private.key", "tests/sa-private.key");
    cout << "1" <<endl;
    LoadKey("tests/sa-private.key", privateKey_loaded);
    cout << "2" <<endl;
    LoadKey("tests/sa-public.key", publicKey_loaded);
    cout << "3" <<endl;


    if(privateKey_loaded.GetModulus() != privateKey.GetModulus() ||
    privateKey_loaded.GetPublicExponent() != privateKey.GetPublicExponent() ||
    privateKey_loaded.GetPrivateExponent() != privateKey.GetPrivateExponent())
    {
        throw runtime_error("key data did not round trip");
    }


    string message = "This is a secret message.";
    string cipher = RSAEncryptString(publicKey, message);
    string recovered = RSADecryptString(privateKey, cipher);

    cout << "Original Message: " << message << endl;
    cout << "Cipher Text: " << cipher << endl;
    cout << "Recovered Message: " << recovered << endl;

    return 0;
}