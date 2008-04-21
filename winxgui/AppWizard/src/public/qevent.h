//文件名 qevent.h
//邮件  QWL1996 at GMAIL.COM
//时间  2007.3.25
//功能  委托库 QLib::Event<>
//版本  1.0

//许可协议:
//你可以遵循CPL许可证下自由使用或发布本软件。
//CPL许可证：Common Public License 1.0 (http://opensource.org/licenses/cpl.php)
//你也可以在这个发布中一个名为CPL.txt的文件中获得CPL许可证的详细信息。无论你以
//何种形式使用本软件，你都必须同意本协议中的所有条款。并且，你必须保证这个软件
//的完整性。你不能从本软件中删除这个声明，以及其他任何东西。

//简介  一个简洁高效的C++委托库,支持普通函数,仿函数,类成员函数的委托库,以相同方式声明0-9个参数的任意委托

// 编译器支持 VC60 VC70 VC71 VC80
// operator = ()
// operator safebool ()

//编译器支持 VC60 VC70 VC71
//声明形式 以相同方式声明0-9个参数的任意委托
// QLib::Event<int> ev0; 
// QLib::Event<int,int> ev1;
// QLib::Event<void,int,int> ev2;
//构造函数 支持Event,Event中的单个成员[],普通函数，仿函数，类成员函数，
// QLib::Event<int,int> ev1(&Test1), e1(&Test1),v1;
// QLib::Event<int,int> ev1((Hello()));
// QLib::Event<int,int> ev1(&h,&H::Test1);
// QLib::Event<int,int> ev1(e1); 
// QLib::Event<int,int> ev1(e1[0]); 
//绑定函数  bind 支持普通函数，仿函数，类成员函数, Event
// ev1.bind(&Test1); 
// ev1.bind((Hello())); 
// ev1.bind(&h,&H::Test1);
//解除函数绑定 unbind
//获得已绑定函数的数目 hasbind
//重载运算符 +=, -= 对应 bind, unbind ，支持普通函数，仿函数，类成员函数和 Event
// ev1 += &Test1; 
// ev1 += Hello(); 
// ev1 += QLib::Event(&h,&H::Test1);
// ev1 += e1; 
// ev1 += ev1[0]; 
//重载运算符 ==, != 判断两个Event是否相同，也可判断单一委托时是否与函数相同
// bool b = (ev1 == ev1); 
// bool b = (ev1 == &Test1);
//重载 = 运算符 用于复制Event或单一委托
// ev1 = ev; 
// ev1 = &Test1; ....
//辅助函数
// QLib::Event::param 参数个数
// ev1.size() 委托的函数数目
// ev1.empty() 是否为空
// ev1.clear() 清空
// ev1.removesame() 去除重复的函数
//将Event当作为一个函数进行委托时
// ev1.bind(&e1,&ev::operator());
//将Event中函数传递给另一个Event时
// ev1 += e1;
// ev1.bind(e1);
//调用形式 支持全部调用和单个委托函数的调用
// ev1(10);
// for (int i = 0; i < ev1.size(); i++)
//        ev1[i](10);

#ifndef _QEVENT_20050320_H_
#define _QEVENT_20050320_H_

#pragma warning(disable:4715)
#pragma warning(disable:4786)

#include <vector>
#include <typeinfo>

namespace QLib
{

struct QLib_Event
{

struct NullType;
struct dummy { void nonnull(){};};

typedef void (dummy::*safe_bool)(); //确保safebool不能转型为任何其它类型！

 
template <typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
struct Length
{
	template <typename T1 = NullType> 
	struct Len
	{
		enum{value = 1};
	};
	template<> 
	struct Len<NullType>
	{
		enum {value = 0};
	};	
	enum enum_len {value = Len<T1>::value + Len<T2>::value+Len<T3>::value+Len<T4>::value+Len<T5>::value+Len<T6>::value+Len<T7>::value+Len<T8>::value+Len<T9>::value};
};
//模仿Loki库实现is_function区分普通函数和仿函数
template <typename T>
struct is_function
{
	struct PointerHelper
	{
		PointerHelper(const volatile void*);
	};

	static char IsPointer(PointerHelper);
	static int  IsPointer(...);
	static T MakeT();

	enum { value = (sizeof(char) == sizeof(IsPointer(MakeT()))) };
};

struct MemberFuncBase{
	virtual MemberFuncBase * Clone() = 0;
	virtual bool Equals(MemberFuncBase*) = 0;
};

template <typename CLS, typename PMFC>
struct MemberFuncImpl : public MemberFuncBase
{
	CLS * pcls;
	PMFC  pmf;
	virtual MemberFuncBase * Clone()
	{
		MemberFuncImpl<CLS,PMFC> * p = new MemberFuncImpl<CLS,PMFC>;
		p->pcls = pcls;
		p->pmf = pmf;
		return p;
	}
	virtual bool Equals(MemberFuncBase * base)
	{
		MemberFuncImpl<CLS,PMFC> * p = static_cast<MemberFuncImpl<CLS,PMFC>*>(base);
		return (pcls == p->pcls && pmf == p->pmf);
	}
};

struct EventPtr
{
	union any_ptr
	{
		void * obj_ptr;	
		const void * const_obj_ptr;
		MemberFuncBase * mem_ptr;
	};	

	enum enum_ptr 
	{ 
		any_null, 
		any_obj,
		any_mem, 
		any_fun
	};

	any_ptr any;
	char	vt;

	EventPtr() : vt(any_null) 
	{
	}
	~EventPtr()
	{
		clear();
	}	
	inline void clear()
	{
		if(vt == any_mem) 
			delete any.mem_ptr;
		vt = any_null;
		any.obj_ptr = NULL;
	}
	inline bool empty()
	{
		return vt == any_null;
	}
	EventPtr(const EventPtr & ptr)
	{
		vt = ptr.vt;
		if (vt == any_mem)
		{
			any.mem_ptr = ptr.any.mem_ptr->Clone();
		}
		else
		{
			any.obj_ptr = ptr.any.obj_ptr;
		}
	}
	const EventPtr & operator = (const EventPtr & ptr)
	{
		clear();
		vt = ptr.vt;
		if (vt == any_mem)
		{
			any.mem_ptr = ptr.any.mem_ptr->Clone();
		}
		else
		{
			any.obj_ptr = ptr.any.obj_ptr;
		}
		return *this;
	}
	inline bool operator == (const EventPtr & ptr)
	{
		if (vt != ptr.vt)
			return false;
		if (vt == any_fun)
			return bool(any.obj_ptr == ptr.any.obj_ptr);
		else if (vt == any_mem)
			return bool(any.mem_ptr->Equals(ptr.any.mem_ptr));
		else if (vt == any_obj)
			return bool((typeid(any.obj_ptr) == typeid(ptr.any.obj_ptr) != 0));
		return false;
	}
	inline bool operator != (const EventPtr & ptr)
	{
		return !(*this == ptr);
	}

	inline void set_function_ptr(void * obj_ptr)
	{
		clear();
		vt = any_fun;
		any.obj_ptr = obj_ptr;
	}
	inline void set_function_obj(void * obj_ptr)
	{
		clear();
		vt = any_obj;
		any.obj_ptr = obj_ptr;
	}
	inline void set_function_obj(const void * obj_ptr)
	{
		clear();
		vt = any_obj;
		any.const_obj_ptr = obj_ptr;
	}
	inline void set_member_func(MemberFuncBase * mem_ptr)
	{
		clear();
		vt = any_mem;
		any.mem_ptr = mem_ptr;
	}
};

template <unsigned int n> 
struct EventHelper;

template<>
struct EventHelper<0>
{
	template <typename R>
	struct EventImpl
	{
		template <typename T0 = NullType>
		struct Param
		{
			struct SingleEvent
			{
				R (*invoke)(EventPtr*);
				EventPtr	ptr;

				inline bool empty()
				{
					return ptr.empty();
				}
				inline void clear()
				{
					ptr.clear();
					invoke = NULL;
				}
				inline R operator()()
				{
					return invoke(&ptr);
				}
			};
						 
			typedef typename std::vector<SingleEvent*> EventList;
			EventList	lst;
		
			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					return (fun)();
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					return fun();
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					return (p->pcls->*p->pmf)();
				}
			};
			R operator()()
			{
				for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
				{
					if (i == lst.end()-1)
						return (*i)->invoke(&(*i)->ptr);
					(*i)->invoke(&(*i)->ptr);
				}
			}
		};
	};
	template <>
	struct EventImpl<void>
	{
		typedef void R;
		template <typename T0 = NullType>
		struct Param
		{
			struct SingleEvent
			{
				R (*invoke)(EventPtr*);
				EventPtr	ptr;

				inline bool empty()
				{
					return ptr.empty();
				}
				inline void clear()
				{
					ptr.clear();
					invoke = NULL;
				}
				inline R operator()()
				{
					invoke(&ptr);
				}
			};
			 
			typedef typename std::vector<SingleEvent*> EventList;
			EventList	lst;
			
			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					(fun)();
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					fun();
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					(p->pcls->*p->pmf)();
				}
			};
			R operator()()
			{
				for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
				{
					(*i)->invoke(&(*i)->ptr);
				}
			}
		};
	};
	template <typename R, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
	struct EventBase : public EventImpl<R>::Param<>
	{
	};
};

template<>
struct EventHelper<1>
{
	template <typename R>
	struct EventImpl
	{
		template <typename T1>
		struct Param
		{
			struct SingleEvent
			{
				R (*invoke)(EventPtr*,T1);
				EventPtr	ptr;

				inline bool empty()
				{
					return ptr.empty();
				}
				inline void clear()
				{
					ptr.clear();
					invoke = NULL;
				}
				inline R operator()(T1 t1)
				{
					return invoke(&ptr,t1);
				}
			};
			 
			typedef typename std::vector<SingleEvent*> EventList;
			EventList	lst;
			
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					return fun(t1);
				}
			};
			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					return (fun)(t1);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				inline static R Invoke(EventPtr * ptr, T1 t1)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					return ((p->pcls)->*(p->pmf))(t1);
				}
			};
			inline R operator()(T1 t1)
			{
				for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
				{
					if (i == lst.end()-1)
						return (*i)->invoke(&(*i)->ptr,t1);
					(*i)->invoke(&(*i)->ptr,t1);
				}
			}
		};
	};
	template <>
	struct EventImpl<void>
	{
		typedef void R;
		template <typename T1>
		struct Param
		{
			struct SingleEvent
			{
				R (*invoke)(EventPtr*,T1);
				EventPtr	ptr;

				inline bool empty()
				{
					return ptr.empty();
				}
				inline void clear()
				{
					ptr.clear();
					invoke = NULL;
				}
				inline R operator()(T1 t1)
				{
					invoke(&ptr,t1);
				}
			};
			 
			typedef typename std::vector<SingleEvent*> EventList;
			EventList lst;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					(fun)(t1);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					fun(t1);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					((p->pcls)->*(p->pmf))(t1);
				}
			};
			R operator()(T1 t1)
			{
				for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
				{
					(*i)->invoke(&(*i)->ptr,t1);
				}
			}
		};
	};
	template <typename R, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
	struct EventBase : public EventImpl<R>::Param<T1>//,T2,T3,T4,T5,T6,T7,T8,T9>
	{
	};
};

template<>
struct EventHelper<2>
{
	template <typename R>
	struct EventImpl
	{
		template <typename T1, typename T2>
		struct Param
		{
			struct SingleEvent
			{
				R (*invoke)(EventPtr*,T1,T2);
				EventPtr	ptr;

				inline bool empty()
				{
					return ptr.empty();
				}
				inline void clear()
				{
					ptr.clear();
					invoke = NULL;
				}
				inline R operator()(T1 t1, T2 t2)
				{
					return invoke(&ptr,t1,t2);
				}
			};
		 
			typedef typename std::vector<SingleEvent*> EventList;
			EventList	lst;
			
			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					return (fun)(t1,t2);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					return fun(t1,t2);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					return ((p->pcls->*p->pmf)(t1,t2));
				}
			};
			R operator()(T1 t1, T2 t2)
			{
				for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
				{
					if (i == lst.end()-1)
						return (*i)->invoke(&(*i)->ptr,t1,t2);
					(*i)->invoke(&(*i)->ptr,t1,t2);
				}
			}
		};
	};
	template <>
	struct EventImpl<void>
	{
		typedef void R;
		template <typename T1, typename T2>
		struct Param
		{
			struct SingleEvent
			{
				R (*invoke)(EventPtr*,T1,T2);
				EventPtr	ptr;

				inline bool empty()
				{
					return ptr.empty();
				}
				inline void clear()
				{
					ptr.clear();
					invoke = NULL;
				}
				inline R operator()(T1 t1, T2 t2)
				{
					invoke(&ptr,t1,t2);
				}
			};
			 
			typedef typename std::vector<SingleEvent*> EventList;
			EventList	lst;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					(fun)(t1,t2);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					fun(t1,t2);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					(p->pcls->*p->pmf)(t1,t2);
				}
			};
			R operator()(T1 t1, T2 t2)
			{
				for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
				{
					(*i)->invoke(&(*i)->ptr,t1,t2);
				}
			}
		};
	};
	template <typename R, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
	struct EventBase : public EventImpl<R>::Param<T1,T2>
	{
	};
};

template<>
struct EventHelper<3>
{
	template <typename R>
	struct EventImpl
	{
		template <typename T1, typename T2, typename T3>
		struct Param
		{
			struct SingleEvent
			{
				R (*invoke)(EventPtr*,T1,T2,T3);
				EventPtr	ptr;

				inline bool empty()
				{
					return ptr.empty();
				}
				inline void clear()
				{
					ptr.clear();
					invoke = NULL;
				}
				inline R operator()(T1 t1, T2 t2, T3 t3)
				{
					return invoke(&ptr,t1,t2,t3);
				}
			};
			 
			typedef typename std::vector<SingleEvent*> EventList;
			EventList	lst;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					return (fun)(t1,t2,t3);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					return fun(t1,t2,t3);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					return ((p->pcls->*p->pmf)(t1,t2,t3));
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3)
			{
				for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
				{
					if (i == lst.end()-1)
						return (*i)->invoke(&(*i)->ptr,t1,t2,t3);
					(*i)->invoke(&(*i)->ptr,t1,t2,t3);
				}
			}
		};
	};
	template <>
	struct EventImpl<void>
	{
		typedef void R;
		template <typename T1, typename T2, typename T3>
		struct Param
		{
			struct SingleEvent
			{
				R (*invoke)(EventPtr*,T1,T2,T3);
				EventPtr	ptr;

				inline bool empty()
				{
					return ptr.empty();
				}
				inline void clear()
				{
					ptr.clear();
					invoke = NULL;
				}
				inline R operator()(T1 t1, T2 t2, T3 t3)
				{
					invoke(&ptr,t1,t2,t3);
				}
			};
						 
			typedef typename std::vector<SingleEvent*> EventList;
			EventList	lst;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					(fun)(t1,t2,t3);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					fun(t1,t2,t3);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					(p->pcls->*p->pmf)(t1,t2,t3);
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3)
			{
				for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
				{
					(*i)->invoke(&(*i)->ptr,t1,t2,t3);
				}
			}
		};
	};
	template <typename R, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
	struct EventBase : public EventImpl<R>::Param<T1,T2,T3>
	{
	};
};

template<>
struct EventHelper<4>
{
	template <typename R>
	struct EventImpl
	{
		template <typename T1, typename T2, typename T3, typename T4>
		struct Param
		{
			struct SingleEvent
			{
				R (*invoke)(EventPtr*,T1,T2,T3,T4);
				EventPtr	ptr;

				inline bool empty()
				{
					return ptr.empty();
				}
				inline void clear()
				{
					ptr.clear();
					invoke = NULL;
				}
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4)
				{
					return invoke(&ptr,t1,t2,t3,t4);
				}
			};
						 
			typedef typename std::vector<SingleEvent*> EventList;
			EventList	lst;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					return (fun)(t1,t2,t3,t4);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					return fun(t1,t2,t3,t4);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					return ((p->pcls->*p->pmf)(t1,t2,t3,t4));
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4)
			{
				for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
				{
					if (i == lst.end()-1)
						return (*i)->invoke(&(*i)->ptr,t1,t2,t3,t4);
					(*i)->invoke(&(*i)->ptr,t1,t2,t3,t4);
				}
			}
		};
	};
	template <>
	struct EventImpl<void>
	{
		typedef void R;
		template <typename T1, typename T2, typename T3, typename T4>
		struct Param
		{
			struct SingleEvent
			{
				R (*invoke)(EventPtr*,T1,T2,T3,T4);
				EventPtr	ptr;

				inline bool empty()
				{
					return ptr.empty();
				}
				inline void clear()
				{
					ptr.clear();
					invoke = NULL;
				}
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4)
				{
					invoke(&ptr,t1,t2,t3,t4);
				}
			};
						
			typedef typename std::vector<SingleEvent*> EventList;
			EventList	lst;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					(fun)(t1,t2,t3,t4);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					fun(t1,t2,t3,t4);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					(p->pcls->*p->pmf)(t1,t2,t3,t4);
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4)
			{
				for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
				{
					(*i)->invoke(&(*i)->ptr,t1,t2,t3,t4);
				}
			}
		};
	};
	template <typename R, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
	struct EventBase : public EventImpl<R>::Param<T1,T2,T3,T4>
	{
	};
};

template<>
struct EventHelper<5>
{
	template <typename R>
	struct EventImpl
	{
		template <typename T1, typename T2, typename T3, typename T4, typename T5>
		struct Param
		{
			struct SingleEvent
			{
				R (*invoke)(EventPtr*,T1,T2,T3,T4,T5);
				EventPtr	ptr;

				inline bool empty()
				{
					return ptr.empty();
				}
				inline void clear()
				{
					ptr.clear();
					invoke = NULL;
				}
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
				{
					return invoke(&ptr,t1,t2,t3,t4,t5);
				}
			};
						 
			typedef typename std::vector<SingleEvent*> EventList;
			EventList	lst;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					return (fun)(t1,t2,t3,t4,t5);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					return fun(t1,t2,t3,t4,t5);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					return ((p->pcls->*p->pmf)(t1,t2,t3,t4,t5));
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
			{
				for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
				{
					if (i == lst.end()-1)
						return (*i)->invoke(&(*i)->ptr,t1,t2,t3,t4,t5);
					(*i)->invoke(&(*i)->ptr,t1,t2,t3,t4,t5);
				}
			}
		};
	};
	template <>
	struct EventImpl<void>
	{
		typedef void R;
		template <typename T1, typename T2, typename T3, typename T4, typename T5>
		struct Param
		{
			struct SingleEvent
			{
				R (*invoke)(EventPtr*,T1,T2,T3,T4,T5);
				EventPtr	ptr;

				inline bool empty()
				{
					return ptr.empty();
				}
				inline void clear()
				{
					ptr.clear();
					invoke = NULL;
				}
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
				{
					invoke(&ptr,t1,t2,t3,t4,t5);
				}
			};
						 
			typedef typename std::vector<SingleEvent*> EventList;
			EventList	lst;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					(fun)(t1,t2,t3,t4,t5);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					fun(t1,t2,t3,t4,t5);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					(p->pcls->*p->pmf)(t1,t2,t3,t4,t5);
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
			{
				for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
				{
					(*i)->invoke(&(*i)->ptr,t1,t2,t3,t4,t5);
				}
			}
		};
	};
	template <typename R, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
	struct EventBase : public EventImpl<R>::Param<T1,T2,T3,T4,T5>
	{
	};
};

template<>
struct EventHelper<6>
{
	template <typename R>
	struct EventImpl
	{
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct Param
		{
			struct SingleEvent
			{
				R (*invoke)(EventPtr*,T1,T2,T3,T4,T5,T6);
				EventPtr	ptr;

				inline bool empty()
				{
					return ptr.empty();
				}
				inline void clear()
				{
					ptr.clear();
					invoke = NULL;
				}
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
				{
					return invoke(&ptr,t1,t2,t3,t4,t5,t6);
				}
			};
						 
			typedef typename std::vector<SingleEvent*> EventList;
			EventList	lst;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					return (fun)(t1,t2,t3,t4,t5,t6);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					return fun(t1,t2,t3,t4,t5,t6);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					return ((p->pcls->*p->pmf)(t1,t2,t3,t4,t5,t6));
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
			{
				for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
				{
					if (i == lst.end()-1)
						return (*i)->invoke(&(*i)->ptr,t1,t2,t3,t4,t5,t6);
					(*i)->invoke(&(*i)->ptr,t1,t2,t3,t4,t5,t6);
				}
			}
		};
	};
	template <>
	struct EventImpl<void>
	{
		typedef void R;
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
		struct Param
		{
			struct SingleEvent
			{
				R (*invoke)(EventPtr*,T1,T2,T3,T4,T5,T6);
				EventPtr	ptr;

				inline bool empty()
				{
					return ptr.empty();
				}
				inline void clear()
				{
					ptr.clear();
					invoke = NULL;
				}
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
				{
					invoke(&ptr,t1,t2,t3,t4,t5,t6);
				}
			};
						 
			typedef typename std::vector<SingleEvent*> EventList;
			EventList	lst;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					(fun)(t1,t2,t3,t4,t5,t6);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					fun(t1,t2,t3,t4,t5,t6);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					(p->pcls->*p->pmf)(t1,t2,t3,t4,t5,t6);
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
			{
				for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
				{
					(*i)->invoke(&(*i)->ptr,t1,t2,t3,t4,t5,t6);
				}
			}
		};
	};
	template <typename R, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
	struct EventBase : public EventImpl<R>::Param<T1,T2,T3,T4,T5,T6>
	{
	};
};

template<>
struct EventHelper<7>
{
	template <typename R>
	struct EventImpl
	{
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct Param
		{
			struct SingleEvent
			{
				R (*invoke)(EventPtr*,T1,T2,T3,T4,T5,T6,T7);
				EventPtr	ptr;

				inline bool empty()
				{
					return ptr.empty();
				}
				inline void clear()
				{
					ptr.clear();
					invoke = NULL;
				}
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
				{
					return invoke(&ptr,t1,t2,t3,t4,t5,t6,t7);
				}
			};
						 
			typedef typename std::vector<SingleEvent*> EventList;
			EventList	lst;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					return (fun)(t1,t2,t3,t4,t5,t6,t7);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					return fun(t1,t2,t3,t4,t5,t6,t7);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					return ((p->pcls->*p->pmf)(t1,t2,t3,t4,t5,t6,t7));
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
			{
				for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
				{
					if (i == lst.end()-1)
						return (*i)->invoke(&(*i)->ptr,t1,t2,t3,t4,t5,t6,t7);
					(*i)->invoke(&(*i)->ptr,t1,t2,t3,t4,t5,t6,t7);
				}
			}
		};
	};
	template <>
	struct EventImpl<void>
	{
		typedef void R;
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
		struct Param
		{
			struct SingleEvent
			{
				R (*invoke)(EventPtr*,T1,T2,T3,T4,T5,T6,T7);
				EventPtr	ptr;

				inline bool empty()
				{
					return ptr.empty();
				}
				inline void clear()
				{
					ptr.clear();
					invoke = NULL;
				}
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
				{
					invoke(&ptr,t1,t2,t3,t4,t5,t6,t7);
				}
			};
						 
			typedef typename std::vector<SingleEvent*> EventList;
			EventList	lst;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					(fun)(t1,t2,t3,t4,t5,t6,t7);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					fun(t1,t2,t3,t4,t5,t6,t7);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					(p->pcls->*p->pmf)(t1,t2,t3,t4,t5,t6,t7);
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
			{
				for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
				{
					(*i)->invoke(&(*i)->ptr,t1,t2,t3,t4,t5,t6,t7);
				}
			}
		};
	};
	template <typename R, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
	struct EventBase : public EventImpl<R>::Param<T1,T2,T3,T4,T5,T6,T7>
	{
	};
};

template<>
struct EventHelper<8>
{
	template <typename R>
	struct EventImpl
	{
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct Param
		{
			struct SingleEvent
			{
				R (*invoke)(EventPtr*,T1,T2,T3,T4,T5,T6,T7,T8);
				EventPtr	ptr;

				inline bool empty()
				{
					return ptr.empty();
				}
				inline void clear()
				{
					ptr.clear();
					invoke = NULL;
				}
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
				{
					return invoke(&ptr,t1,t2,t3,t4,t5,t6,t7,t8);
				}
			};
						 
			typedef typename std::vector<SingleEvent*> EventList;
			EventList	lst;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					return (fun)(t1,t2,t3,t4,t5,t6,t7,t8);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					return fun(t1,t2,t3,t4,t5,t6,t7,t8);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					return ((p->pcls->*p->pmf)(t1,t2,t3,t4,t5,t6,t7,t8));
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
			{
				for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
				{
					if (i == lst.end()-1)
						return (*i)->invoke(&(*i)->ptr,t1,t2,t3,t4,t5,t6,t7,t8);
					(*i)->invoke(&(*i)->ptr,t1,t2,t3,t4,t5,t6,t7,t8);
				}
			}
		};
	};
	template <>
	struct EventImpl<void>
	{
		typedef void R;
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		struct Param
		{
			struct SingleEvent
			{
				R (*invoke)(EventPtr*,T1,T2,T3,T4,T5,T6,T7,T8);
				EventPtr	ptr;

				inline bool empty()
				{
					return ptr.empty();
				}
				inline void clear()
				{
					ptr.clear();
					invoke = NULL;
				}
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
				{
					invoke(&ptr,t1,t2,t3,t4,t5,t6,t7,t8);
				}
			};
						 
			typedef typename std::vector<SingleEvent*> EventList;
			EventList	lst;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					(fun)(t1,t2,t3,t4,t5,t6,t7,t8);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					fun(t1,t2,t3,t4,t5,t6,t7,t8);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					(p->pcls->*p->pmf)(t1,t2,t3,t4,t5,t6,t7,t8);
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
			{
				for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
				{
					(*i)->invoke(&(*i)->ptr,t1,t2,t3,t4,t5,t6,t7,t8);
				}
			}
		};
	};
	template <typename R, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
	struct EventBase : public EventImpl<R>::Param<T1,T2,T3,T4,T5,T6,T7,T8>
	{
	};
};

template<>
struct EventHelper<9>
{
	template <typename R>
	struct EventImpl
	{
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct Param
		{
			struct SingleEvent
			{
				R (*invoke)(EventPtr*,T1,T2,T3,T4,T5,T6,T7,T8,T9);
				EventPtr	ptr;

				inline bool empty()
				{
					return ptr.empty();
				}
				inline void clear()
				{
					ptr.clear();
					invoke = NULL;
				}
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
				{
					return invoke(&ptr,t1,t2,t3,t4,t5,t6,t7,t8,t9);
				}
			};
						 
			typedef typename std::vector<SingleEvent*> EventList;
			EventList	lst;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8,T9 t9)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					return (fun)(t1,t2,t3,t4,t5,t6,t7,t8,t9);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					return fun(t1,t2,t3,t4,t5,t6,t7,t8,t9);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					return ((p->pcls->*p->pmf)(t1,t2,t3,t4,t5,t6,t7,t8,t9));
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
			{
				for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
				{
					if (i == lst.end()-1)
						return (*i)->invoke(&(*i)->ptr,t1,t2,t3,t4,t5,t6,t7,t8,t9);
					(*i)->invoke(&(*i)->ptr,t1,t2,t3,t4,t5,t6,t7,t8,t9);
				}
			}
		};
	};
	template <>
	struct EventImpl<void>
	{
		typedef void R;
		template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
		struct Param
		{
			struct SingleEvent
			{
				R (*invoke)(EventPtr*,T1,T2,T3,T4,T5,T6,T7,T8,T9);
				EventPtr	ptr;

				inline bool empty()
				{
					return ptr.empty();
				}
				inline void clear()
				{
					ptr.clear();
					invoke = NULL;
				}
				inline R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
				{
					invoke(&ptr,t1,t2,t3,t4,t5,t6,t7,t8,t9);
				}
			};
						
			typedef typename std::vector<SingleEvent*> EventList;
			EventList	lst;

			template <typename Fun>
			struct FunctionPtr
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
				{
					Fun fun = static_cast<Fun>(ptr->any.obj_ptr);
					(fun)(t1,t2,t3,t4,t5,t6,t7,t8,t9);
				}
			};
			template <typename Fun>
			struct FunctionObj
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
				{
					Fun & fun = reinterpret_cast<Fun&>(ptr->any.obj_ptr);
					fun(t1,t2,t3,t4,t5,t6,t7,t8,t9);
				}
			};
			template <typename CLS, typename PMFC>
				struct MemberFunc : public MemberFuncImpl<CLS,PMFC>
			{
				static R Invoke(EventPtr * ptr, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
				{
					MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>(ptr->any.mem_ptr);
					(p->pcls->*p->pmf)(t1,t2,t3,t4,t5,t6,t7,t8,t9);
				}
			};
			R operator()(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
			{
				for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
				{
					(*i)->invoke(&(*i)->ptr,t1,t2,t3,t4,t5,t6,t7,t8,t9);
				}
			}
		};
	};
	template <typename R, typename T1 = NullType, typename T2 = NullType, typename T3 = NullType, typename T4 = NullType, typename T5 = NullType, typename T6 = NullType, typename T7 = NullType, typename T8 = NullType, typename T9 = NullType>
	struct EventBase : public EventImpl<R>::Param<T1,T2,T3,T4,T5,T6,T7,T8,T9>
	{
	};
};

}; //QLib_Event

template <typename R, typename T1 = QLib_Event::NullType, typename T2 = QLib_Event::NullType, typename T3 = QLib_Event::NullType, typename T4 = QLib_Event::NullType, typename T5 = QLib_Event::NullType, typename T6 = QLib_Event::NullType, typename T7 = QLib_Event::NullType, typename T8 = QLib_Event::NullType, typename T9 = QLib_Event::NullType>
class Event : public QLib_Event::EventHelper<QLib_Event::Length<T1,T2,T3,T4,T5,T6,T7,T8,T9>::value>::EventBase<R,T1,T2,T3,T4,T5,T6,T7,T8,T9>
{
public:
	enum event_param 
	{
		param = QLib_Event::Length<T1,T2,T3,T4,T5,T6,T7,T8,T9>::value
	};

	typedef typename QLib_Event::EventHelper<param>::EventBase<R,T1,T2,T3,T4,T5,T6,T7,T8,T9>::SingleEvent SingleEvent;
	typedef typename QLib_Event::EventHelper<param>::EventBase<R,T1,T2,T3,T4,T5,T6,T7,T8,T9>::EventList	  EventList;
	typedef typename QLib_Event::EventPtr EventPtr;
	typedef typename Event<R,T1,T2,T3,T4,T5,T6,T7,T8,T9> EventType;
	typedef typename R	ResultType;
	typedef typename T1 Param1Type;
	typedef typename T2 Param2Type;
	typedef typename T3 Param3Type;
	typedef typename T4 Param4Type;
	typedef typename T5 Param5Type;
	typedef typename T6 Param6Type;
	typedef typename T7 Param7Type;
	typedef typename T8 Param8Type;
	typedef typename T9 Param9Type;
public:
	//测试是否为evnet
	template <typename T>
	struct is_event
	{
		enum {value = 0};
	};
	template<>
	struct is_event<Event>
	{
		enum {value = 1};
	};
	template<>
	struct is_event<SingleEvent>
	{
		enum {value = 1};
	};

public:
	//空构造函数
	Event()
	{
	}
	//构造函数 Event
	Event(EventType & ev)
	{
		clear();
		copy(ev);	
	}
	//构造函数 普通函数,仿函数,SingleEvent
	template <typename T>
		Event(const T & t)
	{
		clear();
		copy_helper<T>::copy(this,t);
	}
	//构造函数  类成员函数
	template <typename CLS, typename PMFC>
		Event(CLS * pcls, const PMFC & pmf)
	{
		clear();
		bind(pcls,pmf);
	}
	//析构函数
	~Event()
	{
		clear();
	}	
	//赋值函数
	inline const EventType & operator = (const EventType & ev)
	{
		copy(ev);
		return *this;
	}
	//判断是否为空
	operator QLib_Event::safe_bool () const
    { 
		return (lst.size() == 0 ) ? 0 : &QLib_Event::dummy::nonnull; 
	}
	//[]运算符,支持 operator[]()形式
	inline SingleEvent & operator[] (int i) const
	{
		return (*lst[i]);
	}
	inline operator const SingleEvent & () const
	{
		return **lst.begin();
	}
	//+=运算符 
	inline void operator += (const EventType & ev)
	{
		for (EventList::const_iterator i = ev.lst.begin(); i != ev.lst.end(); i++)
		{
			lst.push_back(new SingleEvent(**i));
		}
	}
	//-=运算符
	inline void operator -= (const EventType & ev)
	{
		if (*this == ev)
		{
			clear();
			return;
		}
		for (EventList::const_iterator i = ev.lst.begin(); i != ev.lst.end(); i++)
		{
			for (EventList::iterator j = lst.begin(); j != lst.end(); j++)
			{
				if ((*j)->ptr == (*i)->ptr && (*j)->invoke == (*i)->invoke)
				{
					delete *j;
					lst.erase(j);
					break;
				}
			}
		}
	}
	// == 运算符
	inline bool operator == (const EventType & ev)
	{
		if (lst.size() != ev.lst.size())
			return false;
		for (EventList::const_iterator i = lst.begin(), j = ev.lst.begin();
				i != lst.end() && j != ev.lst.end(); i++,j++)
		{
			if ((*i)->ptr != (*j)->ptr || (*i)->invoke != (*j)->invoke)
				return false;
		}
		return true;
	}
	// -= 运算符
	inline bool operator != (const EventType & ev)
	{
		return !(*this == ev);
	}
	//交换
	inline void swap(EventType & ev)
	{
		lst.swap(ev.lst);
	}
	//去除重复元素
	void removesame()
	{
		EventType ev;
		for (EventList::iterator i = lst.begin(); i != lst.end(); i++)
		{
			if (ev.find(*i) == false)
			{
				ev.lst.push_back(new SingleEvent(**i));
			}
		}
		*this = ev;
	}
	//是否为空
	inline bool empty()
	{
		return (lst.begin() == lst.end());
	}
	//大小 元素个数
	inline size_t size()
	{
		return lst.size();
	}
	//清空
	inline void clear()
	{
		for (EventList::iterator i = lst.begin(); i != lst.end(); i++)
			delete *i;
		lst.clear();
	}
	//bind 普通函数,仿函数
	template <typename Fun>
		inline void bind(const Fun & fun)
	{
		if (is_event<Fun>::value)
			*this += fun;
		else
			lst.push_back(bind_helper<QLib_Event::is_function<Fun>::value>::bind(fun));
	}
	//hasbind 普通函数,仿函数
	template <typename Fun>
		inline int hasbind(const Fun & fun)
	{
		int n = 0;
		for (EventList::iterator i = lst.begin(); i != lst.end(); i++)
		{
			if (bind_helper<QLib_Event::is_function<Fun>::value>::ifbind(*i,fun))
			{
				n++;
				continue;
			}
		}
		return n;
	}
	//unbind 普通函数,仿函数
	template <typename Fun>
		inline bool unbind(const Fun & fun)
	{
		if (is_event<Fun>::value)
		{
			int size = lst.size();
			*this -= fun;
			return size != lst.size();
		}
		for (EventList::iterator i = lst.begin(); i != lst.end(); i++)
		{
			if (bind_helper<QLib_Event::is_function<Fun>::value>::ifbind(*i,fun))
			{
				delete *i;
				lst.erase(i);
				int size = lst.size();
				return true;
			}
		}
		return false;
	}
	//bind 类成员函数
	template <typename CLS, typename PMFC>
		inline void bind(CLS * pcls, const PMFC & pmf)
	{
		MemberFunc<CLS,PMFC> * pmem = new MemberFunc<CLS,PMFC>;
		pmem->pcls = pcls;
		pmem->pmf = pmf;
		SingleEvent * in = new SingleEvent;
		in->ptr.set_member_func(pmem);
		in->invoke = &MemberFunc<CLS,PMFC>::Invoke;
		lst.push_back(in);
	}
	//hasbind 类成员函数
	template <typename CLS, typename PMFC>
		inline int hasbind(CLS * pcls, PMFC pmf)
	{
		int n = 0;
		for (EventList::iterator i = lst.begin(); i != lst.end(); i++)
		{
			if ((*i)->ptr.vt == EventPtr::any_mem)
			{
				MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>((*i)->ptr.any.mem_ptr);
				if (p->pcls == pcls &&
					p->pmf == pmf)
				{	
					n++;
					continue;
				}
			}
		}
		return n;
	}
	//unbind 类成员函数
	template <typename CLS, typename PMFC>
		inline bool unbind(CLS * pcls, PMFC pmf)
	{
		for (EventList::iterator i = lst.begin(); i != lst.end(); i++)
		{
			if ((*i)->ptr.vt == EventPtr::any_mem)
			{
				MemberFunc<CLS,PMFC> * p = static_cast<MemberFunc<CLS,PMFC>*>((*i)->ptr.any.mem_ptr);
				if (p->pcls == pcls &&
					p->pmf == pmf)
				{	
					delete *i;
					lst.erase(i);
					return true;
				}
			}
		}
		return false;
	}
	//辅助拷贝函数
	inline void copy(const EventType & ev)
	{
		clear();
		for (EventList::const_iterator i = ev.lst.begin(); i != ev.lst.end(); i++)
		{
			lst.push_back(new SingleEvent(**i));
		}
	}
public:
	//查找元素
	inline bool find(const SingleEvent * in)
	{
		for (EventList::const_iterator i = lst.begin(); i != lst.end(); i++)
		{
			if ((*i)->ptr == in->ptr && (*i)->invoke == in->invoke)
				return true;
		}
		return false;
	}
	inline int find_index(const SingleEvent & in, int start = 0)
	{
		for (int i = start; i < (int)lst.size(); i++)
		{
			if (lst[i]->ptr == in.ptr && lst[i]->invoke == in.invoke)
				return i;
		}
		return -1;
	}
	//bind 辅助函数
	template <bool>
	struct bind_helper
	{
		template <typename Fun>
		static SingleEvent * bind(const Fun & fun)
		{
			SingleEvent * in = new SingleEvent;
			in->ptr.set_function_obj(static_cast<const void*>(&fun));
			in->invoke = &FunctionObj<Fun>::Invoke;
			return in;
		};
		template <typename Fun>
		static bool ifbind(SingleEvent * in, const Fun & fun)
		{
			if (in->ptr.vt == EventPtr::any_obj &&
				typeid(reinterpret_cast<Fun&>(in->ptr.any.obj_ptr)) == typeid(fun) )
				return true;
			return false;
		}
	};
	template<>
	struct bind_helper<true>
	{
		template <typename Fun>
		static SingleEvent * bind(const Fun & fun)
		{
			SingleEvent * in = new SingleEvent;
			in->ptr.set_function_ptr(static_cast<void*>(fun));
			in->invoke = &FunctionPtr<Fun>::Invoke;
			return in;
		};
		template <typename Fun>
		static bool ifbind(SingleEvent * in, const Fun & fun)
		{
			if (in->ptr.vt == EventPtr::any_fun &&
				static_cast<Fun>(in->ptr.any.obj_ptr) == fun )
				return true;
			return false;
		}
	};
protected:
	//辅助拷贝函数
	template <typename Fun>
	struct copy_helper
	{
		static void copy(EventType * pEv,const Fun & fun)
		{
			pEv->lst.push_back(bind_helper<QLib_Event::is_function<Fun>::value>::bind(fun));
		}
	};
	template<>
	struct copy_helper<Event>
	{
		static void copy(EventType * pEv,const EventType & ev)
		{
			pEv->copy(ev);
		}
	};
	template<>
	struct copy_helper<SingleEvent>
	{
		static void copy(EventType * pEv, const SingleEvent & in)
		{
			pEv->lst.push_back(new SingleEvent(in));
		}
	};
}; // class Event


}; // namespace QLib


#endif