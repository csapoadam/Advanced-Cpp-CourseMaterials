// Lesson-01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include "types.h"

/*

class MyClass{
	int val;
public:
	explicit MyClass(int v) : val{ v } {}
	virtual void print() { std::cout << val << std::endl; }
};

class MyChildClass : public MyClass {
public:
	MyChildClass() : MyClass{0} {}
	void print();
};

void MyChildClass::print() {
	std::cout << "Childclass" << std::endl;
}

class MyGrandchildClass : public MyChildClass {
public:
	MyGrandchildClass() : MyChildClass{} {}
	void print() { std::cout << "Grandchildclass" << std::endl; }
};

void function(int* ip, int length) {
	for (int inx = 0; inx < length; inx++) {
		std::cout << ip[inx] << ", ";
	}
	std::cout << std::endl;
}
*/

/*
void function2(std::array arr, int length) {
	for (int inx = 0; inx < length; inx++) {
		std::cout << ip[inx] << ", ";
	}
	std::cout << std::endl;
}
*/

/*

auto add(int a, int b) {
	return a + b;
}

auto multiply(int a, int b) {
	return a * b;
}

auto applyBinary(binaryIntOp f, int a, int b) {
	return f(a, b);
}

class MultiplyWithCount {
	int calledNTimes;
public:
	MultiplyWithCount() : calledNTimes{0} {}
	void print() { std::cout << "I was called " << calledNTimes << " times" << std::endl; }
	operator std::string() { return "I was called " + std::to_string(calledNTimes) + " times"; }
	operator binaryIntOp() {
		calledNTimes++;
		return multiply;
	}
};

*/

class ConcatStrings {
public:
	std::string operator()(std::string s1, std::string s2) {
		return s1 + s2;
	}
};

class ConcatStringsWithRvalueRefs {
public:
	std::string operator()(std::string&& s1, std::string&& s2) {
		return s1 + s2;
	}
};

auto& returnRef(int& p) {
	return p;
}

struct MyStruct {
	int d;
	MyStruct(int d) : d(d) {}
};

template <typename Object>
auto increment(Object&& toIncrement) {
	toIncrement++;
	return toIncrement;
}


int main()
{
	int value = 5;
	int& newvalue = increment(value);
	std::cout << "newvalue = " << newvalue << std::endl;

	/*
	int a = 10;

	decltype(a) b; // a int lesz
	std::cout << "decltype(a) is " << typeid(b).name() << std::endl;
	decltype(returnRef(a)) c = b; // muszaj neki erteket adni! mert referencia
	
	MyStruct* ms = new MyStruct(5);
	decltype(ms->d) e1;
	decltype((ms->d)) e2; // itt is muszaj erteket adni! Nem id-expression kifejezes
	*/

	//std::cout << typeid(decltype(a)).name() << std::endl;
	//std::cout << typeid(decltype(returnRef(a))).name() << std::endl;
	//std::cout << typeid(decltype((ns::nonlocalInt))).name() << std::endl;

	/*
	MultiplyFunctor mf;
	ConcatStringsWithRvalueRefs cs;
	std::cout << applyBinaryFunction<
		MultiplyFunctor, int>(mf, 2, 8) << std::endl;
	std::cout << applyBinaryFunction<
		ConcatStringsWithRvalueRefs,
		std::string>(cs, "Hello ", "World!") << std::endl;
	*/

	/*

	std::cout << intval << std::endl;


	std::cout << " 3 + 4 = " << applyBinary(add, 3, 4) << std::endl;
	std::cout << " 3 + 4 = " << applyBinary(&add, 3, 4) << std::endl;
	MultiplyWithCount mwc;
	std::cout << " 3 * 4 = " << applyBinary(mwc, 3, 4) << std::endl;
	std::cout << " 3 * 4 = " << applyBinary(mwc, 3, 4) << std::endl;
	std::cout << std::string(mwc) << std::endl;
	
	MultiplyFunctor functor;
	std::cout << " 5 * 8 = " << functor(5, 8) << std::endl;

	//applyBinary(functor, 3, 4);
	
	//int arr[]{1,2,3,4};
	fourarr arr{1, 2, 3, 4};
	std::cout << "size of array: " << arr.size() << std::endl;
	
	for (auto& item : arr) {
		item = item + 1;
		std::cout << item << ", ";
	}
	std::cout << std::endl;
	std::cout << arr[0] << std::endl;
	
	std::cout << std::endl;
	*/
	/*
	MyClass c(5);
	MyChildClass x{};
	MyGrandchildClass y{};
	//c.print();
	//x.print();

	std::vector<MyClass*> vec;
	vec.push_back(&c);
	vec.push_back(&x);
	vec.push_back(&y);

	for (auto v : vec) {
		v->print();
	}

	//MyClass d = 5;

	//c.print();
	//d.print();

	//int y{ 55.6 };
	//std::cout << " y = " << y << std::endl;
	*/

	std::cin.get();
    return 0;
}

