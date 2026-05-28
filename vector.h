#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <cstddef>

template <typename T>
class Vector
{
private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;

    void reallocate ( std::size_t new_cap )
    {
        T* new_data = static_cast<T*> ( ::operator new ( sizeof ( T ) * new_cap ) );

        for ( std::size_t i = 0; i < size_; ++i )
        {
            new ( new_data + i ) T ( std::move_if_noexcept ( data_[i] ) );
            data_[i].~T();
        }

        ::operator delete ( data_ );
        data_ = new_data;
        capacity_ = new_cap;
    }

public:
    Vector() : data_ ( nullptr ), size_ ( 0 ), capacity_ ( 0 ) {}

    explicit Vector ( std::size_t n ) : data_ ( nullptr ), size_ ( 0 ), capacity_ ( 0 )
    {
        if ( n > 0 )
        {
            data_ = static_cast<T*> ( ::operator new ( sizeof ( T ) * n ) );

            for ( std::size_t i = 0; i < n; ++i )
            {
                new ( data_ + i ) T();
            }

            size_ = capacity_ = n;
        }
    }

    Vector ( std::size_t n, const T& value ) : data_ ( nullptr ), size_ ( 0 ), capacity_ ( 0 )
    {
        if ( n > 0 )
        {
            data_ = static_cast<T*> ( ::operator new ( sizeof ( T ) * n ) );

            for ( std::size_t i = 0; i < n; ++i )
            {
                new ( data_ + i ) T ( value );
            }

            size_ = capacity_ = n;
        }
    }

    Vector ( std::initializer_list<T> init ) : data_ ( nullptr ), size_ ( 0 ), capacity_ ( 0 )
    {
        if ( init.size() > 0 )
        {
            data_ = static_cast<T*> ( ::operator new ( sizeof ( T ) * init.size() ) );
            std::size_t i = 0;

            for ( const auto& x : init )
            {
                new ( data_ + i ) T ( x );
                ++i;
            }

            size_ = capacity_ = init.size();
        }
    }

    Vector ( const Vector& other ) : data_ ( nullptr ), size_ ( 0 ), capacity_ ( 0 )
    {
        if ( other.size_ > 0 )
        {
            data_ = static_cast<T*> ( ::operator new ( sizeof ( T ) * other.size_ ) );

            for ( std::size_t i = 0; i < other.size_; ++i )
            {
                new ( data_ + i ) T ( other.data_[i] );
            }

            size_ = capacity_ = other.size_;
        }
    }

    Vector ( Vector&& other ) noexcept
        : data_ ( other.data_ ), size_ ( other.size_ ), capacity_ ( other.capacity_ )
    {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    Vector& operator= ( const Vector& other )
    {
        if ( this != &other )
        {
            clear();

            if ( other.size_ > capacity_ )
            {
                ::operator delete ( data_ );
                data_ = static_cast<T*> ( ::operator new ( sizeof ( T ) * other.size_ ) );
                capacity_ = other.size_;
            }

            for ( std::size_t i = 0; i < other.size_; ++i )
            {
                new ( data_ + i ) T ( other.data_[i] );
            }

            size_ = other.size_;
        }

        return *this;
    }

    Vector& operator= ( Vector&& other ) noexcept
    {
        if ( this != &other )
        {
            clear();
            ::operator delete ( data_ );
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }

        return *this;
    }

    ~Vector()
    {
        clear();
        ::operator delete ( data_ );
    }

    std::size_t size() const
    {
        return size_;
    }
    std::size_t capacity() const
    {
        return capacity_;
    }
    bool empty() const
    {
        return size_ == 0;
    }

    void reserve ( std::size_t new_cap )
    {
        if ( new_cap > capacity_ ) reallocate ( new_cap );
    }

    void resize ( std::size_t new_size )
    {
        if ( new_size < size_ )
        {
            for ( std::size_t i = new_size; i < size_; ++i )
            {
                data_[i].~T();
            }

            size_ = new_size;
        }
        else if ( new_size > size_ )
        {
            reserve ( new_size );

            for ( std::size_t i = size_; i < new_size; ++i )
            {
                new ( data_ + i ) T();
            }

            size_ = new_size;
        }
    }

    void push_back ( const T& value )
    {
        if ( size_ == capacity_ )
        {
            reserve ( capacity_ == 0 ? 1 : capacity_ * 2 );
        }

        new ( data_ + size_ ) T ( value );
        ++size_;
    }

    void push_back ( T&& value )
    {
        if ( size_ == capacity_ )
        {
            reserve ( capacity_ == 0 ? 1 : capacity_ * 2 );
        }

        new ( data_ + size_ ) T ( std::move ( value ) );
        ++size_;
    }

    void pop_back()
    {
        if ( size_ == 0 ) return;

        data_[size_ - 1].~T();
        --size_;
    }

    void clear()
    {
        for ( std::size_t i = 0; i < size_; ++i )
        {
            data_[i].~T();
        }

        size_ = 0;
    }

    T& operator[] ( std::size_t idx )
    {
        return data_[idx];
    }
    const T& operator[] ( std::size_t idx ) const
    {
        return data_[idx];
    }

    T& at ( std::size_t idx )
    {
        if ( idx >= size_ ) throw std::out_of_range ( "Vector::at" );

        return data_[idx];
    }

    const T& at ( std::size_t idx ) const
    {
        if ( idx >= size_ ) throw std::out_of_range ( "Vector::at" );

        return data_[idx];
    }

    T& back()
    {
        return data_[size_ - 1];
    }
    const T& back() const
    {
        return data_[size_ - 1];
    }

    T* data()
    {
        return data_;
    }
    const T* data() const
    {
        return data_;
    }

    T* begin()
    {
        return data_;
    }
    T* end()
    {
        return data_ + size_;
    }
    const T* begin() const
    {
        return data_;
    }
    const T* end() const
    {
        return data_ + size_;
    }
    const T* cbegin() const
    {
        return data_;
    }
    const T* cend() const
    {
        return data_ + size_;
    }
};

#endif
