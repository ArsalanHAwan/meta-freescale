BBCLASSEXTEND = ""

require recipes-devtools/qemu/qemu.inc

COMPATIBLE_MACHINE = "(qoriq)"

DEPENDS = "glib-2.0 zlib pixman bison-native"

LIC_FILES_CHKSUM = "file://COPYING;md5=441c28d2cf86e15a37fa47e15a72fbac \
                    file://COPYING.LIB;endline=24;md5=8c5efda6cf1e1b03dcfd0e6c0d271c7f"

SRC_URI = "gitsm://source.codeaurora.org/external/qoriq/qoriq-components/qemu;nobranch=1 \
           file://powerpc_rom.bin \
           file://run-ptest \
           file://0002-Add-subpackage-ptest-which-runs-all-unit-test-cases-.patch \
           file://0001-linux-user-remove-host-stime-syscall.patch \
           "

SRCREV = "521a0dcf59f1ca11e7d9e2f4e1ef3d2dfaebc0e4"

S = "${WORKDIR}/git"

python() {
    d.appendVar('PROVIDES', ' ' + d.getVar('BPN').replace('-qoriq', ''))
    pkgs = d.getVar('PACKAGES').split()
    for p in pkgs:
        if '-qoriq' in p:
            d.appendVar('RPROVIDES:' + p, ' ' + p.replace('-qoriq', ''))
            d.appendVar('RCONFLICTS:' + p, ' ' + p.replace('-qoriq', ''))
            d.appendVar('RREPLACES:' + p, ' ' + p.replace('-qoriq', ''))
}

RDEPENDS:${PN}:class-target += "bash"

EXTRA_OECONF:append:class-target = " --target-list=${@get_qemu_target_list(d)}"
EXTRA_OECONF:append:class-target:mipsarcho32 = "${@bb.utils.contains('BBEXTENDCURR', 'multilib', ' --disable-capstone', '', d)}"
EXTRA_OECONF:append:class-nativesdk = " --target-list=${@get_qemu_target_list(d)}"

do_install:append:class-nativesdk() {
     ${@bb.utils.contains('PACKAGECONFIG', 'gtk+', 'make_qemu_wrapper', '', d)}
}

PACKAGECONFIG ??= " \
    fdt sdl kvm aio libusb \
    ${@bb.utils.filter('DISTRO_FEATURES', 'alsa xen', d)} \
"
PACKAGECONFIG:class-nativesdk ??= "fdt sdl kvm"

PACKAGECONFIG[xkbcommon] = ",,"
PACKAGECONFIG[libudev] = ",,"

DISABLE_STATIC = ""

