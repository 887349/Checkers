#include"stack.hpp"
#include<vector>

struct Stack_int::Impl{
	std::vector<int> v;
};
	

Stack_int::Stack_int() {
	pimpl = new Impl;
}

Stack_int::Stack_int(const Stack_int& s) {
	pimpl = new Impl;
	pimpl->v = s.pimpl->v;
}

Stack_int::~Stack_int() {
	delete pimpl;
}

void Stack_int::push(int elem) {
	pimpl->v.push_back(elem);
}

int Stack_int::pop() {
	int elem{pimpl->v.back()};
	pimpl->v.pop_back();
	return elem;
}

bool Stack_int::is_empty() {
	return (pimpl->v.size() == 0);
}
