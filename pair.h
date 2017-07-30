/* START OF "pair.h" FILE */

#pragma once
#ifndef _PAIR_H
#define _PAIR_H

template <typename KEY_TYPE, typename VALUE_TYPE>
struct PAIR {
   PAIR(void);
   PAIR(const PAIR &) = default;
   PAIR(const KEY_TYPE & key, const VALUE_TYPE & value);

   ~PAIR() {}

   PAIR & operator= (const PAIR & right)
   {
      first = right.first;
      second = right.second;
      return *this;
   }

   void Swap(PAIR & right);

   KEY_TYPE first;
   VALUE_TYPE second;
};


template <typename KEY_TYPE, typename VALUE_TYPE>
PAIR<KEY_TYPE, VALUE_TYPE>::PAIR (void) :
   first(), second()
{
}

template <typename KEY_TYPE, typename VALUE_TYPE>
PAIR<KEY_TYPE, VALUE_TYPE>::PAIR (const KEY_TYPE & key, const VALUE_TYPE & value) :
   first(key), second(value)
{
}

template <typename KEY_TYPE, typename VALUE_TYPE>
void PAIR<KEY_TYPE, VALUE_TYPE>::Swap (PAIR & right)
{
   if (this != &right) {
      Swap(&first, &right.first, sizeof(KEY_TYPE));
      Swap(&second, &right.second, sizeof(VALUE_TYPE));
   }
}

template <typename KEY_TYPE, typename VALUE_TYPE>
inline bool operator== (const PAIR<KEY_TYPE, VALUE_TYPE> & left,
   const PAIR<KEY_TYPE, VALUE_TYPE> & right)
{
   return (left.first == right.first && left.second == right.second);
}

template <typename KEY_TYPE, typename VALUE_TYPE>
inline bool operator!= (const PAIR<KEY_TYPE, VALUE_TYPE> & left,
   const PAIR<KEY_TYPE, VALUE_TYPE> & right)
{
   return !(left == right);
}

template <typename KEY_TYPE, typename VALUE_TYPE>
inline bool operator< (const PAIR<KEY_TYPE, VALUE_TYPE> & left,
   const PAIR<KEY_TYPE, VALUE_TYPE> & right)
{
   return (left.first < right.first ||
      (right.first == left.first && left.second < right.second));
}

template <typename KEY_TYPE, typename VALUE_TYPE>
inline bool operator> (const PAIR<KEY_TYPE, VALUE_TYPE> & left,
   const PAIR<KEY_TYPE, VALUE_TYPE> & right)
{
   return (right < left);
}

template <typename KEY_TYPE, typename VALUE_TYPE>
inline bool operator<= (const PAIR<KEY_TYPE, VALUE_TYPE> & left,
   const PAIR<KEY_TYPE, VALUE_TYPE> & right)
{
   return (!(right < left));
}

template <typename KEY_TYPE, typename VALUE_TYPE>
inline bool operator>=(const PAIR<KEY_TYPE, VALUE_TYPE>& left,
   const PAIR<KEY_TYPE, VALUE_TYPE>& right)
{
   return (!(left < right));
}


void Swap (void * a, void * b, size_t Size);

#endif // _PAIR_H

/* END OF "pair.h" FILE */
