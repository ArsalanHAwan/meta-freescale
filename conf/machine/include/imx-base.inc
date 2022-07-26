# Provides the i.MX common settings

include conf/machine/include/fsl-default-settings.inc
include conf/machine/include/fsl-default-versions.inc

require conf/machine/include/utilities.inc

# Set specific make target and binary suffix
IMX_DEFAULT_BOOTLOADER = "u-boot-fslc"
IMX_DEFAULT_BOOTLOADER:mx8 = "u-boot-imx"

# Machines or distros can define which BSP it should use by default. We are
# intending to default for mainline BSP by default and specific machines or
# DISTROs might change it if need.
#
# Two values are considered valid: mainline, nxp
IMX_DEFAULT_BSP ?= "mainline"

# Those are SoC families we'd like to force the use of mainline BSP.
IMX_DEFAULT_BSP:mxs ?= "mainline"
IMX_DEFAULT_BSP:mx5 ?= "mainline"

MACHINEOVERRIDES =. "use-${IMX_DEFAULT_BSP}-bsp:"

PREFERRED_PROVIDER_u-boot ??= "${IMX_DEFAULT_BOOTLOADER}"
PREFERRED_PROVIDER_u-boot-tools-native ??= "${IMX_DEFAULT_BOOTLOADER}-tools-native"
PREFERRED_PROVIDER_nativesdk-u-boot-tools ??= "nativesdk-${IMX_DEFAULT_BOOTLOADER}-tools"
PREFERRED_PROVIDER_u-boot-mkimage-native ??= "${IMX_DEFAULT_BOOTLOADER}-tools-native"
PREFERRED_PROVIDER_nativesdk-u-boot-mkimage ??= "nativesdk-${IMX_DEFAULT_BOOTLOADER}-tools"
PREFERRED_PROVIDER_virtual/bootloader ??= "${IMX_DEFAULT_BOOTLOADER}"

PREFERRED_PROVIDER_u-boot-mxsboot-native ??= "u-boot-fslc-mxsboot-native"

UBOOT_BINARY ?= "u-boot.${UBOOT_SUFFIX}"
UBOOT_MAKE_TARGET ?= "u-boot.${UBOOT_SUFFIX}"
UBOOT_MAKE_TARGET:mxs ?= "u-boot.sb"
UBOOT_MAKE_TARGET:mx8 ?= ""

UBOOT_SUFFIX ?= "imx"
UBOOT_SUFFIX:mxs ?= "sb"
UBOOT_SUFFIX:mx8 ?= "bin"

UBOOT_ENTRYPOINT:mxs = "0x40008000"
UBOOT_ENTRYPOINT:mx51  = "0x90008000"
UBOOT_ENTRYPOINT:mx53  = "0x70008000"
UBOOT_ENTRYPOINT:mx6  = "0x10008000"
UBOOT_ENTRYPOINT:mx6sl = "0x80008000"
UBOOT_ENTRYPOINT:mx6sll = "0x80008000"
UBOOT_ENTRYPOINT:mx6sx = "0x80008000"
UBOOT_ENTRYPOINT:mx6ul  = "0x10008000"
UBOOT_ENTRYPOINT:mx6ull  = "0x10008000"
UBOOT_ENTRYPOINT:mx7 = "0x80008000"
UBOOT_ENTRYPOINT:mx7ulp = "0x60008000"
UBOOT_ENTRYPOINT:mx8mm  = "0x40480000"
UBOOT_ENTRYPOINT:mx8mn  = "0x40480000"
UBOOT_ENTRYPOINT:mx8mp  = "0x40480000"
UBOOT_ENTRYPOINT:mx8mq  = "0x40480000"
UBOOT_ENTRYPOINT:vf = "0x80008000"

PREFERRED_PROVIDER_virtual/xserver = "xserver-xorg"
XSERVER_DRIVER                  = "xf86-video-fbdev"
XSERVER_DRIVER:imxgpu2d         = "xf86-video-imx-vivante"
XSERVER_DRIVER:vf               = "xf86-video-modesetting"
XSERVER_DRIVER:append_mx8       = " xf86-video-modesetting"
XSERVER_DRIVER:use-mainline-bsp = "xf86-video-armada"
XSERVER = "xserver-xorg \
           xf86-input-evdev \
           ${XSERVER_DRIVER}"

# Ship kernel modules
MACHINE_EXTRA_RRECOMMENDS = "kernel-modules"

# Tunes for hard/soft float-point selection. Note that we allow building for
# thumb support giving distros the chance to enable thumb by setting
# ARM_INSTRUCTION_SET = "thumb"
#
# handled by software
# DEFAULTTUNE:mx6 ?= "cortexa9t-neon"
# handled by hardware
DEFAULTTUNE:mx6    ?= "cortexa9thf-neon"
DEFAULTTUNE:mx6ul  ?= "cortexa7thf-neon"
DEFAULTTUNE:mx6ull ?= "cortexa7thf-neon"
DEFAULTTUNE:mx7    ?= "cortexa7thf-neon"
DEFAULTTUNE:vf     ?= "cortexa5thf-neon"

DEFAULTTUNE:mx8mm  ?= "cortexa53-crypto"
DEFAULTTUNE:mx8mn  ?= "cortexa53-crypto"
DEFAULTTUNE:mx8mp  ?= "cortexa53-crypto"
DEFAULTTUNE:mx8mq  ?= "cortexa53-crypto"
DEFAULTTUNE:mx8qm  ?= "cortexa72-cortexa53-crypto"
DEFAULTTUNE:mx8qxp ?= "cortexa35-crypto"

INHERIT += "machine-overrides-extender"

MACHINEOVERRIDES_EXTENDER:mx25   = "use-mainline-bsp"
MACHINEOVERRIDES_EXTENDER:mx6q   = "imxfbdev:imxipu:imxvpu:imxgpu:imxgpu2d:imxgpu3d"
MACHINEOVERRIDES_EXTENDER:mx6dl  = "imxfbdev:imxpxp:imxipu:imxvpu:imxgpu:imxgpu2d:imxgpu3d:imxepdc"
MACHINEOVERRIDES_EXTENDER:mx6sx  = "imxfbdev:imxpxp:imxgpu:imxgpu2d:imxgpu3d"
MACHINEOVERRIDES_EXTENDER:mx6sl  = "imxfbdev:imxpxp:imxgpu:imxgpu2d:imxepdc"
MACHINEOVERRIDES_EXTENDER:mx6sll = "imxfbdev:imxpxp:imxepdc"
MACHINEOVERRIDES_EXTENDER:mx6ul  = "imxfbdev:imxpxp"
MACHINEOVERRIDES_EXTENDER:mx6ull = "imxfbdev:imxpxp:imxepdc"
MACHINEOVERRIDES_EXTENDER:mx7d   = "imxfbdev:imxpxp:imxepdc"
MACHINEOVERRIDES_EXTENDER:mx7ulp = "imxfbdev:imxpxp:imxgpu:imxgpu2d:imxgpu3d"
MACHINEOVERRIDES_EXTENDER:mx8qm  = "imxdrm:imxdpu:imxgpu:imxgpu2d:imxgpu3d"
MACHINEOVERRIDES_EXTENDER:mx8mm  = "imxdrm:imxvpu:imxgpu:imxgpu2d:imxgpu3d"
MACHINEOVERRIDES_EXTENDER:mx8mn  = "imxdrm:imxgpu:imxgpu3d"
MACHINEOVERRIDES_EXTENDER:mx8mp  = "imxdrm:imxvpu:imxgpu:imxgpu2d:imxgpu3d"
MACHINEOVERRIDES_EXTENDER:mx8mq  = "imxdrm:imxvpu:imxgpu:imxgpu3d"
MACHINEOVERRIDES_EXTENDER:mx8qxp = "imxdrm:imxdpu:imxgpu:imxgpu2d:imxgpu3d"

MACHINEOVERRIDES_EXTENDER_FILTER_OUT:use-mainline-bsp = " \
    imx \
    \
    mx6 \
    mx6q \
    mx6dl \
    mx6sx \
    mx6sl \
    mx6sll \
    mx6ul \
    mx6ull \
    \
    mx7 \
    mx7d \
    mx7ulp \
    \
    mx8 \
    mx8qm \
    mx8mm \
    mx8mn \
    mx8mp \
    mx8mq \
    mx8qxp \
"

# Sub-architecture support
MACHINE_SOCARCH_SUFFIX ?= ""
MACHINE_SOCARCH_SUFFIX:mx6q = "-mx6qdl"
MACHINE_SOCARCH_SUFFIX:mx6dl = "-mx6qdl"
MACHINE_SOCARCH_SUFFIX:mx6sx = "-mx6sx"
MACHINE_SOCARCH_SUFFIX:mx6sl = "-mx6sl"
MACHINE_SOCARCH_SUFFIX:mx6sll= "-mx6sll"
MACHINE_SOCARCH_SUFFIX:mx7d = "-mx7d"
MACHINE_SOCARCH_SUFFIX:mx7ulp = "-mx7ulp"
MACHINE_SOCARCH_SUFFIX:vf60 = "-vf60"
MACHINE_SOCARCH_SUFFIX:vf50 = "-vf50"
MACHINE_SOCARCH_SUFFIX:mx6ul  = "-mx6ul"
MACHINE_SOCARCH_SUFFIX:mx6ull = "-mx6ul"
MACHINE_SOCARCH_SUFFIX:mx8qm  = "-mx8"
MACHINE_SOCARCH_SUFFIX:mx8mm  = "-mx8mm"
MACHINE_SOCARCH_SUFFIX:mx8mn  = "-mx8mn"
MACHINE_SOCARCH_SUFFIX:mx8mp  = "-mx8mp"
MACHINE_SOCARCH_SUFFIX:mx8mq  = "-mx8m"
MACHINE_SOCARCH_SUFFIX:mx8qxp = "-mx8"
MACHINE_SOCARCH_SUFFIX:use-mainline-bsp = "-imx"

MACHINE_ARCH_FILTER = "virtual/kernel"
MACHINE_SOCARCH_FILTER:append_imx = " \
    alsa-lib \
    gstreamer1.0 \
    weston \
"
MACHINE_SOCARCH_FILTER:append_imxvpu = " \
    imx-codec \
    imx-vpuwrap \
    libimxvpuapi \
    virtual/imxvpu \
"
MACHINE_SOCARCH_FILTER:append_imxgpu = " \
    virtual/egl \
    virtual/mesa \
    virtual/libopenvg \
    libdrm \
    cairo \
    libgal-imx \
    opencv \
    pango \
"
MACHINE_SOCARCH_FILTER:append_imxgpu2d = " \
    virtual/libg2d \
"
MACHINE_SOCARCH_FILTER:append_imxgpu3d = " \
    virtual/libgl \
    virtual/libgles1 \
    virtual/libgles2 \
"
MACHINE_SOCARCH_FILTER:append_use-mainline-bsp = " \
    virtual/egl \
    virtual/libopenvg \
    virtual/libg2d \
    virtual/libgl \
    virtual/libgles1 \
    virtual/libgles2 \
    virtual/mesa \
    cairo \
    pango \
    qtbase \
"
MACHINE_SOCARCH_FILTER:append_mx6q = " \
    virtual/opencl-icd \
    opencl-headers \
"
MACHINE_SOCARCH_FILTER:append_mx8 = " \
    virtual/opencl-icd \
    opencl-headers \
"
MACHINE_SOCARCH_FILTER:append_mx8qm = " \
    virtual/libopenvx \
"

INHERIT += "fsl-dynamic-packagearch"

SIGGEN_EXCLUDE_SAFE_RECIPE_DEPS:append = " \
    imx-gpu-viv->kernel-module-imx-gpu-viv \
    libimxvpuapi->virtual/imxvpu \
    imx-vpuwrap->virtual/imxvpu \
    imx-codec->virtual/imxvpu \
    imx-test->virtual/imxvpu \
"

# Firmware
MACHINE_FIRMWARE ?= ""
MACHINE_FIRMWARE:append_mx25 = " firmware-imx-sdma-imx25"
MACHINE_FIRMWARE:append_mx27 = " firmware-imx-vpu-imx27"
MACHINE_FIRMWARE:append_mx7d = " linux-firmware-imx-sdma-imx7d firmware-imx-epdc"
MACHINE_FIRMWARE:append_mx6 = " linux-firmware-imx-sdma-imx6q"
MACHINE_FIRMWARE:append_mx6q = " firmware-imx-vpu-imx6q"
MACHINE_FIRMWARE:append_mx6dl = " firmware-imx-vpu-imx6d firmware-imx-epdc"
MACHINE_FIRMWARE:append_mx6sl = " firmware-imx-epdc"
MACHINE_FIRMWARE:append_mx6sll = " firmware-imx-epdc"
MACHINE_FIRMWARE:append_mx6ull = " firmware-imx-epdc"
MACHINE_FIRMWARE:append_mx53 = " firmware-imx-vpu-imx53 firmware-imx-sdma-imx53"
MACHINE_FIRMWARE:append_mx51 = " firmware-imx-vpu-imx51 firmware-imx-sdma-imx51"
MACHINE_FIRMWARE:append_mx8mm  = " linux-firmware-imx-sdma-imx7d"
MACHINE_FIRMWARE:append_mx8mn  = " linux-firmware-imx-sdma-imx7d"
MACHINE_FIRMWARE:append_mx8mp  = " linux-firmware-imx-sdma-imx7d firmware-imx-easrc-imx8mn firmware-imx-xcvr-imx8mp firmware-sof-imx"
MACHINE_FIRMWARE:append_mx8mq  = " linux-firmware-imx-sdma-imx7d"
MACHINE_FIRMWARE:append_use-mainline-bsp = " linux-firmware-imx-sdma-imx6q linux-firmware-imx-sdma-imx7d firmware-imx-vpu-imx6q firmware-imx-vpu-imx6d"

# FIXME: Needs addition of firmware-imx of official BSPs
#MACHINE_FIRMWARE:append_mx8qxp = " firmware-imx-vpu-imx8qxp"

MACHINE_EXTRA_RRECOMMENDS += "${MACHINE_FIRMWARE}"

# Extra audio support
IMX_ALSA_EXTRA = ""
IMX_ALSA_EXTRA:use-nxp-bsp = "imx-alsa-plugins"
MACHINE_EXTRA_RRECOMMENDS:append_mx6 = " ${@bb.utils.contains('DISTRO_FEATURES', 'alsa', '${IMX_ALSA_EXTRA}', '', d)}"
MACHINE_EXTRA_RRECOMMENDS:append_mx7 = " ${@bb.utils.contains('DISTRO_FEATURES', 'alsa', '${IMX_ALSA_EXTRA}', '', d)}"
MACHINE_EXTRA_RRECOMMENDS:append_mx8 = " ${@bb.utils.contains('DISTRO_FEATURES', 'alsa', '${IMX_ALSA_EXTRA}', '', d)}"

# Extra Cypress Wi-Fi and BTW firmware (Murata)
MACHINE_FIRMWARE:append = " ${@bb.utils.contains('MACHINE_FEATURES', 'bcm4339', 'linux-firmware-bcm4339', '', d)}"
MACHINE_FIRMWARE:append = " ${@bb.utils.contains('MACHINE_FEATURES', 'bcm43430', 'linux-firmware-bcm43430', '', d)}"
MACHINE_FIRMWARE:append = " ${@bb.utils.contains('MACHINE_FEATURES', 'bcm43455', 'linux-firmware-bcm43455', '', d)}"
MACHINE_FIRMWARE:append = " ${@bb.utils.contains('MACHINE_FEATURES', 'bcm4356', 'linux-firmware-bcm4356-pcie', '', d)}"
MACHINE_FIRMWARE:append = " ${@bb.utils.contains('MACHINE_FEATURES', 'bcm4359', 'linux-firmware-bcm4359-pcie', '', d)}"

# Extra QCA Wi-Fi & BTE driver and firmware
MACHINE_EXTRA_RRECOMMENDS:append = " ${@bb.utils.contains('MACHINE_FEATURES', 'qca6174', 'packagegroup-fsl-qca6174', '', d)}"
MACHINE_EXTRA_RRECOMMENDS:append = " ${@bb.utils.contains('MACHINE_FEATURES', 'qca9377', 'packagegroup-fsl-qca9377', '', d)}"

# Extra udev rules
MACHINE_EXTRA_RRECOMMENDS += "udev-rules-imx"

# Jailhouse
MACHINE_EXTRA_RRECOMMENDS += " \
    ${@bb.utils.contains('COMBINED_FEATURES', 'jailhouse', 'jailhouse', '', d)} \
"

# GStreamer 1.0 plugins
MACHINE_GSTREAMER_1_0_PLUGIN        ?= ""
MACHINE_GSTREAMER_1_0_PLUGIN:mx6dl  ?= "gstreamer1.0-plugins-imx-meta"
MACHINE_GSTREAMER_1_0_PLUGIN:mx6q   ?= "gstreamer1.0-plugins-imx-meta"
MACHINE_GSTREAMER_1_0_PLUGIN:mx6sl  ?= "gstreamer1.0-plugins-imx-meta"
MACHINE_GSTREAMER_1_0_PLUGIN:mx6sx  ?= "gstreamer1.0-plugins-imx-meta"
MACHINE_GSTREAMER_1_0_PLUGIN:mx6ul  ?= "gstreamer1.0-plugins-imx-meta"
MACHINE_GSTREAMER_1_0_PLUGIN:mx6ull ?= "gstreamer1.0-plugins-imx-meta"
MACHINE_GSTREAMER_1_0_PLUGIN:mx7d   ?= "gstreamer1.0-plugins-imx-meta"
MACHINE_GSTREAMER_1_0_PLUGIN:mx8mm  ?= "imx-gst1.0-plugin"
MACHINE_GSTREAMER_1_0_PLUGIN:mx8mn  ?= "imx-gst1.0-plugin"
MACHINE_GSTREAMER_1_0_PLUGIN:mx8mp  ?= "imx-gst1.0-plugin"

# Determines if the SoC has support for Vivante kernel driver
SOC_HAS_VIVANTE_KERNEL_DRIVER_SUPPORT        = "0"
SOC_HAS_VIVANTE_KERNEL_DRIVER_SUPPORT:imxgpu = "1"

# Handle Vivante kernel driver setting:
#   0 - machine does not have Vivante GPU driver support
#   1 - machine has Vivante GPU driver support
MACHINE_HAS_VIVANTE_KERNEL_DRIVER_SUPPORT ?= "${SOC_HAS_VIVANTE_KERNEL_DRIVER_SUPPORT}"

# Graphics libraries
PREFERRED_PROVIDER_virtual/egl      ?= "mesa"
PREFERRED_PROVIDER_virtual/libgl    ?= "mesa"
PREFERRED_PROVIDER_virtual/libgles1 ?= "mesa"
PREFERRED_PROVIDER_virtual/libgles2 ?= "mesa"

PREFERRED_PROVIDER_virtual/egl_imxgpu        ?= "imx-gpu-viv"
PREFERRED_PROVIDER_virtual/libgl_imxgpu3d    ?= "imx-gpu-viv"
PREFERRED_PROVIDER_virtual/libgles1_imxgpu3d ?= "imx-gpu-viv"
PREFERRED_PROVIDER_virtual/libgles2_imxgpu3d ?= "imx-gpu-viv"
PREFERRED_PROVIDER_virtual/libg2d            ?= "imx-gpu-g2d"
PREFERRED_PROVIDER_virtual/libg2d_imxdpu     ?= "imx-dpu-g2d"

PREFERRED_VERSION_weston_imx ?= "8.0.0.imx"
PREFERRED_VERSION_weston_use-mainline-bsp = ""

PREFERRED_VERSION_wayland-protocols_mx6 ?= "1.18.imx"
PREFERRED_VERSION_wayland-protocols_mx7 ?= "1.18.imx"
PREFERRED_VERSION_wayland-protocols_mx8 ?= "1.18.imx"

# Use i.MX libdrm Version
PREFERRED_VERSION_libdrm_mx6 ?= "2.4.99.imx"
PREFERRED_VERSION_libdrm_mx7 ?= "2.4.99.imx"
PREFERRED_VERSION_libdrm_mx8 ?= "2.4.99.imx"

# Use i.MX optee Version
PREFERRED_VERSION_optee-os_mx8     ?= "3.7.0.imx"
PREFERRED_VERSION_optee-client_mx8 ?= "3.7.0.imx"
PREFERRED_VERSION_optee-test_mx8   ?= "3.7.0.imx"

# Handle default kernel
IMX_DEFAULT_KERNEL = "linux-fslc-imx"
IMX_DEFAULT_KERNEL:mxs = "linux-fslc"
IMX_DEFAULT_KERNEL:mx5 = "linux-fslc"
IMX_DEFAULT_KERNEL:mx6 = "linux-fslc-imx"
IMX_DEFAULT_KERNEL:mx7 = "linux-fslc-imx"
IMX_DEFAULT_KERNEL:mx8 = "linux-fslc-imx"
IMX_DEFAULT_KERNEL:mx7ulp = "linux-fslc-imx"
IMX_DEFAULT_KERNEL:mx6sll = "linux-fslc-imx"
IMX_DEFAULT_KERNEL:mx6ul = "linux-fslc-imx"
IMX_DEFAULT_KERNEL:mx6ull = "linux-fslc-imx"
IMX_DEFAULT_KERNEL:use-mainline-bsp = "linux-fslc"

PREFERRED_PROVIDER_virtual/kernel ??= "${IMX_DEFAULT_KERNEL}"

SOC_DEFAULT_IMAGE_FSTYPES = "wic.bmap wic.gz"
SOC_DEFAULT_IMAGE_FSTYPES:mxs = "uboot-mxsboot-sdcard wic.bmap wic.gz"

# Do not update fstab file when using wic images
WIC_CREATE_EXTRA_ARGS ?= "--no-fstab-update"

OPTEE_BOOT_IMAGE         = "uTee"
OPTEE_BOOT_IMAGE:aarch64 = ""

IMAGE_FSTYPES ?= "${SOC_DEFAULT_IMAGE_FSTYPES}"

IMAGE_BOOT_FILES ?= " \
    ${KERNEL_IMAGETYPE} \
    ${@make_dtb_boot_files(d)} \
    ${@bb.utils.contains('MACHINE_FEATURES', 'optee', '${OPTEE_BOOT_IMAGE}', '', d)} \
"

### wic default support
OPTEE_WKS_FILE_DEPENDS         = "optee-os"
OPTEE_WKS_FILE_DEPENDS:aarch64 = ""

WKS_FILE_DEPENDS ?= " \
    virtual/bootloader \
    \
    e2fsprogs-native \
    bmap-tools-native \
    ${@bb.utils.contains('MACHINE_FEATURES', 'optee', '${OPTEE_WKS_FILE_DEPENDS}', '', d)} \
"

WKS_FILE_DEPENDS:append_mx8 = " imx-boot "

SOC_DEFAULT_WKS_FILE ?= "imx-uboot-bootpart.wks.in"
SOC_DEFAULT_WKS_FILE:mx8 ?= "imx-imx-boot-bootpart.wks.in"
SOC_DEFAULT_WKS_FILE:mxs ?= "imx-uboot-mxs-bootpart.wks.in"

WKS_FILE ?= "${SOC_DEFAULT_WKS_FILE}"

# Certain machines override the default fsl u-boot with the
# fslc u-boot. To restore the fsl u-boot, add use-fsl-bsp like this:
#   MACHINEOVERRIDES:prepend_imx6ulevk = "use-fsl-bsp:"
UBOOT_MAKE_TARGET:use-fsl-bsp_mx6 = "u-boot.imx"
UBOOT_SUFFIX:use-fsl-bsp_mx6 = "imx"
SPL_BINARY:use-fsl-bsp_mx6 = ""
WKS_FILE:use-fsl-bsp_mx6 = "imx-uboot-bootpart.wks.in"
UBOOT_MAKE_TARGET:use-fsl-bsp_mx7 = "u-boot.imx"
UBOOT_SUFFIX:use-fsl-bsp_mx7 = "imx"
SPL_BINARY:use-fsl-bsp_mx7 = ""
WKS_FILE:use-fsl-bsp_mx7 = "imx-uboot-bootpart.wks.in"

SERIAL_CONSOLES = "115200;ttymxc0"
SERIAL_CONSOLES:mxs = "115200;ttyAMA0"

KERNEL_IMAGETYPE = "zImage"
KERNEL_IMAGETYPE:aarch64 = "Image"

MACHINE_FEATURES = "usbgadget usbhost vfat alsa touchscreen"

SOC_MACHINE_FEATURES_BACKFILL:mx8m = "jailhouse"
MACHINE_FEATURES_BACKFILL:append = " ${SOC_MACHINE_FEATURES_BACKFILL}"

# Add the ability to specify _imx machines
MACHINEOVERRIDES =. "imx:"

HOSTTOOLS_NONFATAL:append_mx8 = " sha384sum"
