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

template <class VtPtr>
struct Traits_ {
	static const char* name() { return "unknown"; }
};

template <class VT>
struct Traits_<Foo1<VT>*> {
	static const char* name() { return "foo1"; }
};

template <class VT>
struct Traits_<Foo2<VT>*> {
	static const char* name() { return "foo2"; }
};

template <class VT>
struct Traits : public Traits_<VT*> {
};

int main()
{
	std::cout << Traits<Foo1<int> >::name() << "\n";
	std::cout << Traits<ExtFoo1>::name() << "\n";
	std::cout << Traits<ExtFoo2>::name() << "\n";
    return 0;
}

