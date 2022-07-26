require kernel-module-qcacld-lea.inc

SUMMARY = "Qualcomm WiFi driver for QCA module 9377"

EXTRA_OEMAKE += " \
    CONFIG_CLD_HL_SDIO_CORE=y \
    CONFIG_FEATURE_COEX_PTA_CONFIG_ENABLE=y \
    CONFIG_PER_VDEV_TX_DESC_POOL=1 \
    CONFIG_QCA_LL_TX_FLOW_CT=1 \
    CONFIG_QCA_SUPPORT_TXRX_DRIVER_TCP_DEL_ACK=y \
    CONFIG_WLAN_FEATURE_FILS=y \
    CONFIG_WLAN_WAPI_MODE_11AC_DISABLE=y \
    MODNAME=qca9377 \
    SAP_AUTH_OFFLOAD=1 \
"

RDEPENDS:${PN} += "firmware-qca9377"
