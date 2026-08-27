# CMakeLists.txt for ESP32 Firmware Component Build
# PhD Thesis Framework - Daniel Moune (University of Buea)

idf_component_register(
    SRCS "main.cpp"
    INCLUDE_DIRS "."
    REQUIRES driver esp_hw_support
)

# Enforce strict register evaluation and suppress optimization 
# to match desktop micro-architectural profiling conditions exactly
target_compile_options(${COMPONENT_LIB} PRIVATE "-O0" "-ggdb")
