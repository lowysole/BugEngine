#include "String.h"
#include <iostream>
using namespace std;



String::String() : len(0) {
	_char = new char[0];
	_char[0] = '\0';
};

String::String(const char* c){
	size_t cont = 0;
	while (c[cont] != '\0') {
		cont++;
	}
	len = cont;

	_char = new char[len+1];
	for (size_t i = 0; i < len; i++){
		_char[i] = c[i];
	}
	_char[len] = '\0';
}

String::String(const String& other) : len(other.len), _char(other._char) {}

String::~String() {

	Clear();
}


String String::operator+(const String& other) const {
	String result_str;
	size_t new_len = len + other.len;
	char* result_char = new char[new_len+1];
	for (size_t i = 0; i < len; i++) {
		result_char[i] = _char[i];
	}
	for (size_t i = len; i < new_len; i++) {
		result_char[i] = other._char[i - len];
	}
	result_char[new_len] = '\0';
	return  result_char;
}

bool String::operator==(const String& other) const {
	if (len != other.len) {
		return false;
	}
	for (size_t i = 0; i < len; i++) {
		if (_char[i] != other._char[i]) {
			return false;
		}
	}
	return true;
}

void String::Clear() {
	if (_char[0] != '\0') {
		delete[] _char;
		_char[0] = '\0';
	}
	len = 0;
}

