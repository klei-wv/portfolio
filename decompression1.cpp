#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode *left;
    HuffmanNode *right;
    HuffmanNode *next;

    HuffmanNode(char c, int x) {
        ch = c;
        freq = x;
        left = NULL;
        right = NULL;
        next = NULL;
    }

    HuffmanNode(int x, HuffmanNode *l, HuffmanNode *r) {
        ch = '\0';
        freq = x;
        left = l;
        right = r;
        next = NULL;
    }
};

class PriorityHuffmanQueue {
public:
    PriorityHuffmanQueue() {
        head = NULL;
    }

    void Enqueue(HuffmanNode *newNode) {
        insertSorted(newNode);
    }

    HuffmanNode *Dequeue() {
        if (head == NULL) {
            cout << "Queue is empty." << endl;
            return NULL;
        } else {
            while (head->next != NULL) {
                HuffmanNode *left = head;
                HuffmanNode *right = head->next;
                int sum = left->freq + right->freq;
                HuffmanNode *rootNode = new HuffmanNode(sum, left, right);
                insertSorted(rootNode);
                head = head->next->next;
            }
            HuffmanNode *temp = head;
            head = NULL;
            return temp;
        }
    }

private:
    HuffmanNode *head;

    void insertSorted(HuffmanNode *newNode) {
        HuffmanNode *current = head;
        HuffmanNode *previous = NULL;
        while (current != NULL && newNode->freq >= current->freq) {
            previous = current;
            current = current->next;
        }
        if (previous == NULL) {
            newNode->next = head;
            head = newNode;
        } else {
            newNode->next = current;
            previous->next = newNode;
        }
    }
};

class Huff {
    int frequency[256];
    string huffmanCode[256];
    PriorityHuffmanQueue Que;

public:
    Huff() {
        root = NULL;
    }

    void initialize() {
        for (int i = 0; i < 256; i++) {
            frequency[i] = 0;
        }
    }

    void huffman() {
        initialize();
        int sizeBit = counter();
        if (sizeBit == 0) {
            return;
        } else {
            root = startQueue();
            cout << setw(10) << "Character"
                 << setw(12) << "Frequency"
                 << setw(12) << "ASCII Value"
                 << setw(20) << "Huffman Code" << endl;
            getCode(root, "");
            string trav = retrieve(sizeBit);
            getChar(root, trav);
        }
    }

    int counter() {
        const string SAVE_FILE = "save.compression";
        ifstream in(SAVE_FILE);
        int sizeBit = 0;

        if (in.is_open()) {
            in >> sizeBit;
            string line;

            int freq;
            while (in >> line >> freq) {
                if (line == "SPACE") {
                    line = " ";
                } else if (line == "NEWLINE") {
                    line = "\n";
                } else if (line == "TAB") {
                    line = "\t";
                }

                int asciiValue = (int)line[0];
                frequency[asciiValue] = freq;
                cout << setw(10) << line
                     << setw(12) << freq
                     << setw(12) << asciiValue << endl;
            }
            in.close();
            return sizeBit;
        }
        return 0;
    }

    HuffmanNode *startQueue() {
        for (int i = 0; i < 256; i++) {
            if (frequency[i] > 0) {
                HuffmanNode *newNode = new HuffmanNode(static_cast<char>(i), frequency[i]);
                Que.Enqueue(newNode);
            }
        }
        HuffmanNode *temp = Que.Dequeue();
        return temp;
    }

    void getCode(HuffmanNode *r, string huffcode) {
        HuffmanNode *temp = r;

        if (temp == NULL) {
            return;
        } else {
            getCode(temp->left, huffcode + "0");
            getCode(temp->right, huffcode + "1");
            if (temp->left == NULL && temp->right == NULL) {
                cout << setw(10) << temp->ch
                     << setw(12) << frequency[(int)temp->ch]
                     << setw(12) << (int)temp->ch
                     << setw(20) << huffcode << endl;
            }
        }
    }

    string retrieve(int sizeBit) {
        const string COMPRESSED_FILE = "compressFile.icpb and ibzm";
        ifstream fp(COMPRESSED_FILE);
        string BITS, ORIG;

        if (fp.is_open()) {
            char c;
            while (fp.get(c)) {
                int ch = static_cast<int>(c);
                int origCH = ch - 32;
                string binary = (origCH == 0) ? "000000" : "";

                while (origCH > 0) {
                    int remainder = origCH % 2;
                    binary = static_cast<char>('0' + remainder) + binary;
                    origCH /= 2;
                }

                while (binary.length() < 6) {
                    binary = '0' + binary;
                }
                BITS += binary;
            }
            int index = 0;
            while (index < sizeBit) {
                ORIG += BITS[index];
                index++;
            }
            cout << ORIG << endl;
            fp.close();
        }
        system("cls");
        return ORIG;
    }

    void getChar(HuffmanNode *r, const string &trav) {
        HuffmanNode *temp = r;
        if (temp != NULL) {
            cout << "File successfully decompressed." << endl;
            cout << "Decompressed file output: " << endl;
            for (char c : trav) {
                if (c == '1') {
                    temp = temp->right;
                } else if (c == '0') {
                    temp = temp->left;
                }

                if (temp->left == NULL && temp->right == NULL) {
                    cout << temp->ch;
                    temp = r;
                }
            }
        }
    }

private:
    HuffmanNode *root;
};

int main() {
    Huff huffman;
    huffman.huffman();
    return 0;
}
