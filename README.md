# Secure-Edge-PWLCM-Benchmark

<!-- Repository Status and Metadata Badges -->
[![License: MIT](https://img.shields.io/badge/License-MIT-blue)](https://opensource.org)
[![Academic-Tier: Q1 Informatics](https://img.shields.io/badge/Academic--Tier-Q1%20Informatics-blue)](https://ieee-iotj.org)
[![Language: C](https://img.shields.io/badge/Language-C-blue)](https://cppreference.com/c)
[![Platform: Ubuntu 20.04.6 LTS](https://img.shields.io/badge/Platform-Ubuntu%2020.04.6%20LTS-orange)](https://ubuntu.com)
[![Target: ESP32 Xtensa](https://img.shields.io/badge/Target-ESP32%20Tensilica%20Xtensa%2032--bit-red)](https://documentation.espressif.com/esp32-wroom-32e_esp32-wroom-32ue_datasheet_en.html)

Empirical replication repository for **Paper B: The Power-Constrained Edge & Communication Network** within the PhD thesis framework at the University of Buea.

---

## 📊 Architectural Overview & Core Thesis Novelty

To review the exact cryptographic convergence math, supervisor baselines, and resource-efficiency breakthroughs that differentiate this research from high-overhead FPGA layouts, analyze the system matrix below:

![Low-Overhead Fixed-Point Chaotic Stream Cipher Infographic](./docs/assets/infographic.png)

---

## 🔬 Technical Abstract
This repository isolates and profiles the hardware execution cycle reduction achieved by migrating a Piecewise Linear Chaotic Map (PWLCM) cipher from standard IEEE-754 floating-point operations down to optimized Q16.16 fixed-point signed integer tracking. This prevents runtime power sags on remote 32-bit agricultural edge microcontrollers.

## Target Architecture Prerequisites
- **Operating System**: Ubuntu 20.04.6 LTS / Debian GNU/Linux
- **Compiler**: GCC v9.4.0 or newer
- **Target Hardware Metric Calibration**: Intel i3-1115G4 dual-core processor clocked at base frequency parameters of 3.00GHz.

## 📂 Repository Structure

Below is the verified layout of this replication repository. Use this map to navigate between the desktop simulation profiling code and the target microcontroller edge firmware:

```text
secure-edge-pwlcm-benchmark/
├── .github/
│   └── workflows/
│       └── c-cpp-ci.yml       # Automated GitHub Actions validation pipeline
├── docs/
│   └── assets/
│       └── infographic.png    # Your system architecture diagram file
├── src/
│   ├── desktop_sim/
│   │   └── benchmark.c        # Documented Intel i3 profiling C file
│   └── esp32_firmware/
│       ├── main.cpp           # Future target micro-controller build script
│       └── CMakeLists.txt     # Native ESP-IDF toolchain build settings
├── .gitignore                 # Enforces filtering of compiled binaries
├── LICENSE                    # Full MIT validation text file string
└── README.md                  # Main repository landing file with badges
```

## Operational Compilation Instructions
To bypass compiler constant-folding optimizations and enforce raw register execution monitoring during iteration blocks, compile with the explicit optimization suppression flag (`-O0`):

```bash
gcc -O0 benchmark.c -o benchmark
```

## Running the Profiler
```bash
./benchmark
```

## 📜 Supervisory Reference Base

This cryptographic core downscales the following mathematical multi-stability and hardware synchronization baselines established by the University of Buea and ICT University faculty networks:

1. **Njitacke, Z. T., Sone, M. E., Fozin, T. F., Tsafack, N., Leutcho, G. D., & Tchapga, C. T. (2021).** 
   *Control of multistability with selection of chaotic attractor: application to image encryption.* 
   *The European Physical Journal Special Topics*, 230(7), 1839–1854.
   * Authentically Hosted on Springer: [https://www.doi.org/10.1140/epjs/s11734-021-00137-6](https://springer.com)

2. **Njitacke, Z. T., Nkapkop, J. D. D., Signing, V. R. F., Tsafack, N., Sone, M. E., & Awrejcewicz, J. (2023).** 
   *Novel extreme multistable tabu learning neuron: Circuit implementation and application to cryptography.* 
   *IEEE Transactions on Industrial Informatics*, 19(8), 8943–8952.
   * Authentically Hosted on IEEE Xplore: [https://www.doi.org/10.1109/TII.2022.3223233](https://ieee.org)

3. **Yemélé, D., Azangue, A. B., Sone, M. E., Fotsin, H., Nono, M. K., & Ngouonkadi, E. B. M. (2024).** 
   *Stability and synchronization in neural network with delayed synaptic connections.* 
   *Chaos: An Interdisciplinary Journal of Nonlinear Science*, 34(2), 023133.
   * Authentically Hosted on AIP Publishing: [https://www.doi.org/10.1063/5.0175408](https://aip.org)
