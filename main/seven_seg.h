class seven_seg {
public:
 enum value {
   zero =  0b1111110,
   one =   0b0110000,
   two =   0b1101101,
   three = 0b1111001,
   four =  0b0110011,
   five =  0b1011011,
   six =   0b1011111,
   seven = 0b1110000,
   eight = 0b1111111,
   nine =  0b1110011
 };
private:
 value current = value::zero;
public:
 seven_seg() = default;
 ~seven_seg() = default;

 seven_seg operator++();
 seven_seg& operator++(int);

 friend seven_seg operator+(seven_seg& l, int r);
 seven_seg& operator+=(int inc);
};
