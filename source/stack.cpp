#include "stack.h"
#include <stdexcept>
#include <iostream>

using namespace std;

template <typename T>
stack<T>::stack(size_t max): _head(nullptr), _size(0), _max(max) {}

template <typename T>
stack<T>::~stack() {
	node *tmp = _head;
	node *next;
	while (tmp) {
		next = tmp->get_next();
		delete tmp;
		tmp = next;
	}
}

template <typename T>
void stack<T>::push(T ent) {
	if (full()) throw runtime_error("queue is full");
	if (_head == nullptr) {
		_head = new node(ent);
		_size++;
		return;
	}
	
	node *new_node = new node(ent, _head);
	_head = new_node;
	_size++;
}

template <typename T>
T stack<T>::pop() {
	if (empty()) throw runtime_error("queue is empty");
	T tmp = _head->get_entry();
	node *tmp_node = _head;
	_head = _head->get_next();
	delete tmp_node;
	_size--;
	return tmp;
}

template <typename T>
T &stack<T>::peek() {
	if (empty()) throw runtime_error("queue is empty");
	return _head->get_entry();
}


template <typename T>
bool stack<T>::full() {
	return (_size == _max) && (_max > 0);
}

template <typename T>
bool stack<T>::empty() { return _size == 0; }

template <typename T>
size_t stack<T>::size() { return _size; }

template class stack<int>;
