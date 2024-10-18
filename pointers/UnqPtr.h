//
// Created by tomin on 29.09.2024.
//

#ifndef SMARTPOINTER_UNQPTR_H
#define SMARTPOINTER_UNQPTR_H

template<typename T>
class UnqPtr {
private:
    T* ptr;

public:
    // Constructor
    explicit UnqPtr(T* p = nullptr) {
        ptr = p;
    }

    // Destructor
    ~UnqPtr() {
        delete ptr;
    }

    // Prohibit copying
    UnqPtr(const UnqPtr&) = delete;
    UnqPtr& operator=(const UnqPtr&) = delete;

    // Allow movement
    UnqPtr(UnqPtr&& sp) noexcept : ptr(sp.ptr) {
        sp.ptr = nullptr;
    }

    UnqPtr& operator=(UnqPtr&& sp) noexcept {  // rvalue-ссылка (временный объект, который не имеет постоянного адреса)
        if (this != &sp) {
            delete ptr;
            ptr = sp.ptr;
            sp.ptr = nullptr;
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

    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }

    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }
};

#endif //SMARTPOINTER_UNQPTR_H
