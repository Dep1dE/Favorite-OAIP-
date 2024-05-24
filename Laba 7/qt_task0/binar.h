#ifndef BINAR_H
#define BINAR_H
#include <iostream>
#include <vector>


template <typename T>
class Weak_ptr;

template <typename T>
class Shared_ptr
{
    friend class Weak_ptr<T>;

private:
    T* ptr;
    int* count;

public:
    Shared_ptr() : ptr(nullptr), count(nullptr) { }
    Shared_ptr(T* _ptr) : ptr(_ptr), count(new int(1)) { }
    Shared_ptr(const Shared_ptr& other) : ptr(other.ptr), count(other.count) { if (count) ++(*count); }

    ~Shared_ptr()
    {
        if (!ptr && !count) return;

        --(*count);

        if (!*count) { delete ptr; delete count; }
    }

    Shared_ptr& operator = (const Shared_ptr& other)
    {
        if (!ptr)
        {
            if (!other.ptr) return *this;

            this->ptr = other.ptr;
            this->count = other.count;

            ++(*count);

            return *this;
        }

        if (this->ptr == other.ptr) return *this;

        --(*count);

        if (!*count) { delete ptr; delete count; }

        this->ptr = other.ptr;
        this->count = other.count;

        if (count) ++(*count);

        return *this;
    }

    int Count() const
    {
        if (count) return *count;

        return 0;
    }

    bool operator ==(const Shared_ptr& other)
    {
        return this->ptr == other.ptr;
    }

    bool operator !=(const Shared_ptr& other)
    {
        return this->ptr != other.ptr;
    }

    operator bool() { return ptr != nullptr; }

    void reset(T* ptr)
    {
        if (!this->ptr)
        {
            this->ptr = ptr;
            this->count = new int(1);

            return;
        }

        if (this->ptr == ptr) return;

        --(*count);

        if (!*count) { delete this->ptr; delete this->count; }

        if (!ptr)
        {
            this->ptr = nullptr;
            this->count = nullptr;
        }

        this->ptr = ptr;
        this->count = new int(1);
    }

    T& operator *() { return *ptr; }

    T* operator ->() { return ptr; }
};

template <typename T>
class Weak_ptr
{
private:
    T* ptr;
    int* count;

public:
    Weak_ptr() : ptr(nullptr), count(nullptr) { }
    Weak_ptr(const Shared_ptr<T>& other) : ptr(other.ptr), count(other.count) { }
    Weak_ptr(const Weak_ptr& other) : ptr(other.ptr), count(other.count) { }

    ~Weak_ptr() { ptr = nullptr; count = nullptr; }

    Weak_ptr& operator = (const Weak_ptr& other)
    {
        this->ptr = other.ptr;
        this->count = other.count;

        return *this;
    }

    Shared_ptr<T> lock()
    {
        if (!count || !*count) return Shared_ptr<T>();

        return Shared_ptr<T>(ptr);
    }
};
class BinaryHeap
{
private:
    std::vector<int> v;

public:
    BinaryHeap() : v() {}

    BinaryHeap(std::initializer_list<int> l)
    {
        for (auto it : l) v.push_back(it);

        for (int i = v.size() / 2; i >= 0; i--)
        {
            sequence(i);
        }
    }

    void insert(const int& n)
    {
        v.push_back(n);

        int current = v.size() - 1;
        int parent = (current - 1) / 2;

        while (current && (v[parent] < v[current]))
        {
            std::swap(v[parent], v[current]);

            current = parent;
            parent = (current - 1) / 2;
        }
    }

    void sequence(int& i)
    {
        int left = 0;
        int right = 0;
        int biggest = 0;

        int max = 0;

        while (true)
        {
            left = 2 * i + 1;
            right = 2 * i + 2;
            biggest = i;

            if (right < v.size())
            {
                max = (v[left] >= v[right]) ? left : right;

                if (v[biggest] < v[max]) biggest = max;
            }
            else if (left < v.size())
            {
                if (v[biggest] < v[left]) biggest = left;
            }

            if (biggest == i) break;

            std::swap(v[biggest], v[i]);

            i = biggest;
        }
    }

    int Size() { return v.size(); }

    int& operator[](const int& i) { return v[i]; }
};
#endif // BINAR_H