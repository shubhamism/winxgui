/* -------------------------------------------------------------------------
//	文件名		：	example/atom.dl.h
//	创建者		：	许式伟
//	创建时间	：	5/1/2003 12:47:32 AM
//	功能描述	：	
//
// -----------------------------------------------------------------------*/
#ifndef __EXAMPLE_ATOM_DL_H__
#define __EXAMPLE_ATOM_DL_H__

class KClassNormal
{
published:
	interface Interface1, Interface2;
	void operator=(const KClassNormal& r);
	BOOL operator==(const KClassNormal& r) const;
	STDMETHODIMP _Init();

	STDMETHODIMP_(int) get() const;
	STDMETHODIMP set(int a) nonconst;

public:
	STDMETHODIMP_(const char*) do_get() const;
	STDMETHODIMP do_set(const char*);
};

doc = 
	{ $(Interface) | $(_Comment) };

Interface =
	"interface" $(_blank) $(_csymbol = InterfaceName) $(_Imp);

Comment =
	"//" $(_eol);
	
Imp =
	";" |
	$(_BaseInterfaceImp) $(_Content) |
	$(_Content)
	;
	
BaseInterfaceImp = 
	":" $(_Access) $(_csymbol = BaseInterface);

Access =
	$(_AccessModifier) $(_blank) | "";

AccessModifier =
	"public" | "protected" | "private";
	
Content =
	"{" $(_FuncList) "}" ";" ;
	
FuncList = {
	$(_AccessModifier) ":" |
	$(_Comment) |
	$(Func) };

Func = 
	$(_RetTypeImpl) "(" $(_ArgList) ")" $(_Pure) ";" ;
	
RetTypeImpl =
	"STDPROC_" "(" $(_Type = RetType) ")" $(_csymbol = FuncName) |
	"STDPROC" $(_blank) $(_csymbol = FuncName) |
	"STDMETHOD_" "(" $(_Type = RetType) "," $(_csymbol = FuncName) ")" |
	"STDMETHOD" "(" $(_csymbol = FuncName) ")" |
	$(_Type = RetType) $(_blank) "__stdcall" $(_blank) $(_csymbol = FuncName)
	;
	
Type =
	$(_Modifier) $(_csymbol) $(_Pointer);
	
Pure =
	"PURE" | "=" "0";
	
Modifier =
	"const" $(_blank) | "";
	
Pointer =
	{ "*" } | "";

ArgList =
	{ $(Arg) "," } $(Arg) | $(Arg) | "";

Arg = $(_ArgModifier) $(_Arg0);

ArgModifier =
	"IN" | "OUT" | "";

Arg0 =
	$(_ArgImpl) $(_DefaultValueImp);
	
DefaultValueImp =
	"=" $(_csymbol = DefaultValue) | "";

ArgImpl =
	$(_Type = ArgType) $(_csymbol = ArgName) |
	$(_Type = ArgType)
	;

#endif /* __EXAMPLE_ATOM_DL_H__ */
