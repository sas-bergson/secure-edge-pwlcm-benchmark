# Secure-Edge-PWLCM-Benchmark

<!-- Repository Status and Metadata Badges -->
[![License: MIT](https://shields.io)](https://opensource.org)
[![Language: C](https://shields.io)](https://mozilla.org)
[![Platform: Ubuntu%2020.04-LTS](https://shields.io)](https://ubuntu.com)
[![Target: ESP32%20Xtensa](https://shields.io)](https://espressif.com)
[![Academic-Tier: Q1%20Informatics](https://shields.io)](https://ieee-iotj.org)

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
This cryptography core ports and downscales the following high-dimensional multi-stability baselines established by the University of Buea and ICT University supervisory clusters:
1. **Njitacke, Sone, et al. (2021)** - Attractor Selection Strategy: [https://doi.org](https://doi.org)
2. **Njitacke, Sone, et al. (2023)** - Tabu Learning Chaotic Neuron: [https://doi.org](https://doi.org)
3. **Sone (2018)** - Cross-Layer Hardware Network Security Scheme: [https://doi.org](https://doi.org)
