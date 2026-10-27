#include <iostream>
#include <stdexcept>

template <typename T>
class my_unique_ptr {
private:
    T* m_ptr;

public:
    
    explicit my_unique_ptr(T* ptr = nullptr) noexcept : m_ptr(ptr) {}

    
    ~my_unique_ptr() {
        delete m_ptr;
        m_ptr = nullptr;
    }

    
    my_unique_ptr(const my_unique_ptr&) = delete;

    
    my_unique_ptr& operator=(const my_unique_ptr&) = delete;

    
    my_unique_ptr(my_unique_ptr&& other) noexcept : m_ptr(other.m_ptr) {
        other.m_ptr = nullptr;  
    }

    my_unique_ptr& operator=(my_unique_ptr&& other) noexcept {
        if (this != &other) {
            delete m_ptr;       
            m_ptr = other.m_ptr;
            other.m_ptr = nullptr;
        }
        return *this;
    }

    
    T& operator*() const {
        if (!m_ptr) {
            throw std::runtime_error("my_unique_ptr: dereference of nullptr");
        }
        return *m_ptr;
    }

    
    T* operator->() const noexcept {
        return m_ptr;
    }

    
    T* release() noexcept {
        T* raw = m_ptr;
        m_ptr = nullptr;        
        return raw;
    }

    
    explicit operator bool() const noexcept {
        return m_ptr != nullptr;
    }

    
    void reset(T* new_ptr = nullptr) {
        if (new_ptr == m_ptr) return;
        delete m_ptr;
        m_ptr = new_ptr;
    }
};



struct TestObject {
    int value;
    TestObject(int v) : value(v) { std::cout << "TestObject created: " << value << "\n"; }
    ~TestObject() { std::cout << "TestObject destroyed: " << value << "\n"; }
};