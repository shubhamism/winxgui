#include <iostream>

template <class ValueT>
struct ArgTraits
{
	static const char* name() { return "ValueT"; }
};

template <class ValueT, size_t n>
struct ArgTraits<const ValueT[n]>
{
	static const char* name() { return "const ValueT[]"; }
};

template <class ValueT, size_t n>
struct ArgTraits<ValueT[n]>
{
	static const char* name() { return "ValueT[]"; }
};

template <class ValueT>
struct ArgTraits<const ValueT*>
{
	static const char* name() { return "const ValueT*"; }
};

template <class ValueT>
struct ArgTraits<ValueT*>
{
	static const char* name() { return "ValueT*"; }
};

template <class ValueT>
struct ArgTraits<const ValueT&>
{
	static const char* name() { return "const ValueT&"; }
};

template <class ValueT>
struct ArgTraits<ValueT&>
{
	static const char* name() { return "ValueT&"; }
};

template <class ValueT>
void test_arg_traits(const ValueT& v)
{
	std::cout << ArgTraits<ValueT>::name() << "\n";
}

template <class ValueT>
void test_arg_traits(ValueT& v)
{
	std::cout << ArgTraits<ValueT>::name() << "\n";
}

int main()
{
	char const s1[] = "Hello";
	const char* s2 = "Hello";
	char s3[] = "Hello";
	char* s4 = (char*)"Hello";
	char*& s5 = s4;
	const char*& s6 = s2;
	
	test_arg_traits("Hello");
	test_arg_traits(s1);
	test_arg_traits(s2);
	test_arg_traits(s3);
	test_arg_traits(s4);
	test_arg_traits(s5);
	test_arg_traits(s6);
    return 0;
}

