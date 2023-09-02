#include "include/LockValue.h"
#include "include/function.h"
#if 0
    以下为版权信息
    Optimum Memory - Subsystem performance for gaming
    SM8475 platform
    DoC : 2023 / 8 / 28
    Copyright(c) 2023 asto18089.All rights reserved.
#endif
void sm8475opt() {
    // # Lock DDR min frequency to 3110MHz
    lock_val(3196000, "/sys/devices/system/cpu/bus_dcvs/DDR/boost_freq");

    lock_val(1555000, "/sys/devices/system/cpu/bus_dcvs/DDR/soc:qcom,memlat:ddr:silver/max_freq");
    lock_val(3196000, "/sys/devices/system/cpu/bus_dcvs/DDR/19091000.qcom,bwmon-ddr/max_freq");
    lock_val(3196000, "/sys/devices/system/cpu/bus_dcvs/DDR/soc:qcom,memlat:ddr:prime/max_freq");
    lock_val(3196000, "/sys/devices/system/cpu/bus_dcvs/DDR/soc:qcom,memlat:ddr:prime-latfloor/max_freq");
    lock_val(1555000, "/sys/devices/system/cpu/bus_dcvs/DDR/soc:qcom,memlat:ddr:gold-compute/max_freq");
    lock_val(3196000, "/sys/devices/system/cpu/bus_dcvs/DDR/soc:qcom,memlat:ddr:gold/max_freq");
    lock_val(1555000, "/sys/devices/system/cpu/bus_dcvs/DDR/soc:qcom,memlat:ddr:silver/min_freq");
    lock_val(1555000, "/sys/devices/system/cpu/bus_dcvs/DDR/19091000.qcom,bwmon-ddr/min_freq");
    lock_val(1555000, "/sys/devices/system/cpu/bus_dcvs/DDR/soc:qcom,memlat:ddr:prime/min_freq");
    lock_val(1555000, "/sys/devices/system/cpu/bus_dcvs/DDR/soc:qcom,memlat:ddr:prime-latfloor/min_freq");
    lock_val(1555000, "/sys/devices/system/cpu/bus_dcvs/DDR/soc:qcom,memlat:ddr:gold-compute/min_freq");
    lock_val(1555000, "/sys/devices/system/cpu/bus_dcvs/DDR/soc:qcom,memlat:ddr:gold/min_freq");

    // # Lock L3 Cache frequency to 1804MHz
    lock_val(1804800, "/sys/devices/system/cpu/bus_dcvs/L3/boost_freq");
    lock_val(1804000, "/sys/devices/system/cpu/bus_dcvs/L3/soc:qcom,memlat:l3:silver/max_freq");
    lock_val(1804000, "/sys/devices/system/cpu/bus_dcvs/L3/soc:qcom,memlat:l3:prime/max_freq");
    lock_val(1804000, "/sys/devices/system/cpu/bus_dcvs/L3/soc:qcom,memlat:l3:gold/max_freq");
    lock_val(1708800, "/sys/devices/system/cpu/bus_dcvs/L3/soc:qcom,memlat:l3:prime-compute/max_freq");
    lock_val(1804000, "/sys/devices/system/cpu/bus_dcvs/L3/soc:qcom,memlat:l3:silver/min_freq");
    lock_val(1804000, "/sys/devices/system/cpu/bus_dcvs/L3/soc:qcom,memlat:l3:prime/min_freq");
    lock_val(1804000, "/sys/devices/system/cpu/bus_dcvs/L3/soc:qcom,memlat:l3:gold/min_freq");
    lock_val(1708800, "/sys/devices/system/cpu/bus_dcvs/L3/soc:qcom,memlat:l3:prime-compute/min_freq");

    // # Lock performance governor on Prime and Gold cluster
    /*
    std::string performance = "performance";
    lock_val(performance, "/sys/devices/system/cpu/cpufreq/policy4/scaling_governor");
    lock_val(performance, "/sys/devices/system/cpu/cpufreq/policy7/scaling_governor");
    */
}