#include <cassert>
#include <map>
#include <iostream>

template<typename T, T default_value>
class Matrix {
    using map = std::map<std::pair<size_t, size_t>, T>;
public:

    size_t size() {
        clean_up();
        return value_map_.size();
    }

    T &operator()(size_t x, size_t y) {
        auto it = value_map_.find({x, y});
        if (it != value_map_.end())
            return it->second;
        else {
            return value_map_[{x, y}] = default_value;
        }

    }

    typename map::iterator begin() {
        return value_map_.begin();
    }

    typename map::iterator end() {
        return value_map_.end();
    }

    friend std::ostream &operator<<(std::ostream &out, const Matrix &matrix) {
        for (auto it = matrix.value_map_.begin(); it != matrix.value_map_.end();) {
            out << "x: " << it->first.first << " y: " << it->first.second << " value: " << it->second << "\n";
            ++it;
        }
    }

private:
    map value_map_;

    void clean_up() {
        for (auto it = value_map_.begin(); it != value_map_.end();)
            if (it->second == default_value)
                it = value_map_.erase(it);
            else
                ++it;
    }
};

int main() {
    Matrix<int, -1> matrix;
    assert(matrix.size() == 0);
    auto a = matrix(0, 0);
    assert(a == -1);
    assert(matrix.size() == 0);
    matrix(100, 100) = 314;
    assert(matrix(100, 100) == 314);
    assert(matrix.size() == 1);
    matrix.~Matrix();

    Matrix<int, 0> m;
    int N = 10;
    for (int i = 0; i < N; i++) {
        m(i, i) = i;
        m(N - 1 - i, i) = i;
    }

    std::cout << m;

    return 0;
}