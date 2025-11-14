#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>   // for system()
using namespace std;


// Base Abstract Class

class Encryptor {
protected:
    string key;
public:
    Encryptor(const string &k) : key(k) {}
    virtual ~Encryptor() {}

    virtual void encryptFile(const string &inputFile, const string &outputFile) = 0;
    virtual void decryptFile(const string &inputFile, const string &outputFile) = 0;

};


// Caesar Cipher Encryption

class CaesarEncryptor : public Encryptor {
public:
    CaesarEncryptor(const string &k) : Encryptor(k) {}

    int shiftValue() {
        int s = 0;
        for (char c : key) s += c; // for each loop
        return (s % 26) + 1;
    }

void encryptFile(const string &inputFile, const string &outputFile) override {
    ifstream fin(inputFile, ios::binary);
    ofstream fout(outputFile, ios::binary);
    if (!fin || !fout) { cout << "Error opening files.\n"; return; }

    const int s   = shiftValue();
    const int s26 = s % 26;  
    const int s10 = s % 10;  
    const int s94 = s % 94;  

    cout << "Encrypting (extended, whitespace preserved) with shift = " << s << "...\n";

    char ch;
    while (fin.get(ch)) {
        unsigned char uch = static_cast<unsigned char>(ch);

        if (std::isspace(uch)) {
        }
        else if (ch >= 'a' && ch <= 'z') {
            ch = char(((ch - 'a' + s26) % 26) + 'a');
        }
        else if (ch >= 'A' && ch <= 'Z') {
            ch = char(((ch - 'A' + s26) % 26) + 'A');
        }
        else if (ch >= '0' && ch <= '9') {
            ch = char(((ch - '0' + s10) % 10) + '0');
        }
        else if (uch >= 33 && uch <= 126) {
            ch = char(((int(uch) - 33 + s94) % 94) + 33);
        }

        fout.put(ch);
    }
    cout << "Encryption complete.\n";
}

 void decryptFile(const string &inputFile, const string &outputFile) override {
    ifstream fin(inputFile, ios::binary);
    ofstream fout(outputFile, ios::binary);
    if (!fin || !fout) { cout << "Error opening files.\n"; return; }

    const int s   = shiftValue();
    const int s26 = s % 26; 
    const int s10 = s % 10; 
    const int s94 = s % 94;  

    cout << "Decrypting (extended, whitespace preserved) with shift = " << s << "...\n";

    char ch;
    while (fin.get(ch)) {
        unsigned char uch = static_cast<unsigned char>(ch);

        if (std::isspace(uch)) {
        }
        else if (ch >= 'a' && ch <= 'z') {
            ch = char(((ch - 'a' - s26 + 26) % 26) + 'a');
        }
        else if (ch >= 'A' && ch <= 'Z') {
            ch = char(((ch - 'A' - s26 + 26) % 26) + 'A');
        }
        else if (ch >= '0' && ch <= '9') {
            ch = char(((ch - '0' - s10 + 10) % 10) + '0');
        }
        else if (uch >= 33 && uch <= 126) {
            ch = char(((int(uch) - 33 - s94 + 94) % 94) + 33);
        }

        fout.put(ch);
    }
    cout << "Decryption complete.\n";
}
};

// File Operations

void createFile() {
    string name, line;
    cout << "Enter file name: ";
    cin >> name;

    ofstream file(name);
    if (!file) {
        cout << "Error creating file.\n";
        return;
    }

    cout << "Enter text (type END on a new line to stop):\n";
    cin.ignore();
    while (true) {
        getline(cin, line);
        if (line == "END") break;
        file << line << "\n";
    }
    cout << "File created successfully.\n";
}

void readFile() {
    string name, line;
    cout << "Enter file name: ";
    cin >> name;

    ifstream file(name);
    if (!file) {
        cout << "Cannot open file.\n";
        return;
    }

    cout << "\nFile contents:\n";
    while (getline(file, line)) cout << line << "\n";
}

void editFile() {
    string name, line;
    cout << "Enter file name: ";
    cin >> name;

    ofstream file(name, ios::app); // ios is mode that : open,app,write
    if (!file) {
        cout << "Cannot open file.\n";
        return;
    }

    cout << "Enter text to append (type END to stop):\n";
    cin.ignore();
    while (true) {
        getline(cin, line);
        if (line == "END") break;
        file << line << "\n";
    }
    cout << "Text appended successfully.\n";
}

void deleteFile() {
    string name;
    cout << "Enter file name: ";
    cin >> name;

    if (remove(name.c_str()) == 0)
        cout << "File deleted successfully.\n";
    else
        cout << "Error deleting file.\n";
}

void listFiles() {
#ifdef _WIN32
    system("dir");
#else
    system("ls");
#endif
}


// Main Program

