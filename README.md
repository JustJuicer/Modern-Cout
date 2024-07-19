# 现代C++ 标准输出拓展库
cout 库是一个单头文件的库，提供了方便快速的输出方式
# 环境
需要C++20标准
# 示例
以下是使用示例
## 打印
### 标准库通用打印方式
```cpp
ju::cout << "hello world\n";   
```

### 函数风格的打印

```cpp
ju::cout("hello ", "world\n");
int val{ 3 };
ju::cout("val: ", val, "\n");
```

### 换行与颜色
```cpp
using namespace ju;

coutln("auto break"); 

cred("red, 红色输出\n");
cred << "red\n";

cgreen("green, 绿色输出\n");
cgreen << "green\n";

cblue("blue, 蓝色输出\n");
cblue << "blue\n";

// 支持用operator<<输出
// cxxx << "...";
```

### 标准库类输出重载

```cpp
using namespace ju;
coutln(std::vector{1, 2, 3, 4});
// output [1, 2, 3, 4]

coutln(make_tuple("first", "second", 1, 2.5));
// output (first, second, 1, 2.5)

coutln(make_pair("char*",2.5));
// output (char*, 2.5)

std::optional<int> option;
coutln(option);
// output null

std::optional<int> option1{4};
coutln(option1);
// output 4
```

### 

### 可迭代对象输出重载
#### 自定义可迭代对象
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
### 重载字符串转换接口
#### 重载toString接口
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
#### 重载operator<<
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

### 多维range输出

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

### 取消重载std类型输出重载
```cpp
#define NO_STD_TYPE_OVERLOAD
```