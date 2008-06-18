///////////////////////////////////////////////////////////////////////////////
// main.hpp
//
//  Copyright 2004 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "stdafx.h"

boost::proto::terminal<char>::type const _ch_o = {'>'};

inline void example()
{
	std::string str = "I was born on >5/30/1973 at 7am.\nI was born on 6/20/1975 at 7am.\n";

    // define some custom mark_tags with names more meaningful than s1, s2, etc.
    mark_tag day(1), month(2), year(3), delim(4);

    // this regex finds a date
    regex_ date = *~_ch_o
			>> (month= repeat<1,2>(_d))           // find the month ...
            >> (delim= (set= '/','-'))            // followed by a delimiter ...
            >> (day=   repeat<1,2>(_d)) >> delim  // and a day followed by the same delimiter ...
            >> (year=  repeat<1,2>(_d >> _d));    // and the year.

	regex_iterator_ cur( str.begin(), str.end(), date);
	regex_iterator_ end;
	
	for( ; cur != end; ++cur )
	{
		match_results_ item = *cur;
		sub_match_ matched = item[0];
		std::cout << matched << '\n';
		std::cout << item[year] << '-' << item[month] << '-' << item[day] << '\n';
	}
}

///////////////////////////////////////////////////////////////////////////////
// main

int main()
{
    example();
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
