PROVIDES:remove_imxgpu   = "virtual/egl"
PROVIDES:remove_imxgpu3d = "virtual/libgl virtual/libgles1 virtual/libgles2"

PACKAGECONFIG:remove_imxgpu   = "egl gbm"
PACKAGECONFIG:remove_imxgpu3d = "gles"

# FIXME: mesa should support 'x11-no-tls' option
python () {
    overrides = d.getVar("OVERRIDES").split(":")
    if "imxgpu2d" not in overrides:
        return

    x11flag = d.getVarFlag("PACKAGECONFIG", "x11", False)
    d.setVarFlag("PACKAGECONFIG", "x11", x11flag.replace("--enable-glx-tls", "--enable-glx"))
}

# Enable Etnaviv and Freedreno support
PACKAGECONFIG:append_use-mainline-bsp = " gallium etnaviv kmsro freedreno"

USE_OSMESA_ONLY ?= "no"

# Etnaviv support state for i.MX8 is unknown, therefore only enable OSMesa and
# disable Gallium for now. If you still want to enable Etnaviv, just set
# USE_OSMESA_ONLY:mx8 = "no" in your bbappend.
USE_OSMESA_ONLY:mx8 ?= "yes"

# Enable OSMesa which also requires dri (classic) swrast
PACKAGECONFIG:append = " ${@oe.utils.conditional('USE_OSMESA_ONLY', 'yes', ' osmesa', '', d)}"
PACKAGECONFIG:remove = " ${@oe.utils.conditional('USE_OSMESA_ONLY', 'yes', 'gallium', '', d)}"
DRIDRIVERS:append = "${@oe.utils.conditional('USE_OSMESA_ONLY', 'yes', 'swrast', '', d)}"

BACKEND = \
    "${@bb.utils.contains('DISTRO_FEATURES', 'wayland', 'wayland', \
        bb.utils.contains('DISTRO_FEATURES',     'x11',     'x11', \
                                                             'fb', d), d)}"

# FIXME: Dirty hack to allow use of Vivante GPU libGL binary
do_install:append_imxgpu3d () {
    rm -f ${D}${libdir}/libGL.* \
          ${D}${includedir}/GL/gl.h \
          ${D}${includedir}/GL/glcorearb.h \
          ${D}${includedir}/GL/glext.h \
          ${D}${includedir}/GL/glx.h \
          ${D}${includedir}/GL/glxext.h
    if [ "${BACKEND}" = "x11" ]; then
        rm -f ${D}${libdir}/pkgconfig/gl.pc
    fi
}

do_install:append_imxgpu () {
    rm -rf ${D}${includedir}/KHR
}
