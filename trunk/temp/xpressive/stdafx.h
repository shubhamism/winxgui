
#pragma warning(disable:4819)

#include <boost/xpressive/xpressive.hpp>
#include <iostream>
#include <iomanip>

using namespace boost::xpressive;

typedef std::string::const_iterator iterator_;

typedef basic_regex<iterator_> regex_;
typedef regex_iterator<iterator_> regex_iterator_;
typedef regex_iterator_::value_type match_results_;
typedef match_results_::value_type sub_match_;
