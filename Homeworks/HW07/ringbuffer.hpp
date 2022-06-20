#ifndef __RING_BUFFER_H
#define __RING_BUFFER_H
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <cstdlib>
#include <cstring>

/* Initial size of the buffer */
#define RING_BUFFER_INIT_SIZE       8

/* You should grow buffer size to RING_BUFFER_GROW_FACTOR1 * _M_capacity, when current _M_capacity < 1024
   And RING_BUFFER_GROW_FACTOR2 * _M_capacity, when current _M_capacity >= 1024 */
#define RING_BUFFER_GROW_FACTOR1    2
#define RING_BUFFER_GROW_FACTOR2    1.5

namespace __detail
{
    // Iterator of vector (implement this)
    template <typename _Tp>
    class __iterator;

   // Const iterator of vector (implement this)
    template <typename _Tp>
    class __const_iterator;
}

/* The ring_buffer structure */
template <typename _Tp>
class RingBuffer{
public:
   // Type renaming
   typedef size_t                                           size_type;
   typedef _Tp                                              value_type;
   typedef _Tp*                                             pointer;
   typedef _Tp&                                             reference;
   typedef const _Tp&                                       const_reference;
   typedef ptrdiff_t                                        difference_type;
   typedef typename __detail::__iterator<_Tp>               iterator;
   typedef typename __detail::__const_iterator<_Tp>         const_iterator;

   /* Create a new ring buffer. You should allocate memory for its _M_content,
      initialize the _M_read_pos, _M_write_pos, and its _M_capacity to RING_BUFFER_INIT_SIZE */
   RingBuffer();

   // Copy and move constructor are deleted
   RingBuffer(const RingBuffer& other) = delete;

   RingBuffer(RingBuffer&& other) = delete;

   /* Destroy the given ring buffer, free all resources you've allocated. */
   ~RingBuffer();
   
   /* Returns its _M_capacity */
   size_t get_capacity() const;

   /* Returns true if the given ring buffer is empty, false otherwise */
   bool is_empty() const;

   /* Read an element from the ring buffer (i.e., the dequeue operation), *data records 
   the element popped. returns true if the operation succeeded, false otherwise. */
   bool read(_Tp& data);

   /* Write an element which value is `data` to the ring buffer (i.e., the enqueue operation),
   returns true if the operation succeeded, false otherwise. Note that when the buffer is 
   full, grow its size to make sure the element can be write successfully. The detailed 
   requirements of size growth are in the homework description. */
   bool write(const _Tp& data);

   /* Read "rdsize" elements from the ring buffer, and fill them to "data".
   Notice that you should only return true when this operation succeeds.
   If there are not enough elements in the buffer, just DO NOTHING and 
   return false. DO NOT modify the ring buffer and data for such cases.
   If size of "data" vector does not match "rdsize", you should resize "data" */
   bool read_multi(size_t rdsize, std::vector<_Tp>& data);

   /* Write "wrtsize" elements to the ring buffer. The values to write are 
   provided in "data". Returns true if succeeds, false otherwise. Don't 
   forget to grow your buffer size properly. */
   bool write_multi(size_t wrtsize, const std::vector<_Tp>& data);

   /* For every element in the ring buffer, apply "func" to it. For example,
   Your buffer currently contains 3 elements 1, 2, 4. If the map function is to 
   "add five", then their values should be 6, 7, 9 after calling this function. */
   bool map(std::function<_Tp(_Tp)>&& func);

   /* The iterator is used to interate through the ringbuffer. By iterating through the ring buffer, it means start from the oldest element in the ring buffer (i.e. the element pointed by "_M_read_pos"), to the latest one. end() should return the slot after the last element. You can refer to standart library for more info  */
   iterator begin();
   iterator end();

   // Const iterators
   const_iterator cbegin() const;
   const_iterator cend() const;

private:
   /* Grows the ringbuffer _M_capacity according to the growth factor */
   void grow();
   friend class __detail::__iterator<_Tp>;
   friend class __detail::__const_iterator<_Tp>;

private:
   size_t      _M_capacity;
   size_t      _M_read_pos;
   size_t      _M_write_pos;
   _Tp*          _M_content;
};

#include "ringbuffer.ipp"

#endif
