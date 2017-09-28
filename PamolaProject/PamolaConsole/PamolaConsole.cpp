// PamolaConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>

class foo
{
public:


	int a;

private:

};



class bar
{
public:

	std::vector<foo*> foos;

private:

};


int main1()
{

	bar* bar1 = new bar;

	foo* foo1 = new foo;
	foo* foo2 = new foo;
	foo* foo3 = new foo;

	foo1->a = 1;
	foo2->a = 2;
	foo3->a = 3;

	bar1->foos = { foo1,foo2,foo3 };

	std::vector<foo*> x;
	x = bar1->foos;

	std::cout << "Length of X:\t" << x.size() << std::endl;

	std::cout << "x = [";
	for each (foo* var in x)
	{
		std::cout << " " << var->a;
	}
	std::cout << "]" << std::endl;


	x.erase(x.begin());

	std::cout << "Length of X:\t" << x.size() << std::endl;

	std::cout << "x = [";
	for each (foo* var in x)
	{
		std::cout << " " << var->a;
	}
	std::cout << "]" << std::endl;

	std::cout << "Length of Foos:\t" << bar1->foos.size() << std::endl;

	std::cout << "bar1.foos = [";
	for each (foo* var in bar1->foos)
	{
		std::cout << " " << var->a;
	}
	std::cout << "]" << std::endl;

	delete bar1;
	delete foo1;
	delete foo2;
	delete foo3;

	return 0;
}

int main2()
{
	bool A; bool B;
		
	std::cout << "Enter boolean A:\t";
	std::cin >> A;

	std::cout << "Enter boolean B:\t";
	std::cin >> B;

	switch (A*2 + B*1)
	{
	case 0: std::cout << "A = false, B = false";	break;
	case 1: std::cout << "A = false, B = true";		break;
	case 2: std::cout << "A = true, B = false";		break;
	case 3: std::cout << "A = true, B = true";		break;
	default:
		break;
	}

	std::string loko;
	std::cin >> loko;
	return 0;
}

int main()
{
	main2();
	return 0;
}
