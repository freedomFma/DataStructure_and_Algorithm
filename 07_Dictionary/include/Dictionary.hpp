#include "Rank.hpp"
#undef get

#ifndef DICTIONARY_H
#define DICTIONARY_H

template <typename K, typename V>
struct Dictionary{
    virtual Rank size() = 0;
    virtual bool put(K key, V value) = 0;
    virtual V* get(K key) = 0;
    virtual bool remove(K key) = 0;
};

#endif