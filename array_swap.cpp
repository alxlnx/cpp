#include <iostream>

void swap_arrs(int** a, int** b) {
	int* tmp = *a;
	*a = *b;
	*b = tmp;
}

int main() {
	//int a[] = {1, 2, 3};
	//int b[] = {4, 5, 6};
	int* a = new int[]{1, 2, 3};
	int* b = new int[]{4, 6, 6};

	std::cout << "a:\n";
	for (int i{}; i < 3; ++i) {
		std::cout << a[i];
	}
	std::cout << '\n';
	
	std::cout << "b:\n";
	for (int i{}; i < 3; ++i) {
		std::cout << b[i];
	}
	std::cout << '\n';

	swap_arrs(&a, &b);

	std::cout << "a:\n";
	for (int i{}; i < 3; ++i) {
		std::cout << a[i];
	}
	std::cout << '\n';
	
	std::cout << "b:\n";
	for (int i{}; i < 3; ++i) {
		std::cout << b[i];
	}
	std::cout << '\n';

	return 0;
}
