#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <iostream>
#include <cstdlib>

// Simple resizable array template class
// that includes some of std::vector's basic operations


// NOTE: mstd::vector<T*> takes ownership of the passed pointers instead of copying them
// That means that if the pointers are deleted elsewhere, the program will *hopefully* crash
namespace mstd {
    template <typename T>
    class vector {
    private:
        size_t _size;
        size_t _capacity;
        int _last;
        T *_entries;

        void _enlarge() {
            T *tmp = new T[_capacity * 2];
            for (size_t i = 0; i < _size; i++) {
                tmp[i] = _entries[i];
            }

            delete[] _entries;

            _entries = tmp;

            _capacity *= 2;
        }

    public:
        explicit vector( bool ptr = false, size_t capacity = 1)
                : _size(0), _capacity(capacity), _last(0) {
            _entries = new T[_capacity];
        }

        vector(const vector &other)
                : _size(other._size),
                  _capacity(other._capacity) {

            _entries = new T[_capacity];
            for (size_t i = 0; i < _size; i++) {
                _entries[i] = other._entries[i];
            }
            _last = other._last;
        }

        vector(const vector &other, int start, int end) {
            if (start < 0 || end > (int) other._size) return;
            _capacity = other._capacity;
            _size = (size_t) end - start;
            _last = other._last;
            _entries = new T[_capacity];
            int cur = 0;
            for (size_t i = (size_t) start; i < (size_t) end; i++) {
                _entries[cur++] = other._entries[i];
            }
        }

        vector sublist(int start, int length) {
            if (start + length > (int) _size) {
                throw std::runtime_error("Bad indices");
            }

            vector tmp;
            for (size_t i = (size_t) start; i <= (size_t) start + length; i++) {
                tmp.push(_entries[i]);
            }

            return tmp;
        }

        ~vector() {
            delete[] _entries;
        }

        void push(T ent) {
            if (_size + 1>= (size_t) _capacity) {
                _enlarge();
            }

            _entries[_last++] = ent;
            _size++;
        }

        void add(T ent) {
            push(ent);
        }

        void insert_at(int index, T ent) {
            if (_size + 1>= (size_t) _capacity) {
                _enlarge();
            }

            if (index == 0) {
                push(ent);
                return;
            }

            for (size_t i = _size - 1; i >= index; i--) {
                _entries[i + 1] = _entries[i];
            }

            _entries[index] = ent;
            _size++;
        }

        bool in(T ent) {
            for (size_t i = 0; i < _size; i++) {
                if (_entries[i] == ent) {
                    return true;
                }
            }
            return false;
        }

        T &at(int index) {
            if (index >= (int) _size) {
                throw std::runtime_error("Index out of range:");
            }

            return _entries[index];
        }

        // Method sugar
        T &get(int index) {
            return at(index);
        }



        T *at_p(int index) {
            if (index >= (int) _size) {
                throw std::runtime_error("Index out of range");
            }

            return &_entries[index];
        }

        // Method sugar
        T *get_p(int index) {
            return at_p(index);
        }

        int get_index(T ent) {
            for (size_t i = 0; i < _size; i++) {
                if (_entries[i] == ent) return (int) i;
            }
            return -1;
        }

        void clear() {
            if (_size != 0) delete[] _entries;

            _size = 0;

            _last = 0;

            _capacity = 1;
            _entries = new T[_capacity];
        }

        void set_at(int index, T ent) {
            if (index < 0 || index > (int) _size) {
                throw std::runtime_error("Bad index: " + index);
            }

            _entries[index] = ent;
        }


        bool remove(T ent) {
            T *tmp = new T[_capacity];
            int j = 0;
            bool found = false;
            for (size_t i = 0; i < _size; i++) {
                if (_entries[i] == ent) {
                    found = true;
                    continue;
                }

                tmp[j++] = _entries[i];
            }

            if (found) {
                delete[] _entries;
                _entries = tmp;

                _size--;
                _last--;
            } else {
                delete[] tmp;
            }

            return found;
        }

        void remove_at(int index) {
            if (index >= (int) _size || index < 0) {
                throw std::runtime_error("Bad index: " + index);
            }
            T *tmp_ent = new T[_capacity];

            int j = 0;
            for (size_t i = 0; i < _size; i++) {
                if ((int) i != index) {
                    tmp_ent[j++] = _entries[i];
                }
            }

            delete[] _entries;

            _entries = tmp_ent;

            _size--;
            _last--;
        }

        size_t size() { return _size; }

        vector operator=(const vector &other) {
            delete[] _entries;
            _size = other._size;
            _capacity = other._capacity;
            _entries = new T[_capacity];
            for (size_t i = 0; i < _capacity; i++) {
                _entries[i] = other._entries[i];
            }

            return *this;
        }

        bool operator==(const vector &other) {
            return true;
        }

        friend std::ostream &operator<<(std::ostream &out, vector vec) {
            out << vec._size;
            return out;
        }
    };

    template <typename T>
    class vector;

    template <typename T>
    class vector<T *> {
    private:
        size_t _size;
        size_t _capacity;
        int _last;
        T **_entries;

        void _enlarge() {
            T **tmp = new T*[_capacity * 2];
            for (size_t i = 0; i < _size; i++) {
                tmp[i] = new T(*_entries[i]);
            }

            for (int i = 0; i < _size; i++) {
                delete _entries[i];
            }
            delete[] _entries;

            _entries = tmp;

            _capacity *= 2;
        }

    public:
        explicit vector(size_t capacity = 1)
                : _size(0), _capacity(capacity), _last(0) {
            _entries = new T*[_capacity];
        }

        vector(const vector &other)
                : _size(other._size),
                  _capacity(other._capacity) {

            _entries = new T*[_capacity];
            for (size_t i = 0; i < _size; i++) {
                _entries[i] = new T(*other._entries[i]);
            }
            _last = other._last;
        }

        vector(const vector &other, int start, int end) {
            if (start < 0 || end > (int) other._size) return;
            _capacity = other._capacity;
            _size = (size_t) end - start;
            _last = other._last;
            _entries = new T*[_capacity];
            int cur = 0;
            for (size_t i = (size_t) start; i < (size_t) end; i++) {
                _entries[cur++] = new T(other._entries[i]);
            }
        }

        ~vector() {
            for (int i = 0; i < _size; i++) {
                delete _entries[i];
            }
            delete[] _entries;
        }

        void push(T *ent) {
            if (_size + 1 >= (size_t) _capacity) {
                _enlarge();
            }

            _entries[_last++] = ent;
            _size++;
        }

        vector sublist(int start, int length) {
            if (start + length > (int) _size) {
                throw std::runtime_error("Bad indices");
            }

            vector tmp;
            for (size_t i = (size_t) start; i <= (size_t) start + length; i++) {
                tmp.push(_entries[i]);
            }

            return tmp;
        }

        void add(T *ent) {
            push(ent);
        }

        void insert_at(int index, T *ent) {
            if (_size + 1>= (size_t) _capacity) {
                _enlarge();
            }

            if (index == 0) {
                push(ent);

            }

            for (size_t i = _size - 1; i >= index; i--) {
                _entries[i + 1] = _entries[i];
            }

            _entries[index] = ent;
            _size++;
        }

        bool in(T *ent) {
            for (size_t i = 0; i < _size; i++) {
                if (*_entries[i] == *ent) {
                    return true;
                }
            }
            return false;
        }

        T *at(int index) {
            if (index >= (int) _size) {
                throw std::runtime_error("Index out of range:");
            }

            return _entries[index];
        }

        // Method sugar
        T *get(int index) {
            return at(index);
        }

        int get_index(T ent) {
            for (size_t i = 0; i < _size; i++) {
                if (*_entries[i] == *ent) return (int) i;
            }
            return -1;
        }

        void clear() {
            if (_size != 0) {
                for (int i = 0; i < _size; i++) {
                    delete _entries[i];
                }
                delete[] _entries;
            }

            _size = 0;

            _last = 0;

            _capacity = 1;
            _entries = new T*[_capacity];
        }

        void set_at(int index, T *ent) {
            if (index < 0 || index > (int) _size) {
                throw std::runtime_error("Bad index: " + index);
            }

            _entries[index] = new T(*ent);
        }

        //
        bool remove(T *ent) {
            T **tmp = new T*[_capacity];
            int j = 0;
            bool found = false;
            for (size_t i = 0; i < _size; i++) {
                if (*_entries[i] == *ent) {
                    delete _entries[i];
                    found = true;
                    continue;
                }

                tmp[j++] = _entries[i];
            }

            // TODO: Not tested!
            if (found) {
                delete[] _entries;
                _entries = tmp;

                _size--;
                _last--;
            } else {
                delete[] tmp;
            }

            return found;
        }

        void remove_at(int index) {
            if (index >= (int) _size || index < 0) {
                throw std::runtime_error("Bad index: " + index);
            }
            T *tmp_ent = new T[_capacity];

            int j = 0;
            for (size_t i = 0; i < _size; i++) {
                if ((int) i != index) {
                    tmp_ent[j++] = _entries[i];
                }
            }

            delete[] _entries;

            _entries = tmp_ent;

            _size--;
            _last--;
        }

        size_t size() { return _size; }

        vector<T*> &operator=(const vector<T*> &other) {
            if (_entries != other._entries) {
                return *this;
            }
            for (int i = 0; i < _size; i++) {
                delete _entries[i];
            }
            delete[] _entries;
            _size = other._size;
            _capacity = other._capacity;
            _entries = new T[_capacity];
            for (size_t i = 0; i < _capacity; i++) {
                _entries[i] = new T(*other._entries[i]);
            }

            return *this;
        }

        friend std::ostream &operator<<(std::ostream &out, vector<T*> vec) {
            out << vec._size;
            return out;
        }
    };
}


#endif //MY_VECTOR_H
