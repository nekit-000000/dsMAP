/* START OF "pair.h" FILE */

#ifndef _PAIR_H_INCLUDED
#define _PAIR_H_INCLUDED
#pragma once

template <typename KeyType, typename ValueType>
struct PAIR
{
  KeyType first;
  ValueType second;

  PAIR (void);
  PAIR (const PAIR &) = default;
  PAIR (const KeyType & key, const ValueType & value);

  ~PAIR() {}

  PAIR & operator= (const PAIR & right)
  {
    first = right.first;
    second = right.second;
    return *this;
  }

  void swap (PAIR & right);
};

template <typename KeyType, typename ValueType>
PAIR<KeyType, ValueType>::PAIR (void) :
  first(), second()
{
}

template <typename KeyType, typename ValueType>
PAIR<KeyType, ValueType>::PAIR (const KeyType & key, const ValueType & value) :
  first(key), second(value)
{
}

template <typename KeyType, typename ValueType>
void PAIR<KeyType, ValueType>::swap (PAIR & right)
{
  if (this != &right) {
    Swap(&first, &right.first, sizeof(KeyType));
    Swap(&second, &right.second, sizeof(ValueType));
  }
}

template <typename KeyType, typename ValueType>
inline bool operator== (const PAIR<KeyType, ValueType> & left,
  const PAIR<KeyType, ValueType> & right)
{
  return (left.first == right.first && left.second == right.second);
}

template <typename KeyType, typename ValueType>
inline bool operator!= (const PAIR<KeyType, ValueType> & left,
  const PAIR<KeyType, ValueType> & right)
{
  return !(left == right);
}

template <typename KeyType, typename ValueType>
inline bool operator< (const PAIR<KeyType, ValueType> & left,
  const PAIR<KeyType, ValueType> & right)
{
  return (left.first < right.first ||
    (right.first == left.first && left.second < right.second));
}

template <typename KeyType, typename ValueType>
inline bool operator> (const PAIR<KeyType, ValueType> & left,
  const PAIR<KeyType, ValueType> & right)
{
  return (right < left);
}

template <typename KeyType, typename ValueType>
inline bool operator<= (const PAIR<KeyType, ValueType> & left,
  const PAIR<KeyType, ValueType> & right)
{
  return (!(right < left));
}

template <typename KeyType, typename ValueType>
inline bool operator>=(const PAIR<KeyType, ValueType>& left,
  const PAIR<KeyType, ValueType>& right)
{
  return (!(left < right));
}

void Swap (void * a, void * b, size_t size);

#endif // _PAIR_H_INCLUDED

/* END OF "pair.h" FILE */
