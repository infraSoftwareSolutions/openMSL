#pragma once
#ifndef OPENMSL___MSL___STATICS_HPP
#define OPENMSL___MSL___STATICS_HPP
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <sstream>

/**
 * @file statics.hpp
 * @brief A header file containing static functions and a class for handling Cartesian vectors and forces.
 * This file defines a set of mathematical functions for vector operations, as well as a class `CartesianVector`
 * that encapsulates the properties and operations of Cartesian vectors and forces. The class provides methods for
 * parsing vector strings, calculating resultant magnitudes, angles, and performing arithmetic operations on vectors.
 * The functions and class are designed to be used in the context of engineering statics problems, where forces and vectors
 * are commonly represented in Cartesian form. The code is written in C++23 and follows best practices for exception safety and performance.
 * @note The functions and methods in this file are marked as `noexcept` to indicate that they do not throw exceptions, ensuring strong exception safety guarantees.
 * @author Ali Lafi
 * @date [Date]
 */

namespace msl
{

    const double PI(3.14159);

    constexpr float square(float x) noexcept { return std::pow(x, 2); }
    
    // convert the degrees to radians
    constexpr float toRadians(float degrees) noexcept { return degrees * PI / 180.0; }
    
    // convert the randians to degrees
    constexpr float todegrees(float radians) noexcept { return (radians * 180.0) / PI; }
    
    constexpr float CosineLaw(float A, float B, float angleDegrees) noexcept
    {
        float angleRad = toRadians(angleDegrees);
        return sqrt(square(A) + square(B) - 2 * A * B * cos(angleRad));
    }

    constexpr float SineLawFindSide(float B, float angleA, float angleB) noexcept { return (B * sin(toRadians(angleA))) / sin(toRadians(angleB)); }
    
    constexpr float thataSineLaw(float Fr, float F, float Thata) noexcept { return todegrees(asin((F * sin(toRadians(Thata))) / Fr)); }
    
    /// @brief Class to handle Cartesian Vectors and Forces
    class CartesianVector
    {
    private:
        double x = 0, y = 0, z = 0, F = 0;
        double Ux = 0, Uy = 0, Uz = 0;
        double Fx = 0, Fy = 0, Fz = 0;
        std::string CartesianForce, RVector;
        // Parses a vector string like "3i+4j+5k"
    protected:

        /**
         * @brief Parses a vector string in the format "ai+bj+ck" and extracts the components.
         *
         * This function takes a string representation of a 3D vector in the form "ai+bj+ck"
         * (where a, b, c are numeric values and i, j, k are axis indicators) and extracts
         * the individual components.
         *
         * @param vecStr The input vector string in the format "ai+bj+ck" (e.g., "3.5i+2.1j+1.0k")
         * @param a Output parameter for the i-component (x-axis) of the vector
         * @param b Output parameter for the j-component (y-axis) of the vector
         * @param c Output parameter for the k-component (z-axis) of the vector
         *
         * @throws std::invalid_argument if the string cannot be converted to a double
         * @throws std::out_of_range if the converted value is out of range for double
         *
         * @note This function assumes the input string is well-formed with '+' as delimiter
         *       between components. Invalid or malformed input may lead to undefined behavior.
         *
         * @example
         *   double x, y, z;
         *   parseVector("3.5i+2.1j+1.0k", x, y, z);
         *   // x = 3.5, y = 2.1, z = 1.0
         */
        void parseVector(const std::string &vecStr, double &a, double &b, double &c) noexcept
        {
            std::stringstream ss(vecStr);
            std::string token;
            while (getline(ss, token, '+'))
            {
                double val = stod(token.substr(0, token.length() - 1));
                char axis = token.back();
                if (axis == 'i')
                    a = val;
                else if (axis == 'j')
                    b = val;
                else if (axis == 'k')
                    c = val;
            }
        }

    public:
        /// @brief Default constructor
        CartesianVector() = default;

        /// @brief Constructor for position vector and scalar force
        /// @param rStr the position vector in string form
        /// @param force the scalar force
        CartesianVector(const std::string &rStr, double force) noexcept
        {
            set_RVector(rStr, force);
        }

        /**
         * @brief Constructor for Cartesian force string
         * @param forceStr the Cartesian force in string form
         * @note Example of forceStr: "3i+4j+5k"
         * @throw none exception guarantee: noexcept.
         */
        CartesianVector(const std::string &forceStr) noexcept
        {
            set_CartesianForce(forceStr);
        }

        /**
         * @brief Constructor for Cartesian components and scalar force
         * @param xVal the x component
         * @param yVal the y component
         * @param zVal the z component
         * @param force the scalar force
         * @throw none exception guarantee: noexcept.
         */
        CartesianVector(double xVal, double yVal, double zVal, double force) noexcept
        {
            x = xVal;
            y = yVal;
            z = zVal;
            F = force;
            double R = getResultant();
            Ux = x / R;
            Uy = y / R;
            Uz = z / R;
            Fx = Ux * F;
            Fy = Uy * F;
            Fz = Uz * F;
        }

        /**
         * @brief Copy constructor
         * @param other the other CartesianVector to copy from
         * @throw none exception guarantee: noexcept.
         */
        CartesianVector(const CartesianVector &other) noexcept
        {
            x = other.x;
            y = other.y;
            z = other.z;
            F = other.F;
            Ux = other.Ux;
            Uy = other.Uy;
            Uz = other.Uz;
            Fx = other.Fx;
            Fy = other.Fy;
            Fz = other.Fz;
            CartesianForce = other.CartesianForce;
            RVector = other.RVector;
        }

        /**
         * Set force from Cartesian form: e.g., "3i+4j+5k"
         * @brief Sets the Cartesian force from a string representation.
         * @param forceStr The Cartesian force in string form (e.g., "3i+4j+5k").
         * @note This function parses the input string to extract the force components
         *      along the x, y, and z axes, updates the internal state of the object,
         *     and calculates the unit vector components.
         * @throw none exception guarantee: noexcept.
         */
        constexpr void set_CartesianForce(const std::string &forceStr) noexcept
        {
            CartesianForce = forceStr;
            parseVector(forceStr, Fx, Fy, Fz);
            double R = getResultantForce();
            Ux = Fx / R;
            Uy = Fy / R;
            Uz = Fz / R;
        }

        /**
         * Set position vector and scalar force
         * @brief Sets the position vector and scalar force.
         * @param rStr The position vector in string form (e.g., "3i +4j +5k").
         * @param force The scalar force.
         * @note This function parses the input string to extract the position vector
         */
        constexpr void set_RVector(const std::string &rStr, double force) noexcept
        {
            RVector = rStr;
            F = force;
            parseVector(rStr, x, y, z);
            double R = getResultant();
            Ux = x / R;
            Uy = y / R;
            Uz = z / R;
            Fx = Ux * F;
            Fy = Uy * F;
            Fz = Uz * F;
        }

        /**
         * @brief Get the resultant magnitude of the position vector
         * @return The resultant magnitude of the position vector
         * @throw none exception guarantee: noexcept.
         */
        constexpr double getResultant() const noexcept { return sqrt(x * x + y * y + z * z); }

        /**
         * @brief Get the resultant magnitude of the force vector
         * @return The resultant magnitude of the force vector
         * @throw none exception guarantee: noexcept.
         */
        constexpr double getResultantForce() const noexcept { return sqrt(Fx * Fx + Fy * Fy + Fz * Fz); }

        /**
         * @brief Get the angles between the position vector and the coordinate axes
         * @return A vector containing the angles (in degrees) with respect to the x, y, and z axes
         * @throw none exception guarantee: noexcept.
         */
        constexpr std::vector<double> getAngles() const noexcept
        {
            double R = getResultant();
            return {
                acos(x / R) * 180.0 / PI,
                acos(y / R) * 180.0 / PI,
                acos(z / R) * 180.0 / PI};
        }

        /**
         * @brief Get the Cartesian force as a string
         * @return The Cartesian force in string form
         * @throw none exception guarantee: noexcept.
         */
        constexpr std::string get_CartesianForce() const noexcept { return "(" + std::to_string(Fx) + "i)+(" + std::to_string(Fy) + "j)+(" + std::to_string(Fz) + "k)"; }

        /**
         * @brief Get the unit vector as a string
         * @return The unit vector in string form
         * @throw none exception guarantee: noexcept.
         */
        constexpr std::string get_UnitVector() const noexcept { return "(" + std::to_string(Ux) + "i)+(" + std::to_string(Uy) + "j)+(" + std::to_string(Uz) + "k)"; }

        /**
         * @brief Get the position vector as a string
         * @return The position vector in string form
         * @throw none exception guarantee: noexcept.
         */
        constexpr std::string get_RVector() const noexcept { return "(" + std::to_string(x) + "i)+(" + std::to_string(y) + "j)+(" + std::to_string(z) + "k)"; }

        /**
         * @brief Overloaded arithmetic operators for CartesianVector
         * @note These operators modify the current object in place.
         * @throw none exception guarantee: noexcept.
         */
        void operator+=(const CartesianVector &other) noexcept
        {
            Fx += other.Fx;
            Fy += other.Fy;
            Fz += other.Fz;
            double R = getResultantForce();
            Ux = Fx / R;
            Uy = Fy / R;
            Uz = Fz / R;
            F = R;
        }

        /**
         * @brief Overloaded arithmetic operators for CartesianVector
         * @note These operators modify the current object in place.
         * @throw none exception guarantee: noexcept.
         */
        void operator+=(double scalar) noexcept
        {
            Fx += scalar;
            Fy += scalar;
            Fz += scalar;
            double R = getResultantForce();
            Ux = Fx / R;
            Uy = Fy / R;
            Uz = Fz / R;
            F = R;
        }

        /**
         * @brief Overloaded arithmetic operators for CartesianVector
         * @note These operators modify the current object in place.
         * @throw none exception guarantee: noexcept.
         */
        void operator-=(const CartesianVector &other) noexcept
        {
            Fx -= other.Fx;
            Fy -= other.Fy;
            Fz -= other.Fz;
            double R = getResultantForce();
            Ux = Fx / R;
            Uy = Fy / R;
            Uz = Fz / R;
            F = R;
        }

        /**
         * @brief Overloaded arithmetic operators for CartesianVector
         * @note These operators modify the current object in place.
         * @throw none exception guarantee: noexcept.
         */
        void operator*=(double scalar) noexcept
        {
            Fx *= scalar;
            Fy *= scalar;
            Fz *= scalar;
            double R = getResultantForce();
            Ux = Fx / R;
            Uy = Fy / R;
            Uz = Fz / R;
            F = R;
        }

        /**
         * @brief Overloaded arithmetic operators for CartesianVector
         * @note These operators modify the current object in place.
         * @throw none exception guarantee: noexcept.
         */
        void operator*=(const CartesianVector &other) noexcept
        {
            Fx *= other.Fx;
            Fy *= other.Fy;
            Fz *= other.Fz;
            double R = getResultantForce();
            Ux = Fx / R;
            Uy = Fy / R;
            Uz = Fz / R;
            F = R;
        }

        /**
         * @brief Overloaded arithmetic operators for CartesianVector
         * @note These operators modify the current object in place.
         * @throw none exception guarantee: noexcept.
         */
        void operator/=(double scalar) noexcept
        {
            Fx /= scalar;
            Fy /= scalar;
            Fz /= scalar;
            double R = getResultantForce();
            Ux = Fx / R;
            Uy = Fy / R;
            Uz = Fz / R;
            F = R;
        }

        /**
         * @brief Overloaded arithmetic operators for CartesianVector
         * @note These operators modify the current object in place.
         * @throw none exception guarantee: noexcept.
         */
        void operator/=(const CartesianVector &other) noexcept
        {
            Fx /= other.Fx;
            Fy /= other.Fy;
            Fz /= other.Fz;
            double R = getResultantForce();
            Ux = Fx / R;
            Uy = Fy / R;
            Uz = Fz / R;
            F = R;
        }

        /**
         * @brief Overloaded arithmetic operators for CartesianVector
         * @note These operators modify the current object in place.
         * @throw none exception guarantee: noexcept.
         */
        void operator=(double scalar) noexcept
        {
            Fx = scalar;
            Fy = scalar;
            Fz = scalar;
            double R = getResultantForce();
            Ux = Fx / R;
            Uy = Fy / R;
            Uz = Fz / R;
            F = R;
        }

        /**
         * @brief Overloaded arithmetic operators for CartesianVector
         * @note These operators modify the current object in place.
         * @throw none exception guarantee: noexcept.
         */
        void operator=(const CartesianVector &other) noexcept
        {
            x = other.x;
            y = other.y;
            z = other.z;
            F = other.F;
            Ux = other.Ux;
            Uy = other.Uy;
            Uz = other.Uz;
            Fx = other.Fx;
            Fy = other.Fy;
            Fz = other.Fz;
            CartesianForce = other.CartesianForce;
            RVector = other.RVector;
        }
    };

    /**
     * Moment = Force × Distance
     * @brief Calculate the moment given distance and force
     * @param distance The distance from the pivot point
     * @param force The applied force
     * @return The calculated moment
     * @throw none exception guarantee: noexcept.
     */
    constexpr double Moment(double distance, double force) noexcept { return distance * force; }
}
#endif // OPENMSL___MSL___STATICS_HPP