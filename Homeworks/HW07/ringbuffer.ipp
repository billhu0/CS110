

// The iterator class
template <typename _Tp>
class __detail::__iterator {
   public:
    // Default constructor
    __iterator() = default;

    // Copy constructor
    __iterator(const __iterator& a) {
        _ptr   = a._ptr;
        rb_ptr = a.rb_ptr;
    }

    // Initialize iterator with a ptr and ringbuffer ptr
    __iterator(_Tp* p, RingBuffer<_Tp>* buffer_ptr) {
        _ptr   = p;
        rb_ptr = buffer_ptr;
    }

    // Destructor (keep it default)
    ~__iterator() = default;

    // operator overloads

    // copy assignment operator =
    __iterator<_Tp>& operator=(const __iterator& a) {
        _ptr   = a._ptr;
        rb_ptr = a.rb_ptr;
        return *this;
    }

    // dereference operator *
    _Tp& operator*() { return *_ptr; }

    // arrow operator ->
    _Tp* operator->() { return _ptr; }

    // comparison operator ==
    bool operator==(const __iterator& a) { return _ptr == a._ptr; }

    // comparison operator !=
    bool operator!=(const __iterator& a) { return _ptr != a._ptr; }

    // self increment operator ++ (prefix) (++i)
    __iterator<_Tp>& operator++() {
        // if we are already at the end, since the buffer is a ring,
        // we should go to the front
        if (_ptr == &rb_ptr->_M_content[rb_ptr->_M_capacity - 1]) {
            _ptr = &rb_ptr->_M_content[0];
        } else
            _ptr++;  // otherwise, simply iterate the pointer once
        return *this;
    }

    // self decrement operator -- (prefix) (--i)
    __iterator<_Tp>& operator--() {
        // if we are already at the beginning, go to the end
        if (_ptr == &rb_ptr->_M_content[0]) {
            _ptr = &rb_ptr->_M_content[rb_ptr->_M_capacity - 1];
        } else
            _ptr--;  // otherwise, simply iterate the pointer once
        return *this;
    }

    // self increment operator ++ (suffix) (i++)
    __iterator<_Tp> operator++(int) {
        // save a copy of the original value
        __iterator<_Tp> result = *this;
        // iterate self:
        // if we are already at the end, since the buffer is a ring,
        // we should go to the front
        if (_ptr == &rb_ptr->_M_content[rb_ptr->_M_capacity - 1]) {
            _ptr = &rb_ptr->_M_content[0];
        } else
            _ptr++;  // otherwise, simply iterate the pointer once
        // return the original value;
        return result;
    }

    // self decrement operator -- (suffix) (i--)
    __iterator<_Tp> operator--(int) {
        // save a copy of the original value
        __iterator<_Tp> result = *this;

        // iterate self
        // if we are already at the beginning, go to the end
        if (_ptr == &rb_ptr->_M_content[0]) {
            _ptr = &rb_ptr->_M_content[rb_ptr->_M_capacity - 1];
        } else
            _ptr--;  // otherwise, simply iterate the pointer once
        // return the original value;
        return result;
    }

    // Arithmetic operator +
    __iterator<_Tp> operator+(int n) {
        __iterator<_Tp> result = *this;
        for (int i = 0; i < n; i++) ++result;  // use operator ++ (prefix)
        return result;
    }

    // operator -
    __iterator<_Tp> operator-(int n) {
        __iterator<_Tp> result = *this;
        for (int i = 0; i < n; i++) --result;  // use operator -- (prefix)
        return result;
    }

    // Compound assignment operator
    __iterator<_Tp>& operator+=(int n) {
        for (int i = 0; i < n; i++) ++(*this);  // use operator ++ (prefix)
        return *this;
    }

    // operator -=
    __iterator<_Tp>& operator-=(int n) {
        for (int i = 0; i < n; i++) --(*this);  // use operator -- (prefix)
        return *this;
    }

   private:
    // iterator members
    _Tp*             _ptr   = nullptr;
    RingBuffer<_Tp>* rb_ptr = nullptr;
    friend class __detail::__const_iterator<_Tp>;
};

// const iterator
template <typename _Tp>
class __detail::__const_iterator {
   public:
    // Default constructor
    __const_iterator() = default;

    // Copy constructor
    __const_iterator(const __const_iterator& a) {
        _ptr   = a._ptr;
        rb_ptr = a.rb_ptr;
    }

    // Initialize the iterator with a given ptr
    __const_iterator(_Tp* p, const RingBuffer<_Tp>* buffer_ptr) {
        _ptr   = p;
        rb_ptr = buffer_ptr;
    }

    // Copy constructor from normal non-const iterator
    __const_iterator(const __iterator<_Tp>& a) {
        _ptr   = a._ptr;
        rb_ptr = a.rb_ptr;
    }

    // Destructor (empty)
    ~__const_iterator() = default;

    // operator overloads

    // copy assignment operator =
    __const_iterator<_Tp>& operator=(const __const_iterator& a) {
        _ptr   = a._ptr;
        rb_ptr = a.rb_ptr;
        return *this;
    }

    // dereference operator *
    const _Tp& operator*() { return *_ptr; }

    // arrow operator ->
    const _Tp* operator->() { return _ptr; }

    // comparison operator ==
    bool operator==(const __const_iterator& a) { return _ptr == a._ptr; }

    // comparison operator !=
    bool operator!=(const __const_iterator& a) { return _ptr != a._ptr; }

    // self increment operator ++ (prefix)
    __const_iterator<_Tp>& operator++() {
        // if we are already at the end, since the buffer is a ring,
        // we should go to the front
        if (_ptr == &rb_ptr->_M_content[rb_ptr->_M_capacity - 1]) {
            _ptr = &rb_ptr->_M_content[0];
        } else {
            // otherwise, simply iterate the pointer once
            _ptr++;
        }
        return *this;
    }

    // self decrement operator -- (prefix)
    __const_iterator<_Tp>& operator--() {
        // if we are already at the beginning, go to the end
        if (_ptr == &rb_ptr->_M_content[0]) {
            _ptr = &rb_ptr->_M_content[rb_ptr->_M_capacity - 1];
        } else {
            // otherwise, simply iterate the pointer once
            _ptr--;
        }
        return *this;
    }

    // self increment operator ++ (suffix)
    __const_iterator<_Tp> operator++(int) {
        // save a copy of the original value
        __const_iterator<_Tp> result = *this;

        // iterate self:
        // if we are already at the end, since the buffer is a ring,
        // we should go to the front
        if (_ptr == &rb_ptr->_M_content[rb_ptr->_M_capacity - 1]) {
            _ptr = &rb_ptr->_M_content[0];
        } else {
            // otherwise, simply iterate the pointer once
            _ptr++;
        }

        // return the original value;
        return result;
    }

    // self decrement operator -- (suffix)
    __const_iterator<_Tp> operator--(int) {
        // save a copy of the original value
        __const_iterator<_Tp> result = *this;

        // iterate self
        // if we are already at the beginning, go to the end
        if (_ptr == &rb_ptr->_M_content[0]) {
            _ptr = &rb_ptr->_M_content[rb_ptr->_M_capacity - 1];
        } else {
            // otherwise, simply iterate the pointer once
            _ptr--;
        }

        // return the original value;
        return result;
    }

    // Arithmetic operator
    __const_iterator<_Tp> operator+(int n) {
        __const_iterator<_Tp> result = *this;
        for (int i = 0; i < n; i++) ++result;  // use operator ++ (prefix)
        return result;
    }

    // operator -
    __const_iterator<_Tp> operator-(int n) {
        __const_iterator<_Tp> result = *this;
        for (int i = 0; i < n; i++) --result;  // use operator -- (prefix)
        return result;
    }

    // Compound assignment operator
    __const_iterator<_Tp>& operator+=(int n) {
        for (int i = 0; i < n; i++) {
            ++(*this);
        }
        return *this;
    }

    // operator -=
    __const_iterator<_Tp>& operator-=(int n) {
        for (int i = 0; i < n; i++) {
            --(*this);
        }
        return *this;
    }

   private:
    // iterator members
    const _Tp*             _ptr   = nullptr;
    const RingBuffer<_Tp>* rb_ptr = nullptr;
};

// }  // namespace __detail

/* Create a new ring buffer. You should allocate memory for its _M_content,
      initialize the _M_read_pos, _M_write_pos, and its _M_capacity to
   RING_BUFFER_INIT_SIZE */
template <typename _Tp>
RingBuffer<_Tp>::RingBuffer() {
    /* Init the ring buffer */
    _M_capacity  = RING_BUFFER_INIT_SIZE;
    _M_read_pos  = 0;
    _M_write_pos = 0;
    /* Alloc a space for the content of the buffer */
    _M_content = new _Tp[RING_BUFFER_INIT_SIZE];
}

/* Destroy the given ring buffer, free all resources you've allocated. */
template <typename _Tp>
RingBuffer<_Tp>::~RingBuffer() {
    // check if our content is nullptr. If not, free it.
    if (_M_content) delete[] _M_content;
}

/* Returns its _M_capacity */
template <typename _Tp>
size_t RingBuffer<_Tp>::get_capacity() const {
    return _M_capacity;
}

/* Returns true if the given ring buffer is empty, false otherwise */
template <typename _Tp>
bool RingBuffer<_Tp>::is_empty() const {
    return _M_read_pos == _M_write_pos;
}

/* Read an element from the ring buffer (i.e., the dequeue operation), *data
   records the element popped. returns true if the operation succeeded, false
   otherwise. */
template <typename _Tp>
bool RingBuffer<_Tp>::read(_Tp& data) {
    // Check if our buffer is empty
    if (is_empty()) return false;
    // read out the data
    data = _M_content[_M_read_pos];
    // iterate 'read_pos' once by using mod operation
    _M_read_pos = (_M_read_pos + 1) % _M_capacity;
    return true;
}

/* Read "rdsize" elements from the ring buffer, and fill them to "data".
   Notice that you should only return true when this operation succeeds.
   If there are not enough elements in the buffer, just DO NOTHING and
   return false. DO NOT modify the ring buffer and data for such cases.
   If size of "data" vector does not match "rdsize", you should resize "data" */
template <typename _Tp>
bool RingBuffer<_Tp>::read_multi(size_t rdsize, std::vector<_Tp>& data) {
    // if read_size = 0 or the buffer is empty, stop
    if (rdsize == 0 || is_empty()) return false;
    // calculate how many elements we have
    size_t element_cnt = (_M_write_pos - _M_read_pos + _M_capacity) % _M_capacity;
    // check if there are enough elements
    if (rdsize > element_cnt) return false;
    // There are enough elements. But we need to resize 'data' first
    data.resize(rdsize);
    // Start reading.
    for (int i = 0; rdsize; i++, rdsize--) {
        // read the content and store
        data[i] = _M_content[_M_read_pos];
        // iterate 'read_pos' once using mod
        _M_read_pos = (_M_read_pos + 1) % _M_capacity;
    }
    return true;
}

/* Write an element which value is `data` to the ring buffer (i.e., the enqueue
   operation), returns true if the operation succeeded, false otherwise. Note
   that when the buffer is full, grow its size to make sure the element can be
   write successfully. The detailed requirements of size growth are in the
   homework description. */
template <typename _Tp>
bool RingBuffer<_Tp>::write(const _Tp& data) {
    // calculate how many elements we have
    size_t element_cnt = (_M_write_pos - _M_read_pos + _M_capacity) % _M_capacity;
    // grow ringbuffer if needed
    if (element_cnt == _M_capacity - 1) grow();

    // At this time, capacity is already expanded if full.
    // We have sufficient capacity now. Write the data.
    _M_content[_M_write_pos] = data;
    // iterate 'write_pos' once
    _M_write_pos = (_M_write_pos + 1) % _M_capacity;
    // write complete. return
    return true;
}

/* Write "wrtsize" elements to the ring buffer. The values to write are
   provided in "data". Returns true if succeeds, false otherwise. Don't
   forget to grow your buffer size properly. */
template <typename _Tp>
bool RingBuffer<_Tp>::write_multi(size_t wrtsize, const std::vector<_Tp>& data) {
    // wrtsize==0 check
    if (wrtsize == 0 || data.size() < wrtsize) return false;
    // use a for-loop to write all the data
    for (size_t i = 0; i < wrtsize; i++) write(data[i]);
    return true;
}

/* For every element in the ring buffer, apply "func" to it. For example,
   Your buffer currently contains 3 elements 1, 2, 4. If the map function is to
   "add five", then their values should be 6, 7, 9 after calling this function.
 */
template <typename _Tp>
bool RingBuffer<_Tp>::map(std::function<_Tp(_Tp)>&& func) {
    // start iteration from read_pos, apply map function one by one
    // until reaching the end (write_pos)
    for (size_t iter = _M_read_pos; iter != _M_write_pos; iter = (iter + 1) % _M_capacity) {
        _M_content[iter] = func(_M_content[iter]);
    }
    return true;
}

/* The iterator is used to interate through the ringbuffer. By iterating through
 * the ring buffer, it means start from the oldest element in the ring buffer
 * (i.e. the element pointed by "_M_read_pos"), to the latest one. end() should
 * return the slot after the last element. You can refer to standart library for
 * more info  */
template <typename _Tp>
__detail::__iterator<_Tp> RingBuffer<_Tp>::begin() {
    return __detail::__iterator<_Tp>(&_M_content[_M_read_pos], this);
}

// iterator end()
template <typename _Tp>
__detail::__iterator<_Tp> RingBuffer<_Tp>::end() {
    return __detail::__iterator<_Tp>(&_M_content[_M_write_pos], this);
}

// Const iterators
template <typename _Tp>
__detail::__const_iterator<_Tp> RingBuffer<_Tp>::cbegin() const {
    return __detail::__const_iterator<_Tp>(&_M_content[_M_read_pos], this);
}

// iterator cend()
template <typename _Tp>
__detail::__const_iterator<_Tp> RingBuffer<_Tp>::cend() const {
    return __detail::__const_iterator<_Tp>(&_M_content[_M_write_pos], this);
}

/* Grows the ringbuffer _M_capacity according to the growth factor */
template <typename _Tp>
void RingBuffer<_Tp>::grow() {
    // grow ringbuffer in this function.
    // calculate the original element count
    size_t element_cnt = (_M_write_pos - _M_read_pos + _M_capacity) % _M_capacity;

    if (element_cnt == _M_capacity - 1) {
        // buffer is full. Expand capacity.
        // calculate the new capacity according to the current capacity
        size_t new_capacity = _M_capacity * ((_M_capacity < 1024) ? RING_BUFFER_GROW_FACTOR1
                                                                  : RING_BUFFER_GROW_FACTOR2);
        // malloc a new content
        _Tp* new_content = new _Tp[new_capacity];
        // copy data
        for (int i = 0; is_empty() == false; i++) {
            read(new_content[i]);
        }
        // free the old buffer content
        delete[] _M_content;
        // update buffer properties
        _M_content   = new_content;   // set the new content []
        _M_capacity  = new_capacity;  // set the new capaity
        _M_read_pos  = 0;             // the new read_pos should be at the beginning
        _M_write_pos = element_cnt;   // the write_pos is at the end
    }
}
