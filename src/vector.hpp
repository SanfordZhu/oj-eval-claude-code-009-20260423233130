#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>

namespace sjtu
{
/**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
template<typename T>
class vector
{
public:
    /**
     * a type for actions of the elements of a vector, and you should write
     *   a class named const_iterator with same interfaces.
     */
    /**
     * you can see RandomAccessIterator at CppReference for help.
     */
    class const_iterator;
    class iterator
    {
    // The following code is written for the C++ type_traits library.
    // Type traits is a C++ feature for describing certain properties of a type.
    // For instance, for an iterator, iterator::value_type is the type that the
    // iterator points to.
    // STL algorithms and containers may use these type_traits (e.g. the following
    // typedef) to work properly. In particular, without the following code,
    // @code{std::sort(iter, iter1);} would not compile.
    // See these websites for more information:
    // https://en.cppreference.com/w/cpp/header/type_traits
    // About value_type: https://blog.csdn.net/u014299153/article/details/72419713
    // About iterator_category: https://en.cppreference.com/w/cpp/iterator
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using iterator_category = std::random_access_iterator_tag;

    private:
        T* ptr;
        const vector* container;
        iterator(T* p, const vector* vec) : ptr(p), container(vec) {}
        friend class vector;
        friend class const_iterator;

    public:
        iterator() : ptr(nullptr), container(nullptr) {}
        /**
         * return a new iterator which pointer n-next elements
         * as well as operator-
         */
        iterator operator+(const int &n) const
        {
            return iterator(ptr + n, container);
        }
        iterator operator-(const int &n) const
        {
            return iterator(ptr - n, container);
        }
        // return the distance between two iterators,
        // if these two iterators point to different vectors, throw invaild_iterator.
        int operator-(const iterator &rhs) const
        {
            if (container != rhs.container)
                throw invalid_iterator();
            return ptr - rhs.ptr;
        }
        iterator& operator+=(const int &n)
        {
            ptr += n;
            return *this;
        }
        iterator& operator-=(const int &n)
        {
            ptr -= n;
            return *this;
        }
        /**
         * iter++
         */
        iterator operator++(int)
        {
            iterator old = *this;
            ptr++;
            return old;
        }
        /**
         * ++iter
         */
        iterator& operator++()
        {
            ptr++;
            return *this;
        }
        /**
         * iter--
         */
        iterator operator--(int)
        {
            iterator old = *this;
            ptr--;
            return old;
        }
        /**
         * --iter
         */
        iterator& operator--()
        {
            ptr--;
            return *this;
        }
        /**
         * *it
         */
        T& operator*() const
        {
            return *ptr;
        }
        T* operator->() const
        {
            return ptr;
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
        bool operator==(const iterator &rhs) const
        {
            return ptr == rhs.ptr;
        }
        bool operator==(const const_iterator &rhs) const
        {
            return ptr == rhs.ptr;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const iterator &rhs) const
        {
            return ptr != rhs.ptr;
        }
        bool operator!=(const const_iterator &rhs) const
        {
            return ptr != rhs.ptr;
        }

        bool operator<(const iterator &other) const
        {
            return ptr < other.ptr;
        }
        bool operator>(const iterator &other) const
        {
            return ptr > other.ptr;
        }
        bool operator<=(const iterator &other) const
        {
            return ptr <= other.ptr;
        }
        bool operator>=(const iterator &other) const
        {
            return ptr >= other.ptr;
        }
    };
    /**
     * has same function as iterator, just for a const object.
     */
    class const_iterator
    {
    public:
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = const T*;
        using reference = const T&;
        using iterator_category = std::random_access_iterator_tag;

    private:
        const T* ptr;
        const vector* container;
        const_iterator(const T* p, const vector* vec) : ptr(p), container(vec) {}
        friend class vector;
        friend class iterator;

    public:
        const_iterator() : ptr(nullptr), container(nullptr) {}
        /**
         * return a new iterator which pointer n-next elements
         * as well as operator-
         */
        const_iterator operator+(const int &n) const
        {
            return const_iterator(ptr + n, container);
        }
        const_iterator operator-(const int &n) const
        {
            return const_iterator(ptr - n, container);
        }
        // return the distance between two iterators,
        // if these two iterators point to different vectors, throw invaild_iterator.
        int operator-(const const_iterator &rhs) const
        {
            if (container != rhs.container)
                throw invalid_iterator();
            return ptr - rhs.ptr;
        }
        const_iterator& operator+=(const int &n)
        {
            ptr += n;
            return *this;
        }
        const_iterator& operator-=(const int &n)
        {
            ptr -= n;
            return *this;
        }
        /**
         * iter++
         */
        const_iterator operator++(int)
        {
            const_iterator old = *this;
            ptr++;
            return old;
        }
        /**
         * ++iter
         */
        const_iterator& operator++()
        {
            ptr++;
            return *this;
        }
        /**
         * iter--
         */
        const_iterator operator--(int)
        {
            const_iterator old = *this;
            ptr--;
            return old;
        }
        /**
         * --iter
         */
        const_iterator& operator--()
        {
            ptr--;
            return *this;
        }
        /**
         * *it
         */
        const T& operator*() const
        {
            return *ptr;
        }
        const T* operator->() const
        {
            return ptr;
        }
        /**
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
        bool operator==(const const_iterator &rhs) const
        {
            return ptr == rhs.ptr;
        }
        bool operator==(const iterator &rhs) const
        {
            return ptr == rhs.ptr;
        }
        /**
         * some other operator for iterator.
         */
        bool operator!=(const const_iterator &rhs) const
        {
            return ptr != rhs.ptr;
        }
        bool operator!=(const iterator &rhs) const
        {
            return ptr != rhs.ptr;
        }

        bool operator<(const const_iterator &other) const
        {
            return ptr < other.ptr;
        }
        bool operator>(const const_iterator &other) const
        {
            return ptr > other.ptr;
        }
        bool operator<=(const const_iterator &other) const
        {
            return ptr <= other.ptr;
        }
        bool operator>=(const const_iterator &other) const
        {
            return ptr >= other.ptr;
        }
    };

private:
    T* data;
    size_t n_size;
    size_t n_capacity;

    void expand()
    {
        if (n_size < n_capacity)
            return;
        size_t new_capacity = (n_capacity == 0) ? 1 : n_capacity * 2;
        T* new_data = static_cast<T*>(operator new(new_capacity * sizeof(T)));
        for (size_t i = 0; i < n_size; ++i)
        {
            new (new_data + i) T(data[i]);
            data[i].~T();
        }
        operator delete(data);
        data = new_data;
        n_capacity = new_capacity;
    }

public:
    /**
     * Constructs
     * At least two: default constructor, copy constructor
     */
    vector() : data(nullptr), n_size(0), n_capacity(0) {}

    vector(const vector &other)
    {
        n_size = other.n_size;
        n_capacity = other.n_size;
        if (n_capacity == 0)
        {
            data = nullptr;
            return;
        }
        data = static_cast<T*>(operator new(n_capacity * sizeof(T)));
        for (size_t i = 0; i < n_size; ++i)
        {
            new (data + i) T(other.data[i]);
        }
    }

    /**
     * Destructor
     */
    ~vector()
    {
        clear();
        if (data != nullptr)
            operator delete(data);
    }

    /**
     * Assignment operator
     */
    vector &operator=(const vector &other)
    {
        if (this == &other)
            return *this;
        clear();
        if (data != nullptr)
            operator delete(data);
        n_size = other.n_size;
        n_capacity = other.n_size;
        if (n_capacity == 0)
        {
            data = nullptr;
            return *this;
        }
        data = static_cast<T*>(operator new(n_capacity * sizeof(T)));
        for (size_t i = 0; i < n_size; ++i)
        {
            new (data + i) T(other.data[i]);
        }
        return *this;
    }

    /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     */
    T & at(const size_t &pos)
    {
        if (pos >= n_size)
            throw index_out_of_bound();
        return data[pos];
    }

    const T & at(const size_t &pos) const
    {
        if (pos >= n_size)
            throw index_out_of_bound();
        return data[pos];
    }

    /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     * !!! Pay attentions
     *   In STL this operator does not check the boundary but I want you to do.
     */
    T & operator[](const size_t &pos)
    {
        if (pos >= n_size)
            throw index_out_of_bound();
        return data[pos];
    }

    const T & operator[](const size_t &pos) const
    {
        if (pos >= n_size)
            throw index_out_of_bound();
        return data[pos];
    }

    /**
     * access the first element.
     * throw container_is_empty if size == 0
     */
    const T & front() const
    {
        if (n_size == 0)
            throw container_is_empty();
        return data[0];
    }

    /**
     * access the last element.
     * throw container_is_empty if size == 0
     */
    const T & back() const
    {
        if (n_size == 0)
            throw container_is_empty();
        return data[n_size - 1];
    }

    T & front()
    {
        if (n_size == 0)
            throw container_is_empty();
        return data[0];
    }

    T & back()
    {
        if (n_size == 0)
            throw container_is_empty();
        return data[n_size - 1];
    }

    /**
     * returns an iterator to the beginning.
     */
    iterator begin()
    {
        return iterator(data, this);
    }

    const_iterator begin() const
    {
        return const_iterator(data, this);
    }

    const_iterator cbegin() const
    {
        return const_iterator(data, this);
    }

    /**
     * returns an iterator to the end.
     */
    iterator end()
    {
        return iterator(data + n_size, this);
    }

    const_iterator end() const
    {
        return const_iterator(data + n_size, this);
    }

    const_iterator cend() const
    {
        return const_iterator(data + n_size, this);
    }

    /**
     * checks whether the container is empty
     */
    bool empty() const
    {
        return n_size == 0;
    }

    /**
     * returns the number of elements
     */
    size_t size() const
    {
        return n_size;
    }

    /**
     * clears the contents
     */
    void clear()
    {
        for (size_t i = 0; i < n_size; ++i)
        {
            data[i].~T();
        }
        n_size = 0;
    }

    /**
     * inserts value before pos
     * returns an iterator pointing to the inserted value.
     */
    iterator insert(iterator pos, const T &value)
    {
        size_t index = pos - begin();
        expand();
        for (size_t i = n_size; i > index; --i)
        {
            new (data + i) T(data[i - 1]);
            data[i - 1].~T();
        }
        new (data + index) T(value);
        n_size++;
        return begin() + static_cast<int>(index);
    }

    /**
     * inserts value at index ind.
     * after inserting, this->at(ind) == value
     * returns an iterator pointing to the inserted value.
     * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
     */
    iterator insert(const size_t &ind, const T &value)
    {
        if (ind > n_size)
            throw index_out_of_bound();
        return insert(begin() + static_cast<int>(ind), value);
    }

    /**
     * removes the element at pos.
     * return an iterator pointing to the following element.
     * If the iterator pos refers the last element, the end() iterator is returned.
     */
    iterator erase(iterator pos)
    {
        size_t index = pos - begin();
        pos->~T();
        for (size_t i = index; i < n_size - 1; ++i)
        {
            new (data + i) T(data[i + 1]);
            data[i + 1].~T();
        }
        n_size--;
        return begin() + static_cast<int>(index);
    }

    /**
     * removes the element with index ind.
     * return an iterator pointing to the following element.
     * throw index_out_of_bound if ind >= size
     */
    iterator erase(const size_t &ind)
    {
        if (ind >= n_size)
            throw index_out_of_bound();
        return erase(begin() + static_cast<int>(ind));
    }

    /**
     * adds an element to the end.
     */
    void push_back(const T &value)
    {
        expand();
        new (data + n_size++) T(value);
    }

    /**
     * remove the last element from the end.
     * throw container_is_empty if size() == 0
     */
    void pop_back()
    {
        if (n_size == 0)
            throw container_is_empty();
        data[--n_size].~T();
    }
};

}

#endif
