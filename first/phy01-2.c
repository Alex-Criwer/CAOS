#include <stdio.h>
#include <inttypes.h>

const size_t LENGTH_OF_SIGN = 1;
const size_t LENGTH_OF_MANTISSA = 52;
const size_t LENGTH_OF_EXPONENT = 11;
const size_t FULL_LENGTH = 64;

typedef enum {
    PlusZero      = 0x00,
    MinusZero     = 0x01,
    PlusInf       = 0xF0,
    MinusInf      = 0xF1,
    PlusRegular   = 0x10,
    MinusRegular  = 0x11,
    PlusDenormal  = 0x20,
    MinusDenormal = 0x21,
    SignalingNaN  = 0x30,
    QuietNaN      = 0x31
} float_class_t;

typedef union {
    double realValue;
    uint64_t uintValue;
} reinterpretCastInC;

extern float_class_t
classify(double *value_ptr){
    reinterpretCastInC numberInBinary;
    numberInBinary.realValue = *value_ptr;
    uint64_t sign = (numberInBinary.uintValue >> (FULL_LENGTH - LENGTH_OF_SIGN));
    uint64_t exponent = ((numberInBinary.uintValue << (LENGTH_OF_SIGN)) >> (LENGTH_OF_MANTISSA + LENGTH_OF_SIGN));
    uint64_t mantissa = ((numberInBinary.uintValue << (LENGTH_OF_SIGN + LENGTH_OF_EXPONENT)) >>  (LENGTH_OF_SIGN + LENGTH_OF_EXPONENT));
    uint64_t temp = 0;
    uint64_t exponentFullOfOne = ((~temp) >> (LENGTH_OF_MANTISSA + LENGTH_OF_SIGN));

    if(sign == 0){
        if(exponent == 0 && mantissa == 0){
            return PlusZero;
        } else if (exponent == exponentFullOfOne && mantissa == 0){
            return PlusInf;
        } else if (exponent == exponentFullOfOne &&  mantissa != 0 && (mantissa >> (LENGTH_OF_MANTISSA - 1)) == 0){
            return SignalingNaN;
        } else if (exponent == exponentFullOfOne && mantissa != 0 && (mantissa >> (LENGTH_OF_MANTISSA - 1)) == 1){
            return QuietNaN;
        } else if (exponent == 0 && mantissa != 0){
            return PlusDenormal;
        } else {
            return PlusRegular;
        }
    } else {
        if (exponent == 0 && mantissa == 0){
            return MinusZero;
        } else if (exponent == exponentFullOfOne && mantissa == 0){
            return MinusInf;
        } else if (exponent == exponentFullOfOne &&  mantissa != 0 && (mantissa >> (LENGTH_OF_MANTISSA - 1)) == 0){
            return SignalingNaN;
        } else if (exponent == exponentFullOfOne && mantissa != 0 && (mantissa >> (LENGTH_OF_MANTISSA - 1)) == 1){
            return QuietNaN;
        } else if (exponent == 0 && mantissa != 0){
            return MinusDenormal;
        } else {
            return MinusRegular;
        }
    }
}