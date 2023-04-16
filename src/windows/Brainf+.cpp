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
    string t = fread(home+"/bfpc.cpp");
    t.pop_back();
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
