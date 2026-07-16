#pragma once
#ifndef OPENMSL___MSL___PID_HPP
#define OPENMSL___MSL___PID_HPP
#include "udt/core/bfs.hpp"
#include "numerical.hpp"
#include "cfrost/structure.h"
#include <map>
#include <vector>
#include <functional>

/**
 * @file control.hpp
 * @brief This file contains the implementation of the P, I, and D controllers, as well as a block controller that can combine them in series or parallel.
 * The p_controller class implements a proportional controller, the i_controller class implements an integral controller, and the d_controller class implements a derivative controller. Each controller has methods to set its parameters, compute its output based on an input function, and store the output values over time. The block_controller class can combine the three controllers in different configurations based on a state form represented by a BFS_16 object.
 * The controllers use the numerical library for numerical integration and differentiation, and they store their output values in a map for later retrieval. The classes also include operator overloads for assignment and comparison, as well as methods to reset their parameters and output values.
 * @author Ali Lafi
 * @date 2024-06
 */

namespace msl
{
    class p_controller;
    class i_controller;
    class d_controller;
    
    class p_controller
    {
    private:
        double kp = 0.0;
        double setpoint = 0.0;
        func<double(double)> input_function;
        hash_map<double, double> output_values;

    public:
        p_controller() noexcept : 
        kp(0.0),
        setpoint(0.0),
        input_function(nullptr) {}
        
        p_controller(const p_controller &other) noexcept : 
        kp(other.kp),
        setpoint(other.setpoint),
        input_function(other.input_function),
        output_values(other.output_values) {}
        
        p_controller(double Kp, double Setpoint,
        func<double(double)> InputFunction) noexcept : 
        kp(Kp), 
        setpoint(Setpoint),
        input_function(InputFunction) {}
        
        inline procedure(reset) noexcept
        {
            kp = 0.0;
            setpoint = 0.0;
            input_function = nullptr;
            output_values.clear();
        }
        
        inline void reset_input_function(func<double(double)> InputFunction) noexcept { input_function = InputFunction; }
        
        inline void reset_kp(double Kp) noexcept { kp = Kp; }

        inline void reset_setpoint(double Setpoint) noexcept { setpoint = Setpoint; }
        
        inline void set(
            double Kp, 
            double Setpoint,
            func<double(double)> InputFunction) noexcept
        {
            kp = Kp;
            setpoint = Setpoint;
            input_function = InputFunction;
        }
        
        inline constexpr double get_kp() const noexcept { return kp; }
        
        inline constexpr double get_setpoint() const noexcept { return setpoint; }

        inline func<double(double)> get_input_function() const noexcept { return input_function; }
        
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

        inline const hash_map<double, double> &get_output_values() const noexcept { return output_values; }
        
        inline bool is_empty() const noexcept
        {
            return (kp == 0.0) &&
                   (setpoint == 0.0) &&
                   (input_function == nullptr) &&
                   (output_values.empty());
        }
        
        inline bool operator!=(const p_controller &other) noexcept { return !(*this == other); }
        
        inline void operator=(func<double(double)> InputFunction) noexcept { input_function = InputFunction; }
        
        inline void operator=(const p_controller &other) noexcept
        {
            if (this != &other)
            {
                kp = other.kp;
                setpoint = other.setpoint;
                input_function = other.input_function;
                output_values = other.output_values;
            }
        }

        inline bool operator==(const p_controller &other) noexcept
        {
            return (kp == other.kp) &&
                   (setpoint == other.setpoint) &&
                   (input_function.target_type() == other.input_function.target_type()) &&
                   (output_values == other.output_values);
        }
        
        inline void operator<<(const i_controller &other) noexcept
        {
            kp = other.get_ki();
            setpoint = other.get_setpoint();
            input_function = other.get_input_function();
            output_values = other.get_output_values();
        }
        
        inline void operator<<(const d_controller &other) noexcept
        {
            kp = other.get_kd();
            setpoint = other.get_setpoint();
            input_function = other.get_input_function();
            output_values = other.get_output_values();
        }
        
        inline void operator>>(i_controller &other) noexcept { other.set(kp, setpoint, input_function); }
        
        inline void operator>>(d_controller &other) noexcept { other.set(kp, setpoint, input_function); }
    };

    class i_controller
    {
    private:
        double ki = 0.0;
        double setpoint = 0.0;
        func<double(double)> input_function;
        hash_map<double, double> output_values;

    public:
        i_controller() noexcept : 
        ki(0.0),
        setpoint(0.0),
        input_function(nullptr) {}
        
        i_controller(const i_controller &other) noexcept : 
        ki(other.ki),
        setpoint(other.setpoint),
        input_function(other.input_function),
        output_values(other.output_values) {}

        i_controller(double Ki, double Setpoint,
        func<double(double)> InputFunction) noexcept : 
        ki(Ki), 
        setpoint(Setpoint),
        input_function(InputFunction) {}

        inline procedure(reset) noexcept
        {
            ki = 0.0;
            setpoint = 0.0;
            input_function = nullptr;
            output_values.clear();
        }

        inline void reset_input_function(func<double(double)> InputFunction) noexcept { input_function = InputFunction; }
        
        inline void reset_ki(double Ki) noexcept { ki = Ki; }
        
        inline void reset_setpoint(double Setpoint) noexcept { setpoint = Setpoint; }
        
        inline constexpr double get_ki() const noexcept { return ki; }

        inline void set(double Ki, double Setpoint,
            func<double(double)> InputFunction) noexcept
        {
            ki = Ki;
            setpoint = Setpoint;
            input_function = InputFunction;
        }

        inline constexpr double get_setpoint() const noexcept { return setpoint; }
        
        inline func<double(double)> get_input_function() const noexcept { return input_function; }

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

        inline const hash_map<double, double> &get_output_values() const noexcept { return output_values; }

        inline bool is_empty() const noexcept
        {
            return (ki == 0.0) &&
                   (setpoint == 0.0) &&
                   (input_function == nullptr) &&
                   (output_values.empty());
        }

        inline void operator=(func<double(double)> InputFunction) noexcept { input_function = InputFunction; }

        inline void operator=(const i_controller &other) noexcept
        {
            if (this != &other)
            {
                ki = other.ki;
                setpoint = other.setpoint;
                input_function = other.input_function;
                output_values = other.output_values;
            }
        }

        inline bool operator!=(const i_controller &other) noexcept { return !(*this == other); }

        inline bool operator==(const i_controller &other) noexcept
        {
            return (ki == other.ki) &&
                   (setpoint == other.setpoint) &&
                   (input_function.target_type() == other.input_function.target_type()) &&
                   (output_values == other.output_values);
        }

        inline void operator<<(const p_controller &other) noexcept
        {
            ki = other.get_kp();
            setpoint = other.get_setpoint();
            input_function = other.get_input_function();
            output_values = other.get_output_values();
        }

        inline void operator<<(const d_controller &other) noexcept
        {
            ki = other.get_kd();
            setpoint = other.get_setpoint();
            input_function = other.get_input_function();
            output_values = other.get_output_values();
        }

        inline void operator>>(p_controller &other) noexcept { other.set(ki, setpoint, input_function); }

        inline void operator>>(d_controller &other) noexcept { other.set(ki, setpoint, input_function); }
    };

    class d_controller
    {
    private:
        double kd = 0.0;
        double setpoint = 0.0;
        func<double(double)> input_function;
        hash_map<double, double> output_values;

    protected:
        double Derivate(func<double(double)> f, double x, double h)
        {
            CFDD<true> derivator;
            derivator.set_value(f, h);
            return derivator.FirDer(x / h);
        }

    public:
        d_controller() noexcept : 
        kd(0.0),
        setpoint(0.0), 
        input_function(nullptr) {}

        d_controller(const d_controller &other) noexcept : 
        kd(other.kd),
        setpoint(other.setpoint),
        input_function(other.input_function),
        output_values(other.output_values) {}
        
        d_controller(double Kd, double Setpoint,
        func<double(double)> InputFunction) noexcept : 
        kd(Kd), 
        setpoint(Setpoint),
        input_function(InputFunction) {}
        
        inline void set(double Kd, double Setpoint,
            func<double(double)> InputFunction) noexcept
        {
            kd = Kd;
            setpoint = Setpoint;
            input_function = InputFunction;
        }

        inline constexpr double get_kd() const noexcept { return kd; }
        
        inline constexpr double get_setpoint() const noexcept { return setpoint; }
        
        inline func<double(double)> get_input_function() const noexcept { return input_function; }
        
        inline procedure(reset) noexcept
        {
            kd = 0.0;
            setpoint = 0.0;
            input_function = nullptr;
            output_values.clear();
        }

        inline void reset_kd(double Kd) noexcept { kd = Kd; }

        inline void reset_setpoint(double Setpoint) noexcept { setpoint = Setpoint; }
        
        inline void reset_input_function(func<double(double)> InputFunction) noexcept { input_function = InputFunction; }

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

        inline const hash_map<double, double> &get_output_values() const noexcept { return output_values; }
        
        inline bool is_empty() const noexcept
        {
            return (kd == 0.0) &&
                   (setpoint == 0.0) &&
                   (input_function == nullptr) &&
                   (output_values.empty());
        }

        inline void operator=(func<double(double)> InputFunction) noexcept { input_function = InputFunction; }

        inline void operator=(const d_controller &other) noexcept
        {
            if (this != &other)
            {
                kd = other.kd;
                setpoint = other.setpoint;
                input_function = other.input_function;
                output_values = other.output_values;
            }
        }

        inline bool operator==(const d_controller &other) noexcept
        {
            return (kd == other.kd) &&
                   (setpoint == other.setpoint) &&
                   (input_function.target_type() == other.input_function.target_type()) &&
                   (output_values == other.output_values);
        }

        inline void operator<<(const i_controller &other) noexcept
        {
            kd = other.get_ki();
            setpoint = other.get_setpoint();
            input_function = other.get_input_function();
            output_values = other.get_output_values();
        }

        inline void operator<<(const p_controller &other) noexcept
        {
            kd = other.get_kp();
            setpoint = other.get_setpoint();
            input_function = other.get_input_function();
            output_values = other.get_output_values();
        }

        inline void operator>>(i_controller &other) noexcept { other.set(kd, setpoint, input_function); }
    
        inline void operator>>(p_controller &other) noexcept { other.set(kd, setpoint, input_function); }
    };

    class block_controller
    {
    private:
        udt::bfs_16 state_form; // will indicate the type of the controller and the combination if it sireses or parallel
        p_controller p_controller;
        i_controller i_controller;
        d_controller d_controller;

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
        
        inline procedure(reset) noexcept
        {
            state_form.reset_all();
            p_controller.reset();
            i_controller.reset();
            d_controller.reset();
        }
    };
}
#endif // OPENMSL___MSL___PID_HPP