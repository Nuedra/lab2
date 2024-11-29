#ifndef LAB1_SMRT_PTR_HPP
#define LAB1_SMRT_PTR_HPP

#include <stdexcept>
#include <typeinfo>

template <typename T>
class SmrtPtr {
private:
    T* ptr;                  // Указатель на управляемый объект
    size_t* ref_count;       // Указатель на счетчик ссылок

    void release() const{
        if (--(*ref_count) == 0) {  // Уменьшаем счетчик, удаляем, если он обнуляется
            delete ptr;
            delete ref_count;
        }
    }

public:
    explicit SmrtPtr(T *p = nullptr) : ptr(p), ref_count(new size_t(1)) {}

    SmrtPtr(const SmrtPtr<T> &other) : ptr(other.ptr), ref_count(other.ref_count) {
        ++(*ref_count);
    }

    // Шаблонный конструктор копирования для совместимых типов
    template <typename U>
    SmrtPtr(const SmrtPtr<U>& other) : ptr(static_cast<T*>(other.ptr)), ref_count(other.ref_count) {
        ++(*ref_count);
    }

    // Деструктор
    ~SmrtPtr() {
        release();
    }

    SmrtPtr<T>& operator=(const SmrtPtr<T> &other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            ++(*ref_count);
        }

        return *this;
    }

    // Шаблонный оператор присваивания для совместимых типов
    template <typename U>
    SmrtPtr<T>& operator=(const SmrtPtr<U>& other) {
        if (this != static_cast<const SmrtPtr<T>*>(&other)) {
            release();
            ptr = static_cast<T*>(other.ptr);
            ref_count = other.ref_count;
            ++(*ref_count);
        }

        return *this;
    }

    T& operator*() {
        if (ptr != nullptr) return *ptr;
        throw std::logic_error("Error: null pointer dereference");
    }

    const T& operator*() const {
        if (ptr != nullptr) return *ptr;
        throw std::logic_error("Error: null pointer dereference");
    }

    T* operator->() {
        if (ptr != nullptr) return ptr;
        throw std::logic_error("Error: null pointer access");
    }

    const T* operator->() const {
        if (ptr != nullptr) return ptr;
        throw std::logic_error("Error: null pointer access");
    }


    [[nodiscard]] size_t use_count() const {
        return *ref_count;
    }

    [[nodiscard]] bool null() const {
        return ptr == nullptr;
    }


    template <typename U>
    friend class SmrtPtr;
};


template <typename T>
class SmrtPtr<T[]> {
private:
    T* ptr;
    size_t* ref_count;

    void release() const {
        if (--(*ref_count) == 0) {
            delete[] ptr;
            delete[] ref_count;
        }
    }

public:
    explicit SmrtPtr(T *p = nullptr) : ptr(p), ref_count(new size_t(1)) {}

    SmrtPtr(const SmrtPtr<T[]> &other) : ptr(other.ptr), ref_count(other.ref_count) {
        ++(*ref_count);
    }

    template <typename U>
    SmrtPtr(const SmrtPtr<U[]>& other) : ptr(dynamic_cast<T*>(other.ptr)), ref_count(other.ref_count) {
        if (!ptr) {
            throw std::bad_cast();
        }

        ++(*ref_count);
    }

    ~SmrtPtr() {
        release();
    }

    SmrtPtr<T[]>& operator=(const SmrtPtr<T[]> &other) {
        if (this != &other) {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            ++(*ref_count);
        }

        return *this;
    }

    // Шаблонный оператор присваивания для подтипов
    template <typename U>
    SmrtPtr<T[]>& operator=(const SmrtPtr<U[]>& other) {
        T* temp_ptr = dynamic_cast<T*>(other.ptr);  // Проверка приведения типа

        if (!temp_ptr) {
            throw std::bad_cast();
        }

        release();
        ptr = temp_ptr;
        ref_count = other.ref_count;
        ++(*ref_count);

        return *this;
    }

    const T& operator*() const {
        if (ptr != nullptr) return *ptr;
        throw std::logic_error("Error: null pointer dereference!");
    }

    const T* operator->() const {
        if (ptr != nullptr) return ptr;
        throw std::logic_error("Error: null pointer access");
    }

    const T& operator[](size_t index) const {
        if (ptr != nullptr) return ptr[index];
        throw std::logic_error("Error: null pointer dereference");
    }


    [[nodiscard]] size_t use_count() const {
        return *ref_count;
    }

    template <typename U>
    friend class SmrtPtr;
};

#endif //LAB1_SMRT_PTR_HPP
