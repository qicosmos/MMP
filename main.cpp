#include<iostream>
#include<tuple>
#include <brigand.hpp>
#include "list.hpp"

void test_list()
{
	using namespace cosmos;
	using my_list = list<int, bool>;
	using my_list1 = push_back<my_list, char, double>;
	static_assert(std::is_same<my_list1, list<int, bool, char, double>>::value, "no");
	using my_list4 = list<bool, char, char, double, char>;
	static_assert(std::is_same<erase_dupl<my_list4>, list<bool, char, double>>::value, "no");
	static_assert(std::is_same<erase_front<1, my_list4>, list<char, char, double, char>>::value, "no");
	static_assert(std::is_same<erase_front<2, my_list4>, list<char, double, char>>::value, "no");

	static_assert(std::is_same<slice<1, 3, list<bool, char, char, double, char>>, list<char, char>>::value, "no");
	static_assert(std::is_same<slice<0, 3, list<bool, char, char, double, char>>, list<bool, char, char>>::value, "no");

	static_assert(std::is_same<replace_at<2, short, my_list1>, list<int, bool, short, double>>::value, "no");

	using my_list5 = list<bool, char, char, int, double, int, double, char>;
	static_assert(std::is_same<erase_dupl<my_list5>, list<bool, char, int, double>>::value, "no");

	static_assert(std::is_same<replace_all<short, char, my_list5>, list<bool, short, short, int, double, int, double, short>>::value, "no");

	static_assert(std::is_same<erase_all<char, my_list4>, list<bool, double>>::value, "no");
	static_assert(std::is_same<erase_all<char, my_list>, my_list>::value, "no");

	static_assert(std::is_same<erase_type<char, my_list1>, list<int, bool, double>>::value, "no");
	static_assert(size<my_list>::value == 2, "no");
	using my_list3 = pop_front<my_list1>;
	static_assert(std::is_same<my_list3, list<bool, char, double>>::value, "no");
	static_assert(std::is_same<reverse<my_list3>, list<double, char, bool>>::value, "no");
	using ty = at<1, my_list>;
	static_assert(std::is_same<at<2, my_list1>, char>::value, "no");
	static_assert(std::is_same<front<my_list>, int>::value, "no");
	static_assert(std::is_same<back<my_list>, bool>::value, "no");
	using spl = split<3, my_list1 >;

	static_assert(index_of<char, list<bool, char, double>>::value==1, "no");
	static_assert(index_of<double, list<bool, char, double>>::value == 2, "no");
	static_assert(index_of<bool, list<bool, char, double>>::value == 0, "no");
	static_assert(index_of<short, list<bool, char, double>>::value == -1, "no");

	static_assert(std::is_same<as_tuple<my_list>, std::tuple<int, bool>>::value, "no");
	static_assert(std::is_same<as_pair<my_list>, std::pair<int, bool>>::value, "no");
	using spl1 = split<3, std::tuple<int, bool, char, double>, std::tuple<> >;
	std::cout << typeid(spl1).name() << std::endl;
	using spl2 = split1<3, list<int, bool, char, double>>;
	std::cout << typeid(spl2).name() << std::endl;
	static_assert(std::is_same<split<3, my_list1>, list<int, bool,char>>::value, "no");
	static_assert(std::is_same<split1<3, my_list1>, list<int, bool, char>>::value, "no");
	static_assert(std::is_same<pop_back<my_list1>, list<int, bool, char>>::value, "no");
	static_assert(std::is_same<erase_at<2, my_list1>, list<int, bool, double>>::value, "no");
	static_assert(std::is_same<append<my_list, list<char, double>>, my_list1>::value, "no");

	using my_list2 = push_front<my_list, char, double>;
	static_assert(std::is_same<my_list2, list<char, double, int, bool>>::value, "no");

	using my_tp = push_back<std::tuple<int, double>, char, bool>;
	static_assert(std::is_same<my_tp, std::tuple<int, double, char, bool >>::value, "no");
}

void test()
{
	using my_list = brigand::list<bool, int, char *>;
	using e1 = brigand::at<my_list, std::integral_constant<int, 1>>;

	// you might want to use the convenience function at_c
	using e1bis = brigand::at_c<my_list, 1>;
	using my_list2 = brigand::push_back<my_list, char>;
	using my_list3 = brigand::push_front<my_list2, bool>;

	// head is 'bool'
	using head = brigand::front<my_list>;

	// last is 'char *'
	using last = brigand::back<my_list>;
	static_assert(std::is_same<head, bool>::value, "no");
	using my_tuple = brigand::as_tuple<my_list>;
	my_tuple t;
}

int main()
{
	test_list();
	test();
	return 0;
}