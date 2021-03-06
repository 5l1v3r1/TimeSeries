#ifndef TS_ITERATORS_INDEXES_H
#define TS_ITERATORS_INDEXES_H
#include <functional>
#include <iostream>
#include <ts_arithmetic.h>
namespace TimeSeries::details::iterators
{
  template<typename ValueType, bool iterTime = true>
  struct _iterator_indexes : public details::arithmetic::_incrementable_object<
                                 _iterator_indexes<ValueType, iterTime>>,
                             public details::arithmetic::_comparable_object<
                                 _iterator_indexes<ValueType, iterTime>>
  {
    using value_ptr_t = ValueType*;
    using time_ptr_t  = double*;

    value_ptr_t data;
    time_ptr_t time;
    std::size_t increment = 1;

    _iterator_indexes() = delete;

    _iterator_indexes(const _iterator_indexes& other)
        : data{other.data}, time{other.time}, increment{other.increment}
    {}

    _iterator_indexes(time_ptr_t time, value_ptr_t data, std::size_t increment)
        : data{data}, time{time}, increment{increment}
    {}

    _iterator_indexes& operator=(const _iterator_indexes& other)
    {
      data = other.data;
      time = other.time;
      increment = other.increment;
      return *this;
    }

    friend void swap(_iterator_indexes& lhs, _iterator_indexes& rhs)
    {
      std::swap(lhs.data, rhs.data);
      std::swap(lhs.time, rhs.time);
      std::swap(lhs.increment, rhs.increment);
    }

    void next(int offset)
    {
      this->data += offset * increment;
      if constexpr(iterTime) { this->time += offset; }
    }

    void prev(int offset) { next(-offset); }

    bool equals(const _iterator_indexes& other) const
    {
      return data == other.data and time == other.time and
             increment == other.increment;
    }

    bool gt(const _iterator_indexes& other) const { return data > other.data; }

    std::size_t distance(const _iterator_indexes& other) const
    {
      if constexpr(iterTime) { return time - other.time; }
      return data - other.data;
    }

    inline auto v() const { return *data; }
    inline auto t() const { return *time; }
    inline auto& v() { return *data; }
    inline auto& t() { return *time; }

    inline auto v_ptr() const { return data; }
    inline auto t_ptr() const { return time; }
  };
} // namespace TimeSeries::details::iterators
#endif
