#pragma once

#include <cstdint>

#if defined _MSC_VER || defined __BORLANDC__
typedef __int64 int64;
typedef unsigned __int64 uint64;
#  define CV_BIG_INT(n)   n##I64
#  define CV_BIG_UINT(n)  n##UI64
#else
typedef int64_t int64;
   typedef uint64_t uint64;
#  define CV_BIG_INT(n)   n##LL
#  define CV_BIG_UINT(n)  n##ULL
#endif
typedef union Cv32suf {
    int i;
    unsigned u;
    float f;
} Cv32suf;
typedef union Cv64suf {
    int64_t i;
    uint64_t u;
    double f;
} Cv64suf;
struct softdouble;

struct softfloat {
public:
    /** @brief Default constructor */
    softfloat() { v = 0; }

    /** @brief Copy constructor */
    softfloat(const softfloat &c) { v = c.v; }

    /** @brief Assign constructor */
    softfloat &operator=(const softfloat &c) {
        if (&c != this) v = c.v;
        return *this;
    }

    /** @brief Construct from raw

    Builds new value from raw binary representation
    */
    static const softfloat fromRaw(const uint32_t a) {
        softfloat x;
        x.v = a;
        return x;
    }

    /** @brief Construct from integer */
    explicit softfloat(const uint32_t);

    explicit softfloat(const uint64_t);

    explicit softfloat(const int32_t);

    explicit softfloat(const int64_t);

#ifdef CV_INT32_T_IS_LONG_INT
    // for platforms with int32_t = long int
explicit softfloat( const int a ) { *this = softfloat(static_cast<int32_t>(a)); }
#endif

    /** @brief Construct from float */
    explicit softfloat(const float a) {
        Cv32suf s;
        s.f = a;
        v = s.u;
    }

    /** @brief Type casts  */
    operator softdouble() const;

    operator float() const {
        Cv32suf s;
        s.u = v;
        return s.f;
    }

    /** @brief Basic arithmetics */
    softfloat operator+(const softfloat &) const;

    softfloat operator-(const softfloat &) const;

    softfloat operator*(const softfloat &) const;

    softfloat operator/(const softfloat &) const;

    softfloat operator-() const {
        softfloat x;
        x.v = v ^ (1U << 31);
        return x;
    }

    /** @brief Remainder operator

    A quote from original SoftFloat manual:

    > The IEEE Standard remainder operation computes the value
    > a - n * b, where n is the integer closest to a / b.
    > If a / b is exactly halfway between two integers, n is the even integer
    > closest to a / b. The IEEE Standard’s remainder operation is always exact and so requires no rounding.
    > Depending on the relative magnitudes of the operands, the remainder functions
    > can take considerably longer to execute than the other SoftFloat functions.
    > This is an inherent characteristic of the remainder operation itself and is not a flaw
    > in the SoftFloat implementation.
    */
    softfloat operator%(const softfloat &) const;

    softfloat &operator+=(const softfloat &a) {
        *this = *this + a;
        return *this;
    }

    softfloat &operator-=(const softfloat &a) {
        *this = *this - a;
        return *this;
    }

    softfloat &operator*=(const softfloat &a) {
        *this = *this * a;
        return *this;
    }

    softfloat &operator/=(const softfloat &a) {
        *this = *this / a;
        return *this;
    }

    softfloat &operator%=(const softfloat &a) {
        *this = *this % a;
        return *this;
    }

    /** @brief Comparison operations

     - Any operation with NaN produces false
       + The only exception is when x is NaN: x != y for any y.
     - Positive and negative zeros are equal
    */
    bool operator==(const softfloat &) const;

    bool operator!=(const softfloat &) const;

    bool operator>(const softfloat &) const;

    bool operator>=(const softfloat &) const;

    bool operator<(const softfloat &) const;

    bool operator<=(const softfloat &) const;

    /** @brief NaN state indicator */
    inline bool isNaN() const { return (v & 0x7fffffff) > 0x7f800000; }

    /** @brief Inf state indicator */
    inline bool isInf() const { return (v & 0x7fffffff) == 0x7f800000; }

    /** @brief Subnormal number indicator */
    inline bool isSubnormal() const { return ((v >> 23) & 0xFF) == 0; }

    /** @brief Get sign bit */
    inline bool getSign() const { return (v >> 31) != 0; }

    /** @brief Construct a copy with new sign bit */
    inline softfloat setSign(bool sign) const {
        softfloat x;
        x.v = (v & ((1U << 31) - 1)) | ((uint32_t) sign << 31);
        return x;
    }

    /** @brief Get 0-based exponent */
    inline int getExp() const { return ((v >> 23) & 0xFF) - 127; }

    /** @brief Construct a copy with new 0-based exponent */
    inline softfloat setExp(int e) const {
        softfloat x;
        x.v = (v & 0x807fffff) | (((e + 127) & 0xFF) << 23);
        return x;
    }

    /** @brief Get a fraction part

    Returns a number 1 <= x < 2 with the same significand
    */
    inline softfloat getFrac() const {
        uint_fast32_t vv = (v & 0x007fffff) | (127 << 23);
        return softfloat::fromRaw(vv);
    }

    /** @brief Construct a copy with provided significand

    Constructs a copy of a number with significand taken from parameter
    */
    inline softfloat setFrac(const softfloat &s) const {
        softfloat x;
        x.v = (v & 0xff800000) | (s.v & 0x007fffff);
        return x;
    }

    /** @brief Zero constant */
    static softfloat zero() { return softfloat::fromRaw(0); }

    /** @brief Positive infinity constant */
    static softfloat inf() { return softfloat::fromRaw(0xFF << 23); }

    /** @brief Default NaN constant */
    static softfloat nan() { return softfloat::fromRaw(0x7fffffff); }

    /** @brief One constant */
    static softfloat one() { return softfloat::fromRaw(127 << 23); }

    /** @brief Smallest normalized value */
    static softfloat min() { return softfloat::fromRaw(0x01 << 23); }

    /** @brief Difference between 1 and next representable value */
    static softfloat eps() { return softfloat::fromRaw((127 - 23) << 23); }

    /** @brief Biggest finite value */
    static softfloat max() { return softfloat::fromRaw((0xFF << 23) - 1); }

    /** @brief Correct pi approximation */
    static softfloat pi() { return softfloat::fromRaw(0x40490fdb); }

    uint32_t v;
};

struct softdouble {
public:
    /** @brief Default constructor */
    softdouble() : v(0) {}

    /** @brief Copy constructor */
    softdouble(const softdouble &c) { v = c.v; }

    /** @brief Assign constructor */
    softdouble &operator=(const softdouble &c) {
        if (&c != this) v = c.v;
        return *this;
    }

    /** @brief Construct from raw

    Builds new value from raw binary representation
    */
    static softdouble fromRaw(const uint64_t a) {
        softdouble x;
        x.v = a;
        return x;
    }

    /** @brief Construct from integer */
    explicit softdouble(const uint32_t);

    explicit softdouble(const uint64_t);

    explicit softdouble(const int32_t);

    explicit softdouble(const int64_t);

#ifdef CV_INT32_T_IS_LONG_INT
    // for platforms with int32_t = long int
explicit softdouble( const int a ) { *this = softdouble(static_cast<int32_t>(a)); }
#endif

    /** @brief Construct from double */
    explicit softdouble(const double a) {
        Cv64suf s;
        s.f = a;
        v = s.u;
    }

    /** @brief Type casts  */
    operator softfloat() const;

    operator double() const {
        Cv64suf s;
        s.u = v;
        return s.f;
    }

    /** @brief Basic arithmetics */
    softdouble operator+(const softdouble &) const;

    softdouble operator-(const softdouble &) const;

    softdouble operator*(const softdouble &) const;

    softdouble operator/(const softdouble &) const;

    softdouble operator-() const {
        softdouble x;
        x.v = v ^ (1ULL << 63);
        return x;
    }

    /** @brief Remainder operator

    A quote from original SoftFloat manual:

    > The IEEE Standard remainder operation computes the value
    > a - n * b, where n is the integer closest to a / b.
    > If a / b is exactly halfway between two integers, n is the even integer
    > closest to a / b. The IEEE Standard’s remainder operation is always exact and so requires no rounding.
    > Depending on the relative magnitudes of the operands, the remainder functions
    > can take considerably longer to execute than the other SoftFloat functions.
    > This is an inherent characteristic of the remainder operation itself and is not a flaw
    > in the SoftFloat implementation.
    */
    softdouble operator%(const softdouble &) const;

    softdouble &operator+=(const softdouble &a) {
        *this = *this + a;
        return *this;
    }

    softdouble &operator-=(const softdouble &a) {
        *this = *this - a;
        return *this;
    }

    softdouble &operator*=(const softdouble &a) {
        *this = *this * a;
        return *this;
    }

    softdouble &operator/=(const softdouble &a) {
        *this = *this / a;
        return *this;
    }

    softdouble &operator%=(const softdouble &a) {
        *this = *this % a;
        return *this;
    }

    /** @brief Comparison operations

     - Any operation with NaN produces false
       + The only exception is when x is NaN: x != y for any y.
     - Positive and negative zeros are equal
    */
    bool operator==(const softdouble &) const;

    bool operator!=(const softdouble &) const;

    bool operator>(const softdouble &) const;

    bool operator>=(const softdouble &) const;

    bool operator<(const softdouble &) const;

    bool operator<=(const softdouble &) const;

    /** @brief NaN state indicator */
    inline bool isNaN() const { return (v & 0x7fffffffffffffff) > 0x7ff0000000000000; }

    /** @brief Inf state indicator */
    inline bool isInf() const { return (v & 0x7fffffffffffffff) == 0x7ff0000000000000; }

    /** @brief Subnormal number indicator */
    inline bool isSubnormal() const { return ((v >> 52) & 0x7FF) == 0; }

    /** @brief Get sign bit */
    inline bool getSign() const { return (v >> 63) != 0; }

    /** @brief Construct a copy with new sign bit */
    softdouble setSign(bool sign) const {
        softdouble x;
        x.v = (v & ((1ULL << 63) - 1)) | ((uint_fast64_t) (sign) << 63);
        return x;
    }

    /** @brief Get 0-based exponent */
    inline int getExp() const { return ((v >> 52) & 0x7FF) - 1023; }

    /** @brief Construct a copy with new 0-based exponent */
    inline softdouble setExp(int e) const {
        softdouble x;
        x.v = (v & 0x800FFFFFFFFFFFFF) | ((uint_fast64_t) ((e + 1023) & 0x7FF) << 52);
        return x;
    }

    /** @brief Get a fraction part

    Returns a number 1 <= x < 2 with the same significand
    */
    inline softdouble getFrac() const {
        uint_fast64_t vv = (v & 0x000FFFFFFFFFFFFF) | ((uint_fast64_t) (1023) << 52);
        return softdouble::fromRaw(vv);
    }

    /** @brief Construct a copy with provided significand

    Constructs a copy of a number with significand taken from parameter
    */
    inline softdouble setFrac(const softdouble &s) const {
        softdouble x;
        x.v = (v & 0xFFF0000000000000) | (s.v & 0x000FFFFFFFFFFFFF);
        return x;
    }

    /** @brief Zero constant */
    static softdouble zero() { return softdouble::fromRaw(0); }

    /** @brief Positive infinity constant */
    static softdouble inf() { return softdouble::fromRaw((uint_fast64_t) (0x7FF) << 52); }

    /** @brief Default NaN constant */
    static softdouble nan() { return softdouble::fromRaw(CV_BIG_INT(0x7FFFFFFFFFFFFFFF)); }

    /** @brief One constant */
    static softdouble one() { return softdouble::fromRaw((uint_fast64_t) (1023) << 52); }

    /** @brief Smallest normalized value */
    static softdouble min() { return softdouble::fromRaw((uint_fast64_t) (0x01) << 52); }

    /** @brief Difference between 1 and next representable value */
    static softdouble eps() { return softdouble::fromRaw((uint_fast64_t) (1023 - 52) << 52); }

    /** @brief Biggest finite value */
    static softdouble max() { return softdouble::fromRaw(((uint_fast64_t) (0x7FF) << 52) - 1); }

    /** @brief Correct pi approximation */
    static softdouble pi() { return softdouble::fromRaw(CV_BIG_INT(0x400921FB54442D18)); }

    uint64_t v;
};
