#include "cout.hpp"
#include <vector>
using namespace ju;
int main(){
    coutln("printing test");
    cred("red\n");
    cgreen("green\n");
    cblue("blue\n");
    cout("to cover");
    rout("cover\n");
    coutln("vector: ", std::vector{1, 2, 3, 4, 5});
}