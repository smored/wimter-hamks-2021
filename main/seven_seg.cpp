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

seven_seg& seven_seg::operator=(int val) {
  switch(val) {
    case 0:
      current = value::zero;
      break; 
    case 1:
      current = value::one;
      break;
    case 2:
      current = value::two;
      break;
    case 3:
      current = value::three;
      break;  
    case 4:
      current = value::four;
      break;
    case 5:
      current = value::five;
      break;
    case 6:
      current = value::six;
      break;  
    case 7:
      current = value::seven;
      break;
    case 8:
      current = value::eight;
      break;
    case 9:
      current = value::nine;
      break; 
  }
  return *this;
}

void seven_seg::light() {
  for (int i = 0; i < NUM_PINS; ++i) {
    digitalWrite(i + FIRST_PIN, (current >> i) & 1 ? LOW : HIGH);
  }
}
