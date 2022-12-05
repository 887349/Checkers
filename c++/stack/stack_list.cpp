#include"stack.hpp"

struct Cella{
	int info;
	Cella* next;
};




struct Stack_int::Impl{
	Cella* head;
};

Stack_int::Stack_int() {
	pimpl = new Impl;
	pimpl->head = nullptr;
}

Stack_int::Stack_int(const Stack_int& s) {
	Cella* pc{s.pimpl->head};
	pimpl->head = nullptr;
	Cella* last = nullptr;

	while (pc) {
		Cella* nuova = new Cella;
		nuova->info = pc->info;
		nuova->next = nullptr;
		if (pimpl->head==nullptr) {
			pimpl->head = nuova;
			last = nuova;
		}
		else {
			last->next = nuova;
			last = nuova;
		}
		pc = pc->next;
	}
}

void Stack_int::push(int elem) { //Prepend
	Cella* nuova = new Cella;
	nuova->info = elem;
	nuova->next = pimpl->head;
	pimpl->head=nuova;
}

int Stack_int::pop() {
	int elem = pimpl->head->info;
	Cella* supp = pimpl->head;
	pimpl->head=pimpl->head->next;
	delete supp;
	return elem;
}

bool Stack_int::is_empty() {
	return (pimpl->head == nullptr);
}

Stack_int::~Stack_int() {
	while(pimpl->head) {
		Cella* supp = pimpl->head;
		pimpl->head=pimpl->head->next;
		delete supp;
	}
	delete pimpl;
}
