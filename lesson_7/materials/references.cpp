#include <iostream>

int&& xvalue_func();
int& lvalue_func();
int prvalue_func();

int main(int argc, char ** argv)
{
	double d = 0.0;
	const int i = 0;
	
	//#1: Ok, простое lvalue
	int & lvalue = lvalue_func();
	//#2: Error, lvalue ссылка не может быть привязана к prvalue
	int & wrong_lvalue1 = prvalue_func();
	//#3: Error, lvalue ссылка не может быть привязана к xvalue
	int & wrong_lvalue2 = xvalue_func();
	/*
		#4: Error, lvalue ссылка на не константу, не может быть
		привязана к константному выражению
	*/
	int & non_const_lvalue = i;
	/*
		#5: Error, lvalue ссылка не может быть привязана к переменной,
		чей интегральный тип не совпадает с типом ссылки
	*/
	int & type_mismatch_lvalue = d;
	
	//#6: Error, rvalue ссылка не может быть привязана к lvalue
	int && rvalue1 = lvalue_func();
	//#7: Ok, rvalue ссылка привязывается к xvalue
	int && rvalue2 = xvalue_func();
	//#8: Ok, rvalue ссылка привязывается к prvalue
	int && rvalue3 = prvalue_func();
	//#9: Ok, rvalue ссылка привязывается к prvalue
	int && rvalue4 = 0;
	/*
		#10: Error, rvalue ссылка на не константу, не может быть
		привязана к  константному выражению
	*/
	int && non_const_rvalue = i;
	/*
		#11: Ok, rvalue ссылка может быть привязана к переменной, чей
		интегральный тип не совпадает с типом ссылки
	*/
	int && type_mismatch_rvalue = d;

	//#12: Ok, const Type & может быть привязано к любому выражению
	const int & const_lvalue1 = lvalue_func();
	//#13: Ok, const Type & может быть привязано к любому выражению
	const int & const_lvalue2 = prvalue_func();
	//#14: Ok, const Type & может быть привязано к любому выражению
	const int & const_lvalue3 = xvalue_func();
	//#15: Ok, const Type & может быть привязано к любому выражению
	const int & const_lvalue4 = i;
	//#16: Ok, const Type & может быть привязано к любому выражению
	const int & const_lvalue5 = d;
	//#17: Ok, const Type & может быть привязано к любому выражению
	const int & const_lvalue6 = 0;

	//#18: Error, const Type && не может быть привязано к lvalue
	const int && const_rvalue1 = lvalue_func();
	//#19: Ok, const Type && может быть привязано к prvalue
	const int && const_rvalue2 = prvalue_func();
	//#20: Ok, const Type && может быть привязано к xvalue
	const int && const_rvalue3 = xvalue_func();
	//#21: Error, const Type && не может быть привязано к lvalue
	const int && const_rvalue4 = i;
	/*
		#22: Ok, const Type && может быть привязано к выражению, чей
		интегральный тип не совпадает с типом ссылки
	*/
	const int && const_rvalue5 = d;

	system("pause");

	return EXIT_SUCCESS;
}

int && xvalue_func()
{
	return 5;
}

int & lvalue_func()
{
	static int i = 0;
	return i;
}

int prvalue_func()
{
	return 5;
}