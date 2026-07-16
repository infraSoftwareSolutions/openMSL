#pragma once
#ifndef OPENMSL___MSL___dLd_HPP
#define OPENMSL___MSL___dLd_HPP
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "cfrost/structure.h"

/**
 * @file logic.hpp
 * @brief This header file defines classes for handling data sizes and numeral system conversions.
 * This header file defines classes for handling data sizes and conversions between different numeral systems (decimal, hexadecimal, octal, binary). The `data` class provides methods for converting between various data size units (bits, nibbles, bytes, words, kilobytes, megabytes, gigabytes, terabytes). The `decimal`, `hexadecimal`, `octal`, and `binary` classes provide functionality for representing and converting between these numeral systems. Each class includes constructors, assignment operators, and methods for performing conversions and displaying information about the data or numeral system. The code also includes error handling for invalid inputs.
 * @author Ali Lafi
 * @date 2024-06-01
 */


namespace msl
{
    class hexadecimal;
    class octal;
    class binary;
    class data
    {
    private:
        double dataSize;
        str dataType;

    public:
        data() noexcept : dataSize(0), dataType("bits") {}
        data(double d) noexcept : dataSize(d) {}
        data(const str &dt) noexcept : dataType(dt) {}
        data(const data &other) noexcept : dataSize(other.dataSize), dataType(other.dataType) {}
        data(double d, const str &dt) noexcept : dataSize(d), dataType(dt) {}
        
        void set_values(double d, const str &dt) noexcept
        {
            dataSize = d;
            dataType = dt;
        }
        
        void data_dictionary(char ch = '?') noexcept
        {
            std::cout << "1-Bit = 0 OR 1" << newl;
            std::cout << "1-Nibble = 4-Bits" << newl;
            std::cout << "1-Byte = 8-Bits = 2-Nibble" << newl;
            std::cout << "1-word = 2-Byte = 4-Nibble = 16-Bits" << newl;
            std::cout << "1-killo = 2^10" << newl;
            std::cout << "1-Mega = 2^20" << newl;
            std::cout << "1-Giga = 2^30" << newl;
            std::cout << "1-Tira = 2^40" << newl;
        }
        
        double to_bits(double amountOfdat = 1, const str& condat = "nibble")
        {
            if (condat == "nibble")
                return (amountOfdat * 4);
            else if (condat == "byte")
                return (amountOfdat * 8);
            else if (condat == "word")
                return (amountOfdat * 16);
            else if (condat == "killo")
                return (amountOfdat * pow(2, 10));
            else if (condat == "mega")
                return (amountOfdat * pow(2, 20));
            else if (condat == "giga")
                return (amountOfdat * pow(2, 30));
            else if (condat == "Tira")
                return (amountOfdat * pow(2, 40));
            else
                throw std::invalid_argument("wrong data choosing");
        }
        
        double to_nibbles(double amountOfdat = 1, const str& condat = "byte")
        {
            if (condat == "bits")
                return (amountOfdat / 4);
            else if (condat == "byte")
                return (amountOfdat * 2);
            else if (condat == "word")
                return (amountOfdat * 4);
            else if (condat == "killo")
                return (amountOfdat * pow(2, 8));
            else if (condat == "mega")
                return (amountOfdat * pow(2, 18));
            else if (condat == "giga")
                return (amountOfdat * pow(2, 28));
            else if (condat == "Tira")
                return (amountOfdat * pow(2, 38));
            else
                throw std::invalid_argument("wrong data choosing");
        }

        double to_bytes(double amountOfdat = 1, const str& condat = "word")
        {
            if (condat == "bits")
                return (amountOfdat / 8);
            else if (condat == "nibble")
                return (amountOfdat / 2);
            else if (condat == "word")
                return (amountOfdat * 2);
            else if (condat == "killo")
                return (amountOfdat * pow(2, 7));
            else if (condat == "mega")
                return (amountOfdat * pow(2, 17));
            else if (condat == "giga")
                return (amountOfdat * pow(2, 27));
            else if (condat == "Tira")
                return (amountOfdat * pow(2, 37));
            else
                throw std::invalid_argument("wrong data choosing");
        }
        
        double to_word(double amountOfdat = 1, const str& condat = "killo")
        {
            if (condat == "bits")
                return (amountOfdat / 16);
            else if (condat == "nibble")
                return (amountOfdat / 4);
            else if (condat == "byte")
                return (amountOfdat / 2);
            else if (condat == "killo")
                return (amountOfdat * pow(2, 6));
            else if (condat == "mega")
                return (amountOfdat * pow(2, 16));
            else if (condat == "giga")
                return (amountOfdat * pow(2, 26));
            else if (condat == "Tira")
                return (amountOfdat * pow(2, 36));
            else
                throw std::invalid_argument("wrong data choosing");
        }

        double to_killo(double amountOfdat = 1, const str& condat = "mega")
        {
            if (condat == "bits")
                return (amountOfdat / pow(2, 10));
            else if (condat == "nibble")
                return (amountOfdat / pow(2, 8));
            else if (condat == "byte")
                return (amountOfdat / pow(2, 7));
            else if (condat == "word")
                return (amountOfdat / pow(2, 6));
            else if (condat == "mega")
                return (amountOfdat * pow(2, 10));
            else if (condat == "giga")
                return (amountOfdat * pow(2, 20));
            else if (condat == "Tira")
                return (amountOfdat * pow(2, 30));
            else
                throw std::invalid_argument("wrong data choosing");
        }

        double to_mega(float amountOfdat = 1, const str& condat = "giga")
        {
            if (condat == "bits")
                return (amountOfdat / pow(2, 20));
            else if (condat == "nibble")
                return (amountOfdat / pow(2, 18));
            else if (condat == "byte")
                return (amountOfdat / pow(2, 17));
            else if (condat == "word")
                return (amountOfdat / pow(2, 16));
            else if (condat == "killo")
                return (amountOfdat / pow(2, 10));
            else if (condat == "giga")
                return (amountOfdat * pow(2, 10));
            else if (condat == "Tira")
                return (amountOfdat * pow(2, 20));
            else
                throw std::invalid_argument("wrong data choosing");
        }

        double to_giga(double amountOfdat = 1, const str& condat = "Tira")
        {
            if (condat == "bits")
                return (amountOfdat / pow(2, 30));
            else if (condat == "nibble")
                return (amountOfdat / pow(2, 28));
            else if (condat == "byte")
                return (amountOfdat / pow(2, 27));
            else if (condat == "word")
                return (amountOfdat / pow(2, 26));
            else if (condat == "killo")
                return (amountOfdat / pow(2, 20));
            else if (condat == "mega")
                return (amountOfdat / pow(2, 10));
            else if (condat == "Tira")
                return (amountOfdat * pow(2, 10));
            else
                throw std::invalid_argument("wrong data choosing");
        }

        double to_tira(double amountOfdat = 1, const str& condat = "giga")
        {
            if (condat == "bits")
                return (amountOfdat / pow(2, 40));
            else if (condat == "nibble")
                return (amountOfdat / pow(2, 38));
            else if (condat == "byte")
                return (amountOfdat / pow(2, 37));
            else if (condat == "word")
                return (amountOfdat / pow(2, 36));
            else if (condat == "killo")
                return (amountOfdat / pow(2, 30));
            else if (condat == "mega")
                return (amountOfdat / pow(2, 20));
            else if (condat == "giga")
                return (amountOfdat / pow(2, 10));
            else
                throw std::invalid_argument("wrong data choosing");
        }

        procedure(clear) noexcept
        {
            dataSize = 0;
            dataType = "bits";
        }
        
        procedure(display) const
        {
            std::cout << "data Size: "
                      << dataSize << " "
                      << dataType << newl;
        }
        
        void operator=(const data &other) noexcept
        {
            dataSize = other.dataSize;
            dataType = other.dataType;
        }
        
        void operator=(double d) noexcept { dataSize = d; }
        
        void operator=(const str &dt) noexcept { dataType = dt; }
        
        bool operator==(double d) noexcept { return dataSize == d; }
        
        bool operator==(const str &dt) noexcept { return dataType == dt; }
        
        bool operator!=(double d) noexcept { return dataSize != d; }
        
        bool operator!=(const str &dt) { return dataType != dt; }
        
        void operator+=(double d) noexcept { dataSize += d; }
        
        void operator-=(double d) noexcept { dataSize -= d; }
        
        void operator*=(double d) noexcept { dataSize *= d; }
        
        void operator/=(double d) noexcept { dataSize /= d; }
        
        ~data() = default;
    };

    class decimal
    {
    private:
        long double decNum;

    public:
        decimal() : decNum(0) {}
        
        decimal(long double num) noexcept : decNum(num) {}
        
        decimal(const decimal &other) noexcept : decNum(other.decNum) {}
        
        decimal(const hexadecimal &hex)
        {
            str snum = hex.get();
            float cov = 0;
            float base = 1;
            bool isFraction = false;
            bool isNegative = false;
            float fractionBase = 1.0 / 16;
            size_t startIndex = 0;
            if (!snum.empty() && snum[0] == '-')
            {
                isNegative = true;
                startIndex = 1;
            }
            for (int i = snum.length() - 1; i >= static_cast<int>(startIndex); i--)
            {
                if (snum[i] == '.')
                {
                    isFraction = true;
                    continue;
                }
                int value;
                if (snum[i] >= '0' && snum[i] <= '9')
                    value = snum[i] - '0';
                else if (snum[i] >= 'A' && snum[i] <= 'F')
                    value = snum[i] - 'A' + 10;
                else if (snum[i] >= 'a' && snum[i] <= 'f')
                    value = snum[i] - 'a' + 10;
                else
                    throw std::invalid_argument("Not valid character: " + str(1, snum[i]));
                if (isFraction)
                {
                    cov += value * fractionBase;
                    fractionBase /= 16;
                }
                else
                {
                    cov += value * base;
                    base *= 16;
                }
            }
            if (isNegative)
                cov *= -1;
            decNum = cov;
        }
        
        decimal(const octal &oct)
        {
            str octStr = oct.get(); // Assuming octal class has a get() method
            size_t dotPos = octStr.find('.');
            str intPartStr = (dotPos == str::npos) ? octStr : octStr.substr(0, dotPos);
            str fracPartStr = (dotPos == str::npos) ? "" : octStr.substr(dotPos + 1);
            // Convert integer part
            float cov = 0.0;
            int base = 1;
            for (int i = intPartStr.length() - 1; i >= 0; --i)
            {
                char ch = intPartStr[i];
                if (ch < '0' || ch > '7')
                {
                    std::cout << "Invalid digit in integer part: " << ch << newl;
                    throw std::invalid_argument("Invalid octal digit in integer part");
                }
                int lastdigit = ch - '0';
                cov += lastdigit * base;
                base *= 8;
            }
            // Convert fractional part
            float frac = 0.0;
            float fracBase = 1.0f / 8.0f;
            for (size_t i = 0; i < fracPartStr.length(); ++i)
            {
                char ch = fracPartStr[i];
                if (ch < '0' || ch > '7')
                {
                    std::cout << "Invalid digit in fractional part: " << ch << newl;
                    throw std::invalid_argument("Invalid octal digit in fractional part");
                }
                int digit = ch - '0';
                frac += digit * fracBase;
                fracBase /= 8.0f;
            }
            decNum = cov + frac;
        }
        
        decimal(const binary &bin)
        {
            // Assume binary class has a method get() that returns the binary string
            str binStr = bin.get(); // You may need to implement get() in binary
            size_t dotPos = binStr.find('.');
            str intPartStr = (dotPos == str::npos) ? binStr : binStr.substr(0, dotPos);
            str fracPartStr = (dotPos == str::npos) ? "" : binStr.substr(dotPos + 1);
            // Convert integer part
            float integerPart = 0;
            int base = 1;
            for (int i = intPartStr.length() - 1; i >= 0; --i)
            {
                char ch = intPartStr[i];
                if (ch != '0' && ch != '1')
                {
                    std::cout << "Invalid binary digit: " << ch << newl;
                    throw std::invalid_argument("Invalid binary input");
                }
                int lastdigit = ch - '0';
                integerPart += lastdigit * base;
                base *= 2;
            }
            // Convert fractional part
            float fractionalPart = 0.0;
            float fracBase = 0.5f;
            for (size_t i = 0; i < fracPartStr.length(); ++i)
            {
                char ch = fracPartStr[i];
                if (ch != '0' && ch != '1')
                {
                    std::cout << "Invalid fractional digit: " << ch << newl;
                    throw std::invalid_argument("Invalid binary input");
                }
                int digit = ch - '0';
                fractionalPart += digit * fracBase;
                fracBase /= 2.0f;
            }
            decNum = integerPart + fractionalPart;
        }
        
        void set(long double num) { decNum = num; }
        
        long double get() const noexcept { return decNum; }
        
        void base(char ch)
        {
            if (ch == '?' || ch == '!')
                std::cout << "The base is 10" << newl;
        }
        
        void operator=(const hexadecimal &hex)
        {
            str snum = hex.get();
            float cov = 0;
            float base = 1;
            bool isFraction = false;
            bool isNegative = false;
            float fractionBase = 1.0 / 16;
            size_t startIndex = 0;
            if (!snum.empty() && snum[0] == '-')
            {
                isNegative = true;
                startIndex = 1;
            }
            for (int i = snum.length() - 1; i >= static_cast<int>(startIndex); i--)
            {
                if (snum[i] == '.')
                {
                    isFraction = true;
                    continue;
                }
                int value;
                if (snum[i] >= '0' && snum[i] <= '9')
                    value = snum[i] - '0';
                else if (snum[i] >= 'A' && snum[i] <= 'F')
                    value = snum[i] - 'A' + 10;
                else if (snum[i] >= 'a' && snum[i] <= 'f')
                    value = snum[i] - 'a' + 10;
                else
                    throw std::invalid_argument("Not valid character: " + str(1, snum[i]));
                if (isFraction)
                {
                    cov += value * fractionBase;
                    fractionBase /= 16;
                }
                else
                {
                    cov += value * base;
                    base *= 16;
                }
            }
            if (isNegative)
                cov *= -1;
            decNum = cov;
        }
        
        void operator=(const octal &oct)
        {
            str octStr = oct.get(); // Assuming octal class has a get() method
            size_t dotPos = octStr.find('.');
            str intPartStr = (dotPos == str::npos) ? octStr : octStr.substr(0, dotPos);
            str fracPartStr = (dotPos == str::npos) ? "" : octStr.substr(dotPos + 1);
            // Convert integer part
            float cov = 0.0;
            int base = 1;
            for (int i = intPartStr.length() - 1; i >= 0; --i)
            {
                char ch = intPartStr[i];
                if (ch < '0' || ch > '7')
                {
                    std::cout << "Invalid digit in integer part: " << ch << newl;
                    throw std::invalid_argument("Invalid octal digit in integer part");
                }
                int lastdigit = ch - '0';
                cov += lastdigit * base;
                base *= 8;
            }
            // Convert fractional part
            float frac = 0.0;
            float fracBase = 1.0f / 8.0f;
            for (size_t i = 0; i < fracPartStr.length(); ++i)
            {
                char ch = fracPartStr[i];
                if (ch < '0' || ch > '7')
                {
                    std::cout << "Invalid digit in fractional part: " << ch << newl;
                    throw std::invalid_argument("Invalid octal digit in fractional part");
                }
                int digit = ch - '0';
                frac += digit * fracBase;
                fracBase /= 8.0f;
            }
            decNum = cov + frac;
        }
        
        void operator=(const binary &bin)
        {
            // Assume binary class has a method get() that returns the binary string
            str binStr = bin.get(); // You may need to implement get() in binary
            size_t dotPos = binStr.find('.');
            str intPartStr = (dotPos == str::npos) ? binStr : binStr.substr(0, dotPos);
            str fracPartStr = (dotPos == str::npos) ? "" : binStr.substr(dotPos + 1);
            // Convert integer part
            float integerPart = 0;
            int base = 1;
            for (int i = intPartStr.length() - 1; i >= 0; --i)
            {
                char ch = intPartStr[i];
                if (ch != '0' && ch != '1')
                {
                    std::cout << "Invalid binary digit: " << ch << newl;
                    throw std::invalid_argument("Invalid binary input");
                }
                int lastdigit = ch - '0';
                integerPart += lastdigit * base;
                base *= 2;
            }
            // Convert fractional part
            float fractionalPart = 0.0;
            float fracBase = 0.5f;
            for (size_t i = 0; i < fracPartStr.length(); ++i)
            {
                char ch = fracPartStr[i];
                if (ch != '0' && ch != '1')
                {
                    std::cout << "Invalid fractional digit: " << ch << newl;
                    throw std::invalid_argument("Invalid binary input");
                }
                int digit = ch - '0';
                fractionalPart += digit * fracBase;
                fracBase /= 2.0f;
            }
            decNum = integerPart + fractionalPart;
        }
        
        long double get() const { return decNum; }
        
        decimal &operator++()
        {
            ++decNum;
            return *this;
        }
        
        decimal &operator--()
        {
            --decNum;
            return *this;
        }
        
        const decimal &operator+(const decimal &other) noexcept { return decNum + other.decNum; }
        
        const decimal &operator-(const decimal &other) noexcept { return decNum - other.decNum; }
        
        const decimal &operator*(const decimal &other) noexcept { return decNum * other.decNum; }
        
        const decimal &operator/(const decimal &other) noexcept { return decNum / other.decNum; }
        
        const decimal &operator+(const hexadecimal &other) noexcept
        {
            decimal temp = other;
            return *this + temp;
        }
        
        const decimal &operator-(const hexadecimal &other) noexcept
        {
            decimal temp = other;
            return *this - temp;
        }
        
        const decimal &operator*(const hexadecimal &other) noexcept
        {
            decimal temp = other;
            return *this * temp;
        }
        
        const decimal &operator/(const hexadecimal &other) noexcept
        {
            decimal temp = other;
            return *this / temp;
        }
        
        const decimal &operator+(const octal &other) noexcept
        {
            decimal temp = other;
            return *this + temp;
        }
        
        const decimal &operator-(const octal &other) noexcept
        {
            decimal temp = other;
            return *this - temp;
        }
        
        const decimal &operator*(const octal &other) noexcept
        {
            decimal temp = other;
            return *this * temp;
        }
        
        const decimal &operator/(const octal &other) noexcept
        {
            decimal temp = other;
            return *this / temp;
        }
        
        const decimal &operator+(const binary &other) noexcept
        {
            decimal temp = other;
            return *this + temp;
        }
        
        const decimal &operator-(const binary &other) noexcept
        {
            decimal temp = other;
            return *this - temp;
        }
        
        const decimal &operator*(const binary &other) noexcept
        {
            decimal temp = other;
            return *this * temp;
        }
        
        const decimal &operator/(const binary &other) noexcept
        {
            decimal temp = other;
            return *this / temp;
        }
        
        void operator+=(const decimal &other) noexcept { decNum += other.decNum; }
        
        void operator-=(const decimal &other) noexcept { decNum -= other.decNum; }
        
        void operator*=(const decimal &other) noexcept { decNum *= other.decNum; }
        
        void operator/=(const decimal &other) noexcept { decNum /= other.decNum; }
        
        void operator+=(long double num) noexcept { decNum += num; }
        
        void operator-=(long double num) noexcept { decNum -= num; }
        
        void operator*=(long double num) noexcept { decNum *= num; }
        
        void operator/=(long double num)
        {
            if (num == 0)
                throw std::invalid_argument("division by zero");
            decNum /= num;
        }
        
        const decimal &operator+=(const hexadecimal &other) noexcept
        {
            decimal temp = other;
            *this += temp;
        }
        
        const decimal &operator-=(const hexadecimal &other) noexcept
        {
            decimal temp = other;
            *this -= temp;
        }
        
        const decimal &operator*=(const hexadecimal &other) noexcept
        {
            decimal temp = other;
            *this *= temp;
        }
        
        const decimal &operator/=(const hexadecimal &other) noexcept
        {
            decimal temp = other;
            *this /= temp;
        }
        
        const decimal &operator+=(const octal &other) noexcept
        {
            decimal temp = other;
            *this += temp;
        }
        
        const decimal &operator-=(const octal &other) noexcept
        {
            decimal temp = other;
            *this -= temp;
        }
        
        const decimal &operator*=(const octal &other) noexcept
        {
            decimal temp = other;
            *this *= temp;
        }
        
        const decimal &operator/=(const octal &other) noexcept
        {
            decimal temp = other;
            *this /= temp;
        }
        
        const decimal &operator+=(const binary &other) noexcept
        {
            decimal temp = other;
            *this += temp;
        }
        
        const decimal &operator-=(const binary &other) noexcept
        {
            decimal temp = other;
            *this -= temp;
        }
        
        const decimal &operator*=(const binary &other) noexcept
        {
            decimal temp = other;
            *this *= temp;
        }
        
        const decimal &operator/=(const binary &other) noexcept
        {
            decimal temp = other;
            *this /= temp;
        }
        
        void operator=(const decimal &other) noexcept { decNum = other.decNum; }
    };

    class hexadecimal
    {
    private:
        str hexNum;
        const hash_map<char, int> hexdigits = {
            {'0', 0},
            {'1', 1},
            {'2', 2},
            {'3', 3},
            {'4', 4},
            {'5', 5},
            {'6', 6},
            {'7', 7},
            {'8', 8},
            {'9', 9},
            {'A', 10},
            {'B', 11},
            {'C', 12},
            {'d', 13},
            {'E', 14},
            {'F', 15}};

    public:
        hexadecimal() : hexNum("") {}
        
        hexadecimal(const str &hex)
        {
            hexNum = hex;
            for (char ch : hexNum)
            {
                if (find(hexdigits.begin(), hexdigits.end(), ch) == hexdigits.end())
                    throw std::invalid_argument("Invalid hexadecimal input");
            }
        }
        
        hexadecimal(hexadecimal &hex)
        {
            hexNum = hex.get();
            for (char ch : hexNum)
            {
                if (find(hexdigits.begin(), hexdigits.end(), ch) == hexdigits.end())
                    throw std::invalid_argument("Invalid hexadecimal input");
            }
        }
        
        hexadecimal(const decimal &dec)
        {
            float decValue = dec.get();
            if (decValue < 0)
                throw std::invalid_argument("Negative decimal value not supported for hexadecimal conversion");
            if (decValue == 0)
                hexNum = "0";
            str result;
            int intValue = static_cast<int>(decValue);
            while (intValue > 0)
            {
                int remainder = intValue % 16;
                if (remainder < 10)
                    result += static_cast<char>('0' + remainder);
                else
                    result += static_cast<char>('A' + (remainder - 10));
                intValue /= 16;
            }
            std::reverse(result.begin(), result.end());
            hexNum = result;
        }
        
        hexadecimal(int num)
        {
            hexNum = std::to_string(num);
            for (char ch : hexNum)
            {
                if (find(hexdigits.begin(), hexdigits.end(), ch) == hexdigits.end())
                    throw std::invalid_argument("Invalid hexadecimal input");
            }
        }
        
        void set(const str &hex)
        {
            hexNum = hex;
            for (char ch : hexNum)
            {
                if (find(hexdigits.begin(), hexdigits.end(), ch) == hexdigits.end())
                    throw std::invalid_argument("Invalid hexadecimal input");
            }
        }
        
        str get() const noexcept { return hexNum; }
        
        procedure(clear) noexcept { hexNum.clear(); }
        
        procedure(base) noexcept { std::cout << "The base is 16" << newl; }

        void base(char ch)
        {
            if (ch == '?' || ch == '!')
                std::cout << "The base is 16" << newl;
        }
        
        bool empty() const noexcept { return hexNum.empty(); }
        
        void operator=(octal &oct) const
        {
            if (hexNum.empty())
                throw std::invalid_argument("No hexadecimal value provided");
            // Convert hexNum to decimal
            float decimalValue = 0;
            float base = 1;
            for (int i = hexNum.length() - 1; i >= 0; --i)
            {
                char ch = hexNum[i];
                int value = 0;
                if (ch >= '0' && ch <= '9')
                    value = ch - '0';
                else if (ch >= 'A' && ch <= 'F')
                    value = ch - 'A' + 10;
                else if (ch >= 'a' && ch <= 'f')
                    value = ch - 'a' + 10;
                else if (ch == '.')
                    continue; // skip decimal point for now
                else
                    throw std::invalid_argument("Invalid hexadecimal character");
                decimalValue += value * base;
                base *= 16;
            }
            // Convert decimal to octal
            float octalValue = 0;
            float octBase = 1;
            int intdecimal = static_cast<int>(decimalValue);
            while (intdecimal > 0)
            {
                int lastdigit = intdecimal % 8;
                octalValue += lastdigit * octBase;
                octBase *= 10;
                intdecimal /= 8;
            }
            std::cout << octalValue << newl;
        }
        
        float operator=(binary &bin) const
        {
            if (hexNum.empty())
                throw std::invalid_argument("No hexadecimal value provided");
            // Convert hexNum to decimal
            float decimalValue = 0;
            float base = 1;
            for (int i = hexNum.length() - 1; i >= 0; --i)
            {
                char ch = hexNum[i];
                int value = 0;
                if (ch >= '0' && ch <= '9')
                    value = ch - '0';
                else if (ch >= 'A' && ch <= 'F')
                    value = ch - 'A' + 10;
                else if (ch >= 'a' && ch <= 'f')
                    value = ch - 'a' + 10;
                else if (ch == '.')
                    continue; // skip decimal point for now
                else
                    throw std::invalid_argument("Invalid hexadecimal character");
                decimalValue += value * base;
                base *= 16;
            }
            // Convert decimal to binary
            float binaryValue = 0;
            float binBase = 1;
            int intdecimal = static_cast<int>(decimalValue);
            while (intdecimal > 0)
            {
                int lastdigit = intdecimal % 2;
                binaryValue += lastdigit * binBase;
                binBase *= 10;
                intdecimal /= 2;
            }
            return binaryValue;
        }
        
        hexadecimal &operator=(decimal &dec)
        {
            float decValue = dec.get();
            if (decValue < 0)
                throw std::invalid_argument("Negative decimal value not supported for hexadecimal conversion");
            if (decValue == 0)
            {
                hexNum = "0";
                return *this;
            }
            str result;
            int intValue = static_cast<int>(decValue);
            while (intValue > 0)
            {
                int remainder = intValue % 16;
                if (remainder < 10)
                    result += static_cast<char>('0' + remainder);
                else
                    result += static_cast<char>('A' + (remainder - 10));
                intValue /= 16;
            }
            std::reverse(result.begin(), result.end());
            hexNum = result;
            return *this;
        }
        
        void operator=(hexadecimal &hex)
        {
            if (hexNum.empty())
                throw std::invalid_argument("No hexadecimal value provided");
            hexNum = hex.get();
        }
        
        hexadecimal &operator++()
        {
            if (hexNum.empty())
                throw std::invalid_argument("No hexadecimal value provided");
            // Increment the hexadecimal value
            int carry = 1;
            for (int i = hexNum.length() - 1; i >= 0 && carry; --i)
            {
                char &ch = hexNum[i];
                if (ch >= '0' && ch <= '9')
                {
                    if (ch == '9')
                    {
                        ch = '0';
                        carry = 1;
                    }
                    else
                    {
                        ch++;
                        carry = 0;
                    }
                }
                else if (ch >= 'A' && ch <= 'F')
                {
                    if (ch == 'F')
                    {
                        ch = 'A';
                        carry = 1;
                    }
                    else
                    {
                        ch++;
                        carry = 0;
                    }
                }
                else
                    throw std::invalid_argument("Invalid hexadecimal character");
            }
            if (carry)
                hexNum = "1" + hexNum;
            return *this;
        }
        
        hexadecimal &operator--()
        {
            if (hexNum.empty())
                throw std::invalid_argument("No hexadecimal value provided");
            // decrement the hexadecimal value
            int carry = 1;
            for (int i = hexNum.length() - 1; i >= 0 && carry; --i)
            {
                char &ch = hexNum[i];
                if (ch >= '0' && ch <= '9')
                {
                    if (ch == '0')
                    {
                        ch = '9';
                        carry = 1;
                    }
                    else
                    {
                        ch--;
                        carry = 0;
                    }
                }
                else if (ch >= 'A' && ch <= 'F')
                {
                    if (ch == 'A')
                    {
                        ch = 'F';
                        carry = 1;
                    }
                    else
                    {
                        ch--;
                        carry = 0;
                    }
                }
                else
                    throw std::invalid_argument("Invalid hexadecimal character");
            }
            if (carry)
                hexNum = "F" + hexNum;
            return *this;
        }
        
        hexadecimal operator+(const hexadecimal &hex) const
        {
            if (hexNum.empty())
                throw std::invalid_argument("No hexadecimal value provided");
            hexadecimal result;
            decimal dec1 = *this, dec2 = hex;
            decimal sumdec = dec1;
            sumdec += dec2.get();
            result = sumdec;
            return result;
        }
        
        hexadecimal operator-(const hexadecimal &hex) const
        {
            if (hexNum.empty())
                throw std::invalid_argument("No hexadecimal value provided");
            hexadecimal result;
            decimal dec1 = *this, dec2 = hex;
            decimal diffdec = dec1;
            diffdec -= dec2.get();
            result = diffdec;
            return result;
        }
        
        hexadecimal operator*(const hexadecimal &hex) const
        {
            if (hexNum.empty())
                throw std::invalid_argument("No hexadecimal value provided");
            hexadecimal result;
            decimal dec1 = *this, dec2 = hex;
            decimal proddec = dec1;
            proddec *= dec2.get();
            result = proddec;
            return result;
        }
        
        hexadecimal operator/(const hexadecimal &hex) const
        {
            if (hexNum.empty())
                throw std::invalid_argument("No hexadecimal value provided");
            hexadecimal result;
            decimal dec1 = *this, dec2 = hex;
            if (dec2.get() == 0)
                throw std::invalid_argument("division by zero");
            decimal quotdec = dec1;
            quotdec /= dec2.get();
            result = quotdec;
            return result;
        }
        
        void operator+=(const hexadecimal &hex)
        {
            if (hexNum.empty())
                throw std::invalid_argument("No hexadecimal value provided");
            hexadecimal tempHex(hex.get());
            *this += tempHex;
        }
        
        void operator-=(const hexadecimal &hex)
        {
            if (hexNum.empty())
                throw std::invalid_argument("No hexadecimal value provided");
            hexadecimal tempHex(hex.get());
            *this -= tempHex;
        }
        
        void operator*=(const hexadecimal &hex)
        {
            if (hexNum.empty())
                throw std::invalid_argument("No hexadecimal value provided");
            hexadecimal tempHex(hex.get());
            *this *= tempHex;
        }
        
        void operator/=(const hexadecimal &hex)
        {
            if (hexNum.empty())
                throw std::invalid_argument("No hexadecimal value provided");
            hexadecimal tempHex(hex.get());
            *this /= tempHex;
        }
        
        ~hexadecimal() = default;
    };

    class octal
    {
    private:
        str octNum;

    public:
        octal() : octNum("") {}
        
        octal(int num)
        {
            octNum = std::to_string(num);
            for (char ch : octNum)
            {
                if (ch < '0' || ch > '7')
                {
                    std::cout << "Invalid octal character: " << ch << newl;
                    throw std::invalid_argument("Invalid octal input");
                }
            }
        }
        
        octal(const str &oct)
        {
            octNum = oct;
            for (char ch : octNum)
            {
                if (ch < '0' || ch > '7')
                {
                    std::cout << "Invalid octal character: " << ch << newl;
                    throw std::invalid_argument("Invalid octal input");
                }
            }
        }
        
        void set(const str &oct)
        {
            octNum = oct;
            for (char ch : octNum)
            {
                if (ch < '0' || ch > '7')
                {
                    std::cout << "Invalid octal character: " << ch << newl;
                    throw std::invalid_argument("Invalid octal input");
                }
            }
        }
        
        str get() const noexcept
        {
            return octNum;
        }

        procedure(base) noexcept { std::cout << "The base is 8" << newl; }
        
        void base(char ch) noexcept
        {
            if (ch == '?' || ch == '!')
                std::cout << "The base is 8" << newl;
        }
        
        bool empty() const
        {
            return octNum.empty();
        }
        
        procedure(clear) noexcept { octNum.clear(); }
        
        void operator=(binary &bin) const
        {
            if (octNum.empty())
                throw std::invalid_argument("No octal value provided");
            // Convert octal string (octNum) to decimal
            int decimalValue = 0;
            int base = 1;
            for (int i = octNum.length() - 1; i >= 0; --i)
            {
                char ch = octNum[i];
                if (ch < '0' || ch > '7')
                    throw std::invalid_argument("Invalid octal character");
                decimalValue += (ch - '0') * base;
                base *= 8;
            }
            // Convert decimal to binary string
            str binaryValue;
            int tempdecimal = decimalValue;
            if (tempdecimal == 0)
                binaryValue = "0";
            else
            {
                while (tempdecimal > 0)
                {
                    binaryValue = (char)('0' + (tempdecimal % 2)) + binaryValue;
                    tempdecimal /= 2;
                }
            }
            // You may want to set this value to a member or print it, depending on your design
            std::cout << binaryValue << newl;
        }
        
        void operator=(decimal &dec) const
        {
            if (octNum.empty())
                throw std::invalid_argument("No octal value provided");
            // Convert octNum (octal string) to decimal
            int decimalValue = 0;
            int base = 1;
            for (int i = octNum.length() - 1; i >= 0; --i)
            {
                char ch = octNum[i];
                if (ch < '0' || ch > '7')
                    throw std::invalid_argument("Invalid octal character");
                decimalValue += (ch - '0') * base;
                base *= 8;
            }
            dec.set(static_cast<float>(decimalValue));
        }

        void operator=(hexadecimal &hex)
        {
            if (octNum.empty())
                throw std::invalid_argument("No octal value provided");
            // Convert octal string to decimal
            int decimalValue = 0;
            int base = 1;
            for (int i = octNum.length() - 1; i >= 0; --i)
            {
                char ch = octNum[i];
                if (ch < '0' || ch > '7')
                    throw std::invalid_argument("Invalid octal character");
                decimalValue += (ch - '0') * base;
                base *= 8;
            }
            // Convert decimal to hexadecimal string
            str hexValue;
            int tempdecimal = decimalValue;
            if (tempdecimal == 0)
                hexValue = "0";
            else
            {
                while (tempdecimal > 0)
                {
                    int remainder = tempdecimal % 16;
                    if (remainder < 10)
                        hexValue += static_cast<char>('0' + remainder);
                    else
                        hexValue += static_cast<char>('A' + (remainder - 10));
                    tempdecimal /= 16;
                }
                std::reverse(hexValue.begin(), hexValue.end());
            }
            hex.set(hexValue);
        }
        
        void operator=(octal &oct)
        {
            if (octNum.empty())
                throw std::invalid_argument("No octal value provided");
            octNum = oct.get();
        }
        
        octal &operator++()
        {
            if (octNum.empty())
                throw std::invalid_argument("No octal value provided");
            // Increment the octal value
            int carry = 1;
            for (int i = octNum.length() - 1; i >= 0 && carry; --i)
            {
                char &ch = octNum[i];
                if (ch >= '0' && ch <= '7')
                {
                    if (ch == '7')
                    {
                        ch = '0';
                        carry = 1;
                    }
                    else
                    {
                        ch++;
                        carry = 0;
                    }
                }
                else
                {
                    throw std::invalid_argument("Invalid octal character");
                }
            }
            if (carry)
                octNum = "1" + octNum;
            return *this;
        }
        
        octal &operator--()
        {
            if (octNum.empty())
                throw std::invalid_argument("No octal value provided");
            // decrement the octal value
            int carry = 1;
            for (int i = octNum.length() - 1; i >= 0 && carry; --i)
            {
                char &ch = octNum[i];
                if (ch >= '0' && ch <= '7')
                {
                    if (ch == '0')
                    {
                        ch = '7';
                        carry = 1;
                    }
                    else
                    {
                        ch--;
                        carry = 0;
                    }
                }
                else
                {
                    throw std::invalid_argument("Invalid octal character");
                }
            }
            if (carry)
                octNum = "7" + octNum;
            return *this;
        }
        
        octal operator+(const octal &oct) const
        {
            if (octNum.empty())
                throw std::invalid_argument("No octal value provided");
            octal result;
            decimal dec1, dec2;
            dec1 = *this;
            dec2 = oct;
            decimal sumdec = dec1;
            sumdec += dec2.get();
            result = sumdec;
            return result;
        }
        
        octal operator-(const octal &oct) const
        {
            if (octNum.empty())
                throw std::invalid_argument("No octal value provided");
            octal result;
            decimal dec1, dec2;
            dec1 = *this;
            dec2 = oct;
            decimal diffdec = dec1;
            diffdec -= dec2.get();
            result = diffdec;
            return result;
        }
        
        octal operator*(const octal &oct) const
        {
            if (octNum.empty())
                throw std::invalid_argument("No octal value provided");
            octal result;
            decimal dec1, dec2;
            dec1 = *this;
            dec2 = oct;
            decimal proddec = dec1;
            proddec *= dec2.get();
            result = proddec;
            return result;
        }
        
        octal operator/(const octal &oct) const
        {
            if (octNum.empty())
                throw std::invalid_argument("No octal value provided");
            octal result;
            decimal dec1, dec2;
            dec1 = *this;
            dec2 = oct;
            if (dec2.get() == 0)
                throw std::invalid_argument("division by zero");
            decimal quotdec = dec1;
            quotdec /= dec2.get();
            result = quotdec;
            return result;
        }
        
        void operator+=(const octal &oct)
        {
            if (octNum.empty())
                throw std::invalid_argument("No octal value provided");
            octal tempOct(oct.get());
            *this += tempOct;
        }
        
        void operator-=(const octal &oct)
        {
            if (octNum.empty())
                throw std::invalid_argument("No octal value provided");
            octal tempOct(oct.get());
            *this -= tempOct;
        }
        
        void operator*=(const octal &oct)
        {
            if (octNum.empty())
                throw std::invalid_argument("No octal value provided");
            octal tempOct(oct.get());
            *this *= tempOct;
        }
        
        void operator/=(const octal &oct)
        {
            if (octNum.empty())
                throw std::invalid_argument("No octal value provided");
            octal tempOct(oct.get());
            *this /= tempOct;
        }

        ~octal() = default;
    };

    class binary
    {
    private:
        str bin;
        str binNum;

    public:

        binary() : bin(""), binNum("") {}

        binary(const str &bincode)
        {
            bin = bincode;
            if (!binary_test(bin))
            {
                std::cout << "Invalid binary input" << newl;
                throw std::invalid_argument("Invalid binary input");
            }
        }

        binary(int bincode)
        {
            binNum = std::to_string(bincode);
            if (!binary_test(binNum))
            {
                std::cout << "Invalid binary input" << newl;
                throw std::invalid_argument("Invalid binary input");
            }
        }

        void set(const str &bincode)
        {
            bin = bincode;
            if (!binary_test(bin))
            {
                std::cout << "Invalid binary input" << newl;
                throw std::invalid_argument("Invalid binary input");
            }
        }

        str get() const noexcept
        {
            return bin.empty() ? binNum : bin;
        }

        bool binary_test(const str &bincode)
        {
            for (char ch : bincode)
            {
                if (ch != '0' && ch != '1' && ch != '.')
                    return false;
            }
            return true;
        }

        bool empty() const
        {
            return bin.empty() && binNum.empty();
        }

        procedure(clear) noexcept
        {
            bin.clear();
            binNum.clear();
        }

        procedure(base) noexcept { std::cout << "The base is 2" << newl; }

        void base(char ch) noexcept
        {
            if (ch == '?' || ch == '!')
                std::cout << "The base is 2" << newl;
        }

        // true ~~> positive || false ~~> negative
        str onesComplement(str bincode, bool numsing = true)
        {
            str resultCode;
            for (char bit : bincode)
            {
                if (bit == '0')
                    resultCode += '1';
                else if (bit == '1')
                    resultCode += '0';
                else
                    return "Error"; // Invalid input
            }
            resultCode += (numsing ? '0' : '1');
            reverse(resultCode.begin(), resultCode.end());
            return resultCode;
        }

        str twosComplement(str bincode)
        {
            if (bincode.empty())
            {
                std::cout << "Error: Empty input!" << newl;
                throw std::invalid_argument("Empty input");
            }
            for (char bit : bincode)
            {
                if (bit != '0' && bit != '1')
                {
                    std::cout << "Error: Invalid character in input: " << bit << newl;
                    throw std::invalid_argument("Invalid character in input");
                }
            }
            for (char &bit : bincode)
                bit = (bit == '1') ? '0' : '1';
            bool carry = true;
            for (int i = bincode.length() - 1; i >= 0; i--)
            {
                if (carry)
                {
                    if (bincode[i] == '0')
                    {
                        bincode[i] = '1';
                        carry = false;
                    }
                    else
                        bincode[i] = '0';
                }
            }
            if (carry)
                bincode = "1" + bincode;
            return bincode;
        }

        void operator=(decimal &dec) const
        {
            if (bin.empty() && binNum.empty())
                throw std::invalid_argument("No binary value provided");
            str targetBin = bin.empty() ? binNum : bin;
            // Convert binary string to decimal
            float decimalValue = 0.0f;
            size_t dotPos = targetBin.find('.');
            str intPartStr = (dotPos == str::npos) ? targetBin : targetBin.substr(0, dotPos);
            str fracPartStr = (dotPos == str::npos) ? "" : targetBin.substr(dotPos + 1);

            // Integer part
            int base = 1;
            for (int i = intPartStr.length() - 1; i >= 0; --i)
            {
                char ch = intPartStr[i];
                if (ch != '0' && ch != '1')
                    throw std::invalid_argument("Invalid binary digit");
                int lastdigit = ch - '0';
                decimalValue += lastdigit * base;
                base *= 2;
            }

            // Fractional part
            float fracBase = 0.5f;
            for (size_t i = 0; i < fracPartStr.length(); ++i)
            {
                char ch = fracPartStr[i];
                if (ch != '0' && ch != '1')
                    throw std::invalid_argument("Invalid binary digit in fractional part");
                int digit = ch - '0';
                decimalValue += digit * fracBase;
                fracBase /= 2.0f;
            }

            dec.set(decimalValue);
        }

        void operator=(octal &oct)
        {
            if (bin.empty() && binNum.empty())
                throw std::invalid_argument("No binary value provided");
            str targetBin = bin.empty() ? binNum : bin;
            // Helper: Convert binary string to decimal
            auto binaryTodecimal = [](const str &binStr) -> int
            {
                int result = 0;
                for (char ch : binStr)
                {
                    if (ch == '0' || ch == '1')
                    {
                        result = result * 2 + (ch - '0');
                    }
                }
                return result;
            };
            int decimalValue = binaryTodecimal(targetBin);
            str octalValue;
            if (decimalValue == 0)
                octalValue = "0";
            else
            {
                while (decimalValue > 0)
                {
                    octalValue = static_cast<char>('0' + (decimalValue % 8)) + octalValue;
                    decimalValue /= 8;
                }
            }
            oct.set(octalValue);
        }

        void operator=(hexadecimal &hex)
        {
            if (bin.empty() && binNum.empty())
                throw std::invalid_argument("No binary value provided");
            str targetBin = bin.empty() ? binNum : bin;
            // Helper: Convert binary string to decimal
            auto binaryTodecimal = [](const str &binStr) -> int
            {
                int result = 0;
                for (char ch : binStr)
                {
                    if (ch == '0' || ch == '1')
                    {
                        result = result * 2 + (ch - '0');
                    }
                }
                return result;
            };
            int decimalValue = binaryTodecimal(targetBin);
            str hexValue;
            if (decimalValue == 0)
            {
                hexValue = "0";
            }
            else
            {
                while (decimalValue > 0)
                {
                    int remainder = decimalValue % 16;
                    if (remainder < 10)
                        hexValue += static_cast<char>('0' + remainder);
                    else
                        hexValue += static_cast<char>('A' + (remainder - 10));
                    decimalValue /= 16;
                }
                std::reverse(hexValue.begin(), hexValue.end());
            }
            hex.set(hexValue);
        }

        void operator=(binary &binObj)
        {
            if (bin.empty() && binNum.empty())
                throw std::invalid_argument("No binary value provided");
            binObj.set(bin.empty() ? binNum : bin);
        }

        binary &operator++()
        {
            if (bin.empty() && binNum.empty())
                throw std::invalid_argument("No binary value provided");
            str &targetBin = bin.empty() ? binNum : bin;
            int carry = 1;
            for (int i = targetBin.length() - 1; i >= 0 && carry; --i)
            {
                char &ch = targetBin[i];
                if (ch == '0')
                {
                    ch = '1';
                    carry = 0;
                }
                else if (ch == '1')
                {
                    ch = '0';
                    carry = 1;
                }
                else
                {
                    throw std::invalid_argument("Invalid binary character");
                }
            }
            if (carry)
                targetBin = "1" + targetBin;
            if (!bin.empty())
                bin = targetBin;
            else
                binNum = targetBin;
            return *this;
        }

        binary &operator--()
        {
            if (bin.empty() && binNum.empty())
                throw std::invalid_argument("No binary value provided");
            str &targetBin = bin.empty() ? binNum : bin;
            int carry = 1;
            for (int i = targetBin.length() - 1; i >= 0 && carry; --i)
            {
                char &ch = targetBin[i];
                if (ch == '1')
                {
                    ch = '0';
                    carry = 0;
                }
                else if (ch == '0')
                {
                    ch = '1';
                    carry = 1;
                }
                else
                {
                    throw std::invalid_argument("Invalid binary character");
                }
            }
            if (carry)
                targetBin = "0" + targetBin; // Underflow case
            if (!bin.empty())
                bin = targetBin;
            else
                binNum = targetBin;
            return *this;
        }

        binary operator+(const binary &binObj) const
        {
            if (bin.empty() && binNum.empty())
                throw std::invalid_argument("No binary value provided");
            binary result;
            decimal dec1, dec2;
            dec1 = *this;
            dec2 = binObj;
            decimal sumdec = dec1;
            sumdec += dec2.get();
            result = sumdec;
            return result;
        }

        binary operator-(const binary &binObj) const
        {
            if (bin.empty() && binNum.empty())
                throw std::invalid_argument("No binary value provided");
            binary result;
            decimal dec1, dec2;
            dec1 = *this;
            dec2 = binObj;
            decimal diffdec = dec1;
            diffdec -= dec2.get();
            result = diffdec;
            return result;
        }

        binary operator*(const binary &binObj) const
        {
            if (bin.empty() && binNum.empty())
                throw std::invalid_argument("No binary value provided");
            binary result;
            decimal dec1, dec2;
            dec1 = *this;
            dec2 = binObj;
            decimal proddec = dec1;
            proddec *= dec2.get();
            result = proddec;
            return result;
        }

        binary operator/(const binary &binObj) const
        {
            if (bin.empty() && binNum.empty())
                throw std::invalid_argument("No binary value provided");
            binary result;
            decimal dec1, dec2;
            dec1 = *this;
            dec2 = binObj;
            if (dec2.get() == 0)
                throw std::invalid_argument("division by zero");
            decimal quotdec = dec1;
            quotdec /= dec2.get();
            result = quotdec;
            return result;
        }

        void operator+=(const binary &binObj)
        {
            if (bin.empty() && binNum.empty())
                throw std::invalid_argument("No binary value provided");
            binary tempBin(binObj.get());
            *this += tempBin;
        }

        void operator-=(const binary &binObj)
        {
            if (bin.empty() && binNum.empty())
                throw std::invalid_argument("No binary value provided");
            binary tempBin(binObj.get());
            *this -= tempBin;
        }

        void operator*=(const binary &binObj)
        {
            if (bin.empty() && binNum.empty())
                throw std::invalid_argument("No binary value provided");
            binary tempBin(binObj.get());
            *this *= tempBin;
        }

        void operator/=(const binary &binObj)
        {
            if (bin.empty() && binNum.empty())
                throw std::invalid_argument("No binary value provided");
            binary tempBin(binObj.get());
            *this /= tempBin;
        }

        ~binary() = default;
    };

    str to_hex(int num) noexcept
    {
        float fnum = num;
        str Newstr, result;
        for (int i = 0; i < num; i++)
        {
            fnum /= 16;
            num /= 16;
            int test = ((fnum - num) * 16);
            if (test == 10)
                Newstr += 'A';
            else if (test == 11)
                Newstr += 'B';
            else if (test == 12)
                Newstr += 'C';
            else if (test == 13)
                Newstr += 'd';
            else if (test == 14)
                Newstr += 'E';
            else if (test == 15)
                Newstr += 'F';
            else if (test <= 9 && test >= 0)
                Newstr += char(48 + test);
        }
        for (int j = Newstr.length() - 1; j >= 0; j--)
            result += Newstr[j];
        return result;
    }

    int to_oct(int num) noexcept
    {
        int count = 0;
        if (num % 8 == 0)
            count = (num / 8) * 10;
        else
            count = ((num / 8) * 10 + (num % 8));
        return count;
    }

    int to_binary(int num) noexcept
    {
        int base = 1, count = 0;
        std::vector<int> vnum;
        while (num > 0)
        {
            vnum.push_back(num % 2);
            num /= 2;
        }
        for (int i = vnum.size() - 1; i >= 0; i--)
        {
            if (i != 0)
                count += vnum[i] * pow(10, i);
            else
                count += vnum[i];
        }
        return count;
    }

    bool binary_test(str bincode) noexcept
    {
        for (int i = 0; i < bincode.length(); i++)
        {
            if (bincode[i] != '1' && bincode[i] != '0')
                return false;
        }
        return true;
    }

    str reverse(str result) noexcept
    {
        str NewRes;
        int len = result.length();
        for (int i = len - 1; i >= 0; i--)
            NewRes += result[i];
        return NewRes;
    }

    str toBCd(int num) noexcept
    {
        str result;
        while (num)
        {
            if (num % 10 == 0)
                result += "0000";
            else if (num % 10 == 1)
                result += "0001";
            else if (num % 10 == 2)
                result += "0010";
            else if (num % 10 == 3)
                result += "0011";
            else if (num % 10 == 4)
                result += "0100";
            else if (num % 10 == 5)
                result += "0101";
            else if (num % 10 == 6)
                result += "0110";
            else if (num % 10 == 7)
                result += "0111";
            else if (num % 10 == 8)
                result += "1000";
            else if (num % 10 == 9)
                result += "1001";
            num /= 10;
        }
        return result;
    }

    str excess_3(int num) noexcept
    {
        int NewNum;
        str result;
        while (num)
        {
            NewNum = num % 10;
            if (NewNum + 3 == 3)
                result += "0011";
            else if (NewNum + 3 == 4)
                result += "0100";
            else if (NewNum + 3 == 5)
                result += "0101";
            else if (NewNum + 3 == 6)
                result += "0110";
            else if (NewNum + 3 == 7)
                result += "0111";
            else if (NewNum + 3 == 8)
                result += "1000";
            else if (NewNum + 3 == 9)
                result += "1001";
            else if (NewNum + 3 == 10)
                result += "1010";
            else if (NewNum + 3 == 11)
                result += "1011";
            else if (NewNum + 3 == 12)
                result += "1100";
            num /= 10;
        }
        return result;
    }

    str code_2421(int num) noexcept
    {
        str result;
        while (num)
        {
            if (num % 10 == 0)
                result += "0000";
            else if (num % 10 == 1)
                result += "0001";
            else if (num % 10 == 2)
                result += "1000";
            else if (num % 10 == 3)
                result += "1001";
            else if (num % 10 == 4)
                result += "1010";
            else if (num % 10 == 5)
                result += "1011";
            else if (num % 10 == 6)
                result += "1100";
            else if (num % 10 == 7)
                result += "1101";
            else if (num % 10 == 8)
                result += "1110";
            else if (num % 10 == 9)
                result += "1111";
            num /= 10;
        }
        return result;
    }

    str code_8421(int num) noexcept
    {
        str result;
        while (num)
        {
            if (num % 10 == 0)
                result += "0000";
            else if (num % 10 == 1)
                result += "0111";
            else if (num % 10 == 2)
                result += "0110";
            else if (num % 10 == 3)
                result += "0101";
            else if (num % 10 == 4)
                result += "0100";
            else if (num % 10 == 5)
                result += "1011";
            else if (num % 10 == 6)
                result += "1010";
            else if (num % 10 == 7)
                result += "1001";
            else if (num % 10 == 8)
                result += "1000";
            else if (num % 10 == 9)
                result += "1111";
            num /= 10;
        }
        return result;
    }

    str gray_code(str bincode) noexcept
    {
        size_t binlen = bincode.length();
        str resultCode;
        if (binlen == 0)
            return "no value send to the function";
        // First bit of Gray code is the same as first bit of binary
        resultCode += bincode[0];
        // Other bits are XOR of adjacent bits in binary
        for (int i = 1; i < binlen; i++)
        {
            if (bincode[i - 1] == bincode[i])
                resultCode += '0';
            else
                resultCode += '1';
        }
        return resultCode;
    }

    str ASCII(char ch) noexcept
    {
        int ChNum = ch;
        int result_code = to_binary(ChNum);
        return std::to_string(result_code);
    }
    
    str error_detecting_code(str bincode, bool evenParity = true) noexcept
    {
        if (!binary_test(bincode))
            return "wrong value in the code.";
        str result;
        short int count = 0;
        for (int i = 0; i < bincode.length(); i++)
            if (bincode[i] == '1')
                count++;
        if (count % 2 == 0 && evenParity)
        {
            result += '0';
            result += bincode;
        }
        else if (count % 2 == 0 || evenParity)
        {
            result += '1';
            result += bincode;
        }
        else if (count % 2 != 0 && evenParity)
        {
            result += '1';
            result += bincode;
        }
        else
        {
            result += '0';
            result += bincode;
        }
        return result;
    }
};
#endif // OPENMSL___MSL___dLd_HPP