#
# Automatically generated make config: don't edit
# Linux kernel version: 2.6.16ADI-2006R1
# Tue Apr 25 15:54:35 2006
#
# CONFIG_MMU is not set
# CONFIG_FPU is not set
CONFIG_RWSEM_GENERIC_SPINLOCK=y
# CONFIG_RWSEM_XCHGADD_ALGORITHM is not set
CONFIG_BFIN=y
CONFIG_SEMAPHORE_SLEEPERS=y
CONFIG_UCLINUX=y
CONFIG_FORCE_MAX_ZONEORDER=14
CONFIG_GENERIC_CALIBRATE_DELAY=y

#
# Code maturity level options
#
CONFIG_EXPERIMENTAL=y
CONFIG_BROKEN_ON_SMP=y
CONFIG_INIT_ENV_ARG_LIMIT=32

#
# General setup
#
CONFIG_LOCALVERSION="blackfin"
CONFIG_LOCALVERSION_AUTO=y
# CONFIG_SYSVIPC is not set
# CONFIG_POSIX_MQUEUE is not set
# CONFIG_BSD_PROCESS_ACCT is not set
CONFIG_SYSCTL=y
# CONFIG_AUDIT is not set
# CONFIG_IKCONFIG is not set
CONFIG_INITRAMFS_SOURCE=""
CONFIG_UID16=y
# CONFIG_CC_OPTIMIZE_FOR_SIZE is not set
CONFIG_EMBEDDED=y
CONFIG_KALLSYMS=y
# CONFIG_KALLSYMS_EXTRA_PASS is not set
# CONFIG_HOTPLUG is not set
CONFIG_PRINTK=y
CONFIG_BUG=y
CONFIG_ELF_CORE=y
CONFIG_BASE_FULL=y
CONFIG_FUTEX=y
CONFIG_EPOLL=y
CONFIG_CC_ALIGN_FUNCTIONS=0
CONFIG_CC_ALIGN_LABELS=0
CONFIG_CC_ALIGN_LOOPS=0
CONFIG_CC_ALIGN_JUMPS=0
CONFIG_SLAB=y
CONFIG_BASE_SMALL=0
# CONFIG_SLOB is not set
CONFIG_OBSOLETE_INTERMODULE=m

#
# Loadable module support
#
CONFIG_MODULES=y
CONFIG_MODULE_UNLOAD=y
# CONFIG_MODULE_FORCE_UNLOAD is not set
CONFIG_OBSOLETE_MODPARM=y
# CONFIG_MODVERSIONS is not set
# CONFIG_MODULE_SRCVERSION_ALL is not set
CONFIG_KMOD=y

#
# Block layer
#

#
# IO Schedulers
#
CONFIG_IOSCHED_NOOP=y
CONFIG_IOSCHED_AS=y
# CONFIG_IOSCHED_DEADLINE is not set
CONFIG_IOSCHED_CFQ=y
CONFIG_DEFAULT_AS=y
# CONFIG_DEFAULT_DEADLINE is not set
# CONFIG_DEFAULT_CFQ is not set
# CONFIG_DEFAULT_NOOP is not set
CONFIG_DEFAULT_IOSCHED="anticipatory"

#
# Blackfin Processor Options
#

#
# Processor and Board Settings
#
# CONFIG_BF533 is not set
# CONFIG_BF532 is not set
# CONFIG_BF531 is not set
# CONFIG_BF534 is not set
# CONFIG_BF535 is not set
# CONFIG_BF536 is not set
# CONFIG_BF537 is not set
CONFIG_BF561=y
CONFIG_BLACKFIN=y
CONFIG_BFIN_DUAL_CORE=y
# CONFIG_BFIN533_EZKIT is not set
# CONFIG_BFIN533_STAMP is not set
# CONFIG_BFIN537_STAMP is not set
# CONFIG_BFIN533_BLUETECHNIX_CM is not set
CONFIG_BFIN561_EZKIT=y
# CONFIG_GENERIC_BOARD is not set
CONFIG_MEM_MT48LC16M16A2TG_75=y

#
# BF561 Specific Configuration
#

#
# Core B Support
#

#
# Core B Support
#
CONFIG_BF561_COREB=y
CONFIG_BF561_COREB_RESET=y

#
# Interrupt Priority Assignment
#

#
# Priority
#
CONFIG_IRQ_PLL_WAKEUP=7
CONFIG_IRQ_DMA1_ERROR=7
CONFIG_IRQ_DMA2_ERROR=7
CONFIG_IRQ_IMDMA_ERROR=7
CONFIG_IRQ_PPI0_ERROR=7
CONFIG_IRQ_PPI1_ERROR=7
CONFIG_IRQ_SPORT0_ERROR=7
CONFIG_IRQ_SPORT1_ERROR=7
CONFIG_IRQ_SPI_ERROR=7
CONFIG_IRQ_UART_ERROR=7
CONFIG_IRQ_RESERVED_ERROR=7
CONFIG_IRQ_DMA1_0=8
CONFIG_IRQ_DMA1_1=8
CONFIG_IRQ_DMA1_2=8
CONFIG_IRQ_DMA1_3=8
CONFIG_IRQ_DMA1_4=8
CONFIG_IRQ_DMA1_5=8
CONFIG_IRQ_DMA1_6=8
CONFIG_IRQ_DMA1_7=8
CONFIG_IRQ_DMA1_8=8
CONFIG_IRQ_DMA1_9=8
CONFIG_IRQ_DMA1_10=8
CONFIG_IRQ_DMA1_11=8
CONFIG_IRQ_DMA2_0=9
CONFIG_IRQ_DMA2_1=9
CONFIG_IRQ_DMA2_2=9
CONFIG_IRQ_DMA2_3=9
CONFIG_IRQ_DMA2_4=9
CONFIG_IRQ_DMA2_5=9
CONFIG_IRQ_DMA2_6=9
CONFIG_IRQ_DMA2_7=9
CONFIG_IRQ_DMA2_8=9
CONFIG_IRQ_DMA2_9=9
CONFIG_IRQ_DMA2_10=9
CONFIG_IRQ_DMA2_11=9
CONFIG_IRQ_TIMER0=10
CONFIG_IRQ_TIMER1=10
CONFIG_IRQ_TIMER2=10
CONFIG_IRQ_TIMER3=10
CONFIG_IRQ_TIMER4=10
CONFIG_IRQ_TIMER5=10
CONFIG_IRQ_TIMER6=10
CONFIG_IRQ_TIMER7=10
CONFIG_IRQ_TIMER8=10
CONFIG_IRQ_TIMER9=10
CONFIG_IRQ_TIMER10=10
CONFIG_IRQ_TIMER11=10
CONFIG_IRQ_PROG0_INTA=11
CONFIG_IRQ_PROG0_INTB=11
CONFIG_IRQ_PROG1_INTA=11
CONFIG_IRQ_PROG1_INTB=11
CONFIG_IRQ_PROG2_INTA=11
CONFIG_IRQ_PROG2_INTB=11
CONFIG_IRQ_DMA1_WRRD0=8
CONFIG_IRQ_DMA1_WRRD1=8
CONFIG_IRQ_DMA2_WRRD0=9
CONFIG_IRQ_DMA2_WRRD1=9
CONFIG_IRQ_IMDMA_WRRD0=12
CONFIG_IRQ_IMDMA_WRRD1=12
CONFIG_IRQ_WDTIMER=13

#
# Board specific issues
#

#
# Board Setup
#
CONFIG_CLKIN_HZ=30000000
CONFIG_MEM_SIZE=64
CONFIG_MEM_ADD_WIDTH=9

#
# LED Status Indicators
#

#
# Console UART Setup
#
# CONFIG_BAUD_9600 is not set
# CONFIG_BAUD_19200 is not set
# CONFIG_BAUD_38400 is not set
CONFIG_BAUD_57600=y
# CONFIG_BAUD_115200 is not set
CONFIG_BAUD_NO_PARITY=y
# CONFIG_BAUD_PARITY is not set
CONFIG_BAUD_1_STOPBIT=y
# CONFIG_BAUD_2_STOPBIT is not set
CONFIG_RAMKERNEL=y
# CONFIG_ROMKERNEL is not set
CONFIG_SELECT_MEMORY_MODEL=y
CONFIG_FLATMEM_MANUAL=y
# CONFIG_DISCONTIGMEM_MANUAL is not set
# CONFIG_SPARSEMEM_MANUAL is not set
CONFIG_FLATMEM=y
CONFIG_FLAT_NODE_MEM_MAP=y
# CONFIG_SPARSEMEM_STATIC is not set
CONFIG_SPLIT_PTLOCK_CPUS=4
CONFIG_LARGE_ALLOCS=y
# CONFIG_IRQCHIP_DEMUX_GPIO is not set

#
# DMA Support
#
# CONFIG_NO_DMA is not set
CONFIG_BFIN_DMA_5XX=y

#
# Cache Support
#
CONFIG_BLKFIN_CACHE=y
CONFIG_BLKFIN_DCACHE=y
# CONFIG_BLKFIN_CACHE_LOCK is not set
# CONFIG_BLKFIN_WB is not set
CONFIG_BLKFIN_WT=y
CONFIG_UNCACHED_1M=y

#
# Clock Settings
#
# CONFIG_HZ_100 is not set
CONFIG_HZ_250=y
# CONFIG_HZ_1000 is not set
CONFIG_HZ=250
# CONFIG_BFIN_KERNEL_CLOCK is not set

#
# Asynchonous Memory Configuration
#

#
# EBIU_AMBCTL Global Control
#
CONFIG_C_AMCKEN=y
CONFIG_C_CDPRIO=y
CONFIG_C_B0PEN=y
CONFIG_C_B1PEN=y
CONFIG_C_B2PEN=y
# CONFIG_C_B3PEN is not set
# CONFIG_C_AMBEN is not set
# CONFIG_C_AMBEN_B0 is not set
# CONFIG_C_AMBEN_B0_B1 is not set
# CONFIG_C_AMBEN_B0_B1_B2 is not set
CONFIG_C_AMBEN_ALL=y

#
# EBIU_AMBCTL Control
#
CONFIG_BANK_0=0x7BB0
CONFIG_BANK_1=0x7BB0
CONFIG_BANK_2=0x7BB0
CONFIG_BANK_3=0x99B3
# CONFIG_BFIN_SPORT is not set

#
# Bus options (PCI, PCMCIA, EISA, MCA, ISA)
#
# CONFIG_PCI is not set

#
# PCCARD (PCMCIA/CardBus) support
#
# CONFIG_PCCARD is not set

#
# PCI Hotplug Support
#

#
# Executable file formats
#
CONFIG_BINFMT_ELF_FDPIC=y
CONFIG_BINFMT_FLAT=y
# CONFIG_BINFMT_ZFLAT is not set
# CONFIG_BINFMT_SHARED_FLAT is not set
# CONFIG_BINFMT_MISC is not set

#
# Power management options
#
CONFIG_PM=y

#
# Networking
#
CONFIG_NET=y

#
# Networking options
#
# CONFIG_NETDEBUG is not set
CONFIG_PACKET=y
# CONFIG_PACKET_MMAP is not set
CONFIG_UNIX=y
# CONFIG_NET_KEY is not set
CONFIG_INET=y
# CONFIG_IP_MULTICAST is not set
# CONFIG_IP_ADVANCED_ROUTER is not set
CONFIG_IP_FIB_HASH=y
CONFIG_IP_PNP=y
# CONFIG_IP_PNP_DHCP is not set
# CONFIG_IP_PNP_BOOTP is not set
# CONFIG_IP_PNP_RARP is not set
# CONFIG_NET_IPIP is not set
# CONFIG_NET_IPGRE is not set
# CONFIG_ARPD is not set
CONFIG_SYN_COOKIES=y
# CONFIG_INET_AH is not set
# CONFIG_INET_ESP is not set
# CONFIG_INET_IPCOMP is not set
# CONFIG_INET_TUNNEL is not set
CONFIG_INET_DIAG=y
CONFIG_INET_TCP_DIAG=y
# CONFIG_TCP_CONG_ADVANCED is not set
CONFIG_TCP_CONG_BIC=y
# CONFIG_IPV6 is not set
# CONFIG_NETFILTER is not set

#
# DCCP Configuration (EXPERIMENTAL)
#
# CONFIG_IP_DCCP is not set

#
# SCTP Configuration (EXPERIMENTAL)
#
# CONFIG_IP_SCTP is not set

#
# TIPC Configuration (EXPERIMENTAL)
#
# CONFIG_TIPC is not set
# CONFIG_ATM is not set
# CONFIG_BRIDGE is not set
# CONFIG_VLAN_8021Q is not set
# CONFIG_DECNET is not set
# CONFIG_LLC2 is not set
# CONFIG_IPX is not set
# CONFIG_ATALK is not set
# CONFIG_X25 is not set
# CONFIG_LAPB is not set
# CONFIG_NET_DIVERT is not set
# CONFIG_ECONET is not set
# CONFIG_WAN_ROUTER is not set

#
# QoS and/or fair queueing
#
# CONFIG_NET_SCHED is not set

#
# Network testing
#
# CONFIG_NET_PKTGEN is not set
# CONFIG_HAMRADIO is not set
# CONFIG_IRDA is not set
# CONFIG_BT is not set
# CONFIG_IEEE80211 is not set

#
# Device Drivers
#

#
# Generic Driver Options
#
CONFIG_STANDALONE=y
CONFIG_PREVENT_FIRMWARE_BUILD=y
# CONFIG_FW_LOADER is not set

#
# Connector - unified userspace <-> kernelspace linker
#
# CONFIG_CONNECTOR is not set

#
# Memory Technology Devices (MTD)
#
CONFIG_MTD=y
# CONFIG_MTD_DEBUG is not set
# CONFIG_MTD_CONCAT is not set
CONFIG_MTD_PARTITIONS=y
# CONFIG_MTD_REDBOOT_PARTS is not set
# CONFIG_MTD_CMDLINE_PARTS is not set

#
# User Modules And Translation Layers
#
CONFIG_MTD_CHAR=m
CONFIG_MTD_BLOCK=y
# CONFIG_FTL is not set
# CONFIG_NFTL is not set
# CONFIG_INFTL is not set
# CONFIG_RFD_FTL is not set

#
# RAM/ROM/Flash chip drivers
#
# CONFIG_MTD_CFI is not set
CONFIG_MTD_JEDECPROBE=m
CONFIG_MTD_GEN_PROBE=m
# CONFIG_MTD_CFI_ADV_OPTIONS is not set
CONFIG_MTD_MAP_BANK_WIDTH_1=y
CONFIG_MTD_MAP_BANK_WIDTH_2=y
CONFIG_MTD_MAP_BANK_WIDTH_4=y
# CONFIG_MTD_MAP_BANK_WIDTH_8 is not set
# CONFIG_MTD_MAP_BANK_WIDTH_16 is not set
# CONFIG_MTD_MAP_BANK_WIDTH_32 is not set
CONFIG_MTD_CFI_I1=y
CONFIG_MTD_CFI_I2=y
# CONFIG_MTD_CFI_I4 is not set
# CONFIG_MTD_CFI_I8 is not set
# CONFIG_MTD_CFI_INTELEXT is not set
# CONFIG_MTD_CFI_AMDSTD is not set
# CONFIG_MTD_CFI_STAA is not set
CONFIG_MTD_MW320D=m
CONFIG_MTD_RAM=y
CONFIG_MTD_ROM=m
# CONFIG_MTD_ABSENT is not set
# CONFIG_MTD_OBSOLETE_CHIPS is not set

#
# Mapping drivers for chip access
#
CONFIG_MTD_COMPLEX_MAPPINGS=y
CONFIG_MTD_BF5xx=m
CONFIG_BFIN_FLASH_SIZE=0x0400000
CONFIG_EBIU_FLASH_BASE=0x20000000

#
# FLASH_EBIU_AMBCTL Control
#
CONFIG_BFIN_FLASH_BANK_0=0x7BB0
CONFIG_BFIN_FLASH_BANK_1=0x7BB0
CONFIG_BFIN_FLASH_BANK_2=0x7BB0
CONFIG_BFIN_FLASH_BANK_3=0x7BB0
CONFIG_MTD_UCLINUX=y
# CONFIG_MTD_PLATRAM is not set

#
# Self-contained MTD device drivers
#
# CONFIG_MTD_SLRAM is not set
# CONFIG_MTD_PHRAM is not set
# CONFIG_MTD_MTDRAM is not set
# CONFIG_MTD_BLKMTD is not set
# CONFIG_MTD_BLOCK2MTD is not set

#
# Disk-On-Chip Device Drivers
#
# CONFIG_MTD_DOC2000 is not set
# CONFIG_MTD_DOC2001 is not set
# CONFIG_MTD_DOC2001PLUS is not set

#
# NAND Flash Device Drivers
#
# CONFIG_MTD_NAND is not set

#
# OneNAND Flash Device Drivers
#
# CONFIG_MTD_ONENAND is not set

#
# Parallel port support
#
# CONFIG_PARPORT is not set

#
# Plug and Play support
#

#
# Block devices
#
# CONFIG_BLK_DEV_COW_COMMON is not set
# CONFIG_BLK_DEV_LOOP is not set
# CONFIG_BLK_DEV_NBD is not set
CONFIG_BLK_DEV_RAM=y
CONFIG_BLK_DEV_RAM_COUNT=16
CONFIG_BLK_DEV_RAM_SIZE=4096
# CONFIG_BLK_DEV_INITRD is not set
# CONFIG_CDROM_PKTCDVD is not set
# CONFIG_ATA_OVER_ETH is not set

#
# ATA/ATAPI/MFM/RLL support
#
# CONFIG_IDE is not set

#
# SCSI device support
#
# CONFIG_RAID_ATTRS is not set
# CONFIG_SCSI is not set

#
# Multi-device support (RAID and LVM)
#
# CONFIG_MD is not set

#
# Fusion MPT device support
#
# CONFIG_FUSION is not set

#
# IEEE 1394 (FireWire) support
#

#
# I2O device support
#

#
# Network device support
#
CONFIG_NETDEVICES=y
# CONFIG_DUMMY is not set
# CONFIG_BONDING is not set
# CONFIG_EQUALIZER is not set
# CONFIG_TUN is not set

#
# PHY device support
#
# CONFIG_PHYLIB is not set

#
# Ethernet (10 or 100Mbit)
#
CONFIG_NET_ETHERNET=y
CONFIG_MII=y
CONFIG_SMC91X=y

#
# Ethernet (1000 Mbit)
#

#
# Ethernet (10000 Mbit)
#

#
# Token Ring devices
#

#
# Wireless LAN (non-hamradio)
#
# CONFIG_NET_RADIO is not set

#
# Wan interfaces
#
# CONFIG_WAN is not set
# CONFIG_PPP is not set
# CONFIG_SLIP is not set
# CONFIG_SHAPER is not set
# CONFIG_NETCONSOLE is not set
# CONFIG_NETPOLL is not set
# CONFIG_NET_POLL_CONTROLLER is not set

#
# ISDN subsystem
#
# CONFIG_ISDN is not set

#
# Telephony Support
#
# CONFIG_PHONE is not set

#
# Input device support
#
# CONFIG_INPUT is not set

#
# Hardware I/O ports
#
# CONFIG_SERIO is not set
# CONFIG_GAMEPORT is not set

#
# Character devices
#
# CONFIG_SPI_ADC_BF533 is not set
# CONFIG_BF533_PFLAGS is not set
# CONFIG_BF5xx_PPIFCD is not set
# CONFIG_BF5xx_PPI is not set
# CONFIG_BFIN_TIMER_LATENCY is not set
# CONFIG_VT is not set
# CONFIG_SERIAL_NONSTANDARD is not set

#
# Serial drivers
#
# CONFIG_SERIAL_8250 is not set

#
# Non-8250 serial port support
#
CONFIG_SERIAL_BLACKFIN=y
CONFIG_SERIAL_BLACKFIN_DMA=y
# CONFIG_SERIAL_BLACKFIN_PIO is not set
CONFIG_UNIX98_PTYS=y
CONFIG_LEGACY_PTYS=y
CONFIG_LEGACY_PTY_COUNT=256

#
# CAN, the car bus and industrial fieldbus
#
# CONFIG_CAN4LINUX is not set

#
# IPMI
#
# CONFIG_IPMI_HANDLER is not set

#
# Watchdog Cards
#
# CONFIG_WATCHDOG is not set
# CONFIG_RTC is not set
# CONFIG_GEN_RTC is not set
# CONFIG_BLACKFIN_RTC is not set
# CONFIG_BLACKFIN_DPMC is not set
# CONFIG_DTLK is not set
# CONFIG_R3964 is not set

#
# Ftape, the floppy tape device driver
#
# CONFIG_RAW_DRIVER is not set

#
# TPM devices
#
# CONFIG_TCG_TPM is not set
# CONFIG_TELCLOCK is not set

#
# I2C support
#
# CONFIG_I2C is not set

#
# SPI support
#
# CONFIG_SPI is not set
# CONFIG_SPI_MASTER is not set

#
# Dallas's 1-wire bus
#
# CONFIG_W1 is not set

#
# Hardware Monitoring support
#
CONFIG_HWMON=y
# CONFIG_HWMON_VID is not set
# CONFIG_SENSORS_F71805F is not set
# CONFIG_HWMON_DEBUG_CHIP is not set

#
# Misc devices
#

#
# Multimedia Capabilities Port drivers
#

#
# Multimedia devices
#
# CONFIG_VIDEO_DEV is not set

#
# Digital Video Broadcasting Devices
#
# CONFIG_DVB is not set

#
# Graphics support
#
# CONFIG_FB is not set

#
# Sound
#
# CONFIG_SOUND is not set

#
# USB support
#
CONFIG_USB_ARCH_HAS_HCD=y
# CONFIG_USB_ARCH_HAS_OHCI is not set
# CONFIG_USB is not set

#
# NOTE: USB_STORAGE enables SCSI, and 'SCSI disk support'
#

#
# USB Gadget Support
#
# CONFIG_USB_GADGET is not set

#
# MMC/SD Card support
#
# CONFIG_MMC is not set

#
# InfiniBand support
#

#
# EDAC - error detection and reporting (RAS) (EXPERIMENTAL)
#

#
# File systems
#
CONFIG_EXT2_FS=y
CONFIG_EXT2_FS_XATTR=y
# CONFIG_EXT2_FS_POSIX_ACL is not set
# CONFIG_EXT2_FS_SECURITY is not set
# CONFIG_EXT2_FS_XIP is not set
# CONFIG_EXT3_FS is not set
CONFIG_FS_MBCACHE=y
# CONFIG_REISERFS_FS is not set
# CONFIG_JFS_FS is not set
# CONFIG_FS_POSIX_ACL is not set
# CONFIG_XFS_FS is not set
# CONFIG_OCFS2_FS is not set
# CONFIG_MINIX_FS is not set
# CONFIG_ROMFS_FS is not set
CONFIG_INOTIFY=y
# CONFIG_QUOTA is not set
CONFIG_DNOTIFY=y
# CONFIG_AUTOFS_FS is not set
# CONFIG_AUTOFS4_FS is not set
# CONFIG_FUSE_FS is not set

#
# CD-ROM/DVD Filesystems
#
# CONFIG_ISO9660_FS is not set
# CONFIG_UDF_FS is not set

#
# DOS/FAT/NT Filesystems
#
# CONFIG_MSDOS_FS is not set
# CONFIG_VFAT_FS is not set
# CONFIG_NTFS_FS is not set

#
# Pseudo filesystems
#
CONFIG_PROC_FS=y
CONFIG_SYSFS=y
# CONFIG_TMPFS is not set
# CONFIG_HUGETLB_PAGE is not set
CONFIG_RAMFS=y
# CONFIG_RELAYFS_FS is not set
# CONFIG_CONFIGFS_FS is not set

#
# Miscellaneous filesystems
#
# CONFIG_ADFS_FS is not set
# CONFIG_AFFS_FS is not set
# CONFIG_HFS_FS is not set
# CONFIG_HFSPLUS_FS is not set
# CONFIG_BEFS_FS is not set
# CONFIG_BFS_FS is not set
# CONFIG_EFS_FS is not set
CONFIG_YAFFS_FS=m
CONFIG_YAFFS_YAFFS1=y
# CONFIG_YAFFS_DOES_ECC is not set
CONFIG_YAFFS_YAFFS2=y
CONFIG_YAFFS_AUTO_YAFFS2=y
# CONFIG_YAFFS_DISABLE_LAZY_LOAD is not set
# CONFIG_YAFFS_DISABLE_WIDE_TNODES is not set
CONFIG_YAFFS_DISABLE_CHUNK_ERASED_CHECK=y
CONFIG_YAFFS_SHORT_NAMES_IN_RAM=y
# CONFIG_JFFS_FS is not set
CONFIG_JFFS2_FS=m
CONFIG_JFFS2_FS_DEBUG=0
CONFIG_JFFS2_FS_WRITEBUFFER=y
# CONFIG_JFFS2_SUMMARY is not set
# CONFIG_JFFS2_COMPRESSION_OPTIONS is not set
CONFIG_JFFS2_ZLIB=y
CONFIG_JFFS2_RTIME=y
# CONFIG_JFFS2_RUBIN is not set
# CONFIG_CRAMFS is not set
# CONFIG_VXFS_FS is not set
# CONFIG_HPFS_FS is not set
# CONFIG_QNX4FS_FS is not set
# CONFIG_SYSV_FS is not set
# CONFIG_UFS_FS is not set

#
# Network File Systems
#
CONFIG_NFS_FS=m
CONFIG_NFS_V3=y
# CONFIG_NFS_V3_ACL is not set
# CONFIG_NFS_V4 is not set
# CONFIG_NFS_DIRECTIO is not set
# CONFIG_NFSD is not set
CONFIG_LOCKD=m
CONFIG_LOCKD_V4=y
CONFIG_NFS_COMMON=y
CONFIG_SUNRPC=m
# CONFIG_RPCSEC_GSS_KRB5 is not set
# CONFIG_RPCSEC_GSS_SPKM3 is not set
CONFIG_SMB_FS=m
# CONFIG_SMB_NLS_DEFAULT is not set
# CONFIG_CIFS is not set
# CONFIG_NCP_FS is not set
# CONFIG_CODA_FS is not set
# CONFIG_AFS_FS is not set
# CONFIG_9P_FS is not set

#
# Partition Types
#
# CONFIG_PARTITION_ADVANCED is not set
CONFIG_MSDOS_PARTITION=y

#
# Native Language Support
#
CONFIG_NLS=m
CONFIG_NLS_DEFAULT="iso8859-1"
# CONFIG_NLS_CODEPAGE_437 is not set
# CONFIG_NLS_CODEPAGE_737 is not set
# CONFIG_NLS_CODEPAGE_775 is not set
# CONFIG_NLS_CODEPAGE_850 is not set
# CONFIG_NLS_CODEPAGE_852 is not set
# CONFIG_NLS_CODEPAGE_855 is not set
# CONFIG_NLS_CODEPAGE_857 is not set
# CONFIG_NLS_CODEPAGE_860 is not set
# CONFIG_NLS_CODEPAGE_861 is not set
# CONFIG_NLS_CODEPAGE_862 is not set
# CONFIG_NLS_CODEPAGE_863 is not set
# CONFIG_NLS_CODEPAGE_864 is not set
# CONFIG_NLS_CODEPAGE_865 is not set
# CONFIG_NLS_CODEPAGE_866 is not set
# CONFIG_NLS_CODEPAGE_869 is not set
# CONFIG_NLS_CODEPAGE_936 is not set
# CONFIG_NLS_CODEPAGE_950 is not set
# CONFIG_NLS_CODEPAGE_932 is not set
# CONFIG_NLS_CODEPAGE_949 is not set
# CONFIG_NLS_CODEPAGE_874 is not set
# CONFIG_NLS_ISO8859_8 is not set
# CONFIG_NLS_CODEPAGE_1250 is not set
# CONFIG_NLS_CODEPAGE_1251 is not set
# CONFIG_NLS_ASCII is not set
# CONFIG_NLS_ISO8859_1 is not set
# CONFIG_NLS_ISO8859_2 is not set
# CONFIG_NLS_ISO8859_3 is not set
# CONFIG_NLS_ISO8859_4 is not set
# CONFIG_NLS_ISO8859_5 is not set
# CONFIG_NLS_ISO8859_6 is not set
# CONFIG_NLS_ISO8859_7 is not set
# CONFIG_NLS_ISO8859_9 is not set
# CONFIG_NLS_ISO8859_13 is not set
# CONFIG_NLS_ISO8859_14 is not set
# CONFIG_NLS_ISO8859_15 is not set
# CONFIG_NLS_KOI8_R is not set
# CONFIG_NLS_KOI8_U is not set
# CONFIG_NLS_UTF8 is not set

#
# Profiling support
#
# CONFIG_PROFILING is not set

#
# Kernel hacking
#
# CONFIG_PRINTK_TIME is not set
# CONFIG_MAGIC_SYSRQ is not set
# CONFIG_DEBUG_KERNEL is not set
CONFIG_LOG_BUF_SHIFT=14
# CONFIG_DEBUG_BUGVERBOSE is not set
# CONFIG_DEBUG_INFO is not set
# CONFIG_DEBUG_SERIAL_EARLY_INIT is not set
# CONFIG_DEBUG_HWERR is not set
# CONFIG_DUAL_CORE_TEST_MODULE is not set
# CONFIG_BOOTPARAM is not set
# CONFIG_NO_KERNEL_MSG is not set
CONFIG_CPLB_INFO=y
# CONFIG_NO_ACCESS_CHECK is not set

#
# Security options
#
# CONFIG_KEYS is not set
CONFIG_SECURITY=y
# CONFIG_SECURITY_NETWORK is not set
CONFIG_SECURITY_CAPABILITIES=y
# CONFIG_SECURITY_SECLVL is not set

#
# Cryptographic options
#
# CONFIG_CRYPTO is not set

#
# Hardware crypto devices
#

#
# Library routines
#
# CONFIG_CRC_CCITT is not set
# CONFIG_CRC16 is not set
CONFIG_CRC32=y
# CONFIG_LIBCRC32C is not set
CONFIG_ZLIB_INFLATE=m
CONFIG_ZLIB_DEFLATE=m
