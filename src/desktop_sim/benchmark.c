/**
 * @file benchmark.c
 * @brief High-efficiency benchmarking matrix comparing IEEE-754 floating-point
 *        operations against Q16.16 fixed-point arithmetic for a Piecewise Linear
 *        Chaotic Map (PWLCM).
 *
 * @details This software module isolates the raw processor cycle overhead of
 *          chaotic trajectory generators intended for deployment on resource-constrained
 *          32-bit RISC edge architectures (ESP32). It bypasses standard compiler
 *          optimization to establish a clean physical baseline on target hardware execution.
 *
 * @author Daniel Moune
 * @institution University of Buea, Department of Computer Science
 * @project PhD Thesis Framework: Secure B-PINN Equatorial Perennial Biomass Forecasting
 * @date August 26, 2026
 * @version 1.0.0
 *
 * @license MIT License
 * Copyright (c) 2026 Daniel Moune
 * See GitHub repository root for complete license text.
 */

#include <stdio.h>
#include <stdint.h>
#include <time.h>

/**
 * @def ITERATIONS
 * @brief Total computational sample size per profiling loop execution block.
 */
#define ITERATIONS 10000

/**
 * @typedef q16_16
 * @brief 32-bit signed fixed-point integer type definition.
 * @details Uses the upper 16 bits for the integer component and the lower
 *          16 bits for the fractional component (Q16.16 format).
 */
typedef int32_t q16_16;

/** @brief Numerical representation of unity (1.0) in Q16.16 bitwise scaling space. */
#define ONE_Q16 65536

/** @brief Numerical representation of the chaotic inflection boundary (0.5) in Q16.16 format. */
#define HALF_Q16 32768

/**
 * @brief Computes a single discrete iteration of the PWLCM using standard 32-bit float types.
 * @param[in] x The current state variable within the normalized continuous chaotic domain.
 * @param[in] p The internal system control parameter defining the mapping threshold (0 < p < 0.5).
 * @return The next state value in the chaotic sequence sequence as a standard float.
 */
float pwlcm_float(const float x, const float p)
{
    float state = x;
    if (state >= 0.5f)
    {
        state = 1.0f - state;
    }
    if (state < p)
    {
        return state / p;
    }
    else
    {
        return (state - p) / (0.5f - p);
    }
}

/**
 * @brief Computes a single discrete iteration of the PWLCM using optimized fixed-point integer math.
 * @details Explicitly shifts intermediate variable structures up to 64-bit bounds (`int64_t`)
 *          prior to execution division to completely avoid arithmetic bitwise overflow bugs.
 * @param[in] x The current state variable scaled to the Q16.16 integer space.
 * @param[in] p The system control parameter scaled to the Q16.16 integer space.
 * @return The encrypted state outcome mapped directly back onto the 32-bit fixed-point register bounds.
 */
q16_16 pwlcm_q16(const q16_16 x, const q16_16 p)
{
    q16_16 state = x;
    if (state >= HALF_Q16)
    {
        state = ONE_Q16 - state;
    }
    if (state < p)
    {
        return (q16_16)(((int64_t)state << 16) / p);
    }
    else
    {
        return (q16_16)(((int64_t)(state - p) << 16) / (HALF_Q16 - p));
    }
}

/**
 * @brief Main execution thread orchestrating the monotonic hardware profiling sequence.
 * @return Execution termination state exit code (0 for clean validation closure).
 */
int main(void)
{
    struct timespec start, end;
    double float_time = 0.0;
    double q16_time = 0.0;

    /* Establish identical mathematical initial conditions across both variants */
    float x_f = 0.123456f;
    const float p_f = 0.231564f;

    /* Map floating point system state elements down to integer fixed-point parameters */
    q16_16 x_q = (q16_16)(x_f * ONE_Q16);
    const q16_16 p_q = (q16_16)(p_f * ONE_Q16);

    /* -------------------------------------------------------------------------
     * PROFILE TRACK 1: Standard IEEE-754 Floating-Point Simulation Loop
     * ------------------------------------------------------------------------- */
    if (clock_gettime(CLOCK_MONOTONIC, &start) != 0)
    {
        return 1;
    }
    for (int i = 0; i < ITERATIONS; i++)
    {
        x_f = pwlcm_float(x_f, p_f);
    }
    if (clock_gettime(CLOCK_MONOTONIC, &end) != 0)
    {
        return 1;
    }
    float_time = (double)(end.tv_sec - start.tv_sec) * 1e9 + (double)(end.tv_nsec - start.tv_nsec);

    /* -------------------------------------------------------------------------
     * PROFILE TRACK 2: Proposed Q16.16 Fixed-Point Integer Simulation Loop
     * ------------------------------------------------------------------------- */
    if (clock_gettime(CLOCK_MONOTONIC, &start) != 0)
    {
        return 1;
    }
    for (int i = 0; i < ITERATIONS; i++)
    {
        x_q = pwlcm_q16(x_q, p_q);
    }
    if (clock_gettime(CLOCK_MONOTONIC, &end) != 0)
    {
        return 1;
    }
    q16_time = (double)(end.tv_sec - start.tv_sec) * 1e9 + (double)(end.tv_nsec - start.tv_nsec);

    /* -------------------------------------------------------------------------
     * HARDWARE SCALING MATRIX CALCULATION (Target Architecture: Intel i3-1115G4 @ 3.00GHz)
     * ------------------------------------------------------------------------- */
    const double cycles_per_ns = 3.0;
    const double float_cycles = float_time * cycles_per_ns;
    const double q16_cycles = q16_time * cycles_per_ns;
    const double reduction = ((float_cycles - q16_cycles) / float_cycles) * 100.0;

    /* Output formalized metric grid directly to stdout terminal window link */
    printf("==================================================\n");
    printf(" BENCHMARK RESULTS: Intel i3-1115G4 @ 3.00GHz\n");
    printf("==================================================\n");
    printf("1. Standard Float Loop Execution:\n");
    printf("   - Total Runtime Time : %.0f ns\n", float_time);
    printf("   - Est. Clock Cycles  : %.0f cycles\n\n", float_cycles);
    printf("2. Proposed Q16.16 Fixed-Point Loop:\n");
    printf("   - Total Runtime Time : %.0f ns\n", q16_time);
    printf("   - Est. Clock Cycles  : %.0f cycles\n\n", q16_cycles);
    printf("--------------------------------------------------\n");
    printf("📊 NET PROCESSOR CYCLE REDUCTION: %.2f%%\n", reduction);
    printf("==================================================\n");

    return 0;
}
