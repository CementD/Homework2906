#include <iostream>
#include <memory>
using namespace std;

template <typename T>
class SmartPointer {
private:
    T* ptr;
public:
    SmartPointer() : ptr(nullptr) {}

    SmartPointer(T* p) : ptr(p) {}

    SmartPointer(const SmartPointer& other) = delete;

    SmartPointer& operator=(const SmartPointer& other) = delete;

    SmartPointer(SmartPointer&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    SmartPointer& operator=(SmartPointer&& other) noexcept {
        if (this != &other) {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }
    
    T* get() const {
        return ptr;
    }

    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }

    ~SmartPointer() {
        delete ptr;
    }
};

struct Test {
    Test() { cout << "Test constructed\n"; }
    ~Test() { cout << "Test destructed\n"; }
    void sayHello() const { cout << "Hello from Test\n"; }
};

int main() {
    {
        SmartPointer<Test> ptr1(new Test());
        ptr1->sayHello();
        (*ptr1).sayHello();

        SmartPointer<Test> ptr2 = move(ptr1);
        if (!ptr1.get()) {
            cout << "ptr1 is now null\n";
        }
        ptr2->sayHello();

        SmartPointer<Test> ptr3;
        ptr3 = move(ptr2);
        if (!ptr2.get()) {
            cout << "ptr2 is now null\n";
        }
        ptr3->sayHello();
    }

    return 0;
}
