#include <cstring>

template <typename T>
class stack {
private:
	class node {
    private:
        T _entry;
        node *_next;
    public:
        node(T ent, node *next = nullptr) {
            _entry = ent;
            _next = next;
        }

        node(const node &other) {
            _entry = other._entry;
            if (other._next != nullptr)
                _next = new node(other._next->_entry);
        }

        ~node() {
            // Do nothing here
        }

        node *get_next() { return _next; }

        void set_next(node *next) {
            _next = next;
        }

        void add_next(node *next) {
            _next = new node(next->_entry);
        }

        T &get_entry() { return _entry; }

        node &operator=(node &other) {
            _entry = other._entry;
            _next = new node(other._next->_entry);
            return *this;
        }
    };
	
	node *_head;
	size_t _size;
	size_t _max;
	
public:
	stack(size_t max = -1);
	
	stack(const stack &other)=delete;
	
	~stack();
	
	void push(T ent);
	
	T pop();
	
	T &peek();
	
	size_t size();
	
	bool full();
	
	bool empty();
	
	stack operator=(const stack &other)=delete;
};
