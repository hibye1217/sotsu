#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ifstream ftxt;
	string s;
	ftxt.open("readme.txt");

	ftxt >> s;
	cout << s;

	ofstream otxt;
	string str;
	otxt.open("tmp.txt");

	cin >> str;
	otxt << str;

	ftxt.close();
	otxt.close();
}