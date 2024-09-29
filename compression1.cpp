#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;
string filename;
struct HuffmanNode {
    char ch;
    int frequency;
    HuffmanNode *left;
    HuffmanNode *right;
    HuffmanNode *next;

    HuffmanNode(char c, int x) {
        ch = c;
        frequency = x;
        left = NULL;
        right = NULL;
        next = NULL;
    }

    HuffmanNode(int x, HuffmanNode *l, HuffmanNode *r) {
        ch = '\0';
        frequency = x;
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
                int sum = left->frequency + right->frequency;
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

        while (current != NULL && newNode->frequency >= current->frequency) {
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
    PriorityHuffmanQueue queue;

public:
    Huff() {
        root = NULL;
    }

    void initialize() {
        for (int i = 0; i < 256; i++) {
            frequency[i] = 0;
        }
    }

    void counter(const string &file) {
        ifstream in(file);
        if (in.is_open()) {
            char c;
            while (in.get(c)) {
                frequency[(int)c]++;
            }
        }
    }

    HuffmanNode *startQueue() {
        for (int i = 0; i < 256; i++) {
            if (frequency[i] > 0) {
                HuffmanNode *newNode = new HuffmanNode((char)i, frequency[i]);
                queue.Enqueue(newNode);
            }
        }
        return queue.Dequeue();
    }

    void huffman(const string &file) {
        initialize();
        counter(file);
        root = startQueue();
        system("cls");
        cout << "\n\t\t\t\tCharacter";
        cout << "\tFrequency";
        cout << "\tASCII";
        cout << "\t\tHuffman Code" << endl;
        cout << endl;
        getCode(root, "");
        makebit(file);
    }

    void getCode(HuffmanNode *r, string huffcode) {
        if (r == NULL) {
            return;
        } else {
            getCode(r->left, huffcode + "0");
            getCode(r->right, huffcode + "1");
            if (r->left == NULL && r->right == NULL) {
                huffmanCode[(int)r->ch] = huffcode;
                cout << setw(37) << r->ch
                     << setw(15) << frequency[(int)r->ch]
                     << setw(15) << (int)r->ch
                     << setw(20) << huffcode << endl;
            }
        }
    }

    void makebit(const string &file) {
        ifstream in(file);
        if (in.is_open()) {
            char c;
            string bits;
            while (in.get(c)) {
                bits += huffmanCode[(int)c];
            }

            save(bits);
            int bitSize = bits.length();
            int remainder = bitSize % 6;

            if (remainder > 0) {
                for (int i = remainder; i < 6; i++) {
                    bits = bits + "1";
                }
            }
            convertToASCII(bits);
        } else {
            cerr << "Error. Please try opening the file again." << endl;
        }
    }

    void convertToASCII(const string &bits) {
        int bitSize = bits.length();
        int index = 0;
        int count = 0;
        string padded, character;
        while (index < bitSize) {
            count++;
            padded += bits[index];
            if (count == 6) {
                int ascii = stoi(padded, nullptr, 2);
                int add = ascii + 32;
                character += static_cast<char>(add);
                count = 0;
                padded = "";
            }
            index++;
        }
        cout << "\n\t\t\t\t\tFile successfully compressed." << endl;
        cout << "\n\t\t\t\t\tPlease check the compressed file for the results." << endl;
        ofstream out("compressFile.icpb and ibzm");
        if (out.is_open()) {
            out << character;
        }
    }

    void save(string bits) {
        ofstream out("save.compression");
        if (out.is_open()) {
            out << bits.length() << endl;
            for (int i = 0; i < 256; i++) {
                if (frequency[i] > 0) {
                    if ((char)i == 10)
                        out << "NEWLINE" << endl << frequency[i] << endl;
                    else if ((char)i == 32)
                        out << "SPACE" << endl << frequency[i] << endl;
                    else if ((char)i == 9)
                        out << "TAB" << endl << frequency[i] << endl;
                    else
                        out << (char)i << endl << frequency[i] << endl;
                }
            }
        }
    }

private:
    HuffmanNode *root;
};

int main() {
    Huff huffman;
    cout << "\n\n\n\n\n\n\n\t\t\t\t\tHuffman File Compression \n";
    cout << "\n\t\t\t\t\tEnter file name: ";
    cin >> filename;
    const string file = filename + ".txt";
    ifstream read(file);
    if (!read.is_open()) {
        cerr << "Error. Please try opening the file again." << endl;
    } else {
        huffman.huffman(file);
    }
    return 0;
}
