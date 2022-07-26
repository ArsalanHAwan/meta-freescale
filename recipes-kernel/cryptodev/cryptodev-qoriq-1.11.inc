HOMEPAGE = "http://cryptodev-linux.org/"

LICENSE = "GPL-2.0-only"
LIC_FILES_CHKSUM = "file://COPYING;md5=b234ee4d69f5fce4486a80fdaf4a4263"

python() {
    d.appendVar('PROVIDES', ' ' + d.getVar('BPN').replace('-qoriq', ''))
    pkgs = d.getVar('PACKAGES').split()
    for p in pkgs:
        if '-qoriq' in p:
            d.appendVar("RPROVIDES:" + p, ' ' + p.replace('-qoriq', ''))
            d.appendVar("RCONFLICTS:" + p, ' ' + p.replace('-qoriq', ''))
            d.appendVar("RREPLACES:" + p, ' ' + p.replace('-qoriq', ''))
}

SRC_URI = "git://source.codeaurora.org/external/qoriq/qoriq-components/cryptodev-linux;protocol=https;nobranch=1"
SRCREV = "fabe5989a3dc9fba0cd0a40b612247cdde351c01"

S = "${WORKDIR}/git"

CLEANBROKEN = "1"
