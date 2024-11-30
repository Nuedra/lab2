#ifndef COMPARE_HPP
#define COMPARE_HPP

template<typename T>
int compare_default(const T& a, const T& b) {
    if (a < b) {
        return -1;
    }
    if (a > b) {
        return 1;
    }
    return 0;
}

template <typename T, typename KeyType>
class ComparatorWrapper {
public:
    static KeyType T::*key;  // Указатель на поле для сравнения

    // Устанавливаем поле, по которому будет выполняться сравнение
    static void SetKey(KeyType T::*key_field) {
        key = key_field;
    }

    // Статическая функция сравнения, совместимая с интерфейсом сортировщика
    static int Compare(const T& a, const T& b) {
        if (a.*key < b.*key) {
            return -1;
        }
        else if (a.*key > b.*key) {
            return 1;
        }
        return 0;
    }
};

// Определение статического члена класса
template <typename T, typename KeyType>
KeyType T::*ComparatorWrapper<T, KeyType>::key = nullptr;

template <typename T>
class ChainedComparator {
public:
    static std::vector<int(*)(const T&, const T&)> comparators;

    static void AddComparator(int(*cmp)(const T&, const T&)) {
        comparators.push_back(cmp);
    }

    static int Compare(const T& a, const T& b) {
        for (auto& cmp : comparators) {
            int result = cmp(a, b);
            if (result != 0) {
                return result;
            }
        }
        return 0; // Если все компараторы вернули равенство, считаем объекты равными
    }

    static void ClearComparators() {
        comparators.clear();
    }
};

// Определение статического члена
template <typename T>
std::vector<int(*)(const T&, const T&)> ChainedComparator<T>::comparators = {};

#endif COMPARE_HPP