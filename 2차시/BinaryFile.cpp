#include <iostream>
#include <fstream>
#include <iomanip> // ����� �� �Ų����� ����ϱ� ���ؼ�
#include <cstdlib>
using namespace std;

bool getStu(ifstream& stuFile, int& stuId, int& exam1, int& exam2, int& finalExam) {
	stuFile >> stuId >> exam1 >> exam2 >> finalExam;
	if (!stuFile) {
		return false;
	}
	else {
		return true;
	}
}

void calcGrade(int exam1, int exam2, int finalExam, int& avg, char& grade) {
	avg = (exam1 + exam2 + finalExam) / 3;
	if (avg >= 90) { grade = 'A'; }
	else if (avg >= 80) { grade = 'B'; }
	else if (avg >= 70) { grade = 'C'; }
	else if (avg >= 60) { grade = 'D'; }
	else { grade = 'F'; }
}

void writeStu(ofstream& gradesFile, int stuId, int avg, char grade) {
	gradesFile.fill('0');
	gradesFile << setw(4) << stuId;
	gradesFile.fill(' ');
	gradesFile << setw(3) << avg;
	gradesFile << ' ' << grade << endl;
}

int main() {
	cout << "���α׷� ����" << endl;

	ifstream stuFile;
	stuFile.open("ch7STUFL.DAT");
	if (!stuFile) {
		cerr << "FileOpenError" << endl;
		exit(100);
	}

	ofstream gradesFile;
	gradesFile.open("ch7STUGR.DAT");
	if (!gradesFile) {
		cerr << "FileOpenError" << endl;
		exit(102);
	}

	int stuId, exam1, exam2, finalExam, avg;
	char grade;

	while (getStu(stuFile, stuId, exam1, exam2, finalExam)) {
		calcGrade(exam1, exam2, finalExam, avg, grade);
		writeStu(gradesFile, stuId, avg, grade);
	}

	stuFile.close(); gradesFile.close();

	cout << "���α׷� ����" << endl;

	return 0;
}