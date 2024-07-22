#include "cout.hpp"
#include <ranges>
#include <vector>
using namespace ju;
int main(){

    coutln("printing test: __cplusplus: ", __cplusplus);
    cred("red\n");
    cgreen("green\n");
    cblue("blue\n");
    cout("to cover");
    rout("cover\n");
    static_assert(!string_able<std::vector<int>>);
    static_assert(std::ranges::viewable_range<std::vector<int>>);
    coutln("vector: ", std::vector{1, 2, 3, 4, 5});
}