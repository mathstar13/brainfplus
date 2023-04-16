#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
namespace d {
    vector<int> mem = { 0 };
    int pos = 0;
    int atcc = 0;
    char atcs = 'X';
    char atce = 'X';
    string atct = "";
}
string fread(string filename) {
    // Create a text string, which is used to output the text file
    string retv;
    string myText;

    // Read from the text file
    ifstream MyReadFile(filename);
    while (getline(MyReadFile, myText)) {
        // Output the text from the file
        retv += myText + "\n";
    }

    // Close the file
    MyReadFile.close();
    return retv;
}
void mmc(int pos) {
    while (pos >= d::mem.size()) {
        d::mem.push_back(0);
    }
    d::pos = pos;
}
void parse(string t) {
    for (char& c : t) {
        if (d::atcc == 0) {
            if (c == '>') {
                mmc(d::pos + 1);
            }
            else if (c == '<') {
                mmc(d::pos - 1);
            }
            else if (c == '+') {
                d::mem[d::pos]++;
            }
            else if (c == '.') {
                cout << (char)d::mem[d::pos];
            }
            else if (c == '_') {
                cout << d::mem[d::pos];
            }
            else if (c == ',') {
                string c;
                cin >> c;
                d::mem[d::pos] = c[0];
            }
            else if (c == '-') {
                d::mem[d::pos]--;
            }
            else if (c == '[') {
                d::atcc += 1;
                d::atcs = '[';
                d::atce = ']';
            }
            else if (c == '(') {
                d::atcc += 1;
                d::atcs = '(';
                d::atce = ')';
            }
            else if (c == ':') {
                cout << "Dev Help" << endl;
                string ty;
                cout << "1. Get Dev Info\n2. BrainF+ Help\n:";
                cin >> ty;
                if (ty == "1") {
                    string a;
                    cout << "Current Cell: " << d::pos << endl << "Current Numerical Value: " << d::mem[d::pos] << endl;
                    system("pause");
                }
            }
        }
        else {
            if (c == d::atcs) {
                d::atcc++;
            }
            else if (c == d::atce) {
                d::atcc--;
            }
            else {
                d::atct += c;
            }
            if (d::atcc == 0) {
                if (d::atcs == '[') {
                    while (d::mem[d::pos] != 0) {
                        parse(d::atct);
                    }
                    d::atcs = 'X';
                    d::atce = 'X';
                    d::atct = "";
                }
                else if (d::atcs == '(') {
                    mmc(stoi(d::atct));
                    d::atcs = 'X';
                    d::atce = 'X';
                    d::atct = "";
                }
            }
        }
    }
}
int main()
{
    parse("