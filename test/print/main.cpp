#include "cout.hpp"
#include "optional"
#include "vector"
using namespace ju;
int main(){

    coutln("printing test: __cplusplus: ", __cplusplus);
    cred("red\n");
    cgreen("green\n");
    cblue("blue\n");
    cout("to cover");
    rout("cover\n");
    std::optional<const char*> op;
    std::optional<const char*> op_val("op");
    coutln("left value optional: ", op);
    coutln("left value optional: ", op_val);
    
    coutln("right value optional: ", std::optional<const char*>("option"));
    coutln("right value optional: ", std::optional<const char*>());

    cgreen("optional green: ", op, "\n");
    #if __GNUC__ >= 12
        coutln("vector: ", std::vector{1, 2, 3, 4, 5});
    #endif
}