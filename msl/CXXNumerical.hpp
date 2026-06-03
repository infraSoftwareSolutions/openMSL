#pragma once
#ifndef ELC___CXXETL___CXXUML_CXXNUMERICAL_HPP
#define ELC___CXXETL___CXXUML_CXXNUMERICAL_HPP
#include <CXXETL/CXXLite/CXXIO.hpp>
#include <sstream>
#include <functional>
#include <cmath>
#include <numeric>

/**
 * @file CXXNumerical.hpp
 * @brief This header defines a collection of numerical methods and utilities for root finding, optimization, interpolation, and error analysis.
 * The functions include implementations of the Bisection method, Secant method, False Position method, Newton-Raphson method, Muller's method, Golden Section search, and Newton's method for optimization. Additionally, it provides utilities for calculating errors (absolute and relative) and constructing interpolation polynomials (Newton Divided Difference and Lagrange Interpolating Polynomial).
 * @author Ali Lafi
 * @date 2024-06
 */

#define GR 1.61803 // GR means The Golden Ratio
namespace etl
{

    /**
     * @brief Calculates the Absolute True Error (ATE) between a true value and an approximate value.
     *
     * The Absolute True Error is defined as the absolute difference between the true value and the approximate value.
     *
     * @param TrueValue The actual or true value.
     * @param ApproximateValue The estimated or approximate value.
     * @return The absolute difference between TrueValue and ApproximateValue.
     */
    constexpr float ATE(float TrueValue, float ApproximateValue) noexcept { return abs(TrueValue - ApproximateValue); }

    /**
     * @brief Calculates the Absolute Approximate Error (AAE) between two estimates.
     *
     * This function computes the absolute difference between a new estimate and an old estimate,
     * which is commonly used in numerical methods to assess the convergence of iterative algorithms.
     *
     * @param NewEstimate The current or new estimate value.
     * @param OldEstimate The previous or old estimate value.
     * @return The absolute value of the difference between NewEstimate and OldEstimate.
     */
    constexpr float AAE(float NewEstimate, float OldEstimate) noexcept { return abs(NewEstimate - OldEstimate); }

    /**
     * @brief Calculates the Relative True Error (RTE) between a true value and an approximate value.
     *
     * The Relative True Error is computed as the absolute value of the true error (difference between
     * true and approximate values) divided by the true value.
     *
     * @param TrueValue The actual (true) value.
     * @param ApproximateValue The estimated or approximate value.
     * @return The relative true error as a float.
     */
    constexpr float RTE(float TrueValue, float ApproximateValue) noexcept { return abs(ATE(TrueValue, ApproximateValue) / TrueValue); }

    /**
     * @brief Calculates the Relative Approximate Error (RAE) between two estimates.
     *
     * This function computes the relative error by dividing the absolute approximate error (AAE)
     * by the new estimate. It is commonly used in numerical methods to assess the accuracy of
     * iterative solutions.
     *
     * @param NewEstimate The current (new) estimate value.
     * @param OldEstimate The previous (old) estimate value.
     * @return The relative approximate error as a float.
     */
    constexpr float RAE(float NewEstimate, float OldEstimate) noexcept { return abs(AAE(NewEstimate, OldEstimate) / NewEstimate); }

    /**
     * @brief Calculates the approximate relative error threshold for a given number of significant digits.
     *
     * This function computes the error specification (Es) used in numerical methods to determine
     * the stopping criterion based on the number of significant digits.
     *
     * @param n Number of significant digits.
     * @return The relative error threshold as a float.
     */
    constexpr float Es(int n) noexcept { return (0.5 * pow(10, 2 - n)); }

    /**
     * @brief Computes the square of a floating-point number.
     *
     * This function returns the result of raising the input value to the power of 2.
     *
     * @param x The floating-point number to be squared.
     * @return The square of the input value.
     *
     * @note This function is marked as constexpr and noexcept.
     */
    constexpr float square(float x) noexcept { return pow(x, 2); }

    /**
     * @brief Calculates the roots of a quadratic equation of the form ax^2 + bx + c = 0.
     *
     * This function uses the quadratic formula to find the real roots of the equation.
     * The roots are returned as a std::vector<float> containing two elements.
     * If the discriminant is negative, the results may be NaN due to sqrt of a negative number.
     *
     * @param a Coefficient of x^2.
     * @param b Coefficient of x.
     * @param c Constant term.
     * @return std::vector<float> A vector containing the two roots.
     */
    std::vector<float> QuadEquRoots(float a, float b, float c) noexcept
    {
        std::vector<float> roots;
        roots.push_back((-b + sqrt(square(b) - (4 * a * c))) / (2 * a));
        roots.push_back((-b - sqrt(square(b) - (4 * a * c))) / (2 * a));
        return roots;
    }

    /**
     * @brief Calculates the number of iterations required to achieve a desired precision in a numerical method.
     *
     * This function computes the number of iterations (n) needed to reduce the interval [a, b] to within a specified error tolerance (E),
     * typically used in methods such as the bisection method for root finding.
     *
     * @param a The lower bound of the interval.
     * @param b The upper bound of the interval.
     * @param E The desired error tolerance.
     * @return The number of iterations required to achieve the specified precision.
     */
    constexpr float n(float a, float b, float E) noexcept { return (log(b - a) - log(E)) / log(2); }

    /**
     * @brief Approximates the root of a continuous function using the Bisection method.
     *
     * This method requires that the function f(x) has opposite signs at the two endpoints (Xl and Xu),
     * i.e., f(Xl) * f(Xu) < 0.
     *
     * @param f            A continuous function f(x).
     * @param Xl           The lower bound of the interval.
     * @param Xu           The upper bound of the interval.
     * @param iterations   Maximum number of iterations to perform.
     * @param tolerance    Optional threshold to stop when the interval size or f(Xr) is below this value (default = 1e-5).
     * @param ShowIter     If true, prints each iteration step (default = false).
     * @return float       The approximated root value, or NaN if the input is invalid or method fails.
     */
    float Bisection(std::function<float(float)> f, float Xl, float Xu, int iterations, float tolerance = 1e-5, bool ShowIter = false) noexcept
    {
        if (Xl > Xu)
        {
            io::println_error("Error: Lower bound is greater than upper bound.");
            return NAN;
        }
        float Fx_l = f(Xl);
        float Fx_u = f(Xu);
        if (Fx_l * Fx_u > 0)
        {
            io::println_error("Error: No sign change in the interval. Bisection method may not converge.");
            return NAN;
        }
        float Xr = Xl;
        for (int i = 0; i < iterations; ++i)
        {
            Xr = (Xl + Xu) / 2.0f;
            float Fx_r = f(Xr);
            if (ShowIter)
            {
                std::cout << "Iteration " << (i + 1)
                          << ": Xl = " << Xl
                          << ", Xu = " << Xu
                          << ", Xr = " << Xr
                          << ", f(Xr) = " << Fx_r << std::endl;
            }
            if (fabs(Fx_r) < tolerance || fabs(Xu - Xl) < tolerance)
                break;
            if (Fx_l * Fx_r < 0)
            {
                Xu = Xr;
                Fx_u = Fx_r;
            }
            else
            {
                Xl = Xr;
                Fx_l = Fx_r;
            }
        }
        return Xr;
    }

    /**
     * @brief Approximates the root of a continuous function using the Secant Method.
     *
     * This method uses two initial approximations to iteratively converge to a root.
     * Unlike Bisection, the Secant method does not require the function to have a sign change.
     *
     * @param f            The target function f(x) to find the root for.
     * @param Xi           The most recent approximation (xₙ).
     * @param Xi_1         The previous approximation (xₙ₋₁).
     * @param iterations   The maximum number of iterations to perform.
     * @param tolerance    Optional stopping criterion; stops if |Xi+1 - Xi| < tolerance (default = 1e-5).
     * @param ShowIter     If true, prints each iteration step (default = false).
     * @return float       The estimated root, or the last Xi if convergence fails.
     */
    float SecantMethod(std::function<float(float)> f, float Xi, float Xi_1, int iterations, float tolerance = 1e-5, bool ShowIter = false) noexcept
    {
        float Xi_new;
        for (int i = 0; i < iterations; ++i)
        {
            float Fxi = f(Xi);
            float Fxi_1 = f(Xi_1);
            if (Fxi == Fxi_1)
            {
                io::println_error("Division by zero in Secant Method. (f(Xi) == f(Xi-1))");
                return Xi;
            }
            Xi_new = Xi - Fxi * ((Xi - Xi_1) / (Fxi - Fxi_1));
            if (ShowIter)
            {
                std::cout << "Iteration " << (i + 1)
                          << ": Xi-1 = " << Xi_1
                          << ", Xi = " << Xi
                          << ", Xi+1 = " << Xi_new
                          << ", f(Xi+1) = " << f(Xi_new)
                          << std::endl;
            }
            if (abs(Xi_new - Xi) < tolerance)
                break;
            Xi_1 = Xi;
            Xi = Xi_new;
        }
        return Xi_new;
    }

    /**
     * @brief Approximates the root of a continuous function using the False Position method (Regula Falsi).
     *
     * The method uses linear interpolation to estimate the root between two points where the function changes sign.
     * It stops either after a given number of iterations or if the root estimate change is less than a given tolerance.
     *
     * @param f         A function f(x) whose root is to be found.
     * @param Xl        The lower bound of the interval.
     * @param Xu        The upper bound of the interval.
     * @param iteration Maximum number of iterations to perform.
     * @param ShowIter  Optional: show step-by-step details (default = false).
     * @param tolerance Optional: stop if |Xr - previous Xr| < tolerance (default = 1e-5).
     * @return float    The approximated root value, or -1 if input is invalid.
     */
    float False_Position(std::function<float(float)> f, float Xl, float Xu, int iteration, bool ShowIter = false, float tolerance = 1e-5) noexcept
    {
        float Xr = Xl; // initial guess (just for setup)
        float Xr_old = Xr;
        float Fx_l = f(Xl), Fx_u = f(Xu), Fx_r;
        if (Xl > Xu)
        {
            io::println_error("Error: the lower value is greater than the upper value.");
            return -1;
        }
        for (int i = 0; i < iteration; i++)
        {
            Xr_old = Xr;
            Xr = ((Xu * Fx_l) - (Xl * Fx_u)) / (Fx_l - Fx_u);
            Fx_r = f(Xr);
            if (ShowIter)
            {
                std::cout << "Iteration " << i + 1 << ":\n";
                std::cout << "Xr = " << Xr << "\n";
                std::cout << "Fx_r = " << Fx_r << "\n";
            }
            if (fabs(Xr - Xr_old) < tolerance)
            {
                if (ShowIter)
                {
                    std::cout << "Converged: |Xr - Xr_old| = " << fabs(Xr - Xr_old) << " < " << tolerance << "\n";
                }
                break;
            }
            if ((Fx_l * Fx_r) > 0)
            {
                Xl = Xr;
                Fx_l = Fx_r;
                if (ShowIter)
                {
                    std::cout << "(Xl => Xr) --> Xl = " << Xl << "\n";
                    std::cout << "(Fx_l => Fx_r) --> Fx_l = " << Fx_l << "\n";
                }
            }
            else if ((Fx_l * Fx_r) < 0)
            {
                Xu = Xr;
                Fx_u = Fx_r;
                if (ShowIter)
                {
                    std::cout << "(Xu => Xr) --> Xu = " << Xu << "\n";
                    std::cout << "(Fx_u => Fx_r) --> Fx_u = " << Fx_u << "\n";
                }
            }
            else
            {
                // root found exactly
                break;
            }
        }
        return Xr;
    }

    /**
     * @brief Finds the root of a function using the Newton-Raphson method.
     *
     * Uses the formula: Xi+1 = Xi - f(Xi) / f'(Xi)
     * Iterates until either max iterations or convergence (based on tolerance).
     *
     * @param fx         The function f(x) to solve.
     * @param fd         The derivative f'(x) of the function.
     * @param X_0        The initial guess.
     * @param iteration  Number of iterations to perform.
     * @param ShowIter   Optional: show steps during iterations (default = false).
     * @param tolerance  Optional: stop if |Xi+1 - Xi| < tolerance (default = 1e-5).
     * @return float     The approximated root.
     */
    float Newton_Raphson(std::function<float(float)> fx, std::function<float(float)> fd, float X_0, int iteration, bool ShowIter = false, float tolerance = 1e-5) noexcept
    {
        float Xi_old = X_0, Xi_new;
        for (int i = 0; i < iteration; i++)
        {
            float Fi_old = fx(Xi_old);
            float Fi_d = fd(Xi_old);
            if (Fi_d == 0)
            {
                std::cerr << "Division by zero: f'(x) = 0 at iteration " << i + 1 << std::endl;
                return Xi_old;
            }
            Xi_new = Xi_old - (Fi_old / Fi_d);
            if (ShowIter)
            {
                std::cout << "Iteration " << i + 1 << ":\n";
                std::cout << "f(Xi)   = " << Fi_old << "\n";
                std::cout << "f'(Xi)  = " << Fi_d << "\n";
                std::cout << "Xi+1    = " << Xi_new << "\n";
                std::cout << "--------------------------\n";
            }
            if (fabs(Xi_new - Xi_old) < tolerance)
            {
                if (ShowIter)
                    std::cout << "Converged: |Xi+1 - Xi| = " << fabs(Xi_new - Xi_old) << " < " << tolerance << "\n";
                break;
            }
            Xi_old = Xi_new;
        }
        return Xi_old;
    }

    /**
     * @brief Returns the sign of a number.
     * This function returns:
     *      -1 if the number is negative,
     *      1 if the number is positive,
     *      0 if the number is zero.
     * @param dnum The number to check the sign of.
     * @return short int The sign of the number.
     */
    short int sgn(double dnum) noexcept
    {
        double sgn = dnum * -1;
        if (sgn > 0)
            return -1;
        else if (sgn < 0)
            return 1;
        else
            return 0;
    }

    /**
     * @brief Finds the root of a function using Muller's Method.
     *
     * @param f The function to solve.
     * @param X0 Initial guess point X₀.
     * @param X1 Second guess point X₁.
     * @param X2 Third guess point X₂.
     * @param iterations Maximum number of iterations to perform (default = 20).
     * @param tolerance Convergence threshold to stop iteration early (default = 1e-5).
     * @param ShowIter If true, shows detailed steps of each iteration.
     * @return double Approximated root of the function.
     */
    double MullerMethod(std::function<double(double)> f, double X0, double X1, double X2, int iterations = 20, double tolerance = 1e-5, bool ShowIter = false) noexcept
    {
        double X3 = X2;
        for (int i = 0; i < iterations; i++)
        {
            double H0 = X1 - X0;
            double H1 = X2 - X1;
            double Fx0 = f(X0);
            double Fx1 = f(X1);
            double Fx2 = f(X2);
            double δ0 = (Fx1 - Fx0) / H0;
            double δ1 = (Fx2 - Fx1) / H1;
            double a = (δ1 - δ0) / (H1 + H0);
            double b = a * H1 + δ1;
            double c = Fx2;
            double discriminant = b * b - 4 * a * c;
            if (discriminant < 0)
            {
                std::cerr << "Complex root encountered. Discriminant < 0" << std::endl;
                return NAN;
            }
            double denom = b + copysign(1.0, b) * sqrt(discriminant);
            if (denom == 0)
            {
                std::cerr << "Division by zero encountered in denominator." << std::endl;
                return NAN;
            }
            double dx = -2 * c / denom;
            X3 = X2 + dx;
            if (ShowIter)
            {
                std::cout << "Iteration " << i + 1 << ":" << std::endl;
                std::cout << "  a = " << a << ", b = " << b << ", c = " << c << std::endl;
                std::cout << "  X3 = " << X3 << ", f(X3) = " << f(X3) << std::endl;
            }
            if (fabs(dx) < tolerance || fabs(f(X3)) < tolerance)
                break;
            // Shift points for next iteration
            X0 = X1;
            X1 = X2;
            X2 = X3;
        }
        return X3;
    }

    /**
     * @brief Optimizes a function using the Golden Section Search method.
     *
     * @param f The function to optimize.
     * @param Xl Lower bound of interval.
     * @param Xu Upper bound of interval.
     * @param iterations Maximum number of iterations.
     * @param FindMax If true, finds the maximum; otherwise finds the minimum.
     * @param tolerance Optional threshold for early stopping (default = 1e-5).
     * @param ShowIter If true, shows detailed iteration output (default = false).
     * @return double The approximated extremum point (maximum or minimum).
     */
    double GoldenSection(std::function<double(double)> f, double Xl, double Xu, int iterations, bool FindMax = false, double tolerance = 1e-5, bool ShowIter = false) noexcept
    {
        double X1, X2, Fx1, Fx2;
        for (int i = 0; i < iterations; ++i)
        {
            double d = (GR - 1) * (Xu - Xl);
            X1 = Xl + d;
            X2 = Xu - d;
            Fx1 = f(X1);
            Fx2 = f(X2);
            if (ShowIter)
            {
                std::cout << "Iteration " << i + 1 << ":\n";
                std::cout << "  X1 = " << X1 << ", f(X1) = " << Fx1 << std::endl;
                std::cout << "  X2 = " << X2 << ", f(X2) = " << Fx2 << std::endl;
            }
            if (FindMax)
            {
                if (Fx1 > Fx2)
                    Xl = X2;
                else
                    Xu = X1;
            }
            else
            {
                if (Fx1 < Fx2)
                    Xl = X2;
                else
                    Xu = X1;
            }
            if (fabs(Xu - Xl) < tolerance)
                break;
        }
        double Xopt = (Xu + Xl) / 2.0;
        if (ShowIter)
            std::cout << "Optimal point: " << Xopt << ", f(X) = " << f(Xopt) << std::endl;
        return Xopt;
    }

    /**
     * @brief Finds the local extremum of a function using Newton's Method for optimization.
     *
     * @param f_prime The first derivative of the function.
     * @param f_double_prime The second derivative of the function.
     * @param Xi Initial guess.
     * @param iterations Maximum number of iterations.
     * @param tolerance Convergence threshold (default = 1e-6).
     * @param ShowIter Whether to show iteration details (default = false).
     * @return vector<double> All intermediate Xi values computed during iterations.
     */
    std::vector<double> NewtonsMethod(std::function<double(double)> f_prime, std::function<double(double)> f_double_prime, double Xi, int iterations, double tolerance = 1e-6, bool ShowIter = false) noexcept
    {
        std::vector<double> VecIter;
        double Xi_1;
        for (int i = 0; i < iterations; ++i)
        {
            double FFD = f_prime(Xi);
            double FSD = f_double_prime(Xi);
            if (FSD == 0)
            {
                std::cerr << "Division by zero: second derivative is zero." << std::endl;
                return {-1.0};
            }
            Xi_1 = Xi - (FFD / FSD);
            VecIter.push_back(Xi_1);
            if (ShowIter)
            {
                std::cout << "Iteration " << i + 1 << ":\n";
                std::cout << "  Xi     = " << Xi << "\n";
                std::cout << "  f'(Xi) = " << FFD << "\n";
                std::cout << "  f''(Xi)= " << FSD << "\n";
                std::cout << "  Xi+1   = " << Xi_1 << "\n";
            }
            if (abs(Xi_1 - Xi) < tolerance)
                break;
            Xi = Xi_1;
        }
        return VecIter;
    }

    /**
     * @brief Computes the coefficients of the Newton Divided Difference polynomial.
     * @param X The x-coordinates of the data points.
     * @param Fx The corresponding function values at the x-coordinates.
     * @return vector<double> The coefficients of the Newton Divided Difference polynomial.
     * If input is invalid, returns a vector with a single element -1.0.
     */
    std::vector<double> NDD(std::vector<double> X, std::vector<double> Fx) noexcept
    {
        if (X.empty() || Fx.empty())
            return {-1.0};
        if (X.size() != Fx.size())
            return {-1.0};
        int n = X.size();
        std::vector<std::vector<double>> table(n, std::vector<double>(n));
        for (int i = 0; i < n; i++)
            table[i][0] = Fx[i];
        for (int j = 1; j < n; j++)
        {
            for (int i = 0; i < n - j; i++)
                table[i][j] = (table[i + 1][j - 1] - table[i][j - 1]) / (X[i + j] - X[i]);
        }
        std::vector<double> Result;
        for (int j = 0; j < n; j++)
            Result.push_back(table[0][j]);
        return Result;
    }

    /**
     * @brief Computes the Newton Divided Difference polynomial for a function f at given x-coordinates.
     * @param X The x-coordinates of the data points.
     * @param f The function for which the polynomial is computed.
     * @return vector<double> The coefficients of the Newton Divided Difference polynomial.
     * If input is invalid, returns a vector with a single element -1.0.
     */
    std::vector<double> NDD(std::vector<double> X, std::function<double(double)> f) noexcept
    {
        if (X.empty())
            return {-1.0};
        int n = X.size();
        std::vector<double> Fx(n);
        for (int i = 0; i < n; i++)
            Fx[i] = f(X[i]);
        return NDD(X, Fx);
    }

    /**
     * @brief Computes the Lagrange Interpolating Polynomial (LIP) for given x-coordinates and function values.
     * @param X The x-coordinates of the data points.
     * @param Fx The corresponding function values at the x-coordinates.
     * @return string The Lagrange polynomial in string format.
     * If input is invalid, returns an error message.
     */
    std::string LIP(std::vector<double> X, std::vector<double> Fx) noexcept
    {
        if (X.empty() || Fx.empty() || X.size() != Fx.size())
            return "Error: Invalid input";
        std::stringstream equation;
        int n = X.size();
        for (int i = 0; i < n; i++)
        {
            double Li = 1.0;
            for (int j = 0; j < n; j++)
            {
                if (i != j)
                    Li *= (0 - X[j]) / (X[i] - X[j]);
            }
            Li *= Fx[i];
            // Format each term of the polynomial
            if (Li >= 0 && i > 0)
                equation << "+";
            equation << Li;
            if (Li != 0)
                equation << "*x^" << i;
        }
        return equation.str();
    }

    /**
     * @brief Computes the Lagrange Interpolating Polynomial (LIP) for given x-coordinates and a function.
     * @param X The x-coordinates of the data points.
     * @param f The function for which the polynomial is computed.
     * @return string The Lagrange polynomial in string format.
     * If input is invalid, returns an error message.
     */
    std::string LIP(std::vector<double> X, std::function<double(double)> f) noexcept
    {
        if (X.empty())
            return "Error: Invalid input";
        std::vector<double> Fx(X.size());
        for (int i = 0; i < X.size(); i++)
            Fx[i] = f(X[i]);
        return LIP(X, Fx);
    }

    // Forward Finite Divided Difference Formulas
    template <bool function_based>
    class FFDD
    {
    private:
        std::conditional_t<function_based, std::function<double(double)>, std::vector<double>> Fx;
        double h = 0;

    public:
        /**
         * @brief Sets the function values and interval for finite difference calculations.
         * @param F A vector of function values or a function, depending on the template parameter
         * @param H The interval (step size) between data points.
         * @note If function_based is true, F should be a function; otherwise, it should be a vector of values.
         * @note The interval H must be positive.
         * @throws std::invalid_argument if H is not positive or if function_based is true and F is not a function.
         */
        void set_value(std::vector<double> F, double H) noexcept
        {
            if (H <= 0)
            {
                io::println_error("Interval must be positive");
                return;
            }
            Fx = F;
            h = H;
        }

        /**
         * @brief Sets the function and interval for finite difference calculations.
         * @param F A function representing the function values.
         * @param H The interval (step size) between data points.
         * @note If function_based is false, this method will print an error message.
         * @note The interval H must be positive.
         * @throws std::invalid_argument if H is not positive or if function_based is false.
         */
        void set_value(std::function<double(double)> F, double H) noexcept
        {
            if (!function_based)
            {
                io::println_error("Function-based mode is not enabled");
                return;
            }
            if (H <= 0)
            {
                io::println_error("Interval must be positive");
                return;
            }
            Fx = F;
            h = H;
        }

        /**
         * @brief Computes the first derivative using forward finite difference.
         * @param i The index at which to compute the derivative (default is 0).
         * @return The first derivative at index i, or -1.0 if an error occurs.
         * @note If function_based is true, the derivative is computed using the function; otherwise, it uses the stored values.
         * @note The interval h must be positive, and the index i must be within valid range.
         * @throws std::invalid_argument if h is not positive or if index i is out of range.
         */
        double FirDer(int i = 0) noexcept
        {
            if (h <= 0 && !function_based)
            {
                io::println_error("The interval is zero or negative");
                return -1.0;
            }
            if (Fx.empty() && !function_based)
            {
                io::println_error("Values must be set before computing the first derivative");
                return -1.0;
            }
            if (i + 1 >= Fx.size() && !function_based)
            {
                io::println_error("Index out of range for first derivative");
                return -1.0;
            }
            if (function_based)
            {
                if (i < 0)
                {
                    io::println_error("Index cannot be negative for function-based derivative");
                    return -1.0;
                }
                // Use the function to compute the first derivative
                double x = (i == 0) ? 0 : i * h; // Assuming h is the step size
                return (Fx(x + h) - Fx(x)) / h;
            }
            return (Fx[i + 1] - Fx[i]) / h;
        }

        /**
         * @brief Computes the second derivative using forward finite difference.
         * @param i The index at which to compute the derivative (default is 0).
         * @return The second derivative at index i, or -1.0 if an error occurs.
         * @note If function_based is true, the derivative is computed using the function; otherwise, it uses the stored values.
         * @note The interval h must be positive, and the index i must be within valid range.
         * @throws std::invalid_argument if h is not positive or if index i is out of range.
         */
        double SecDer(int i = 0) noexcept
        {
            if (h <= 0)
            {
                io::println_error("The interval is zero or negative");
                return -1.0;
            }
            if (Fx.empty())
            {
                io::println_error("Values must be set before computing the second derivative");
                return -1.0;
            }
            if (i + 2 >= Fx.size())
            {
                io::println_error("Index out of range for second derivative");
                return -1.0;
            }
            if (function_based)
            {
                if (i < 0)
                {
                    io::println_error("Index cannot be negative for function-based derivative");
                    return -1.0;
                }
                // Use the function to compute the second derivative
                double x = (i == 0) ? 0 : i * h; // Assuming h is the step size
                return (Fx(x + 2 * h) - 2 * Fx(x + h) + Fx(x)) / pow(h, 2);
            }
            return (Fx[i + 2] - 2 * Fx[i + 1] + Fx[i]) / pow(h, 2);
        }

        /**
         * @brief Computes the third derivative using forward finite difference.
         * @param i The index at which to compute the derivative (default is 0).
         * @return The third derivative at index i, or -1.0 if an error occurs.
         * @note If function_based is true, the derivative is computed using the function; otherwise, it uses the stored values.
         * @note The interval h must be positive, and the index i must be within valid range.
         * @throws std::invalid_argument if h is not positive or if index i is out of range.
         */
        double ThiDer(int i = 0) noexcept
        {
            if (h <= 0)
            {
                io::println_error("The interval is zero or negative");
                return -1.0;
            }
            if (Fx.empty())
            {
                io::println_error("Values must be set before computing the third derivative");
                return -1.0;
            }
            if (i + 3 >= Fx.size())
            {
                io::println_error("Index out of range for third derivative");
                return -1.0;
            }
            if (function_based)
            {
                if (i < 0)
                {
                    io::println_error("Index cannot be negative for function-based derivative");
                    return -1.0;
                }
                // Use the function to compute the third derivative
                double x = (i == 0) ? 0 : i * h; // Assuming h is the step size
                return (Fx(x + 3 * h) - 3 * Fx(x + 2 * h) + 3 * Fx(x + h) - Fx(x)) / pow(h, 3);
            }
            return (Fx[i + 3] - 3 * Fx[i + 2] + 3 * Fx[i + 1] - Fx[i]) / pow(h, 3);
        }
    };

    // Backward Finite Divided Difference Formulas
    template <bool function_based>
    class BFDD
    {
    private:
        std::conditional_t<function_based, std::function<double(double)>, std::vector<double>> Fx;
        double h = 0;

    public:
        /**
         * @brief Sets the function values and interval for finite difference calculations.
         * @param F A vector of function values or a function, depending on the template parameter
         * @param H The interval (step size) between data points.\
         * @note If function_based is true, F should be a function; otherwise, it should be a vector of values.
         * @note The interval H must be positive.
         * @throws std::invalid_argument if H is not positive or if function_based is true and F is not a function.
         */
        void set_value(std::vector<double> F, double H) noexcept
        {
            if (H <= 0)
            {
                io::println_error("Interval must be positive");
                return;
            }
            Fx = F;
            h = H;
        }

        /**
         * @brief Sets the function and interval for finite difference calculations.
         * @param F A function representing the function values.
         * @param H The interval (step size) between data points.
         * @note If function_based is false, this method will print an error message.
         * @note The interval H must be positive.
         * @throws std::invalid_argument if H is not positive or if function_based is false.
         */
        void set_value(std::function<double(double)> F, double H) noexcept
        {
            if (!function_based)
            {
                io::println_error("Function-based mode is not enabled");
                return;
            }
            if (H <= 0)
            {
                io::println_error("Interval must be positive");
                return;
            }
            Fx = F;
            h = H;
        }

        /**
         * @brief Computes the first derivative using backward finite difference.
         * @param i The index at which to compute the derivative (default is 0).
         * @return The first derivative at index i, or -1.0 if an error occurs.
         * @note If function_based is true, the derivative is computed using the function; otherwise, it uses the stored values.
         * @note The interval h must be positive, and the index i must be within valid range.
         * @throws std::invalid_argument if h is not positive or if index i is out of range.
         */
        double FirDer(int i = 0) noexcept
        {
            if (h <= 0)
            {
                io::println_error("The interval is zero or negative");
                return -1.0;
            }
            if (Fx.empty())
            {
                io::println_error("Values must be set before computing the first derivative");
                return -1.0;
            }
            if (i - 1 < 0)
            {
                io::println_error("Index out of range for first derivative");
                return -1.0;
            }
            if (function_based)
            {
                if (i < 0)
                {
                    io::println_error("Index cannot be negative for function-based derivative");
                    return -1.0;
                }
                // Use the function to compute the first derivative
                double x = (i == 0) ? 0 : i * h; // Assuming h is the step size
                return (Fx(x) - Fx(x - h)) / h;
            }
            return (Fx[i] - Fx[i - 1]) / h;
        }

        /**
         * @brief Computes the second derivative using backward finite difference.
         * @param i The index at which to compute the derivative (default is 0).
         * @return The second derivative at index i, or -1.0 if an error occurs.
         * @note If function_based is true, the derivative is computed using the function; otherwise, it uses the stored values.
         * @note The interval h must be positive, and the index i must be within valid range.
         * @throws std::invalid_argument if h is not positive or if index i is out of range.
         */
        double SecDer(int i = 0) noexcept
        {
            if (h <= 0)
            {
                io::println_error("The interval is zero or negative");
                return -1.0;
            }
            if (Fx.empty())
            {
                io::println_error("Values must be set before computing the second derivative");
                return -1.0;
            }
            if (i - 2 < 0)
            {
                io::println_error("Index out of range for second derivative");
                return -1.0;
            }
            if (function_based)
            {
                if (i < 0)
                {
                    io::println_error("Index cannot be negative for function-based derivative");
                    return -1.0;
                }
                // Use the function to compute the second derivative
                double x = (i == 0) ? 0 : i * h; // Assuming h is the step size
                return (Fx(x) - 2 * Fx(x - h) + Fx(x - 2 * h)) / pow(h, 2);
            }
            return (Fx[i] - 2 * Fx[i - 1] + Fx[i - 2]) / pow(h, 2);
        }

        /**
         * @brief Computes the third derivative using backward finite difference.
         * @param i The index at which to compute the derivative (default is 0).
         * @return The third derivative at index i, or -1.0 if an error occurs.
         * @note If function_based is true, the derivative is computed using the function; otherwise, it uses the stored values.
         * @note The interval h must be positive, and the index i must be within valid range.
         * @throws std::invalid_argument if h is not positive or if index i is out of range.
         */
        double ThiDer(int i = 0) noexcept
        {
            if (h <= 0)
            {
                io::println_error("The interval is zero or negative");
                return -1.0;
            }
            if (Fx.empty())
            {
                io::println_error("Values must be set before computing the third derivative");
                return -1.0;
            }
            if (i - 3 < 0)
            {
                io::println_error("Index out of range for third derivative");
                return -1.0;
            }
            if (function_based)
            {
                if (i < 0)
                {
                    io::println_error("Index cannot be negative for function-based derivative");
                    return -1.0;
                }
                // Use the function to compute the third derivative
                double x = (i == 0) ? 0 : i * h; // Assuming h is the step size
                return (Fx(x) - 3 * Fx(x - h) + 3 * Fx(x - 2 * h) - Fx(x - 3 * h)) / pow(h, 3);
            }
            return (Fx[i] - 3 * Fx[i - 1] + 3 * Fx[i - 2] - Fx[i - 3]) / pow(h, 3);
        }
    };

    // Centered Finite Divided Difference Formulas
    template <bool function_based>
    class CFDD
    {
    private:
        std::conditional_t<function_based, std::function<double(double)>, std::vector<double>> Fx;
        double h = 0;

    public:
        /**
         * @brief Sets the function values and interval for finite difference calculations.
         * @param F A vector of function values or a function, depending on the template parameter
         * @param H The interval (step size) between data points.
         * @note If function_based is true, F should be a function; otherwise, it should be a vector of values.
         * @note The interval H must be positive.
         * @throws std::invalid_argument if H is not positive or if function_based is true and F is not a function.
         */
        void set_value(std::vector<double> F, double H) noexcept
        {
            if (H <= 0)
            {
                io::println_error("Interval must be positive");
                return;
            }
            Fx = F;
            h = H;
        }

        /**
         * @brief Sets the function and interval for finite difference calculations.
         * @param F A function representing the function values.
         * @param H The interval (step size) between data points.
         * @note If function_based is false, this method will print an error message.
         * @note The interval H must be positive.
         * @throws std::invalid_argument if H is not positive or if function_based is false.
         */
        void set_value(std::function<double(double)> F, double H) noexcept
        {
            if (!function_based)
            {
                io::println_error("Function-based mode is not enabled");
                return;
            }
            if (H <= 0)
            {
                io::println_error("Interval must be positive");
                return;
            }
            Fx = F;
            h = H;
        }

        /**
         * @brief Computes the first derivative using centered finite difference.
         * @param i The index at which to compute the derivative (default is 0).
         * @return The first derivative at index i, or -1.0 if an error occurs.
         * @note If function_based is true, the derivative is computed using the function; otherwise, it uses the stored values.
         * @note The interval h must be positive, and the index i must be within valid range.
         * @throws std::invalid_argument if h is not positive or if index i is out of range.
         */
        double FirDer(int i = 0) noexcept
        {
            if (h <= 0)
            {
                io::println_error("The interval is zero or negative");
                return -1.0;
            }
            if (Fx.empty())
            {
                io::println_error("Values must be set before computing the first derivative");
                return -1.0;
            }
            if (i - 1 < 0 || i + 1 >= Fx.size())
            {
                io::println_error("Index out of range for first derivative");
                return -1.0;
            }
            if (function_based)
            {
                if (i < 0)
                {
                    io::println_error("Index cannot be negative for function-based derivative");
                    return -1.0;
                }
                // Use the function to compute the first derivative
                double x = (i == 0) ? 0 : i * h; // Assuming h is the step size
                return (Fx(x + h) - Fx(x - h)) / (2 * h);
            }
            return (Fx[i + 1] - Fx[i - 1]) / (2 * h);
        }

        /**
         * @brief Computes the second derivative using centered finite difference.
         * @param i The index at which to compute the derivative (default is 0).
         * @return The second derivative at index i, or -1.0 if an error occurs.
         * @note If function_based is true, the derivative is computed using the function; otherwise, it uses the stored values.
         * @note The interval h must be positive, and the index i must be within valid range.
         * @throws std::invalid_argument if h is not positive or if index i is out of range.
         */
        double SecDer(int i = 0) noexcept
        {
            if (h <= 0)
            {
                io::println_error("The interval is zero or negative");
                return -1.0;
            }
            if (Fx.empty())
            {
                io::println_error("Values must be set before computing the second derivative");
                return -1.0;
            }
            if (i - 1 < 0 || i + 1 >= Fx.size())
            {
                io::println_error("Index out of range for second derivative");
                return -1.0;
            }
            if (function_based)
            {
                if (i < 0)
                {
                    io::println_error("Index cannot be negative for function-based derivative");
                    return -1.0;
                }
                // Use the function to compute the second derivative
                double x = (i == 0) ? 0 : i * h; // Assuming h is the step size
                return (Fx(x + h) - 2 * Fx(x) + Fx(x - h)) / pow(h, 2);
            }
            return (Fx[i + 1] - 2 * Fx[i] + Fx[i - 1]) / pow(h, 2);
        }

        /**
         * @brief Computes the third derivative using centered finite difference.
         * @param i The index at which to compute the derivative (default is 0).
         * @return The third derivative at index i, or -1.0 if an error occurs.
         * @note If function_based is true, the derivative is computed using the function; otherwise, it uses the stored values.
         * @note The interval h must be positive, and the index i must be within valid range.
         * @throws std::invalid_argument if h is not positive or if index i is out of range.
         */
        double ThiDer(int i = 0) noexcept
        {
            if (h <= 0)
            {
                io::println_error("The interval is zero or negative");
                return -1.0;
            }
            if (Fx.empty())
            {
                io::println_error("Values must be set before computing the third derivative");
                return -1.0;
            }
            if (i - 2 < 0 || i + 2 >= Fx.size())
            {
                io::println_error("Index out of range for third derivative");
                return -1.0;
            }
            if (function_based)
            {
                if (i < 0)
                {
                    io::println_error("Index cannot be negative for function-based derivative");
                    return -1.0;
                }
                // Use the function to compute the third derivative
                double x = (i == 0) ? 0 : i * h; // Assuming h is the step size
                return (Fx(x) - 3 * Fx(x - h) + 3 * Fx(x - 2 * h) - Fx(x - 3 * h)) / pow(h, 3);
            }
            return (Fx[i + 2] - 3 * Fx[i + 1] + 3 * Fx[i - 1] - Fx[i - 2]) / pow(h, 3);
        }
    };

    /**
     * @brief Calculates the definite integral approximation using the Trapezoidal Rule.
     *
     * This function computes the area under a curve between two points `a` and `b`
     * using the Trapezoidal Rule, given the function values at those points (`Fa` and `Fb`).
     *
     * @param b Upper limit of integration.
     * @param a Lower limit of integration.
     * @param Fb Function value at upper limit (`f(b)`).
     * @param Fa Function value at lower limit (`f(a)`).
     * @return Approximated integral value between `a` and `b`.
     */
    double TrapRule(double b, double a, double Fb, double Fa) noexcept
    {
        return ((b - a) * (Fa + Fb)) / 2;
    }

    /**
     * @brief Approximates the definite integral of a function using the trapezoidal rule.
     *
     * This overload computes the integral of the function `fx` from `a` to `b`
     * by evaluating the function at the endpoints and delegating to another
     * TrapRule implementation.
     *
     * @param b Upper limit of integration.
     * @param a Lower limit of integration.
     * @param fx Function to integrate, taking a double and returning a double.
     * @return Approximated value of the definite integral over [a, b].
     */
    double TrapRule(double b, double a, std::function<double(double)> fx) noexcept
    {
        return TrapRule(b, a, fx(b), fx(a));
    }

    /**
     * @brief Approximates the definite integral of a function using the multiple application trapezoidal rule.
     *
     * This function numerically integrates a function over the interval [a, b] using the trapezoidal rule,
     * given a vector of function values Fx at equally spaced points. The interval is divided into n subintervals.
     *
     * @param b The upper limit of integration.
     * @param a The lower limit of integration.
     * @param Fx A vector containing the function values at each point (size should be n+1).
     * @param n The number of subintervals (must be positive and Fx.size() == n+1).
     * @return The approximate value of the definite integral, or -1.0 if Fx is empty.
     *
     * @note The function assumes that Fx contains the function values at points a, a+h, ..., b,
     *       where h = (b - a) / n.
     * @note If Fx is empty, an error message is printed and -1.0 is returned.
     */
    double MulAppTrapRule(double b, double a, std::vector<double> Fx, int n) noexcept
    {
        if (Fx.empty())
        {
            io::println_error("the vector passed to the function is empty");
            return -1.0;
        }
        double h = (b - a) / n;
        double sum = 0;
        for (int i = 1; i < n; i++)
            sum += Fx[i];
        return (h / 2) * (Fx[0] + 2 * sum + Fx[n]);
    }

    /**
     * @brief Approximates the definite integral of a function using the composite trapezoidal rule.
     *
     * This function numerically integrates the function `fx` over the interval [a, b]
     * by dividing it into `n` sub-intervals and applying the composite trapezoidal rule.
     *
     * @param b The upper limit of integration.
     * @param a The lower limit of integration.
     * @param fx The function to integrate, provided as a callable object.
     * @param n The number of sub-intervals (must be positive).
     * @return The approximate value of the definite integral, or -1.0 if `n` is not positive.
     */
    double MulAppTrapRule(double b, double a, std::function<double(double)> fx, int n) noexcept
    {
        if (n <= 0)
        {
            io::println_error("the number of sub-intervals must be positive");
            return -1.0;
        }
        std::vector<double> Fx(n + 1);
        double h = (b - a) / n;
        for (int i = 0; i <= n; i++)
            Fx[i] = fx(a + i * h);
        return MulAppTrapRule(b, a, Fx, n);
    }

    /**
     * @brief Approximates the definite integral of a function using Simpson's 3-point rule.
     *
     * This function applies Simpson's rule to estimate the integral of a function
     * over the interval [a, b] using three function values provided in the vector Fx.
     *
     * @param b The upper limit of integration.
     * @param a The lower limit of integration.
     * @param Fx A vector containing three function values: f(a), f((a+b)/2), and f(b).
     *           The vector must have exactly three elements.
     * @return The approximate value of the integral, or -1.0 if the input vector is empty or has an incompatible size.
     */
    double Simpson3Rule(double b, double a, std::vector<double> Fx) noexcept
    {
        if (Fx.empty())
        {
            io::println_error("the vector past to the function is empty");
            return -1.0;
        }
        if (Fx.size() != 3)
        {
            io::println_error("the size of the vector is incompatible");
            return -1.0;
        }
        double h = b - a;
        return (h / 3) * (Fx[0] + 4 * Fx[1] + Fx[2]);
    }

    /**
     * @brief Approximates the definite integral of a function using Simpson's 1/3 Rule.
     *
     * This function computes the integral of the provided function `fx` over the interval [a, b]
     * using Simpson's 1/3 Rule, which requires evaluating the function at the endpoints and the midpoint.
     *
     * @param b The upper limit of integration.
     * @param a The lower limit of integration.
     * @param fx The function to integrate, provided as a std::function<double(double)>.
     * @return The approximate value of the definite integral over [a, b].
     */
    double Simpson3Rule(double b, double a, std::function<double(double)> fx) noexcept
    {
        return Simpson3Rule(b, a, {fx(a), fx((a + b) / 2), fx(b)});
    }

    /**
     * @brief Approximates the definite integral of a function using Simpson's 3/8 rule.
     *
     * This function applies Simpson's 3/8 rule to estimate the integral of a function
     * over the interval [a, b], given four function values at equally spaced points.
     *
     * @param b The upper limit of integration.
     * @param a The lower limit of integration.
     * @param Fx A vector containing four function values at equally spaced points in [a, b].
     *           Fx[0] = f(a), Fx[1] = f(a + h), Fx[2] = f(a + 2h), Fx[3] = f(b), where h = (b - a) / 3.
     * @return The estimated value of the integral using Simpson's 3/8 rule.
     *         Returns -1.0 if the input vector is empty or its size is not 4.
     */
    double Simpson8Rule(double b, double a, std::vector<double> Fx) noexcept
    {
        if (Fx.empty())
        {
            io::println_error("the vector past to the function is empty");
            return -1.0;
        }
        if (Fx.size() != 4)
        {
            io::println_error("the size of the vector is incompatible");
            return -1.0;
        }
        double h = b - a;
        return (3 * h / 8) * (Fx[0] + 3 * Fx[1] + 3 * Fx[2] + Fx[3]);
    }

    /**
     * @brief Computes Simpson's 3/8 rule for a given function over an interval.
     *
     * This function evaluates Simpson's 3/8 rule using a provided function over the interval [a, b].
     *
     * @param b The upper limit of integration.
     * @param a The lower limit of integration.
     * @param fx The function to integrate, provided as a std::function<double(double)>.
     * @return The approximate value of the integral using Simpson's 3/8 rule.
     */
    double simpson8Rule(double b, double a, std::function<double(double)> fx) noexcept
    {
        return Simpson8Rule(b, a, {fx(a), fx(a + (b - a) / 3), fx(a + 2 * (b - a) / 3), fx(b)});
    }

    /**
     * @brief Computes the Romberg extrapolation for numerical integration.
     *
     * This function applies Romberg's method to a given vector of numerical approximations
     * (typically trapezoidal rule results) to improve the accuracy of the integral estimate.
     *
     * @param Ro A vector of double values representing initial approximations (e.g., trapezoidal estimates).
     * @param Order The order of Romberg extrapolation to perform (number of refinement steps).
     * @return The Romberg extrapolated value of the integral. Returns -1.0 if the input vector is empty.
     *
     * @note The function assumes that the input vector Ro contains enough elements for the specified Order.
     *       If Ro.size() <= Order, the function may result in undefined behavior.
     * @exception Prints an error message if the input vector is empty.
     */
    double RombergMethod(std::vector<double> Ro, int Order) noexcept
    {
        if (Ro.empty())
        {
            io::println_error("the vector passed to the function is empty");
            return -1.0;
        }
        std::vector<std::vector<double>> R;
        R.push_back(Ro);
        for (int i = 1; i <= Order; i++)
        {
            std::vector<double> row;
            for (int j = 0; j < Ro.size() - i; j++)
            {
                double val = (pow(4, i) * R[i - 1][j + 1] - R[i - 1][j]) / (pow(4, i) - 1);
                row.push_back(val);
            }
            R.push_back(row);
        }
        return R[Order][0];
    }

    /**
     * @brief Computes the Romberg extrapolation for a given function over an interval.
     *
     * This function applies Romberg's method to a given function over the interval [a, b].
     *
     * @param fx The function to integrate, provided as a std::function<double(double)>.
     * @param Order The order of Romberg extrapolation to perform (number of refinement steps).
     * @return The Romberg extrapolated value of the integral. Returns -1.0 if the input is invalid.
     */
    double RombergMethod(std::function<double(double)> fx, int Order) noexcept
    {
        return RombergMethod({TrapRule(1.0, 0.0, fx), TrapRule(1.0, 0.0, fx) / 2 + TrapRule(1.0, 0.5, fx) / 2}, Order);
    }

    /**
     * @brief Solves an ordinary differential equation (ODE) using the Euler method.
     *
     * Approximates the solution to the initial value problem dy/dx = f(x, y) with y(x0) = y0
     * over the interval [x0, xn] using n steps.
     *
     * @param f  The function representing dy/dx = f(x, y).
     * @param x0 The initial value of x.
     * @param y0 The initial value of y.
     * @param xn The final value of x.
     * @param n  The number of steps to use in the approximation (must be > 0).
     * @return   A vector of pairs (x, y) representing the approximate solution at each step.
     *           Returns an empty vector if input parameters are invalid.
     *
     * @note This function is noexcept and does not throw exceptions.
     */
    std::vector<std::pair<double, double>> EulerMethod(std::function<double(double, double)> f, double x0, double y0, double xn, int n) noexcept
    {
        // Input validation
        if (n <= 0 || xn <= x0)
        {
            io::println_error("Error: Invalid input parameters");
            return {};
        }
        // Calculate step size
        double h = (xn - x0) / n;
        // Result vector to store (x, y) points
        std::vector<std::pair<double, double>> solution;
        // Initial point
        double x = x0;
        double y = y0;
        solution.push_back({x, y});
        // Euler method iteration
        for (int i = 1; i <= n; i++)
        {
            // y(i+1) = y(i) + h * f(x(i), y(i))
            y = y + h * f(x, y);
            x = x0 + i * h;
            solution.push_back({x, y});
        }
        return solution;
    }
}
#endif // ELC_CXX___CXXLHF___CXXUML_CXXNUMERICAL_HPP