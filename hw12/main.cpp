#include <memory>
#include <list>
#include <iostream>

template<typename T, size_t pool_size_>
class CustomAllocator {
public:
    using value_type = T;

    template<typename U>
    struct rebind {
        using other = CustomAllocator<U, pool_size_>;
    };

    CustomAllocator() :
            pool_(new T[pool_size_]),
            cur_() {}

    T *allocate(size_t n) {
        if (cur_ + n > pool_size_)
            throw std::bad_alloc();
        T *ptr = pool_ + cur_;
        cur_ += n;
        return (ptr);
    }

    void deallocate(T *ptr, size_t n) {

    }

private:
    T *pool_;
    size_t cur_;
};


int main() {
    std::list<int, CustomAllocator<int, 20>> test_list;
    for (int i = 0; i < 15; i++)
        test_list.push_back(i);

    for (const int &i: test_list)
        std::cout << &i << std::endl;
}