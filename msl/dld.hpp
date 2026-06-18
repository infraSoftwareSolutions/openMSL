#pragma once
#ifndef OPENMSL___MSL___DLD_HPP
#define OPENMSL___MSL___DLD_HPP
#include <iostream>
#include <vector>
#include <cmath>
#include <map>
#include <algorithm>
#include <string>
#include <stdexcept>

/**
 * @file dld.hpp
 * @brief This header file defines classes for handling data sizes and numeral system conversions.
 * This header file defines classes for handling data sizes and conversions between different numeral systems (decimal, hexadecimal, octal, binary). The `Data` class provides methods for converting between various data size units (bits, nibbles, bytes, words, kilobytes, megabytes, gigabytes, terabytes). The `decimal`, `hexadecimal`, `octal`, and `binary` classes provide functionality for representing and converting between these numeral systems. Each class includes constructors, assignment operators, and methods for performing conversions and displaying information about the data or numeral system. The code also includes error handling for invalid inputs.
 * @author Ali Lafi
 * @date 2024-06-01
 */

class hexadecimal;
class octal;
class binary;
namespace msl
{
    class Data
    {
    private:
        float dataSize;
        std::string dataType;

    public:
        Data() noexcept : dataSize(0), dataType("Bits") {}
        Data(float D) noexcept : dataSize(D) {}
        Data(const std::string &DT) noexcept : dataType(DT) {}
        Data(const Data &other) noexcept : dataSize(other.dataSize), dataType(other.dataType) {}
        Data(float D, const std::string &DT) noexcept : dataSize(D), dataType(DT) {}
        void set_values(float D, const std::string &DT) noexcept
        {
            dataSize = D;
            dataType = DT;
        }
        void data_dictionary(char ch = '?') noexcept
        {
            std::cout << "1-Bit = 0 OR 1" << std::endl;
            std::cout << "1-Nibble = 4-Bits" << std::endl;
            std::cout << "1-Byte = 8-Bits = 2-Nibble" << std::endl;
            std::cout << "1-word = 2-Byte = 4-Nibble = 16-Bits" << std::endl;
            std::cout << "1-killo = 2^10" << std::endl;
            std::cout << "1-Mega = 2^20" << std::endl;
            std::cout << "1-Giga = 2^30" << std::endl;
            std::cout << "1-Tira = 2^40" << std::endl;
        }
        float To_Bits(float amountOfDat = 1, const char ConDat[20] = "Nibble")
        {
            if (ConDat == "Nibble")
                return (amountOfDat * 4);
            else if (ConDat == "Byte")
                return (amountOfDat * 8);
            else if (ConDat == "Word")
                return (amountOfDat * 16);
            else if (ConDat == "Killo")
                return (amountOfDat * pow(2, 10));
            else if (ConDat == "Mega")
                return (amountOfDat * pow(2, 20));
            else if (ConDat == "Giga")
                return (amountOfDat * pow(2, 30));
            else if (ConDat == "Tira")
                return (amountOfDat * pow(2, 40));
            else
                throw std::invalid_argument("wrong data choosing");
        }
        float To_Nibbles(float amountOfDat = 1, const char ConDat[20] = "Byte")
        {
            if (ConDat == "Bits")
                return (amountOfDat / 4);
            else if (ConDat == "Byte")
                return (amountOfDat * 2);
            else if (ConDat == "Word")
                return (amountOfDat * 4);
            else if (ConDat == "Killo")
                return (amountOfDat * pow(2, 8));
            else if (ConDat == "Mega")
                return (amountOfDat * pow(2, 18));
            else if (ConDat == "Giga")
                return (amountOfDat * pow(2, 28));
            else if (ConDat == "Tira")
                return (amountOfDat * pow(2, 38));
            else
                throw std::invalid_argument("wrong data choosing");
        }
        float To_Bytes(float amountOfDat = 1, const char ConDat[20] = "Word")
        {
            if (ConDat == "Bits")
                return (amountOfDat / 8);
            else if (ConDat == "Nibble")
                return (amountOfDat / 2);
            else if (ConDat == "Word")
                return (amountOfDat * 2);
            else if (ConDat == "Killo")
                return (amountOfDat * pow(2, 7));
            else if (ConDat == "Mega")
                return (amountOfDat * pow(2, 17));
            else if (ConDat == "Giga")
                return (amountOfDat * pow(2, 27));
            else if (ConDat == "Tira")
                return (amountOfDat * pow(2, 37));
            else
                throw std::invalid_argument("wrong data choosing");
        }
        float To_word(float amountOfDat = 1, const char ConDat[20] = "Killo")
        {
            if (ConDat == "Bits")
                return (amountOfDat / 16);
            else if (ConDat == "Nibble")
                return (amountOfDat / 4);
            else if (ConDat == "Byte")
                return (amountOfDat / 2);
            else if (ConDat == "Killo")
                return (amountOfDat * pow(2, 6));
            else if (ConDat == "Mega")
                return (amountOfDat * pow(2, 16));
            else if (ConDat == "Giga")
                return (amountOfDat * pow(2, 26));
            else if (ConDat == "Tira")
                return (amountOfDat * pow(2, 36));
            else
                throw std::invalid_argument("wrong data choosing");
        }
        float To_Killo(float amountOfDat = 1, const char ConDat[20] = "Mega")
        {
            if (ConDat == "Bits")
                return (amountOfDat / pow(2, 10));
            else if (ConDat == "Nibble")
                return (amountOfDat / pow(2, 8));
            else if (ConDat == "Byte")
                return (amountOfDat / pow(2, 7));
            else if (ConDat == "Word")
                return (amountOfDat / pow(2, 6));
            else if (ConDat == "Mega")
                return (amountOfDat * pow(2, 10));
            else if (ConDat == "Giga")
                return (amountOfDat * pow(2, 20));
            else if (ConDat == "Tira")
                return (amountOfDat * pow(2, 30));
            else
                throw std::invalid_argument("wrong data choosing");
        }
        float To_Mega(float amountOfDat = 1, const char ConDat[20] = "Giga")
        {
            if (ConDat == "Bits")
                return (amountOfDat / pow(2, 20));
            else if (ConDat == "Nibble")
                return (amountOfDat / pow(2, 18));
            else if (ConDat == "Byte")
                return (amountOfDat / pow(2, 17));
            else if (ConDat == "Word")
                return (amountOfDat / pow(2, 16));
            else if (ConDat == "Killo")
                return (amountOfDat / pow(2, 10));
            else if (ConDat == "Giga")
                return (amountOfDat * pow(2, 10));
            else if (ConDat == "Tira")
                return (amountOfDat * pow(2, 20));
            else
                throw std::invalid_argument("wrong data choosing");
        }
        float To_Giga(float amountOfDat = 1, const char ConDat[20] = "Tira")
        {
            if (ConDat == "Bits")
                return (amountOfDat / pow(2, 30));
            else if (ConDat == "Nibble")
                return (amountOfDat / pow(2, 28));
            else if (ConDat == "Byte")
                return (amountOfDat / pow(2, 27));
            else if (ConDat == "Word")
                return (amountOfDat / pow(2, 26));
            else if (ConDat == "Killo")
                return (amountOfDat / pow(2, 20));
            else if (ConDat == "Mega")
                return (amountOfDat / pow(2, 10));
            else if (ConDat == "Tira")
                return (amountOfDat * pow(2, 10));
            else
                throw std::invalid_argument("wrong data choosing");
        }
        float To_Tira(float amountOfDat = 1, const char ConDat[20] = "Giga")
        {
            if (ConDat == "Bits")
                return (amountOfDat / pow(2, 40));
            else if (ConDat == "Nibble")
                return (amountOfDat / pow(2, 38));
            else if (ConDat == "Byte")
                return (amountOfDat / pow(2, 37));
            else if (ConDat == "Word")
                return (amountOfDat / pow(2, 36));
            else if (ConDat == "Killo")
                return (amountOfDat / pow(2, 30));
            else if (ConDat == "Mega")
                return (amountOfDat / pow(2, 20));
            else if (ConDat == "Giga")
                return (amountOfDat / pow(2, 10));
            else
                throw std::invalid_argument("wrong data choosing");
        }
        void clear() noexcept
        {
            dataSize = 0;
            dataType = "Bits";
        }
        void display() const
        {
            std::cout << "Data Size: "
                      << dataSize << " "
                      << dataType << std::endl;
        }
        void operator=(const Data &other) noexcept
        {
            dataSize = other.dataSize;
            dataType = other.dataType;
        }
        void operator=(float D) noexcept { dataSize = D; }
        void operator=(const std::string &DT) noexcept { dataType = DT; }
        bool operator==(float D) noexcept { return dataSize == D; }
        bool operator==(const std::string &DT) noexcept { return dataType == DT; }
        bool operator!=(float D) noexcept { return dataSize != D; }
        bool operator!=(const std::string &DT) { return dataType != DT; }
        void operator+=(float D) noexcept { dataSize += D; }
        void operator-=(float D) noexcept { dataSize -= D; }
        void operator*=(float D) noexcept { dataSize *= D; }
        void operator/=(float D) noexcept { dataSize /= D; }
        ~Data() = default;
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
            std::string snum = hex.get();
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
                    throw std::invalid_argument("Not valid character: " + std::string(1, snum[i]));
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
            std::string octStr = oct.get(); // Assuming octal class has a get() method
            size_t dotPos = octStr.find('.');
            std::string intPartStr = (dotPos == std::string::npos) ? octStr : octStr.substr(0, dotPos);
            std::string fracPartStr = (dotPos == std::string::npos) ? "" : octStr.substr(dotPos + 1);
            // Convert integer part
            float cov = 0.0;
            int base = 1;
            for (int i = intPartStr.length() - 1; i >= 0; --i)
            {
                char ch = intPartStr[i];
                if (ch < '0' || ch > '7')
                {
                    std::cout << "Invalid digit in integer part: " << ch << std::endl;
                    throw std::invalid_argument("Invalid octal digit in integer part");
                }
                int lastDigit = ch - '0';
                cov += lastDigit * base;
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
                    std::cout << "Invalid digit in fractional part: " << ch << std::endl;
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
            std::string binStr = bin.get(); // You may need to implement get() in binary
            size_t dotPos = binStr.find('.');
            std::string intPartStr = (dotPos == std::string::npos) ? binStr : binStr.substr(0, dotPos);
            std::string fracPartStr = (dotPos == std::string::npos) ? "" : binStr.substr(dotPos + 1);
            // Convert integer part
            float integerPart = 0;
            int base = 1;
            for (int i = intPartStr.length() - 1; i >= 0; --i)
            {
                char ch = intPartStr[i];
                if (ch != '0' && ch != '1')
                {
                    std::cout << "Invalid binary digit: " << ch << std::endl;
                    throw std::invalid_argument("Invalid binary input");
                }
                int lastDigit = ch - '0';
                integerPart += lastDigit * base;
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
                    std::cout << "Invalid fractional digit: " << ch << std::endl;
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
                std::cout << "The base is 10" << std::endl;
        }
        void operator=(const hexadecimal &hex)
        {
            std::string snum = hex.get();
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
                    throw std::invalid_argument("Not valid character: " + std::string(1, snum[i]));
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
            std::string octStr = oct.get(); // Assuming octal class has a get() method
            size_t dotPos = octStr.find('.');
            std::string intPartStr = (dotPos == std::string::npos) ? octStr : octStr.substr(0, dotPos);
            std::string fracPartStr = (dotPos == std::string::npos) ? "" : octStr.substr(dotPos + 1);
            // Convert integer part
            float cov = 0.0;
            int base = 1;
            for (int i = intPartStr.length() - 1; i >= 0; --i)
            {
                char ch = intPartStr[i];
                if (ch < '0' || ch > '7')
                {
                    std::cout << "Invalid digit in integer part: " << ch << std::endl;
                    throw std::invalid_argument("Invalid octal digit in integer part");
                }
                int lastDigit = ch - '0';
                cov += lastDigit * base;
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
                    std::cout << "Invalid digit in fractional part: " << ch << std::endl;
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
            std::string binStr = bin.get(); // You may need to implement get() in binary
            size_t dotPos = binStr.find('.');
            std::string intPartStr = (dotPos == std::string::npos) ? binStr : binStr.substr(0, dotPos);
            std::string fracPartStr = (dotPos == std::string::npos) ? "" : binStr.substr(dotPos + 1);
            // Convert integer part
            float integerPart = 0;
            int base = 1;
            for (int i = intPartStr.length() - 1; i >= 0; --i)
            {
                char ch = intPartStr[i];
                if (ch != '0' && ch != '1')
                {
                    std::cout << "Invalid binary digit: " << ch << std::endl;
                    throw std::invalid_argument("Invalid binary input");
                }
                int lastDigit = ch - '0';
                integerPart += lastDigit * base;
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
                    std::cout << "Invalid fractional digit: " << ch << std::endl;
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
                throw std::invalid_argument("Division by zero");
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
        std::string hexNum;
        const std::map<char, int> hexDigits = {
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
            {'D', 13},
            {'E', 14},
            {'F', 15}};

    public:
        hexadecimal() : hexNum("") {}
        hexadecimal(const std::string &hex)
        {
            hexNum = hex;
            for (char ch : hexNum)
            {
                if (find(hexDigits.begin(), hexDigits.end(), ch) == hexDigits.end())
                    throw std::invalid_argument("Invalid hexadecimal input");
            }
        }
        hexadecimal(hexadecimal &hex)
        {
            hexNum = hex.get();
            for (char ch : hexNum)
            {
                if (find(hexDigits.begin(), hexDigits.end(), ch) == hexDigits.end())
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
            std::string result;
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
                if (find(hexDigits.begin(), hexDigits.end(), ch) == hexDigits.end())
                    throw std::invalid_argument("Invalid hexadecimal input");
            }
        }
        void set(const std::string &hex)
        {
            hexNum = hex;
            for (char ch : hexNum)
            {
                if (find(hexDigits.begin(), hexDigits.end(), ch) == hexDigits.end())
                    throw std::invalid_argument("Invalid hexadecimal input");
            }
        }
        std::string get() const noexcept { return hexNum; }
        void clear() noexcept
        {
            hexNum.clear();
        }
        void base(char ch)
        {
            if (ch == '?' || ch == '!')
                std::cout << "The base is 16" << std::endl;
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
            int intDecimal = static_cast<int>(decimalValue);
            while (intDecimal > 0)
            {
                int lastDigit = intDecimal % 8;
                octalValue += lastDigit * octBase;
                octBase *= 10;
                intDecimal /= 8;
            }
            std::cout << octalValue << std::endl;
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
            int intDecimal = static_cast<int>(decimalValue);
            while (intDecimal > 0)
            {
                int lastDigit = intDecimal % 2;
                binaryValue += lastDigit * binBase;
                binBase *= 10;
                intDecimal /= 2;
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
            std::string result;
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
            // Decrement the hexadecimal value
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
            decimal sumDec = dec1;
            sumDec += dec2.get();
            result = sumDec;
            return result;
        }
        hexadecimal operator-(const hexadecimal &hex) const
        {
            if (hexNum.empty())
                throw std::invalid_argument("No hexadecimal value provided");
            hexadecimal result;
            decimal dec1 = *this, dec2 = hex;
            decimal diffDec = dec1;
            diffDec -= dec2.get();
            result = diffDec;
            return result;
        }
        hexadecimal operator*(const hexadecimal &hex) const
        {
            if (hexNum.empty())
                throw std::invalid_argument("No hexadecimal value provided");
            hexadecimal result;
            decimal dec1 = *this, dec2 = hex;
            decimal prodDec = dec1;
            prodDec *= dec2.get();
            result = prodDec;
            return result;
        }
        hexadecimal operator/(const hexadecimal &hex) const
        {
            if (hexNum.empty())
                throw std::invalid_argument("No hexadecimal value provided");
            hexadecimal result;
            decimal dec1 = *this, dec2 = hex;
            if (dec2.get() == 0)
                throw std::invalid_argument("Division by zero");
            decimal quotDec = dec1;
            quotDec /= dec2.get();
            result = quotDec;
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
        std::string octNum;

    public:
        octal() : octNum("") {}
        octal(int num)
        {
            octNum = std::to_string(num);
            for (char ch : octNum)
            {
                if (ch < '0' || ch > '7')
                {
                    std::cout << "Invalid octal character: " << ch << std::endl;
                    throw std::invalid_argument("Invalid octal input");
                }
            }
        }
        octal(const std::string &oct)
        {
            octNum = oct;
            for (char ch : octNum)
            {
                if (ch < '0' || ch > '7')
                {
                    std::cout << "Invalid octal character: " << ch << std::endl;
                    throw std::invalid_argument("Invalid octal input");
                }
            }
        }
        void set(const std::string &oct)
        {
            octNum = oct;
            for (char ch : octNum)
            {
                if (ch < '0' || ch > '7')
                {
                    std::cout << "Invalid octal character: " << ch << std::endl;
                    throw std::invalid_argument("Invalid octal input");
                }
            }
        }
        std::string get() const noexcept
        {
            return octNum;
        }
        void base(char ch)
        {
            if (ch == '?' || ch == '!')
                std::cout << "The base is 8" << std::endl;
        }
        bool empty() const
        {
            return octNum.empty();
        }
        void clear() noexcept
        {
            octNum.clear();
        }
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
            std::string binaryValue;
            int tempDecimal = decimalValue;
            if (tempDecimal == 0)
                binaryValue = "0";
            else
            {
                while (tempDecimal > 0)
                {
                    binaryValue = (char)('0' + (tempDecimal % 2)) + binaryValue;
                    tempDecimal /= 2;
                }
            }
            // You may want to set this value to a member or print it, depending on your design
            std::cout << binaryValue << std::endl;
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
            std::string hexValue;
            int tempDecimal = decimalValue;
            if (tempDecimal == 0)
                hexValue = "0";
            else
            {
                while (tempDecimal > 0)
                {
                    int remainder = tempDecimal % 16;
                    if (remainder < 10)
                        hexValue += static_cast<char>('0' + remainder);
                    else
                        hexValue += static_cast<char>('A' + (remainder - 10));
                    tempDecimal /= 16;
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
            // Decrement the octal value
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
            decimal sumDec = dec1;
            sumDec += dec2.get();
            result = sumDec;
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
            decimal diffDec = dec1;
            diffDec -= dec2.get();
            result = diffDec;
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
            decimal prodDec = dec1;
            prodDec *= dec2.get();
            result = prodDec;
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
                throw std::invalid_argument("Division by zero");
            decimal quotDec = dec1;
            quotDec /= dec2.get();
            result = quotDec;
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
        std::string bin;
        std::string binNum;

    public:
        binary() : bin(""), binNum("") {}
        binary(const std::string &bincode)
        {
            bin = bincode;
            if (!binary_test(bin))
            {
                std::cout << "Invalid binary input" << std::endl;
                throw std::invalid_argument("Invalid binary input");
            }
        }
        binary(int bincode)
        {
            binNum = std::to_string(bincode);
            if (!binary_test(binNum))
            {
                std::cout << "Invalid binary input" << std::endl;
                throw std::invalid_argument("Invalid binary input");
            }
        }
        void set(const std::string &bincode)
        {
            bin = bincode;
            if (!binary_test(bin))
            {
                std::cout << "Invalid binary input" << std::endl;
                throw std::invalid_argument("Invalid binary input");
            }
        }
        std::string get() const noexcept
        {
            return bin.empty() ? binNum : bin;
        }
        bool binary_test(const std::string &bincode)
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
        void clear() noexcept
        {
            bin.clear();
            binNum.clear();
        }
        void base(char ch)
        {
            if (ch == '?' || ch == '!')
                std::cout << "The base is 2" << std::endl;
        }
        // true ~~> positive || false ~~> negative
        std::string onesComplement(std::string bincode, bool numsing = true)
        {
            std::string resultCode;
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
        std::string twosComplement(std::string bincode)
        {
            if (bincode.empty())
            {
                std::cout << "Error: Empty input!" << std::endl;
                throw std::invalid_argument("Empty input");
            }
            for (char bit : bincode)
            {
                if (bit != '0' && bit != '1')
                {
                    std::cout << "Error: Invalid character in input: " << bit << std::endl;
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
            std::string targetBin = bin.empty() ? binNum : bin;
            // Convert binary string to decimal
            float decimalValue = 0.0f;
            size_t dotPos = targetBin.find('.');
            std::string intPartStr = (dotPos == std::string::npos) ? targetBin : targetBin.substr(0, dotPos);
            std::string fracPartStr = (dotPos == std::string::npos) ? "" : targetBin.substr(dotPos + 1);

            // Integer part
            int base = 1;
            for (int i = intPartStr.length() - 1; i >= 0; --i)
            {
                char ch = intPartStr[i];
                if (ch != '0' && ch != '1')
                    throw std::invalid_argument("Invalid binary digit");
                int lastDigit = ch - '0';
                decimalValue += lastDigit * base;
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
            std::string targetBin = bin.empty() ? binNum : bin;
            // Helper: Convert binary string to decimal
            auto binaryToDecimal = [](const std::string &binStr) -> int
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
            int decimalValue = binaryToDecimal(targetBin);
            std::string octalValue;
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
            std::string targetBin = bin.empty() ? binNum : bin;
            // Helper: Convert binary string to decimal
            auto binaryToDecimal = [](const std::string &binStr) -> int
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
            int decimalValue = binaryToDecimal(targetBin);
            std::string hexValue;
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
            std::string &targetBin = bin.empty() ? binNum : bin;
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
            std::string &targetBin = bin.empty() ? binNum : bin;
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
            decimal sumDec = dec1;
            sumDec += dec2.get();
            result = sumDec;
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
            decimal diffDec = dec1;
            diffDec -= dec2.get();
            result = diffDec;
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
            decimal prodDec = dec1;
            prodDec *= dec2.get();
            result = prodDec;
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
                throw std::invalid_argument("Division by zero");
            decimal quotDec = dec1;
            quotDec /= dec2.get();
            result = quotDec;
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
    std::string to_hex(int num) noexcept
    {
        float fnum = num;
        std::string Newstr, result;
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
                Newstr += 'D';
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
    bool binary_test(std::string bincode) noexcept
    {
        for (int i = 0; i < bincode.length(); i++)
        {
            if (bincode[i] != '1' && bincode[i] != '0')
                return false;
        }
        return true;
    }
    std::string reverse(std::string result) noexcept
    {
        std::string NewRes;
        int len = result.length();
        for (int i = len - 1; i >= 0; i--)
            NewRes += result[i];
        return NewRes;
    }
    std::string ToBCD(int num) noexcept
    {
        std::string result;
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
    std::string Excess_3(int num) noexcept
    {
        int NewNum;
        std::string result;
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
    std::string code_2421(int num) noexcept
    {
        std::string result;
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
    std::string code_8421(int num) noexcept
    {
        std::string result;
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
    std::string Gray_code(std::string bincode) noexcept
    {
        size_t binlen = bincode.length();
        std::string resultCode;
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
    std::string ASCII(char ch) noexcept
    {
        int ChNum = ch;
        int result_code = to_binary(ChNum);
        return std::to_string(result_code);
    }
    std::string Error_Detecting_code(std::string bincode, bool evenParity = true) noexcept
    {
        if (!binary_test(bincode))
            return "wrong value in the code.";
        std::string result;
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
    bool AND(bool A, bool B) noexcept
    {
        return (A && B);
    }
    bool OR(bool A, bool B) noexcept
    {
        return (A || B);
    }
    bool NAND(bool A, bool B) noexcept
    {
        if (A == true && B == true)
            return false;
        else
            return true;
    }
    bool NOR(bool A, bool B) noexcept
    {
        return !(A || B);
    }
    bool XOR(bool A, bool B) noexcept
    {
        if ((A == false && B == false) || (A == true && B == true))
            return false;
        else
            return true;
    }
    bool XNOR(bool A, bool B) noexcept
    {
        return !(XOR(A, B));
    }
    std::string HalfAdder(bool A, bool B) noexcept
    {
        return std::to_string(A && B) + std::to_string(XOR(A, B));
    }
    std::string HalfSub(bool A, bool B) noexcept
    {
        return std::to_string(XOR(A, B)) + std::to_string((!A) && B);
    }
    std::string FullAdder(bool A, bool B, bool C) noexcept
    {
        bool sum = XOR(XOR(A, B), C); // Correct Sum calculation
        // Correct Carry Out calculation: (A AND B) OR (C AND (A XOR B))
        bool carry_out = (A && B) || (C && XOR(A, B));
        return std::to_string(sum) + std::to_string(carry_out);
    }
    std::string FullSub(bool A, bool B, bool C) noexcept
    {
        bool diff = XOR(XOR(A, B), C); // Correct Difference calculation
        // Correct Borrow Out calculation: (NOT A AND B) OR (C AND (NOT (A XOR B)))
        bool borrow_out = (!A && B) || (C && !(XOR(A, B)));
        return std::to_string(diff) + std::to_string(borrow_out);
    }
    // 2x4 Decoder
    std::string Decoder2x4(bool A, bool B) noexcept // bool >>> 1 = true || 0 = false
    {
        std::string result = "0000";
        int index = (A << 1) | B; // Convert A and B to an index (0-3)
        result[index] = '1';      // Set the corresponding output to '1'
        return result;
    }
    // 3x8 Decoder
    std::string Decoder3x8(bool A, bool B, bool C) noexcept
    {
        std::string result = "00000000";
        int index = (A << 2) | (B << 1) | C; // Convert A, B, and C to an index (0-7)
        result[index] = '1';                 // Set the corresponding output to '1'
        return result;
    }
    // 4x16 Decoder
    std::string Decoder4x16(bool A, bool B, bool C, bool D) noexcept
    {
        std::string result = "0000000000000000";
        int index = (A << 3) | (B << 2) | (C << 1) | D; // Convert A, B, C, and D to an index (0-15)
        result[index] = '1';                            // Set the corresponding output to '1'
        return result;
    }
    std::string Decoder(std::string binInput)
    {
        if (!binary_test(binInput))
            throw std::invalid_argument("Invalid binary input");
        if (binInput.length() < 1 || binInput.length() > 4)
            throw std::invalid_argument("Input length must be between 1 and 4");
        if (binInput.length() == 2)
            return Decoder2x4(binInput[0] == '1', binInput[1] == '1');
        else if (binInput.length() == 3)
            return Decoder3x8(binInput[0] == '1', binInput[1] == '1', binInput[2] == '1');
        else if (binInput.length() == 4)
            return Decoder4x16(binInput[0] == '1', binInput[1] == '1', binInput[2] == '1', binInput[3] == '1');
        else
            throw std::invalid_argument("Unsupported input length");
    }
    std::string Encoder4x2(std::string input)
    {
        if (input.length() != 4 || !binary_test(input))
            throw std::invalid_argument("Input must be a 4-bit binary string");
        int index = -1;
        for (int i = 0; i < 4; ++i)
        {
            if (input[i] == '1')
            {
                if (index != -1)
                    throw std::invalid_argument("Multiple active inputs detected");
                index = i;
            }
        }
        if (index == -1)
            throw std::invalid_argument("No active input detected");
        return std::to_string((index >> 1) & 1) + std::to_string(index & 1);
    }
    std::string Encoder8x3(std::string input)
    {
        if (input.length() != 8 || !binary_test(input))
            throw std::invalid_argument("Input must be an 8-bit binary string");
        int index = -1;
        for (int i = 0; i < 8; ++i)
        {
            if (input[i] == '1')
            {
                if (index != -1)
                    throw std::invalid_argument("Multiple active inputs detected");
                index = i;
            }
        }
        if (index == -1)
            throw std::invalid_argument("No active input detected");
        return std::to_string((index >> 2) & 1) + std::to_string((index >> 1) & 1) + std::to_string(index & 1);
    }
    std::string Encoder16x4(std::string input)
    {
        if (input.length() != 16 || !binary_test(input))
            throw std::invalid_argument("Input must be a 16-bit binary string");
        int index = -1;
        for (int i = 0; i < 16; ++i)
        {
            if (input[i] == '1')
            {
                if (index != -1)
                    throw std::invalid_argument("Multiple active inputs detected");
                index = i;
            }
        }
        if (index == -1)
            throw std::invalid_argument("No active input detected");
        return std::to_string((index >> 3) & 1) + std::to_string((index >> 2) & 1) + std::to_string((index >> 1) & 1) + std::to_string(index & 1);
    }
    std::string Encoder(std::string binInput)
    {
        if (!binary_test(binInput))
            throw std::invalid_argument("Invalid binary input");
        if (binInput.length() < 2 || binInput.length() > 16)
            throw std::invalid_argument("Input length must be between 2 and 16");
        if (binInput.length() == 4)
            return Encoder4x2(binInput);
        else if (binInput.length() == 8)
            return Encoder8x3(binInput);
        else if (binInput.length() == 16)
            return Encoder16x4(binInput);
        else
            throw std::invalid_argument("Unsupported input length");
    }
    std::string Multiplexer2x1(bool A, bool B, bool sel) // A , B = inputs | sel = select line
    {
        return sel ? std::to_string(B) : std::to_string(A);
    }
    std::string Multiplexer4x1(bool A, bool B, bool C, bool D, bool sel1, bool sel2)
    {
        int index = (sel1 << 1) | sel2; // Convert select lines to an index (0-3)
        switch (index)
        {
        case 0:
            return std::to_string(A);
        case 1:
            return std::to_string(B);
        case 2:
            return std::to_string(C);
        case 3:
            return std::to_string(D);
        default:
            throw std::invalid_argument("Invalid select lines");
        }
    }
    std::string Multiplexer8x1(bool A, bool B, bool C, bool D, bool E, bool F, bool G, bool H, bool sel1, bool sel2, bool sel3)
    {
        int index = (sel1 << 2) | (sel2 << 1) | sel3; // Convert select lines to an index (0-7)
        switch (index)
        {
        case 0:
            return std::to_string(A);
        case 1:
            return std::to_string(B);
        case 2:
            return std::to_string(C);
        case 3:
            return std::to_string(D);
        case 4:
            return std::to_string(E);
        case 5:
            return std::to_string(F);
        case 6:
            return std::to_string(G);
        case 7:
            return std::to_string(H);
        default:
            throw std::invalid_argument("Invalid select lines");
        }
    }
    std::string Multiplexer16x1(bool A, bool B, bool C, bool D, bool E, bool F, bool G, bool H, bool I, bool J, bool K, bool L, bool M, bool N, bool O, bool P, bool sel1, bool sel2, bool sel3, bool sel4)
    {
        int index = (sel1 << 3) | (sel2 << 2) | (sel3 << 1) | sel4; // Convert select lines to an index (0-15)
        switch (index)
        {
        case 0:
            return std::to_string(A);
        case 1:
            return std::to_string(B);
        case 2:
            return std::to_string(C);
        case 3:
            return std::to_string(D);
        case 4:
            return std::to_string(E);
        case 5:
            return std::to_string(F);
        case 6:
            return std::to_string(G);
        case 7:
            return std::to_string(H);
        case 8:
            return std::to_string(I);
        case 9:
            return std::to_string(J);
        case 10:
            return std::to_string(K);
        case 11:
            return std::to_string(L);
        case 12:
            return std::to_string(M);
        case 13:
            return std::to_string(N);
        case 14:
            return std::to_string(O);
        case 15:
            return std::to_string(P);
        default:
            throw std::invalid_argument("Invalid select lines");
        }
    }
    std::string Multiplexer(std::string binInput, std::vector<bool> inputs)
    {
        if (!binary_test(binInput))
            throw std::invalid_argument("Invalid binary input");
        int numSelectLines = binInput.length();
        int numInputs = 1 << numSelectLines; // 2^numSelectLines
        if (inputs.size() != numInputs)
            throw std::invalid_argument("Number of inputs does not match select lines");
        if (numSelectLines == 1)
            return Multiplexer2x1(inputs[0], inputs[1], binInput[0] == '1');
        else if (numSelectLines == 2)
            return Multiplexer4x1(inputs[0], inputs[1], inputs[2], inputs[3], binInput[0] == '1', binInput[1] == '1');
        else if (numSelectLines == 3)
            return Multiplexer8x1(inputs[0], inputs[1], inputs[2], inputs[3], inputs[4], inputs[5], inputs[6], inputs[7], binInput[0] == '1', binInput[1] == '1', binInput[2] == '1');
        else if (numSelectLines == 4)
            return Multiplexer16x1(inputs[0], inputs[1], inputs[2], inputs[3], inputs[4], inputs[5], inputs[6], inputs[7],
                                   inputs[8], inputs[9], inputs[10], inputs[11], inputs[12], inputs[13], inputs[14], inputs[15],
                                   binInput[0] == '1', binInput[1] == '1', binInput[2] == '1', binInput[3] == '1');
        else
            throw std::invalid_argument("Unsupported number of select lines");
    }
};
#endif // OPENMSL___MSL___DLD_HPP