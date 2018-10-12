#ifndef _HASH_TABLE_HPP_
#define _HASH_TABLE_HPP_

#include <utility>

namespace pph {

    template <class Key,
        class T,
        class hash = std::hash<Key> >
    class hash_table;

}