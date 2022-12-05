class Stack_int{
public:
	Stack_int();
	Stack_int(const Stack_int& s);
	~Stack_int();

	void push(int elem);
	int pop();
	bool is_empty();

private:
	struct Impl;
	Impl* pimpl;
};

	




