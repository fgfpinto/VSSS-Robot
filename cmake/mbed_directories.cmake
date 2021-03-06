set(MBED_DIR ${LIB_DIR}/mbed-os)

set(MBED_DIRECTORIES
    ${MBED_DIR}
    ${MBED_DIR}/cmsis
    ${MBED_DIR}/cmsis/TARGET_CORTEX_M
    ${MBED_DIR}/drivers
    ${MBED_DIR}/events
    ${MBED_DIR}/events/equeue
    ${MBED_DIR}/features
    ${MBED_DIR}/features/FEATURE_LWIP
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip-eth
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip-eth/arch
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip-eth/arch/TARGET_NXP
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip-eth/arch/TARGET_NXP/TARGET_LPCTarget
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip/src
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip/src/api
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip/src/core
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip/src/core/ipv4
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip/src/core/ipv6
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip/src/include
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip/src/include/lwip
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip/src/include/lwip/priv
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip/src/include/lwip/prot
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip/src/include/netif
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip/src/include/netif/ppp
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip/src/include/netif/ppp/polarssl
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip/src/netif
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip/src/netif/ppp
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip/src/netif/ppp/polarssl
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip-sys
    ${MBED_DIR}/features/FEATURE_LWIP/lwip-interface/lwip-sys/arch
    ${MBED_DIR}/features/filesystem
    ${MBED_DIR}/features/filesystem/bd
    ${MBED_DIR}/features/filesystem/fat
    ${MBED_DIR}/features/filesystem/fat/ChaN
    ${MBED_DIR}/features/filesystem/littlefs
    ${MBED_DIR}/features/filesystem/littlefs/littlefs
    ${MBED_DIR}/features/frameworks
    ${MBED_DIR}/features/frameworks/greentea-client
    ${MBED_DIR}/features/frameworks/greentea-client/greentea-client
    ${MBED_DIR}/features/frameworks/greentea-client/source
    ${MBED_DIR}/features/frameworks/unity
    ${MBED_DIR}/features/frameworks/unity/source
    ${MBED_DIR}/features/frameworks/unity/unity
    ${MBED_DIR}/features/frameworks/utest
    ${MBED_DIR}/features/frameworks/utest/source
    ${MBED_DIR}/features/frameworks/utest/utest
    ${MBED_DIR}/features/mbedtls
    ${MBED_DIR}/features/mbedtls/inc
    ${MBED_DIR}/features/mbedtls/inc/mbedtls
    ${MBED_DIR}/features/mbedtls/platform
    ${MBED_DIR}/features/mbedtls/platform/inc
    ${MBED_DIR}/features/mbedtls/platform/src
    ${MBED_DIR}/features/mbedtls/src
    ${MBED_DIR}/features/nanostack
    ${MBED_DIR}/features/netsocket
    ${MBED_DIR}/features/netsocket/cellular
    ${MBED_DIR}/features/netsocket/cellular/generic_modem_driver
    ${MBED_DIR}/features/netsocket/cellular/utils
    ${MBED_DIR}/features/storage
    ${MBED_DIR}/hal
    ${MBED_DIR}/hal/storage_abstraction
    ${MBED_DIR}/platform
    ${MBED_DIR}/rtos
    ${MBED_DIR}/rtos/TARGET_CORTEX
    ${MBED_DIR}/rtos/TARGET_CORTEX/rtx4
    ${MBED_DIR}/rtos/TARGET_CORTEX/rtx5
    ${MBED_DIR}/rtos/TARGET_CORTEX/rtx5/Include
    ${MBED_DIR}/rtos/TARGET_CORTEX/rtx5/RTX
    ${MBED_DIR}/rtos/TARGET_CORTEX/rtx5/RTX/Config
    ${MBED_DIR}/rtos/TARGET_CORTEX/rtx5/RTX/Include
    ${MBED_DIR}/rtos/TARGET_CORTEX/rtx5/RTX/Source
    ${MBED_DIR}/rtos/TARGET_CORTEX/rtx5/RTX/Source/TOOLCHAIN_GCC
    ${MBED_DIR}/rtos/TARGET_CORTEX/rtx5/RTX/Source/TOOLCHAIN_GCC/TARGET_M3
    ${MBED_DIR}/rtos/TARGET_CORTEX/rtx5/Source
    ${MBED_DIR}/targets
    ${MBED_DIR}/targets/TARGET_NXP
    ${MBED_DIR}/targets/TARGET_NXP/TARGET_LPC176X
    ${MBED_DIR}/targets/TARGET_NXP/TARGET_LPC176X/device
    ${MBED_DIR}/targets/TARGET_NXP/TARGET_LPC176X/device/TOOLCHAIN_GCC_ARM
    ${MBED_DIR}/targets/TARGET_NXP/TARGET_LPC176X/TARGET_MBED_LPC1768)
