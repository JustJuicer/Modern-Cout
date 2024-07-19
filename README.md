# Modern C++ Standard Output  Library
Modern cout is a single-header library in C++20 that provides a convenient and fast way to output data, with overloaded support for most standard library types.

# Environment
Requires C++20 standard.

# Examples
Below are some usage examples.

# Printing
### Standard library's generic printing method
```cpp
ju::cout << "hello world\n";   
```
### Function-style printing
```cpp
ju::cout("hello ", "world\n");
int val{ 3 };
ju::cout("val: ", val, "\n");
```

### Line Breaks and Colors

```cpp
using namespace ju;

coutln("auto break"); 

cred("red\n");
cred << "red\n";

cgreen("green\n");
cgreen << "green\n";

cblue("blue\n");
cblue << "blue\n";

// Supports output using operator<<
// cxxx << "...";
```
### Output Overloads for Standard Library Classes
```cpp
using namespace ju;
coutln(std::vector{1, 2, 3, 4});
// output [1, 2, 3, 4]

coutln(std::make_tuple("first", "second", 1, 2.5));
// output (first, second, 1, 2.5)

coutln(std::make_pair("char*",2.5));
// output (char*, 2.5)

std::optional<int> option;
coutln(option);
// output null

std::optional<int> option1{4};
coutln(option1);
// output 4
```
### Output Overloads for Iterable Objects
#### Custom Iterable Object
For custom classes that satisfy std::ranges::viewable_range and do not have a conversion to string, cout will iterate and output the elements.

```cpp
struct iterable {
    struct iterator {
        using difference_type = ptrdiff_t;
        auto operator*() const { return a; }
        auto& operator++() {
            --a;
            return *this;
        }
        auto& operator++(int) {
            --a;
            return *this;
        }
        bool operator==(iterator iter) const {
            return a > 0 ? false : true;
        }
        inline static int a = 10;
    };
    auto begin(){ return iterator{}; }
    auto end()  { return iterator{}; }
};
using namespace ju;
int main(){
    iterable i;
    coutln(i);
    // output [10 9 8 7 6 5 4 3 2 1]
}
```
### Custom Overloaded String Conversion Interfaces
#### Custom toString Overload
```cpp
struct S{
    std::string toString(){
        return "struct S";
    }
};
using namespace ju;
int main() {
    coutln(S{});
    // output struct S
}
```
#### Custom operator<< Overload
Overload the output stream for your custom class.

```cpp
struct S{
    int a{ 5 };
    friend std::ostream& operator<<(std::ostream& os, S self){
        return os << "a = " << self.a;
    }
};
int main() {
    coutln(S{});
    //output a = 5
}
```
### Multi-Dimensional Range Output
ju::cout supports recursively outputting multi-dimensional nested arrays.

```cpp
using namespace std;
using namespace ju;
coutln << vector{ vector{1, 2, 3}, 
                  vector{4, 5, 6}, 
                  vector{7, 8, 9} };
// output: 
//         [[1 2 3] 
//          [4 5 6] 
//          [7 8 9]]
```
### Disabling Overloads for Standard Types
```cpp
#define NO_STD_TYPE_OVERLOAD
```