#include "seven_seg.h"

seven_seg seven_seg::operator++() {
 seven_seg r = *this;
 this->operator++();
 return r;
}

seven_seg& seven_seg::operator++(int) {
   switch(current) {
   case value::zero:
     current = value::one;
     break;
   case value::one:
     current = value::two;
     break;
   case value::two:
     current = value::three;
     break;  
   case value::three:
     current = value::four;
     break;
   case value::four:
     current = value::five;
     break;
   case value::five:
     current = value::six;
     break;  
   case value::six:
     current = value::seven;
     break;
   case value::seven:
     current = value::eight;
     break;
   case value::eight:
     current = value::nine;
     break; 
   case value::nine:
     current = value::zero;
     break;  
   }
   return *this;
}

seven_seg operator+(seven_seg l, int r) {
 l += r;
 return l;
}

seven_seg& seven_seg::operator+=(int inc) {
 for (int i = 0; i < inc; ++i) {
   ++(*this);  
 }
 return *this;
}
