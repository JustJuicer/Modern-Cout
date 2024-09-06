#include <iostream>
#include <sstream>
#include <string>
#include "catch2/catch_test_macros.hpp"

#define _STD_OUT gss
std::stringstream gss;
#include "cout.hpp"

void clear(std::stringstream& ss){
	ss.str("");
	ss.clear();
}
using namespace ju;

TEST_CASE("print test"){
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



TEST_CASE("rout test"){
	clear(gss);
	print("abcdefg");
	rout("123456\n");
	std::cout << "\\------\n";
	for (auto ch: gss.str()){
		std::cout << "ascii: " << static_cast<int>(ch) << '\n';
	}
	std::cout << "\\------\n";
	for (auto ch: std::string{"abcdefg\r033[K123456\n"}){
		std::cout << "ascii: " << static_cast<int>(ch) << '\n';
	}
	CHECK(gss.str() == std::string{"abcdefg\r\033[K123456\n"});
	std::cout << "-------\n";
	std::cout << std::string{"abcdefg\r\033[K123456\n"};
	std::cout << std::string{"abcdefg\r123456\n"};

}