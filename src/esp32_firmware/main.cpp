/**
 * @file main.cpp
 * @brief ESP32 production firmware implementing a low-overhead, fixed-point
 *        chaotic stream cipher with hardware true random number perturbation.
 *
 * @author Daniel Moune
 * @institution University of Buea, Department of Computer Science
 * @project PhD Thesis Framework: Secure B-PINN Equatorial Perennial Biomass Forecasting
 * @date August 27, 2026
 * @version 1.0.0
 */

#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_cpu.h"
#include "esp_log.h"
#include "soc/wdev_reg.h" // Low-level hardware registry for true silicon noise

static const char *TAG = "SECURE_EDGE_CRYPTO";

typedef int32_t q16_16;
#define ONE_Q16 65536
#define HALF_Q16 32768
#define PERTURB_INTERVAL 32

/**
 * @brief Computes fixed-point iteration of PWLCM map.
 */
inline q16_16 pwlcm_q16(const q16_16 x, const q16_16 p)
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

extern "C" void app_main(void)
{
    ESP_LOGI(TAG, "Initializing secure physical-layer cryptographic loop...");

    // Set up initial conditions derived from pre-shared key arrays
    q16_16 x_state = (q16_16)(0.123456f * ONE_Q16);
    const q16_16 p_param = (q16_16)(0.231564f * ONE_Q16);

    uint32_t iteration_count = 0;

    while (1)
    {
        uint32_t start_cycles = esp_cpu_get_cycle_count();

        // Execute the fast integer chaotic transition mapping step
        x_state = pwlcm_q16(x_state, p_param);
        iteration_count++;

        // ASYNCHRONOUS HARDWARE PERTURBATION LOOP
        // Query target chip physical noise registry every 32 execution orbits
        if (iteration_count % PERTURB_INTERVAL == 0)
        {
            uint32_t raw_silicon_noise = REG_READ(WDEV_RNG_REG);
            x_state ^= (raw_silicon_noise & 0x000F); // Inject 4 bits of entropy
        }

        uint32_t end_cycles = esp_cpu_get_cycle_count();
        uint32_t net_execution_cycles = end_cycles - start_cycles;

        ESP_LOGD(TAG, "State Output: %ld | Clock Cycles Consumed: %lu",
                 x_state, net_execution_cycles);

        // Sleep task to yield execution to RTOS scheduler cores (10ms check-in window)
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
