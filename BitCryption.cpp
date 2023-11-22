#include <iostream>
#include <ctime>
#include <string>
#include <cctype>
#include <limits>

using namespace std;

// Random key generator
string keyGenerator(int howLong) {

    string key;

    srand(time(NULL));

    for (int i = 0; i < howLong; i++) {
        char randomChar = 'a' + rand() % 26;
        key += randomChar;
    }

    return key;
}

// Remove invisible characters from a string
string removeInvisibleCharacters(const string& input) {

    string result;

    for (char c : input) {
        if (isprint(c) && !isspace(c)) {
            result += c;
        }
    }

    return result;
}

// Encrypting sentence with a key
string encrypt(const string& sentence, const string& key) {

    string encryptedSentence = removeInvisibleCharacters(sentence);
    string cleanedKey = removeInvisibleCharacters(key);

    for (int i = 0; i < encryptedSentence.length(); i++) {
        encryptedSentence[i] = (encryptedSentence[i] - 'a' + cleanedKey[i % cleanedKey.length()] - 'a') % 26 + 'a';
    }

    return encryptedSentence;
}

// Decrypting sentence with a key
string decrypt(const string& encryptedSentence, const string& key) {

    string cleanedKey = removeInvisibleCharacters(key);
    string decryptedSentence = encryptedSentence;

    for (int i = 0; i < decryptedSentence.length(); i++) {
        decryptedSentence[i] = (decryptedSentence[i] - 'a' - (cleanedKey[i % cleanedKey.length()] - 'a') + 26) % 26 + 'a';
    }

    return decryptedSentence;
}

int main() {

    string sentence, key, encrypted, decrypted;
    int option,a;

    do {
        cout << "Hi! You can choose from these options based on what you want to do:\n1-Encrypt a sentence\n2-Decrypt a sentence\n3-Exit" << endl;
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (option) {
        case 1:
            cout << "Type a sentence you want to encrypt" << endl;
            getline(cin, sentence);
            key = keyGenerator(sentence.length());
            encrypted = encrypt(sentence, key);
            cout << "Encrypted sentence: " << encrypted << endl;
            cout << "Key that you can use to decrypt this sentence: " << key << endl;
            cout << "Press Enter to clean console. Make sure that you copied key, you will not be able to decrypt sentence without it."<<endl;
            cin.get();
            system("cls");
            break;

        case 2:
            cout << "Type a sentence you want to decrypt" << endl;
            getline(cin, sentence);
            cout << "Type a key that was used to encrypt this sentence" << endl;
            getline(cin, key);
            decrypted = decrypt(sentence, key);
            cout << "Decrypted sentence: " << decrypted << endl;
            cout << "Press Enter to clean console." << endl;
            cin.get();
            system("cls");
            break;

        case 3:
            break;

        default:
            cout << "You were supposed to give me number from 1 to 3" << endl;
            break;
        }

    } while (option != 3);

    return 0;
}
