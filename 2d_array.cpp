#include <iostream>

int main() {
	int n{5}, m{3}; // rows and cols respectively

	int** arr { new int*[n] };
	for (int i{}; i < n; ++i) {
		arr[i] =  new int[m];
	}
	for (int i{}; i < n; ++i) {
		for (int j{}; j < m; ++j) {
			arr[i][j] = i * n + j;
		}
	}

	for (int i{}; i < n; ++i) {
		for (int j{}; j < m; ++j) {
			std::cout << arr[i][j] << ' ';
		}
		std::cout << '\n';
	}
	
	// clean up, yeah it is rather lengthy
	for (int i{}; i < n; ++i) {
		delete[] arr[i];
	}
	delete[] arr;
	
	return 0;
}
