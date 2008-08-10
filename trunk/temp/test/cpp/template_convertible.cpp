#include <iostream>

template <class A>
class Foo1 {
};

template <class A>
class Foo2 {
};

class ExtFoo1 : public Foo1<int>
{
};

class ExtFoo2 : public Foo2<int>
{
};

template <class From, template <class ArgT> class To>
struct IsTemplateConvertible
{
	struct AnyConversion_
	{
		template <typename T1>
		AnyConversion_(const T1&);
	};
	
	struct No_ { char b[0x100]; };
	struct Yes_ { char b[0x200]; };

	template <class ArgT>
	static Yes_ check_(To<ArgT>*, int);
	static No_ check_(AnyConversion_, ...);
	static From* inst_;

	enum {
		value = (sizeof(check_(inst_, 0)) == sizeof(Yes_))
	};
};

int main()
{
	std::cout << IsTemplateConvertible<ExtFoo1, Foo1>::value << "\n";
	std::cout << IsTemplateConvertible<ExtFoo1, Foo2>::value << "\n";
	std::cout << IsTemplateConvertible<ExtFoo2, Foo1>::value << "\n";
	std::cout << IsTemplateConvertible<ExtFoo2, Foo2>::value << "\n";
    return 0;
}

