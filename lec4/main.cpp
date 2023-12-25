#include <iostream>
#include <string>
#include <tuple>
#include <exception>


template <size_t I = 0, typename... Args>
typename std::enable_if<I == sizeof...(Args), void>::type
print_tuple(std::ostream&, const std::tuple<Args...>&) {}

template <size_t I = 0, typename... Args>
typename std::enable_if<I < sizeof...(Args), void>::type
print_tuple(std::ostream& os, const std::tuple<Args...>& t) {
    if (I != 0) os << ", ";
    os << get<I>(t);
    print_tuple<I + 1>(os, t);
}

template <typename Ch, typename Tr, typename... Args>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os, const std::tuple<Args...>& t) {
    os << "(";
    print_tuple(os, t);
    os << ")";
    return os;
}

int main() {
    std::tuple<int, double, std::string, double> myTuple(42, 3.14, "Hello", 0.01);
    std::cout << myTuple << std::endl;
    return 0;
}