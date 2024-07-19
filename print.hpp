#ifndef PRINT_HPP
#define PRINT_HPP

#include <ios>
#include <optional>
#include <ostream>
#include <tuple>
#include <type_traits>
#include <utility>
#ifndef JU_NAMESPACE_BEGIN
    #define JU_NAMESPACE_BEGIN  namespace ju {
    #define JU                  ::ju::
    #define JU_NAMESPACE_END   }
#else
    #define JU                  
    #define JU_NAMESPACE_END    }
#endif
#ifndef BUILD_IN_MODULE
#define EXPORT
#include <concepts>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#else
#define EXPORT export
#endif
#define _STD ::std::
JU_NAMESPACE_BEGIN
constexpr _STD string_view COLOR_RESET = "\033[0m";
constexpr _STD string_view COLOR_GREEN = "\033[32m";
constexpr _STD string_view COLOR_BLUE = "\033[34m";
constexpr _STD string_view COLOR_RED = "\033[31m";

EXPORT
template <typename T>
concept adl_stream = requires(T& t, _STD ostream& os) {
    { os << t } -> _STD convertible_to<_STD ostream&>;
};

template <typename T>
concept mem_to_string = requires(T& t) {
    { t.toString() } -> _STD convertible_to<_STD string>;
};

template <typename T>
concept adl_to_string = requires(T& t) {
    { toString(t) } -> _STD convertible_to<_STD string>;
};

EXPORT
template <typename T>
concept print_able =
    mem_to_string<_STD decay_t<T>> || adl_to_string<_STD decay_t<T>> ||
    adl_stream<_STD decay_t<T>> ||
    requires(T&& obj) { requires requires { _STD to_string(_STD forward<T>(obj)); }; } ||
    _STD convertible_to<_STD decay_t<T>, _STD string>;



EXPORT
template <print_able T>
constexpr _STD string to_string(T&& obj) {
    if constexpr (mem_to_string<_STD decay_t<T>>) {
        return obj.toString();
    } else if constexpr (adl_to_string<_STD decay_t<T>>) {
        return toString(_STD forward<T>(obj));
    } else if constexpr (adl_stream<_STD decay_t<T>>) {
        _STD stringstream s;
        s << _STD forward<T>(obj);
        return s.str();
    } else if constexpr (requires { _STD to_string(_STD forward<T>(obj)); }) {
        return _STD to_string(_STD forward<T>(obj));
    } else if constexpr (_STD convertible_to<_STD decay_t<T>, _STD string>) {
        return static_cast<_STD string>(_STD forward<T>(obj));
    }
}

EXPORT
template <_STD ranges::viewable_range T>
requires(!_STD convertible_to<T, _STD string> &&
         !_STD convertible_to<T, _STD string_view>)
_STD string range_format(T&& range, bool need_delim = false, size_t depth = 0) {
    _STD string res;

    res.push_back('[');

    bool is_first = false;

    for (auto&& ele : range) {
        if (is_first && need_delim)
            res += ", ";
        else if (is_first && !need_delim)
            res.push_back(' ');
        if constexpr (requires { range_format(ele); }) {
            if (is_first) {
                res.push_back('\n');
                for (int i = 0; i < depth + 1; i++)
                    res.push_back(' ');
            }
            res += range_format(ele, need_delim, depth + 1);
        } else {
            res += to_string(_STD forward<decltype(ele)>(ele));
        }
        is_first = true;
    }
    res.push_back(']');
    return res;
}


EXPORT
/**
* @brief this means that T is not a string but can transform to string
* 
* @tparam T 
*/
template <typename T>
concept string_able =
    !_STD is_same_v<_STD decay_t<T>, const char*> &&
    !_STD is_same_v<T, _STD string> && !_STD is_same_v<T, _STD string_view> &&
    (mem_to_string<_STD decay_t<T>> || adl_to_string<_STD decay_t<T>> ||
     _STD convertible_to<_STD decay_t<T>, _STD string>);

EXPORT
template <_STD ranges::viewable_range R>
requires (!string_able<R>)    
_STD ostream& operator<<(_STD ostream& s, R&& rng)
requires(!_STD convertible_to<R, _STD string> 
    && !_STD convertible_to<R, _STD string_view>)
{
    s << range_format(_STD forward<R>(rng));
    return s;
}



EXPORT
template <JU string_able T>
_STD ostream& operator<<(_STD ostream& os, T&& obj) {
    os << to_string(_STD forward<T>(obj));
    return os;
}

inline namespace _access {

    template <typename Derived>
    struct _Out_base{
        auto& flush() const {
            _STD cout.flush();
            return *static_cast<const Derived* const>(this);
        }
        auto fill() const {
            return _STD cout.fill();
        }
        auto fill(char ch) const{
            return _STD cout.fill(ch);
        }
        void clear() const{
            _STD cout.clear();
        }
    };

    template<typename Derived>
    struct _Color_base : _Out_base<_Color_base<Derived>>{
        template<typename ...Args>
        auto& operator()(Args&&... args) const{
            const auto& self = *static_cast<const Derived* const>(this);
            return (((_STD cout << self.COLOR) << ... << _STD forward<Args>(args)) << COLOR_RESET);
        }
    };
    struct _Cout : _Out_base<_Cout>{
        template<typename ...Args>
        auto& operator()(Args&&... args) const {
            return (_STD cout << ... << _STD forward<Args>(args));
        }
    };
    struct _Coutln : _Out_base<_Cout>{
        template<typename ...Args>
        auto& operator()(Args&&... args) const {
            return (_STD cout << ... << _STD forward<Args>(args)) << '\n';
        }
    };
    struct _Log : _Out_base<_Cout>{
        template<typename ...Args>
        auto& operator()(Args&&... args) const {
#ifdef DEBUG
            return (_STD cout << ... << _STD forward<Args>(args));
#else       
            return _STD cout;
#endif
        }
    };
    struct _Rout : _Out_base<_Rout>{
        template<typename ...Args>
        auto& operator()(Args&&... args) const {
            // _STD cout.flush();
            _STD cout << "\r\033[K";
            auto& os = (_STD cout << ... << _STD forward<Args>(args));
            _STD cout.flush();
            return os;
        }
    };

    struct _Red : _Color_base<_Red>{
        _STD string_view COLOR = COLOR_RED;
    };

    struct _Blue : _Color_base<_Red>{
        _STD string_view COLOR = COLOR_BLUE;
    };
    struct _Green : _Color_base<_Red>{
        _STD string_view COLOR = COLOR_GREEN;
    };
}

inline namespace _Cpo {
    inline constexpr _access::_Cout     cout{};
    inline constexpr _access::_Coutln   coutln{};
    inline constexpr _access::_Red      cred{};
    inline constexpr _access::_Green    cgreen{};
    inline constexpr _access::_Blue     cblue{};
    inline constexpr _access::_Rout     rout{};
    inline constexpr _access::_Log      log{};
};

EXPORT
template <typename _C,typename T>
requires (!_STD convertible_to<_STD remove_cvref_t<_C>, _STD ios>)
_STD ostream& operator<<(_C _cout, T&& obj) {
    return _cout(_STD forward<T>(obj));
}

namespace detail{
    template <typename Tp>
    _STD ostream& operator_tuple(_STD ostream& os, Tp&& tuple){
        os << '(';
        bool not_first {false};
        auto print = [&]<typename V>(V&& val){
            using JU operator<<;
            if (not_first){
                os << ", " << _STD forward<V>(val);
            } else {
                os << _STD forward<V>(val);
                not_first = true;
            }
        };
        _STD apply([&]<typename ...Vs>(Vs&&... args){
            (print(args), ...);
        }, tuple);
        os << ')';
        return os;
    }
    template<typename P>
    _STD ostream& operator_pair(_STD ostream os, P&& pair){
        return os << '(' << pair.first << ", " << pair.second << ')';
    }

    template<typename T>
    _STD ostream& operator_optional(_STD ostream& os, T& option){
        if (option.has_value()){
            os << option.value();
        } else {
            os << COLOR_RED << "null" << COLOR_RESET;
        }
        return os;
    }
}


JU_NAMESPACE_END



#ifndef NO_STDTYPE_OVERLOAD

namespace std {
    template<typename T>
    ostream& operator<<(ostream& os, optional<T>& option){
        return JU detail::operator_optional(os, option);
    }
    template<typename T>
    ostream& operator<<(ostream& os, optional<T>&& option){
        return JU detail::operator_optional(os, move(option));
    }


    template<typename T, typename U>
    ostream& operator<<(ostream&os, pair<T, U>& pair){
        return JU detail::operator_pair(os, pair);
    }
    template<typename T, typename U>
    ostream& operator<<(ostream&os, pair<T, U>&& pair){
        return JU detail::operator_pair(os, move(pair));
    }    


    template<typename ...Args>
    ostream& operator<<(ostream& os, tuple<Args...>& tp){
        return JU detail::operator_tuple(os, tp);
    }

    template<typename ...Args>
    ostream& operator<<(ostream& os, tuple<Args...>&& tp){
        return JU detail::operator_tuple(os, move(tp));
    }
}

#endif


#endif