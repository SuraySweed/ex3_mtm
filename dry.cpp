#include <iostream>
#include <vector>
#include <exception>
#include <memory>

#define ZERO 0

using std::exception;
using std::shared_ptr;

class BadInput : public exception {};

void validation(int start, int step, int stop, int vector_size) {
	if (start < ZERO || start >= vector_size || stop < ZERO || stop > vector_size || step <= ZERO) {
		throw BadInput();
	}
}

template <class T>
std::vector<T> slice(std::vector<T> vec, int start, int step, int stop){
	std::vector<T> sliced_vevtor = std::vector<T>();
	validation(start, step, stop, vec.size());
	if (start < stop) {
		for (std::vector<T>::iterator iter = vec.begin(); iter != vec.end(); iter += step) {
			for (int i = start; i < stop; i += step) {
				sliced_vevtor.push_back(vec[i]);
			}
		}
		return sliced_vevtor;
	}
}

class A {
public:
	std::vector<shared_ptr<int>> values;

	void add(int x) { values.push_back(shared_ptr<int>(new int(x))); }
};

int main() {
	A a, sliced;
	a.add(0); a.add(1); a.add(2); a.add(3); a.add(4); a.add(5);
	sliced.values = slice(a.values, 1, 1, 4);
	*(sliced.values[0]) = 800;
	std::cout << *(a.values[1]) << std::endl;
	return 0;
}

/*
int main() {
	std::vector<char> vec1{ 'a', 'b', 'c', 'd', 'e' };
	std::vector<int> empty_vec{};
	 returns vector with values a,c
	try {
		std::vector<char> vec_sliced = slice(vec1, 0, 2, 4);
		std::vector<char> vec_sliced = slice(vec1, 1, 1, 5);
		std::vector<int> vec_sliced = slice(empty_vec, 10, 2, 5);
		for (std::vector<int>::iterator iter = vec_sliced.begin(); iter != vec_sliced.end(); ++iter) {
			std::cout << *iter << " ";
		}
		std::cout << "\n";
	}
	catch(BadInput& e){
		std::cout << "bad input" << std::endl;
	}
	return 0;
}
*/