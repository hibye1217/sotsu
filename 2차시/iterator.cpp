#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> vec{ 10, 20, 30, 40, 50 };

	vector<int>::iterator iter = vec.begin();
	cout << *iter << endl;

	iter++;
	cout << *iter << endl;

	vector<int> vc{ 1, 2, 3, 4, 5 };

	for (auto iter = vc.begin(); iter != vc.end(); iter++) {
		cout << *iter << endl;
	}
	cout << endl;
}