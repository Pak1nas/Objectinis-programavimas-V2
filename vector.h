#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <stdexcept>
#include <initializer_list>

template <typename T>
class Vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void reallocate(size_t new_cap) {
        T* new_data = new T[new_cap];
        for (size_t i = 0; i < size_; ++i)
            new_data[i] = std::move(data_[i]);
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }

public:
    using iterator = T*;
    using const_iterator = const T*;


    Vector() : data_(nullptr), size_(0), capacity_(0) {}


    explicit Vector(size_t n) : data_(new T[n]), size_(n), capacity_(n) {
        for (size_t i = 0; i < size_; ++i)
            data_[i] = T();
    }

    Vector(std::initializer_list<T> init) : data_(new T[init.size()]), size_(init.size()), capacity_(init.size()) {
        size_t i = 0;
        for (const T& val : init)
            data_[i++] = val;
    }


    Vector(const Vector& other) : data_(new T[other.size_]), size_(other.size_), capacity_(other.size_) {
        for (size_t i = 0; i < size_; ++i)
            data_[i] = other.data_[i];
    }


    Vector(Vector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }


    ~Vector() {
        delete[] data_;
    }

    // Copy assignment
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            Vector temp(other);
            swap(temp);
        }
        return *this;
    }

    // Move assignment
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    // Element access
    T& operator[](size_t index) { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }

    T& at(size_t index) {
        if (index >= size_)
            throw std::out_of_range("Vector::at");
        return data_[index];
    }

    const T& at(size_t index) const {
        if (index >= size_)
            throw std::out_of_range("Vector::at");
        return data_[index];
    }

    T& back() {
        return data_[size_ - 1];
    }

    const T& back() const {
        return data_[size_ - 1];
    }

    // Iterators
    iterator begin() { return data_; }
    const_iterator begin() const { return data_; }
    iterator end() { return data_ + size_; }
    const_iterator end() const { return data_ + size_; }

    // Capacity
    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

    void reserve(size_t new_cap) {
        if (new_cap > capacity_)
            reallocate(new_cap);
    }

    void resize(size_t new_size) {
        if (new_size > capacity_)
            reallocate(new_size);
        if (new_size > size_) {
            for (size_t i = size_; i < new_size; ++i)
                data_[i] = T();
        }
        size_ = new_size;
    }

    // Modifiers
    void push_back(const T& value) {
        if (size_ >= capacity_) {
            size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(new_cap);
        }
        data_[size_++] = value;
    }

    void push_back(T&& value) {
        if (size_ >= capacity_) {
            size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(new_cap);
        }
        data_[size_++] = std::move(value);
    }

    void pop_back() {
        if (size_ > 0)
            --size_;
    }

    void clear() {
        size_ = 0;
    }

    void swap(Vector& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
};

#endif
