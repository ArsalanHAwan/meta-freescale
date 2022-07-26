require recipes-bsp/u-boot/u-boot-tools.inc
require u-boot-imx-common.inc

PROVIDES:append:class-target = " ${MLPREFIX}u-boot-tools"
PROVIDES:append:class-native = " u-boot-tools-native"
PROVIDES:append:class-nativesdk = " nativesdk-u-boot-tools"

PACKAGE_ARCH = "${MACHINE_ARCH}"
COMPATIBLE_MACHINE = "(mx6|mx7|mx8)"
COMPATIBLE_MACHINE:class-target = "(mx6|mx7|mx8)"
