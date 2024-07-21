#include <sstream>
#include <string>
#include "catch.hpp"
#define _STD_OUT gss
std::stringstream gss;
#include "cout.hpp"

void clear(std::stringstream& ss){
	ss.str("");
	ss.clear();
}

TEST_CASE("print test"){
	using namespace  ju;
	SECTION("println"){
		clear(gss);
		println("_context_");
		REQUIRE(gss.str() == "_context_\n");
	}
	SECTION("print"){
		clear(gss);
		print("_context_");
		REQUIRE(gss.str() == "_context_");
	}
}