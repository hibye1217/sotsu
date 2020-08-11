#include <iostream>
using namespace std;

int DividePizza(int pizzaSlice, int person) {
	if (person == 0)
		throw person;
	return pizzaSlice / person;
}

int main() {
	int pizzaSlices = 0;
	int persons = -1;
	int slicesPerPerson = 0;

	try {
		cout << "피자 조각수를 입력하시오: ";
		cin >> pizzaSlices;
		cout << "사람 수를 입력하시오: ";
		cin >> persons;

		slicesPerPerson = DividePizza(pizzaSlices, persons);
		cout << "한 사람당 피자는 " << slicesPerPerson << "조각입니다." << endl;
	}
	catch (int e) {
		cout << "사람이 " << e << "명입니다." << endl;
	}

	return 0;
}