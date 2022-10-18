/**
 * @file HashMap.hpp
 * @author  Liron Gershuny <liron.gershuny@mail.huji.ac.il>
 * @version 1.0
 * @date 20 Jan 2020
 *
 * @brief An implementation of template hash-map that include a const-iterator.
 *
 * @section LICENSE
 * This program is not a free software; bla bla bla...
 *
 * @section DESCRIPTION
 * The program defines a template class of hash-map including a nested class for const-iterator.
 *
 */

#ifndef CPP_EX3_HASHMAP_HPP
#define CPP_EX3_HASHMAP_HPP

// ------------------------------ includes ------------------------------
#include <vector>

// -------------------------- const definitions -------------------------

/*
 * @def INIT_CAPACITY 16
 * @brief The initialize capacity of the hash-map
 */
#define INIT_CAPACITY 16

/*
 * @def MIN_VALID_CAPACITY 1
 * @brief The min valid capacity of the hash-map
 */
#define MIN_VALID_CAPACITY 1

/*
 * @def INIT_SIZE 0
 * @brief The initialize size (number of arguments) of the hash-map
 */
#define INIT_SIZE 0

/*
 * @def MIN_LOAD_FACTOR 0.25
 * @brief The min valid load factor of the hash-map
 */
#define MIN_LOAD_FACTOR 0.25

/*
 * @def MAX_LOAD_FACTOR 0.75
 * @brief The max valid load factor of the hash-map
 */
#define MAX_LOAD_FACTOR 0.75

/*
 * @def TABLE_SIZE_FACTOR 2
 * @brief The multiplication factor of capacity when re-hashing the hash-map
 */
#define TABLE_SIZE_FACTOR 2

/*
 * @def INVALID_VECTORS_ERR "Given vectors lengths are not equal"
 * @brief An error message when trying to preform operations on not-equal vector lengths
 */
#define INVALID_VECTORS_ERR "Given vectors lengths are not equal"

/*
 * @def INVALID_KEY_ERR "Given key doesn't exist inside the hash map"
 * @brief An error message when trying to reach a key that doesn't belong to the hash-map
 */
#define INVALID_KEY_ERR "Given key doesn't exist inside the hash map"


// ------------------------ class implementation ------------------------

/**
 * An implementation of hash-map class.
 * @tparam KeyT The template parameter of the hash-map keys
 * @tparam ValueT The template parameter of the hash-map values
 */
template <typename KeyT, typename ValueT>
class HashMap
{
private:
    using bucket = std::vector<std::pair<KeyT, ValueT>>;

    int _size;
    int _capacity;
    double _minLoadFactor;
    double _maxLoadFactor;
    bucket *_mapPointer;
    std::hash<KeyT> _hashFunction;

    /**
     * A function that calculates the hash value of given key according to the given capacity.
     * @param key The given key we want to find in the map
     * @param capacity The capacity of the map
     * @return The hash value after calculation
     */
    int _hashingFunc(const KeyT& key, const int capacity) const
    {
        int hashValue = _hashFunction(key) & (capacity - 1);
        return hashValue;
    }


    /**
     * A function that manage re-hsahing of the map according to given new capacity.
     * @param newCapacity The new capacity of the map
     */
    void _rehashMap(const int& newCapacity)
    {
        auto *tempHashMap = new bucket[newCapacity];

        for(int i = 0 ; i < _capacity ; i++)
        {
            for(std::pair<KeyT, ValueT> currentPair: _mapPointer[i])
            {
                int newHashValue = _hashingFunc(currentPair.first, newCapacity);
                tempHashMap[newHashValue].push_back(currentPair);
            }
        }

        _capacity = newCapacity;
        std::swap(_mapPointer, tempHashMap);
        delete [] tempHashMap;
    }


public:

    /**
     * A default constructor of the hash-map, will initialize all private members of the class.
     */
    HashMap() : _size(INIT_SIZE), _capacity(INIT_CAPACITY), _minLoadFactor(MIN_LOAD_FACTOR),
                _maxLoadFactor(MAX_LOAD_FACTOR), _mapPointer(new bucket[_capacity]){}


    /**
     * A constructor that gets two vectors, one with keys and one with values.
     * will construct hash-map that will be filled with the given key[i]->value[i]
     * @param keyVec A vector full of keys to insert to the hash-map
     * @param valueVec A vector full of values to insert to the hash-map
     */
    HashMap(const std::vector<KeyT>& keyVec, const std::vector<ValueT>& valueVec) : HashMap()
    {
        if(keyVec.size() != valueVec.size())
        {
            delete [] _mapPointer;
            throw std::invalid_argument(INVALID_VECTORS_ERR);
        }
        try
        {
            for(long unsigned int i = 0 ; i < keyVec.size() ; i++)
            {
                (*this)[keyVec[i]] = valueVec[i];
            }
        }
        catch (const std::bad_alloc&)
        {
            delete [] _mapPointer;
            throw;
        }
    }


    /**
     * A copy constructor of hash-map, will get reference to constructed hash-map
     * and initialize new one with the same information of the given one.
     * @param other The given hash-map
     */
    HashMap(const HashMap& other) : _size(other._size), _capacity(other._capacity),
                                    _minLoadFactor(other._minLoadFactor),
                                    _maxLoadFactor(other._maxLoadFactor),
                                    _mapPointer(new bucket[_capacity])
    {
        for(int i = 0 ; i < _capacity ; i++)
        {
            _mapPointer[i] = other._mapPointer[i];
        }
    }


    /**
     * A destructor of the hash-map, will delete all allocated memory.
     */
    ~HashMap()
    {
        delete [] _mapPointer;
    }


    /**
     * A getter function of the size of the hash-map.
     * @return The current size of the hash-map
     */
    int size() const
    {
        return _size;
    }


    /**
     * A getter function of the capacity of the hash-map.
     * @return The current capacity of the hash-map
     */
    int capacity() const
    {
        return _capacity;
    }


    /**
     * A function that checks if the hash-map is empty.
     * @return true if the hash-map is empty, false otherwise
     */
    bool empty() const
    {
        if(_size == 0)
        {
            return true;
        }
        return false;
    }


    /**
     * A function that gets a key and its value and insert the information to the hash-map
     * @param key The given key
     * @param value The given value
     * @return true if the insertion succeeded, false otherwise
     */
    bool insert(const KeyT& key, const ValueT& value)
    {
        if(containsKey(key))
        {
            return false;
        }

        try
        {
            _size++;
            if(getLoadFactor() > _maxLoadFactor)
            {
                _rehashMap(_capacity * TABLE_SIZE_FACTOR);
            }

            int hashValue = _hashingFunc(key, _capacity);
            _mapPointer[hashValue].push_back(std::pair<KeyT, ValueT>(key, value));

            return true;
        }
        catch (std::bad_alloc &)
        {
            _size--;
            return false;
        }
    }


    /**
     * A function that checks if given key is already inside the hash-map.
     * @param key The given key to check
     * @return true if the given key is already inside the map, false otherwise
     */
    bool containsKey(const KeyT& key) const
    {
        int hashValue = _hashingFunc(key, _capacity);

        for(std::pair<KeyT, ValueT> currentPair: _mapPointer[hashValue])
        {
            if(currentPair.first == key)
            {
                return true;
            }
        }
        return false;
    }


    /**
     * A non-const version of 'at' operation that return the value
     * of given key if its inside the hash-map, if not- an exception will be raised.
     * @param key The given key to check
     * @return The value of the given key
     */
    ValueT& at(const KeyT& key)
    {
        int hashValue = _hashingFunc(key, _capacity);

        for(long unsigned int i = 0 ; i < _mapPointer[hashValue].size() ; i++)
        {
            if(_mapPointer[hashValue][i].first == key)
            {
                return _mapPointer[hashValue][i].second;
            }
        }

        throw std::invalid_argument(INVALID_KEY_ERR);
    }


    /**
     * A const version of 'at' operation that return the value
     * of given key if its inside the hash-map, if not- an exception will be raised.
     * @param key The given key to check
     * @return The value of the given key
     */
    const ValueT& at(const KeyT& key) const
    {
        int hashValue = _hashingFunc(key, _capacity);
        for(long unsigned int i = 0 ; i < _mapPointer[hashValue].size() ; i++)
        {
            if(_mapPointer[hashValue][i].first == key)
            {
                return _mapPointer[hashValue][i].second;
            }
        }

        throw std::invalid_argument(INVALID_KEY_ERR);
    }


    /**
     * A function that erase the given key from the hash-map,
     * will check if the key is already in the map amd if so, it will be deleted with its value.
     * @param key The given key to delete
     * @return true if the key and its value is successfully deleted, false otherwise
     */
    bool erase(const KeyT& key)
    {
        if(!containsKey(key))
        {
            return false;
        }

        int hashValue = _hashingFunc(key, _capacity);
        auto it = _mapPointer[hashValue].begin();
        while(it->first != key)
        {
            it++;
        }

        try
        {
            _size--;
            if(getLoadFactor() < _minLoadFactor && _capacity > MIN_VALID_CAPACITY)
            {
                _rehashMap(_capacity / TABLE_SIZE_FACTOR);
            }

            int newHashValue = _hashingFunc(key, _capacity);
            _mapPointer[newHashValue].erase(it);
            return true;
        }
        catch (std::bad_alloc &)
        {
            _size++;
            return false;
        }
    }


    /**
     * A function that calculates the current load factor of the hash-map.
     * @return The current load factor of the map
     */
    double getLoadFactor() const
    {
        double loadFactor = ((double) _size) / ((double) _capacity);
        return loadFactor;
    }


    /**
     * A function that calculates the size of a bucket includes the given key.
     * @param key The given key needed to be found and calculate its bucket size
     * @return The bucket size where the key is founded,
     * will throw an exception if the key is not inside the map
     */
    int bucketSize(const KeyT& key) const
    {
        if(!containsKey(key))
        {
            throw std::invalid_argument(INVALID_KEY_ERR);
        }

        int hashValue = _hashingFunc(key, _capacity);
        int size = _mapPointer[hashValue].size();
        return size;
    }


    /**
     * A function that calculates the index of a bucket includes the given key.
     * @param key The given key needed to be found and calculate its bucket index
     * @return The bucket index where the key is founded,
     * will throw an exception if the key is not inside the map
     */
    int bucketIndex(const KeyT& key) const
    {
        if(!containsKey(key))
        {
            throw std::invalid_argument(INVALID_KEY_ERR);
        }

        int hashValue = _hashingFunc(key, _capacity);
        return hashValue;
    }


    /**
     * A function that delete all the hash-map members,
     * will set the size to zero and initialize new map.
     */
    void clear()
    {
        delete [] _mapPointer;
        _size = 0;
        _mapPointer = new bucket[_capacity];
    }


    /**
     * An implementation of const iterator nested-class
     */
    class const_iterator
    {
    private:
        const HashMap *_hashMap;
        int _currentBucket;
        int _currentObject;

    public:

        typedef const_iterator self_type;
        typedef std::pair<KeyT, ValueT> value_type;
        typedef std::pair<KeyT, ValueT> &reference;
        typedef std::pair<KeyT, ValueT> *pointer;
        typedef int difference_type;
        typedef std::forward_iterator_tag iterator_category;


        /**
         * An explicit constructor of the const iterator. Will initiate all its members
         * according to the current situation of the hash-map.
         * @param hashMap A pointer to the hash-map
         * @param bucket The bucket index we will iterate on
         * @param object The object index inside the current bucket
         */
        explicit const_iterator(const HashMap *hashMap, int bucket = 0, int object = 0) :
                _hashMap(hashMap), _currentBucket(bucket), _currentObject(object)
        {
            if(!_hashMap->empty())
            {
                while(_hashMap->_mapPointer[_currentBucket].empty() &&
                      _currentBucket < _hashMap->capacity())
                {
                    _currentBucket++;
                }
            }
        }


        /**
         * An implementation const version of de-referencing operator.
         * @return The pair of key and its value from the current position in the map
         */
        const std::pair<KeyT, ValueT> &operator*() const
        {
            return _hashMap->_mapPointer[_currentBucket][_currentObject];
        }


        /**
         * An implementation const version of access operator.
         * @return The pair of key and its value from the current position in the map
         */
        const std::pair<KeyT, ValueT> *operator->() const
        {
            auto object = _hashMap->_mapPointer[_currentBucket][_currentObject];
            return &object;
        }


        /**
         * An implementation of increase operator
         * @return const iterator after we moved forward one step
         */
        const_iterator &operator++()
        {
            if(_currentObject == (int) _hashMap->_mapPointer[_currentBucket].size() - 1)
            {
                _currentBucket++;
                _currentObject = 0;
                while(_hashMap->_mapPointer[_currentBucket].empty() &&
                      _currentBucket != _hashMap->_capacity)
                {
                    _currentBucket++;
                }
                return *this;
            }
            else
            {
                _currentObject++;
            }
            return *this;
        }


        /**
         * An implementation of increase operator
         * @return const iterator of the object before we preform increasment
         */
        const const_iterator operator++(int)
        {
            const_iterator temp = *this;
            ++(*this);
            return temp;
        }


        /**
         * An implementation of comparing operator between two hash-map and its members.
         * @param other The second iterator we want to compare to ours
         * @return true if the two iterators represent the same hash-map, false otherwise
         */
        bool operator==(const const_iterator& other) const
        {
            return (_hashMap == other._hashMap && _currentBucket == other._currentBucket &&
                    _currentObject == other._currentObject);
        }


        /**
         * An implementation of comparing operator between two hash-map and its members.
         * @param other The second iterator we want to compare to ours
         * @return true if the two iterators not represent the same hash-map, false otherwise
         */
        bool operator!=(const const_iterator& other) const
        {
            return (!(*this == other));
        }

    };


    /**
     * An implementation of un-const version of begin function of the iterator.
     * @return const iterator to the begining of the map
     */
    const_iterator begin() const
    {
        return const_iterator(this);
    }


    /**
     * An implementation of const version of begin function of the iterator.
     * @return const iterator to the begining of the map
     */
    const const_iterator cbegin() const
    {
        return const_iterator(this);
    }


    /**
     * An implementation of un-const version of end function of the iterator.
     * @return const iterator to the end of the map
     */
    const_iterator end() const
    {
        return const_iterator(this, _capacity);
    }


    /**
     * An implementation of const version of end function of the iterator.
     * @return const iterator to the end of the map
     */
    const const_iterator cend() const
    {
        return const_iterator(this, _capacity);
    }


    /**
     * An implementation of placement operator that iterate over
     * all map objects and copy information from other map.
     * @param other The second hash-map we want to place its information inside our map
     * @return The current hash-map after placement
     */
    HashMap &operator=(const HashMap& other)
    {
        if(this != &other)
        {
            _size = other._size;
            _capacity = other._capacity;
            _minLoadFactor = other._minLoadFactor;
            _maxLoadFactor = other._maxLoadFactor;

            delete [] _mapPointer;
            _mapPointer = new bucket[_capacity];
            for(int i = 0 ; i < _capacity ; i++)
            {
                _mapPointer[i] = other._mapPointer[i];
            }
        }

        return *this;
    }





    /**
     * A un-const version of subscript operator.
     * Will get a key and find its value inside the hash-map
     * @param key The given key to search for its value
     * @return If the map contains the given key return its value, else return zero
     */
    ValueT &operator[](const KeyT& key)
    {
        if(containsKey(key))
        {
            return at(key);
        }
        else
        {
            ValueT value = 0;
            insert(key, value);
            return at(key);
        }
    }


    /**
     * A const version of subscript operator.
     * Will get a key and find its value inside the hash-map
     * @param key The given key to search for its value
     * @return If the map contains the given key return its value, else return zero
     */
    const ValueT &operator[](const KeyT& key) const
    {
        if(containsKey(key))
        {
            return at(key);
        }
        else
        {
            ValueT value = 0;
            insert(key, value);
            return at(key);
        }
    }


    /**
     * An implementation of comparing operator between two hash-maps.
     * @param other The map we want to compare to the current one
     * @return true if the two hash-maps are equal, false otherwise
     */
    bool operator==(const HashMap& other) const
    {
        if(_size != other._size || _capacity != other._capacity)
        {
            return false;
        }

        for(int i = 0 ; i < _capacity ; i++)
        {
            for(std::pair<KeyT, ValueT> currentPair: _mapPointer[i])
            {
                if(!other.containsKey(currentPair.first) ||
                   currentPair.second != other.at(currentPair.first))
                {
                    return false;
                }
            }
        }

        return true;
    }


    /**
     * An implementation of comparing operator between two hash-maps.
     * @param other The map we want to compare to the current one
     * @return true if the two hash-maps are not equal, false otherwise
     */
    bool operator!=(const HashMap& other) const
    {
        return (!(*this == other));
    }

};

#endif //CPP_EX3_HASHMAP_HPP
