FILESEXTRAPATHS:prepend := "${THISDIR}/${BPN}:"

SRC_URI:append_qoriq-ppc = " file://ppc-fixplt.patch "

