/* -------------------------------------------------------------------------
// WINX: a C++ template GUI library - MOST SIMPLE BUT EFFECTIVE
// 
// This file is a part of the WINX Library.
// The use and distribution terms for this software are covered by the
// Common Public License 1.0 (http://opensource.org/licenses/cpl.php)
// which can be found in the file CPL.txt at this distribution. By using
// this software in any fashion, you are agreeing to be bound by the terms
// of this license. You must not remove this notice, or any other, from
// this software.
// 
// Module: testtpl.cpp
// Creator: xushiwei
// Email: xushiweizh@gmail.com
// Date: 2006-12-3 12:59:08
// 
// $Id: TestStdNew.cpp,v 1.1 2006/12/03 05:32:36 xushiwei Exp $
// -----------------------------------------------------------------------*/

#pragma warning(disable:4786)
#include <stdext.h>
#include <tpl/toolbox/KeywordTblGen.h>

void main()
{
	WINX_TEST_APP(std::ErrorLog, "", "testMapUni");

	WINX_TEST_CLASS(tpl::toolbox::TestKeywordTblGen);
}

// -------------------------------------------------------------------------
// $Log: testtpl.cpp,v $
