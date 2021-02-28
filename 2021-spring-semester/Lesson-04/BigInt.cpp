#include <iostream>
#include <string>

using namespace std;

class BigInt {
    int length;
    char* digits;

public:
    explicit BigInt(const string& str)
        : length(str.length())
        , digits(nullptr)
    {
        cout << "BigInt constructed with string: " << str << endl;
        if (length == 0)
            return;
        digits = new char[length];
        for (int i = 0; i < length; ++i)
            digits[i] = str[length - 1 - i];
    }

    explicit BigInt(const char* str)
        : BigInt(string(str))
    {
    }

    friend ostream& operator<<(ostream& o, const BigInt& b)
    {
        for (int i = b.length - 1; i >= 0; --i)
            o << b.digits[i];
        return o;
    }

    ~BigInt() {
        cout << "BigInt destructed: " << *this << endl;
        delete[] digits;
    }

    BigInt(const BigInt& other)
        : length(other.length)
        , digits(other.length ? new char[length] : nullptr)
    {
        for (int i = 0; i < length; ++i)
            digits[i] = other.digits[i];
        cout << "BigInt copy constructed: " << *this << endl;
    }

    BigInt& operator=(const BigInt& other) {
        if (&other == this)
            return *this;
        if (length != other.length) {
            length = other.length;
            delete[] digits;
            digits = new char[length];
        }
        for (int i = 0; i < length; ++i)
            digits[i] = other.digits[i];
        return *this;
    }

    BigInt& operator+=(const BigInt& other)
    {
        if (length < other.length) {
            char* bigger = new char[other.length];
            for (int i = 0; i < other.length; ++i)
                bigger[i] = i < length ? digits[i] : '0';
            delete[] digits;
            digits = bigger;
            length = other.length;
        }
        int carry = 0;
        for (int i = 0; i < other.length; ++i) {
            int sum = digits[i] - '0' + other.digits[i] - '0' + carry;
            digits[i] = sum % 10 + '0';
            carry = sum / 10;
        }
        for (int i = other.length; carry && i < length; ++i) {
            int sum = digits[i] - '0' + carry;
            digits[i] = sum % 10 + '0';
            carry = sum / 10;
        }
        if (carry) {
            char* bigger = new char[length + 1];
            for (int i = 0; i < length; ++i)
                bigger[i] = digits[i];
            delete[] digits;
            digits = bigger;
            digits[length++] = carry + '0';
        }
        return *this;
    }

    BigInt operator+(const BigInt& other) const
    {
        BigInt result = *this;
        result += other;
        return result;
    }

    BigInt(BigInt&& other) noexcept
        : length(other.length)
        , digits(other.digits)
    {
        cout << "BigInt move constructed: " << *this << endl;
        other.digits = nullptr;
        other.length = 0;
    }

    BigInt& operator=(BigInt&& other) noexcept
    {
        length = other.length;
        digits = other.digits;
        other.digits = nullptr;
        other.length = 0;
        cout << "BigInt move assignment: " << *this << endl;
        return *this;
    }

    operator bool() const {
        return length > 0;
    }
};

#include <vector>


int main() {
    BigInt a("1");

    BigInt b(string("2"));
    
    BigInt c {"3"};

    vector<BigInt> v;
    v.push_back(a);
    v.push_back(b);
    v.push_back(c);

    // explicit constructor forbids this:
    //cout << a + "5" << endl;
}
