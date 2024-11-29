#ifndef LAB2_COMPARE_HPP
#define LAB2_COMPARE_HPP

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

template<typename T, typename Key>
int compare_by_key(const T& a, const T& b, Key T::*key) {
    if (a.*key < b.*key) {
        return -1;
    }
    if (a.*key > b.*key) {
        return 1;
    }
    return 0;
}


#endif LAB2_COMPARE_HPP