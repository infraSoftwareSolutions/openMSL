#pragma once
#ifndef OPENMSL___MSL___PID_HPP
#define OPENMSL___MSL___PID_HPP
#include "udt/core/bfs.hpp"
#include "numerical.hpp"
#include <map>
#include <vector>
#include <functional>

/**
 * @file PID.hpp
 * @brief This file contains the implementation of the P, I, and D controllers, as well as a block controller that can combine them in series or parallel.
 * The P_controller class implements a proportional controller, the I_controller class implements an integral controller, and the D_controller class implements a derivative controller. Each controller has methods to set its parameters, compute its output based on an input function, and store the output values over time. The block_controller class can combine the three controllers in different configurations based on a state form represented by a BFS_16 object.
 * The controllers use the numerical library for numerical integration and differentiation, and they store their output values in a map for later retrieval. The classes also include operator overloads for assignment and comparison, as well as methods to reset their parameters and output values.
 * @author Ali Lafi
 * @date 2024-06
 */

namespace msl
{
    class P_controller;
    class I_controller;
    class D_controller;
    
    class P_controller
    {
    private:
        double kp = 0.0;
        double setpoint = 0.0;
        std::function<double(double)> input_function;
        std::map<double, double> output_values;

    public:
        P_controller() noexcept : 
        kp(0.0),
        setpoint(0.0),
        input_function(nullptr) {}
        
        P_controller(const P_controller &other) noexcept : 
        kp(other.kp),
        setpoint(other.setpoint),
        input_function(other.input_function),
        output_values(other.output_values) {}
        
        P_controller(double Kp, double Setpoint,
        std::function<double(double)> InputFunction) noexcept : 
        kp(Kp), 
        setpoint(Setpoint),
        input_function(InputFunction) {}
        
        inline void reset() noexcept
        {
            kp = 0.0;
            setpoint = 0.0;
            input_function = nullptr;
            output_values.clear();
        }
        
        inline void reset_input_function(std::function<double(double)> InputFunction) noexcept { input_function = InputFunction; }
        
        inline void reset_kp(double Kp) noexcept { kp = Kp; }

        inline void reset_setpoint(double Setpoint) noexcept { setpoint = Setpoint; }
        
        inline void set(
            double Kp, 
            double Setpoint,
            std::function<double(double)> InputFunction) noexcept
        {
            kp = Kp;
            setpoint = Setpoint;
            input_function = InputFunction;
        }
        
        inline constexpr double get_kp() const noexcept { return kp; }
        
        inline constexpr double get_setpoint() const noexcept { return setpoint; }

        inline std::function<double(double)> get_input_function() const noexcept { return input_function; }
        
        inline double compute(double time) noexcept
        {
            double input = input_function(time);
            output_values[time] = kp * (setpoint - input);
            return kp * (setpoint - input);
        }

        inline void compute_over_time(
            double start_time,
            double end_time,
            double time_step) noexcept
        {
            for (double t = start_time; t <= end_time; t += time_step)
            {
                compute(t);
            }
        }

        inline const std::map<double, double> &get_output_values() const noexcept { return output_values; }
        
        inline bool is_empty() const noexcept
        {
            return (kp == 0.0) &&
                   (setpoint == 0.0) &&
                   (input_function == nullptr) &&
                   (output_values.empty());
        }
        
        inline bool operator!=(const P_controller &other) noexcept { return !(*this == other); }
        
        inline void operator=(std::function<double(double)> InputFunction) noexcept { input_function = InputFunction; }
        
        inline void operator=(const P_controller &other) noexcept
        {
            if (this != &other)
            {
                kp = other.kp;
                setpoint = other.setpoint;
                input_function = other.input_function;
                output_values = other.output_values;
            }
        }

        inline bool operator==(const P_controller &other) noexcept
        {
            return (kp == other.kp) &&
                   (setpoint == other.setpoint) &&
                   (input_function.target_type() == other.input_function.target_type()) &&
                   (output_values == other.output_values);
        }
        
        inline void operator<<(const I_controller &other) noexcept
        {
            kp = other.get_ki();
            setpoint = other.get_setpoint();
            input_function = other.get_input_function();
            output_values = other.get_output_values();
        }
        
        inline void operator<<(const D_controller &other) noexcept
        {
            kp = other.get_kd();
            setpoint = other.get_setpoint();
            input_function = other.get_input_function();
            output_values = other.get_output_values();
        }
        
        inline void operator>>(I_controller &other) noexcept { other.set(kp, setpoint, input_function); }
        
        inline void operator>>(D_controller &other) noexcept { other.set(kp, setpoint, input_function); }
    };

    class I_controller
    {
    private:
        double ki = 0.0;
        double setpoint = 0.0;
        std::function<double(double)> input_function;
        std::map<double, double> output_values;

    public:
        I_controller() noexcept : 
        ki(0.0),
        setpoint(0.0),
        input_function(nullptr) {}
        
        I_controller(const I_controller &other) noexcept : 
        ki(other.ki),
        setpoint(other.setpoint),
        input_function(other.input_function),
        output_values(other.output_values) {}

        I_controller(double Ki, double Setpoint,
        std::function<double(double)> InputFunction) noexcept : 
        ki(Ki), 
        setpoint(Setpoint),
        input_function(InputFunction) {}

        inline void reset() noexcept
        {
            ki = 0.0;
            setpoint = 0.0;
            input_function = nullptr;
            output_values.clear();
        }

        inline void reset_input_function(std::function<double(double)> InputFunction) noexcept { input_function = InputFunction; }
        
        inline void reset_ki(double Ki) noexcept { ki = Ki; }
        
        inline void reset_setpoint(double Setpoint) noexcept { setpoint = Setpoint; }
        
        inline constexpr double get_ki() const noexcept { return ki; }

        inline void set(double Ki, double Setpoint,
            std::function<double(double)> InputFunction) noexcept
        {
            ki = Ki;
            setpoint = Setpoint;
            input_function = InputFunction;
        }

        inline constexpr double get_setpoint() const noexcept { return setpoint; }
        
        inline std::function<double(double)> get_input_function() const noexcept { return input_function; }

        inline double compute(double time) noexcept
        {
            double integral = MulAppTrapRule(time + 0.01, time - 0.01, [this](double t) { return ki * (setpoint - input_function(t)); }, 100);
            output_values[time] = integral;
            return integral;
        }

        inline void compute_over_time(
            double start_time,
            double end_time,
            double time_step) noexcept
        {
            for (double t = start_time; t <= end_time; t += time_step)
                compute(t);
        }

        inline const std::map<double, double> &get_output_values() const noexcept { return output_values; }

        inline bool is_empty() const noexcept
        {
            return (ki == 0.0) &&
                   (setpoint == 0.0) &&
                   (input_function == nullptr) &&
                   (output_values.empty());
        }

        inline void operator=(std::function<double(double)> InputFunction) noexcept { input_function = InputFunction; }

        inline void operator=(const I_controller &other) noexcept
        {
            if (this != &other)
            {
                ki = other.ki;
                setpoint = other.setpoint;
                input_function = other.input_function;
                output_values = other.output_values;
            }
        }

        inline bool operator!=(const I_controller &other) noexcept { return !(*this == other); }

        inline bool operator==(const I_controller &other) noexcept
        {
            return (ki == other.ki) &&
                   (setpoint == other.setpoint) &&
                   (input_function.target_type() == other.input_function.target_type()) &&
                   (output_values == other.output_values);
        }

        inline void operator<<(const P_controller &other) noexcept
        {
            ki = other.get_kp();
            setpoint = other.get_setpoint();
            input_function = other.get_input_function();
            output_values = other.get_output_values();
        }

        inline void operator<<(const D_controller &other) noexcept
        {
            ki = other.get_kd();
            setpoint = other.get_setpoint();
            input_function = other.get_input_function();
            output_values = other.get_output_values();
        }

        inline void operator>>(P_controller &other) noexcept { other.set(ki, setpoint, input_function); }

        inline void operator>>(D_controller &other) noexcept { other.set(ki, setpoint, input_function); }
    };

    class D_controller
    {
    private:
        double kd = 0.0;
        double setpoint = 0.0;
        std::function<double(double)> input_function;
        std::map<double, double> output_values;

    protected:
        double Derivate(std::function<double(double)> f, double x, double h)
        {
            CFDD<true> derivator;
            derivator.set_value(f, h);
            return derivator.FirDer(x / h);
        }

    public:
        D_controller() noexcept : 
        kd(0.0),
        setpoint(0.0), 
        input_function(nullptr) {}

        D_controller(const D_controller &other) noexcept : 
        kd(other.kd),
        setpoint(other.setpoint),
        input_function(other.input_function),
        output_values(other.output_values) {}
        
        D_controller(double Kd, double Setpoint,
        std::function<double(double)> InputFunction) noexcept : 
        kd(Kd), 
        setpoint(Setpoint),
        input_function(InputFunction) {}
        
        inline void set(double Kd, double Setpoint,
            std::function<double(double)> InputFunction) noexcept
        {
            kd = Kd;
            setpoint = Setpoint;
            input_function = InputFunction;
        }

        inline constexpr double get_kd() const noexcept { return kd; }
        
        inline constexpr double get_setpoint() const noexcept { return setpoint; }
        
        inline std::function<double(double)> get_input_function() const noexcept { return input_function; }
        
        inline void reset() noexcept
        {
            kd = 0.0;
            setpoint = 0.0;
            input_function = nullptr;
            output_values.clear();
        }

        inline void reset_kd(double Kd) noexcept { kd = Kd; }

        inline void reset_setpoint(double Setpoint) noexcept { setpoint = Setpoint; }
        
        inline void reset_input_function(std::function<double(double)> InputFunction) noexcept { input_function = InputFunction; }

        inline double compute(double time) noexcept
        {
            double derivative = kd * Derivate(input_function, time, 0.01);
            output_values[time] = derivative;
            return derivative;
        }

        inline void compute_over_time(
            double start_time,
            double end_time,
            double time_step) noexcept
        {
            for (double t = start_time; t <= end_time; t += time_step)
                compute(t);
        }

        inline const std::map<double, double> &get_output_values() const noexcept { return output_values; }
        
        inline bool is_empty() const noexcept
        {
            return (kd == 0.0) &&
                   (setpoint == 0.0) &&
                   (input_function == nullptr) &&
                   (output_values.empty());
        }

        inline void operator=(std::function<double(double)> InputFunction) noexcept { input_function = InputFunction; }

        inline void operator=(const D_controller &other) noexcept
        {
            if (this != &other)
            {
                kd = other.kd;
                setpoint = other.setpoint;
                input_function = other.input_function;
                output_values = other.output_values;
            }
        }

        inline bool operator==(const D_controller &other) noexcept
        {
            return (kd == other.kd) &&
                   (setpoint == other.setpoint) &&
                   (input_function.target_type() == other.input_function.target_type()) &&
                   (output_values == other.output_values);
        }

        inline void operator<<(const I_controller &other) noexcept
        {
            kd = other.get_ki();
            setpoint = other.get_setpoint();
            input_function = other.get_input_function();
            output_values = other.get_output_values();
        }

        inline void operator<<(const P_controller &other) noexcept
        {
            kd = other.get_kp();
            setpoint = other.get_setpoint();
            input_function = other.get_input_function();
            output_values = other.get_output_values();
        }

        inline void operator>>(I_controller &other) noexcept { other.set(kd, setpoint, input_function); }
    
        inline void operator>>(P_controller &other) noexcept { other.set(kd, setpoint, input_function); }
    };

    class block_controller
    {
    private:
        udt::bfs_16 state_form; // will indicate the type of the controller and the combination if it sireses or parallel
        P_controller p_controller;
        I_controller i_controller;
        D_controller d_controller;

    public:
        block_controller() noexcept : 
        state_form((uint16_t)0),
        p_controller(), 
        i_controller(), 
        d_controller() {}
        
        block_controller(const block_controller &other) noexcept :
        state_form(other.state_form),
        p_controller(other.p_controller),
        i_controller(other.i_controller),
        d_controller(other.d_controller) {}
        
        inline void reset() noexcept
        {
            state_form.reset_all();
            p_controller.reset();
            i_controller.reset();
            d_controller.reset();
        }
    };
}
#endif // OPENMSL___MSL___PID_HPP