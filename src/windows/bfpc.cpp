#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
namespace d {
    vector<int> mem = { 0 };
    vector<string> fnc = {};
    int pos = 0;
    int atcc = 0;
    char atcs = 'X';
    char atce = 'X';
    string atct = "";
    vector<string> atcdat = { "" };
    vector<int> override = {};
    char rcmd = ' ';
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
void mmc(int pos, bool s = true) {
    while (pos >= d::mem.size()) {
        d::mem.push_back(0);
    }
    if (s) {
        d::pos = pos;
    }
}
void parse(string t) {
    for (char& c : t) {
        if (d::atcc == 0) {
            if (c != '(' && d::rcmd != ' ') {
                d::rcmd = ' ';
            }
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
            else if (c == '{') {
                d::atcc += 1;
                d::atcs = '{';
                d::atce = '}';
                d::atcdat = { to_string(d::pos) };
            }
            else if (c == '^') {
                d::rcmd = '^';
            }
            else if (c == '(') {
                d::atcc += 1;
                d::atcs = '(';
                d::atce = ')';
            }
            else if (c == '%') {
                d::override = {};
                int op = d::pos;
                vector<int> om = d::mem;
                parse(d::fnc[d::mem[d::pos]]);
                vector<int> nm = d::mem;
                d::mem = om;
                for (int c = 0; c < d::override.size(); c++) {
                    auto i = d::override[c];
                    mmc(i);
                    d::mem[i] = nm[i];
                }
                d::pos = op;
            }
            else if (c == '&') {
                d::override.push_back(d::pos);
            }
            else if (c == '=') {
                d::rcmd = '=';
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
            if (c == d::atce) {
                d::atcc--;
            }
            else if (c == d::atcs) {
                d::atcc++;
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
                /*else if (d::atcs == '^') {
                    mmc(stoi(d::atct));
                    d::atcs = 'X';
                    d::atce = 'X';
                    d::atct = "";
                }
                else if (d::atcs == '=') {
                    int v = d::mem[d::pos];
                    mmc(stoi(d::atct),false);
                    d::mem[stoi(d::atct)] = v;
                    d::atcs = 'X';
                    d::atce = 'X';
                    d::atct = "";
                }*/
                else if (d::atcs == '{') {
                    mmc(stoi(d::atcdat[0]));
                    d::fnc.push_back(d::atct);
                    d::mem[d::pos] = d::fnc.size() - 1;
                    d::atcs = 'X';
                    d::atce = 'X';
                    d::atct = "";
                }
                else if (d::atcs == '(') {
                    if (d::rcmd == '^') {
                        mmc(stoi(d::atct));
                    }
                    else if (d::rcmd == '=') {
                        int v = d::mem[d::pos];
                        mmc(stoi(d::atct), false);
                        d::mem[stoi(d::atct)] = v;
                    }
                    d::atcs = 'X';
                    d::atce = 'X';
                    d::atct = "";
                    d::rcmd = ' ';
                }
            }
        }
    }
}
int main(int argc, char** argv[])
{
    parse("
