#pragma once
#include <iostream>

template<typename T>
class CircularBuffer {
    T *buffer_;
    int begin_;
    int capacity_;
    int size_;
public:
    CircularBuffer() {
        buffer_ = nullptr;
        begin_ = 0;
        capacity_ = 0;
        size_ = 0;
    }

    ~CircularBuffer() {
        delete[] buffer_;
    }

    CircularBuffer(const CircularBuffer &cb) {
        begin_ = 0;
        capacity_ = cb.capacity_;
        size_ = cb.size_;

        buffer_ = new T[capacity_];
        for (int i = 0; i < size_; ++i) {
            buffer_[i] = cb.buffer_[(cb.begin_ + i) % capacity_];
        }
    }

    //Конструирует буфер заданной ёмкости.
    explicit CircularBuffer(int capacity) {
        capacity_ = capacity;
        buffer_ = new T[capacity_];
        begin_ = 0;
        size_ = 0;
    }

    //Конструирует буфер заданной ёмкости, целиком заполняет его элементом elem.
    CircularBuffer(int capacity, const T &elem) : CircularBuffer(capacity) {
        size_ = capacity_;
        for (int i = 0; i < size_; ++i) {
            buffer_[i] = elem;
        }
    }

    CircularBuffer(CircularBuffer &&cb) {
        buffer_ = cb.buffer_;
        begin_ = cb.begin_;
        capacity_ = cb.capacity_;
        size_ = cb.size_;

        cb.buffer_ = nullptr;
        cb.begin_ = 0;
        cb.capacity_ = 0;
        cb.size_ = 0;
    }

    //Доступ по индексу. Не проверяют правильность индекса.
    T &operator[](int i) {
        return (buffer_[(i + begin_) % capacity_]);
    }

    const T &operator[](int i) const {
        return (buffer_[(i + begin_) % capacity_]);
    }

    //Доступ по индексу. Методы бросают исключение в случае неверного индекса.
    T &at(int i) {
        if (i > size_ || i < 0)
            throw std::out_of_range("Invalid index");
        return (buffer_[(i + begin_) % capacity_]);
    }

    const T &at(int i) const {
        if (i > size_ || i < 0)
            throw std::out_of_range("Invalid index");
        return (buffer_[(i + begin_) % capacity_]);
    }

    T &front() {
        return (buffer_[begin_]);
    } //Ссылка на первый элемент.

    T &back() {
        return (buffer_[(begin_ + size_ - 1) % capacity_]);
    }  //Ссылка на последний элемент.

    const T &front() const {
        return (buffer_[begin_]);
    }

    const T &back() const {
        return (buffer_[(begin_ + size_ - 1) % capacity_]);
    }

    //Линеаризация - сдвинуть кольцевой буфер так, что его первый элемент
    //переместится в начало аллоцированной памяти. Возвращает указатель
    //на первый элемент.
    T *linearize() {
        T *arr = new T[capacity_];
        for (int i = 0; i < size_; ++i) {
            arr[i] = buffer_[(begin_ + i) % capacity_];
        }
        delete[] buffer_;
        buffer_ = arr;
        return buffer_;
    }

    //Проверяет, является ли буфер линеаризованным.
    bool is_linearized() const {
        return (begin_ == 0);
    }

    //Сдвигает буфер так, что по нулевому индексу окажется элемент
    //с индексом new_begin.
    void rotate(int new_begin){
        if (new_begin < 0 || new_begin >= size_) {
            throw std::out_of_range("Invalid new_begin value");
        }
        begin_ = (begin_ + new_begin) % capacity_;
    }

    //Количество элементов, хранящихся в буфере.
    int size() const {
        return (size_);
    }

    bool empty() const {
        return (size_ == 0);
    }

    //true, если size() == capacity().
    bool full() const {
        return (size_ == capacity_);
    }

    //Количество свободных ячеек в буфере.
    int reserve() const {
        return (capacity_ - size_);
    }

    //ёмкость буфера
    int capacity() const {
        return (capacity_);
    }

    void set_capacity(int new_capacity) {
        if (new_capacity < size_)
            throw std::invalid_argument("New capacity is smaller than the current size");

        T *new_buffer = new T[new_capacity];
        for (int i = 0; i < size_; ++i) {
            new_buffer[i] = buffer_[(begin_ + i) % capacity_];
        }
        delete[] buffer_;
        buffer_ = new_buffer;
        capacity_ = new_capacity;
        begin_ = 0;
    }

    //Изменяет размер буфера.
    //В случае расширения, новые элементы заполняются элементом item.
    void resize(int new_size, const T &item = T()) {
        if (new_size < 0) {
            throw std::invalid_argument("New size cannot be negative");
        }
        if (new_size <= size_) {
            size_ = new_size;
        } else {
            if (new_size > capacity_) {
                set_capacity(new_size);
            }
            for (int i = size_; i < new_size; ++i) {
                buffer_[(begin_ + i) % capacity_] = item;
            }
            size_ = new_size;
        }
    }

    //Оператор присваивания.
    CircularBuffer &operator=(const CircularBuffer &cb) {
        if (this != &cb) {
            delete[] buffer_;
            capacity_ = cb.capacity_;
            size_ = cb.size_;
            begin_ = 0;
            buffer_ = new T[capacity_];
            for (int i = 0; i < size_; ++i) {
                buffer_[i] = cb.buffer_[(cb.begin_ + i) % capacity_];
            }
        }
        return *this;
    }

    //Обменивает содержимое буфера с буфером cb.
    void swap(CircularBuffer &cb) {
        std::swap(buffer_, cb.buffer_);
        std::swap(capacity_, cb.capacity_);
        std::swap(size_, cb.size_);
        std::swap(begin_, cb.begin_);
    }

    //Добавляет элемент в конец буфера.
    //Если текущий размер буфера равен его ёмкости, то переписывается
    //первый элемент буфера (т.е., буфер закольцован).
    void push_back(const T &item = T()) {
        if (size_ < capacity_) {
            buffer_[(begin_ + size_) % capacity_] = item;
            ++size_;
        } else {
            buffer_[begin_] = item;
            begin_ = (begin_ + 1) % capacity_;
        }
    }

    //Добавляет новый элемент перед первым элементом буфера.
    //Аналогично push_back, может переписать последний элемент буфера.
    void push_front(const T &item = T()) {
        begin_ = (begin_ - 1 + capacity_) % capacity_;
        buffer_[begin_] = item;
        if (size_ < capacity_)
            ++size_;
    }

    //удаляет последний элемент буфера.
    void pop_back() {
        if (empty())
            throw std::out_of_range("Buffer is empty");
        --size_;
    }

    //удаляет первый элемент буфера.
    void pop_front() {
        if (empty())
            throw std::out_of_range("Buffer is empty");
        begin_ = (begin_ + 1) % capacity_;
        --size_;
    }

    //Вставляет элемент item по индексу pos. Ёмкость буфера остается неизменной.
    void insert(int pos, const T &item = T()) {
        if (pos < 0 || pos > size_)
            throw std::out_of_range("Invalid position for insertion");
        int index = (begin_ + pos) % capacity_;
        for (int i = size_; i > pos; --i) {
            buffer_[(index + i) % capacity_] = buffer_[(index + i - 1) % capacity_];
        }
        buffer_[index] = item;
        if (!full())
            ++size_;
    }

    //Удаляет элементы из буфера в интервале [first, last).
    void erase(int first, int last){
        if (first < 0 || first >= size_ || last < first || last > size_) {
            throw std::out_of_range("Invalid range for erase");
        }
        int index = (begin_ + first) % capacity_;
        int count = last - first;
        for (int i = 0; i < count; ++i) {
            buffer_[(index + i) % capacity_] = buffer_[(index + i + count) % capacity_];
        }
        size_ -= count;
    }

    //Очищает буфер.
    void clear() {
        size_ = 0;
        begin_ = 0;
    }

    friend bool operator==(const CircularBuffer &a, const CircularBuffer &b) {
        if (a.size() != b.size()) {
            return false;
        }
        for (int i = 0; i < a.size(); ++i) {
            if (a[i] != b[i]) {
                return false;
            }
        }
        return true;
    }

    friend bool operator!=(const CircularBuffer &a, const CircularBuffer &b) {
        return !(a == b);
    }
};

