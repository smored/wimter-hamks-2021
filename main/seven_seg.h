#pragma once

#include <Arduino.h>

class seven_seg {
public:
    static constexpr int a = 0b0100000;
    static constexpr int b = 0b1000000;
    static constexpr int c = 0b0000100;
    static constexpr int d = 0b0001000;
    static constexpr int e = 0b0010000;
    static constexpr int f = 0b0000001;
    static constexpr int g = 0b0000010;
    enum value {
        zero = a | b | c | d | e | f,
        one = b | c,
        two = a | b | g | e | d,
        three = a | b | g | c | d,
        four = f | g | b | c,
        five = a | f | g | c | d,
        six = a | f | g | e | c | d,
        seven = a | b | c,
        eight = a | b | c | d | e | f | g,
        nine = a | f | b | g | c
    };

private:
    static constexpr int NUM_PINS = 7;
    const int FIRST_PIN;
    value current = value::zero;

public:
    seven_seg(int firstPin) : FIRST_PIN(firstPin) {
        for (int i = 0; i < NUM_PINS; ++i) {
            pinMode(i + FIRST_PIN, OUTPUT);
        }
    };
    ~seven_seg() = default;

    seven_seg operator++();
    seven_seg &operator++(int);

    friend seven_seg operator+(seven_seg &l, int r);
    seven_seg &operator+=(int inc);

    seven_seg &operator=(int val);

    /**
   * assumes that all pins from FIRST_PIN to FIRST_PIN + 7 are used for the seven segment display.
   * BCD is for losers.
   */
    void light();
};
