#include <iostream>
#include <fstream>
#include <string>
using namespace std;
string fread(string filename) {
    string retv;
    string myText;
    ifstream MyReadFile(filename);
    while (getline(MyReadFile, myText)) {
        retv += myText + "\n";
    }
    MyReadFile.close();
    return retv;
}
void replaceAll(string& str, const string& from, const string& to) {
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}
int main(int argc, char* argv[])
{
    string home;
    {
        char* pValue;
        size_t len;
        errno_t err = _dupenv_s(&pValue, &len, "appdata");
        if (err) return -1;
        if (pValue != 0) {
            string hd(pValue);
            home = fread(hd + "\\Brainf+\\dir.txt");
            replaceAll(home, "\n", "");
        }
        if (home.back() == '\\') {
            home.pop_back();
        }
    }
    string o = "a.exe";
    string bf;
    if (argc == 2){
        bf = fread(argv[1]);
    }
    else if (argc == 1) {
        return 1;
    }
    else {
        int ty = 0;
        for (int i = 1; i < argc; i++) {
            string t = argv[i];
            if (ty == 0) {
                if (t == "-o") {
                    ty = 1;
                }
                else {
                    bf = fread(t);
                }
            }
            else if (ty == 1) {
                o = t;
                ty = 0;
            }
        }
    }
    string t = "#include <iostream>\n#include <fstream>\n#include <string>\n#include <sstream>\n#include <vector>\nusing namespace std;\nnamespace d {\n    vector<int> mem = { 0 };\n    vector<string> fnc = {};\n    int pos = 0;\n    int atcc = 0;\n    char atcs = 'X';\n    char atce = 'X';\n    string atct = \"\";\n    vector<string> atcdat = { \"\" };\n    vector<int> override = {};\n    char rcmd = ' ';\n}\nstring fread(string filename) {\n    // Create a text string, which is used to output the text file\n    string retv;\n    string myText;\n\n    // Read from the text file\n    ifstream MyReadFile(filename);\n    while (getline(MyReadFile, myText)) {\n        // Output the text from the file\n        retv += myText + \"\\n\";\n    }\n\n    // Close the file\n    MyReadFile.close();\n    return retv;\n}\nvoid mmc(int pos, bool s = true) {\n    while (pos >= d::mem.size()) {\n        d::mem.push_back(0);\n    }\n    if (s) {\n        d::pos = pos;\n    }\n}\nvoid parse(string t) {\n    for (char& c : t) {\n        if (d::atcc == 0) {\n            if (c != '(' && d::rcmd != ' ') {\n                d::rcmd = ' ';\n            }\n            if (c == '>') {\n                mmc(d::pos + 1);\n            }\n            else if (c == '<') {\n                mmc(d::pos - 1);\n            }\n            else if (c == '+') {\n                d::mem[d::pos]++;\n            }\n            else if (c == '.') {\n                cout << (char)d::mem[d::pos];\n            }\n            else if (c == '_') {\n                cout << d::mem[d::pos];\n            }\n            else if (c == ',') {\n                string c;\n                cin >> c;\n                d::mem[d::pos] = c[0];\n            }\n            else if (c == '-') {\n                d::mem[d::pos]--;\n            }\n            else if (c == '[') {\n                d::atcc += 1;\n                d::atcs = '[';\n                d::atce = ']';\n            }\n            else if (c == '{') {\n                d::atcc += 1;\n                d::atcs = '{';\n                d::atce = '}';\n                d::atcdat = { to_string(d::pos) };\n            }\n            else if (c == '^') {\n                d::rcmd = '^';\n            }\n            else if (c == '(') {\n                d::atcc += 1;\n                d::atcs = '(';\n                d::atce = ')';\n            }\n            else if (c == '%') {\n                d::override = {};\n                int op = d::pos;\n                vector<int> om = d::mem;\n                parse(d::fnc[d::mem[d::pos]]);\n                vector<int> nm = d::mem;\n                d::mem = om;\n                for (int c = 0; c < d::override.size(); c++) {\n                    auto i = d::override[c];\n                    mmc(i);\n                    d::mem[i] = nm[i];\n                }\n                d::pos = op;\n            }\n            else if (c == '&') {\n                d::override.push_back(d::pos);\n            }\n            else if (c == '=') {\n                d::rcmd = '=';\n            }\n            else if (c == ':') {\n                cout << \"Dev Help\" << endl;\n                string ty;\n                cout << \"1. Get Dev Info\\n2. BrainF+ Help\\n:\";\n                cin >> ty;\n                if (ty == \"1\") {\n                    string a;\n                    cout << \"Current Cell: \" << d::pos << endl << \"Current Numerical Value: \" << d::mem[d::pos] << endl;\n                    system(\"pause\");\n                }\n            }\n        }\n        else {\n            if (c == d::atce) {\n                d::atcc--;\n            }\n            else if (c == d::atcs) {\n                d::atcc++;\n            }\n            else {\n                d::atct += c;\n            }\n            if (d::atcc == 0) {\n                if (d::atcs == '[') {\n                    while (d::mem[d::pos] != 0) {\n                        parse(d::atct);\n                    }\n                    d::atcs = 'X';\n                    d::atce = 'X';\n                    d::atct = \"\";\n                }\n                /*else if (d::atcs == '^') {\n                    mmc(stoi(d::atct));\n                    d::atcs = 'X';\n                    d::atce = 'X';\n                    d::atct = \"\";\n                }\n                else if (d::atcs == '=') {\n                    int v = d::mem[d::pos];\n                    mmc(stoi(d::atct),false);\n                    d::mem[stoi(d::atct)] = v;\n                    d::atcs = 'X';\n                    d::atce = 'X';\n                    d::atct = \"\";\n                }*/\n                else if (d::atcs == '{') {\n                    mmc(stoi(d::atcdat[0]));\n                    d::fnc.push_back(d::atct);\n                    d::mem[d::pos] = d::fnc.size() - 1;\n                    d::atcs = 'X';\n                    d::atce = 'X';\n                    d::atct = \"\";\n                }\n                else if (d::atcs == '(') {\n                    if (d::rcmd == '^') {\n                        mmc(stoi(d::atct));\n                    }\n                    else if (d::rcmd == '=') {\n                        int v = d::mem[d::pos];\n                        mmc(stoi(d::atct), false);\n                        d::mem[stoi(d::atct)] = v;\n                    }\n                    d::atcs = 'X';\n                    d::atce = 'X';\n                    d::atct = \"\";\n                    d::rcmd = ' ';\n                }\n            }\n        }\n    }\n}\nint main(int argc, char* argv[])\n{\n    parse(\"\n"; t.pop_back();
    replaceAll(bf, "\n", "");
    t += bf;
    t += "\");\nreturn 0;\n}";
    ofstream wf("bfp.tmp.cpp", ios::trunc);
    wf << t;
    wf.close();
    replaceAll(home, "\\", "/");
    string c = "start /min \"\" \"" + home + "/bin/g++\" bfp.tmp.cpp -o " + o;
    system(c.c_str());
}
