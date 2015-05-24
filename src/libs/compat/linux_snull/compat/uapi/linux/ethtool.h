#include <generated/autoconf.h>
#ifndef __UAPI_LINUX_ETHTOOL_H__
#define __UAPI_LINUX_ETHTOOL_H__

#include <linux/types.h>
#include <linux/if_ether.h>

/**
 * struct ethtool_cmd - link control and status
 * @cmd: Command number = %ETHTOOL_GSET or %ETHTOOL_SSET
 * @supported: Bitmask of %SUPPORTED_* flags for the link modes,
 *	physical connectors and other link features for which the
 *	interface supports autonegotiation or auto-detection.
 *	Read-only.
 * @advertising: Bitmask of %ADVERTISED_* flags for the link modes,
 *	physical connectors and other link features that are
 *	advertised through autonegotiation or enabled for
 *	auto-detection.
 * @speed: Low bits of the speed
 * @duplex: Duplex mode; one of %DUPLEX_*
 * @port: Physical connector type; one of %PORT_*
 * @phy_address: MDIO address of PHY (transceiver); 0 or 255 if not
 *	applicable.  For clause 45 PHYs this is the PRTAD.
 * @transceiver: Historically used to distinguish different possible
 *	PHY types, but not in a consistent way.  Deprecated.
 * @autoneg: Enable/disable autonegotiation and auto-detection;
 *	either %AUTONEG_DISABLE or %AUTONEG_ENABLE
 * @mdio_support: Bitmask of %ETH_MDIO_SUPPORTS_* flags for the MDIO
 *	protocols supported by the interface; 0 if unknown.
 *	Read-only.
 * @maxtxpkt: Historically used to report TX IRQ coalescing; now
 *	obsoleted by &struct ethtool_coalesce.  Read-only; deprecated.
 * @maxrxpkt: Historically used to report RX IRQ coalescing; now
 *	obsoleted by &struct ethtool_coalesce.  Read-only; deprecated.
 * @speed_hi: High bits of the speed
 * @eth_tp_mdix: Ethernet twisted-pair MDI(-X) status; one of
 *	%ETH_TP_MDI_*.  If the status is unknown or not applicable, the
 *	value will be %ETH_TP_MDI_INVALID.  Read-only.
 * @eth_tp_mdix_ctrl: Ethernet twisted pair MDI(-X) control; one of
 *	%ETH_TP_MDI_*.  If MDI(-X) control is not implemented, reads
 *	yield %ETH_TP_MDI_INVALID and writes may be ignored or rejected.
 *	When written successfully, the link should be renegotiated if
 *	necessary.
 * @lp_advertising: Bitmask of %ADVERTISED_* flags for the link modes
 *	and other link features that the link partner advertised
 *	through autonegotiation; 0 if unknown or not applicable.
 *	Read-only.
 *
 * The link speed in Mbps is split between @speed and @speed_hi.  Use
 * the ethtool_cmd_speed() and ethtool_cmd_speed_set() functions to
 * access it.
 *
 * If autonegotiation is disabled, the speed and @duplex represent the
 * fixed link mode and are writable if the driver supports multiple
 * link modes.  If it is enabled then they are read-only; if the link
 * is up they represent the negotiated link mode; if the link is down,
 * the speed is 0, %SPEED_UNKNOWN or the highest enabled speed and
 * @duplex is %DUPLEX_UNKNOWN or the best enabled duplex mode.
 *
 * Some hardware interfaces may have multiple PHYs and/or physical
 * connectors fitted or do not allow the driver to detect which are
 * fitted.  For these interfaces @port and/or @phy_address may be
 * writable, possibly dependent on @autoneg being %AUTONEG_DISABLE.
 * Otherwise, attempts to write different values may be ignored or
 * rejected.
 *
 * Users should assume that all fields not marked read-only are
 * writable and subject to validation by the driver.  They should use
 * %ETHTOOL_GSET to get the current values before making specific
 * changes and then applying them with %ETHTOOL_SSET.
 *
 * Drivers that implement set_settings() should validate all fields
 * other than @cmd that are not described as read-only or deprecated,
 * and must ignore all fields described as read-only.
 *
 * Deprecated fields should be ignored by both users and drivers.
 */
struct ethtool_cmd {
	__u32	cmd;
	__u32	supported;
	__u32	advertising;
	__u16	speed;
	__u8	duplex;
	__u8	port;
	__u8	phy_address;
	__u8	transceiver;
	__u8	autoneg;
	__u8	mdio_support;
	__u32	maxtxpkt;
	__u32	maxrxpkt;
	__u16	speed_hi;
	__u8	eth_tp_mdix;
	__u8	eth_tp_mdix_ctrl;
	__u32	lp_advertising;
	__u32	reserved[2];
};

#define ETHTOOL_FWVERS_LEN	32
#define ETHTOOL_BUSINFO_LEN	32

/**
 * struct ethtool_drvinfo - general driver and device information
 * @cmd: Command number = %ETHTOOL_GDRVINFO
 * @driver: Driver short name.  This should normally match the name
 *	in its bus driver structure (e.g. pci_driver::name).  Must
 *	not be an empty string.
 * @version: Driver version string; may be an empty string
 * @fw_version: Firmware version string; may be an empty string
 * @bus_info: Device bus address.  This should match the dev_name()
 *	string for the underlying bus device, if there is one.  May be
 *	an empty string.
 * @n_priv_flags: Number of flags valid for %ETHTOOL_GPFLAGS and
 *	%ETHTOOL_SPFLAGS commands; also the number of strings in the
 *	%ETH_SS_PRIV_FLAGS set
 * @n_stats: Number of u64 statistics returned by the %ETHTOOL_GSTATS
 *	command; also the number of strings in the %ETH_SS_STATS set
 * @testinfo_len: Number of results returned by the %ETHTOOL_TEST
 *	command; also the number of strings in the %ETH_SS_TEST set
 * @eedump_len: Size of EEPROM accessible through the %ETHTOOL_GEEPROM
 *	and %ETHTOOL_SEEPROM commands, in bytes
 * @regdump_len: Size of register dump returned by the %ETHTOOL_GREGS
 *	command, in bytes
 *
 * Users can use the %ETHTOOL_GSSET_INFO command to get the number of
 * strings in any string set (from Linux 2.6.34).
 *
 * Drivers should set at most @driver, @version, @fw_version and
 * @bus_info in their get_drvinfo() implementation.  The ethtool
 * core fills in the other fields using other driver operations.
 */
struct ethtool_drvinfo {
	__u32	cmd;
	char	driver[32];
	char	version[32];
	char	fw_version[ETHTOOL_FWVERS_LEN];
	char	bus_info[ETHTOOL_BUSINFO_LEN];
	char	reserved1[32];
	char	reserved2[12];
	__u32	n_priv_flags;
	__u32	n_stats;
	__u32	testinfo_len;
	__u32	eedump_len;
	__u32	regdump_len;
};

#define SOPASS_MAX	6

/**
 * struct ethtool_wolinfo - Wake-On-Lan configuration
 * @cmd: Command number = %ETHTOOL_GWOL or %ETHTOOL_SWOL
 * @supported: Bitmask of %WAKE_* flags for supported Wake-On-Lan modes.
 *	Read-only.
 * @wolopts: Bitmask of %WAKE_* flags for enabled Wake-On-Lan modes.
 * @sopass: SecureOn(tm) password; meaningful only if %WAKE_MAGICSECURE
 *	is set in @wolopts.
 */
struct ethtool_wolinfo {
	__u32	cmd;
	__u32	supported;
	__u32	wolopts;
	__u8	sopass[SOPASS_MAX];
};

/**
 * struct ethtool_regs - hardware register dump
 * @cmd: Command number = %ETHTOOL_GREGS
 * @version: Dump format version.  This is driver-specific and may
 *	distinguish different chips/revisions.  Drivers must use new
 *	version numbers whenever the dump format changes in an
 *	incompatible way.
 * @len: On entry, the real length of @data.  On return, the number of
 *	bytes used.
 * @data: Buffer for the register dump
 *
 * Users should use %ETHTOOL_GDRVINFO to find the maximum length of
 * a register dump for the interface.  They must allocate the buffer
 * immediately following this structure.
 */
struct ethtool_regs {
	__u32	cmd;
	__u32	version;
	__u32	len;
	__u8	data[0];
};

/**
 * struct ethtool_eeprom - EEPROM dump
 * @cmd: Command number = %ETHTOOL_GEEPROM, %ETHTOOL_GMODULEEEPROM or
 *	%ETHTOOL_SEEPROM
 * @magic: A 'magic cookie' value to guard against accidental changes.
 *	The value passed in to %ETHTOOL_SEEPROM must match the value
 *	returned by %ETHTOOL_GEEPROM for the same device.  This is
 *	unused when @cmd is %ETHTOOL_GMODULEEEPROM.
 * @offset: Offset within the EEPROM to begin reading/writing, in bytes
 * @len: On entry, number of bytes to read/write.  On successful
 *	return, number of bytes actually read/written.  In case of
 *	error, this may indicate at what point the error occurred.
 * @data: Buffer to read/write from
 *
 * Users may use %ETHTOOL_GDRVINFO or %ETHTOOL_GMODULEINFO to find
 * the length of an on-board or module EEPROM, respectively.  They
 * must allocate the buffer immediately following this structure.
 */
struct ethtool_eeprom {
	__u32	cmd;
	__u32	magic;
	__u32	offset;
	__u32	len;
	__u8	data[0];
};

/**
 * struct ethtool_eee - Energy Efficient Ethernet information
 * @cmd: ETHTOOL_{G,S}EEE
 * @supported: Mask of %SUPPORTED_* flags for the speed/duplex combinations
 *	for which there is EEE support.
 * @advertised: Mask of %ADVERTISED_* flags for the speed/duplex combinations
 *	advertised as eee capable.
 * @lp_advertised: Mask of %ADVERTISED_* flags for the speed/duplex
 *	combinations advertised by the link partner as eee capable.
 * @eee_active: Result of the eee auto negotiation.
 * @eee_enabled: EEE configured mode (enabled/disabled).
 * @tx_lpi_enabled: Whether the interface should assert its tx lpi, given
 *	that eee was negotiated.
 * @tx_lpi_timer: Time in microseconds the interface delays prior to asserting
 *	its tx lpi (after reaching 'idle' state). Effective only when eee
 *	was negotiated and tx_lpi_enabled was set.
 */
struct ethtool_eee {
	__u32	cmd;
	__u32	supported;
	__u32	advertised;
	__u32	lp_advertised;
	__u32	eee_active;
	__u32	eee_enabled;
	__u32	tx_lpi_enabled;
	__u32	tx_lpi_timer;
	__u32	reserved[2];
};

/**
 * struct ethtool_modinfo - plugin module eeprom information
 * @cmd: %ETHTOOL_GMODULEINFO
 * @type: Standard the module information conforms to %ETH_MODULE_SFF_xxxx
 * @eeprom_len: Length of the eeprom
 *
 * This structure is used to return the information to
 * properly size memory for a subsequent call to %ETHTOOL_GMODULEEEPROM.
 * The type code indicates the eeprom data format
 */
struct ethtool_modinfo {
	__u32   cmd;
	__u32   type;
	__u32   eeprom_len;
	__u32   reserved[8];
};

/**
 * struct ethtool_coalesce - coalescing parameters for IRQs and stats updates
 * @cmd: ETHTOOL_{G,S}COALESCE
 * @rx_coalesce_usecs: How many usecs to delay an RX interrupt after
 *	a packet arrives.
 * @rx_max_coalesced_frames: Maximum number of packets to receive
 *	before an RX interrupt.
 * @rx_coalesce_usecs_irq: Same as @rx_coalesce_usecs, except that
 *	this value applies while an IRQ is being serviced by the host.
 * @rx_max_coalesced_frames_irq: Same as @rx_max_coalesced_frames,
 *	except that this value applies while an IRQ is being serviced
 *	by the host.
 * @tx_coalesce_usecs: How many usecs to delay a TX interrupt after
 *	a packet is sent.
 * @tx_max_coalesced_frames: Maximum number of packets to be sent
 *	before a TX interrupt.
 * @tx_coalesce_usecs_irq: Same as @tx_coalesce_usecs, except that
 *	this value applies while an IRQ is being serviced by the host.
 * @tx_max_coalesced_frames_irq: Same as @tx_max_coalesced_frames,
 *	except that this value applies while an IRQ is being serviced
 *	by the host.
 * @stats_block_coalesce_usecs: How many usecs to delay in-memory
 *	statistics block updates.  Some drivers do not have an
 *	in-memory statistic block, and in such cases this value is
 *	ignored.  This value must not be zero.
 * @use_adaptive_rx_coalesce: Enable adaptive RX coalescing.
 * @use_adaptive_tx_coalesce: Enable adaptive TX coalescing.
 * @pkt_rate_low: Threshold for low packet rate (packets per second).
 * @rx_coalesce_usecs_low: How many usecs to delay an RX interrupt after
 *	a packet arrives, when the packet rate is below @pkt_rate_low.
 * @rx_max_coalesced_frames_low: Maximum number of packets to be received
 *	before an RX interrupt, when the packet rate is below @pkt_rate_low.
 * @tx_coalesce_usecs_low: How many usecs to delay a TX interrupt after
 *	a packet is sent, when the packet rate is below @pkt_rate_low.
 * @tx_max_coalesced_frames_low: Maximum nuumber of packets to be sent before
 *	a TX interrupt, when the packet rate is below @pkt_rate_low.
 * @pkt_rate_high: Threshold for high packet rate (packets per second).
 * @rx_coalesce_usecs_high: How many usecs to delay an RX interrupt after
 *	a packet arrives, when the packet rate is above @pkt_rate_high.
 * @rx_max_coalesced_frames_high: Maximum number of packets to be received
 *	before an RX interrupt, when the packet rate is above @pkt_rate_high.
 * @tx_coalesce_usecs_high: How many usecs to delay a TX interrupt after
 *	a packet is sent, when the packet rate is above @pkt_rate_high.
 * @tx_max_coalesced_frames_high: Maximum number of packets to be sent before
 *	a TX interrupt, when the packet rate is above @pkt_rate_high.
 * @rate_sample_interval: How often to do adaptive coalescing packet rate
 *	sampling, measured in seconds.  Must not be zero.
 *
 * Each pair of (usecs, max_frames) fields specifies that interrupts
 * should be coalesced until
 *	(usecs > 0 && time_since_first_completion >= usecs) ||
 *	(max_frames > 0 && completed_frames >= max_frames)
 *
 * It is illegal to set both usecs and max_frames to zero as this
 * would cause interrupts to never be generated.  To disable
 * coalescing, set usecs = 0 and max_frames = 1.
 *
 * Some implementations ignore the value of max_frames and use the
 * condition time_since_first_completion >= usecs
 *
 * This is deprecated.  Drivers for hardware that does not support
 * counting completions should validate that max_frames == !rx_usecs.
 *
 * Adaptive RX/TX coalescing is an algorithm implemented by some
 * drivers to improve latency under low packet rates and improve
 * throughput under high packet rates.  Some drivers only implement
 * one of RX or TX adaptive coalescing.  Anything not implemented by
 * the driver causes these values to be silently ignored.
 *
 * When the packet rate is below @pkt_rate_high but above
 * @pkt_rate_low (both measured in packets per second) the
 * normal {rx,tx}_* coalescing parameters are used.
 */
struct ethtool_coalesce {
	__u32	cmd;
	__u32	rx_coalesce_usecs;
	__u32	rx_max_coalesced_frames;
	__u32	rx_coalesce_usecs_irq;
	__u32	rx_max_coalesced_frames_irq;
	__u32	tx_coalesce_usecs;
	__u32	tx_max_coalesced_frames;
	__u32	tx_coalesce_usecs_irq;
	__u32	tx_max_coalesced_frames_irq;
	__u32	stats_block_coalesce_usecs;
	__u32	use_adaptive_rx_coalesce;
	__u32	use_adaptive_tx_coalesce;
	__u32	pkt_rate_low;
	__u32	rx_coalesce_usecs_low;
	__u32	rx_max_coalesced_frames_low;
	__u32	tx_coalesce_usecs_low;
	__u32	tx_max_coalesced_frames_low;
	__u32	pkt_rate_high;
	__u32	rx_coalesce_usecs_high;
	__u32	rx_max_coalesced_frames_high;
	__u32	tx_coalesce_usecs_high;
	__u32	tx_max_coalesced_frames_high;
	__u32	rate_sample_interval;
};

/**
 * struct ethtool_ringparam - RX/TX ring parameters
 * @cmd: Command number = %ETHTOOL_GRINGPARAM or %ETHTOOL_SRINGPARAM
 * @rx_max_pending: Maximum supported number of pending entries per
 *	RX ring.  Read-only.
 * @rx_mini_max_pending: Maximum supported number of pending entries
 *	per RX mini ring.  Read-only.
 * @rx_jumbo_max_pending: Maximum supported number of pending entries
 *	per RX jumbo ring.  Read-only.
 * @tx_max_pending: Maximum supported number of pending entries per
 *	TX ring.  Read-only.
 * @rx_pending: Current maximum number of pending entries per RX ring
 * @rx_mini_pending: Current maximum number of pending entries per RX
 *	mini ring
 * @rx_jumbo_pending: Current maximum number of pending entries per RX
 *	jumbo ring
 * @tx_pending: Current maximum supported number of pending entries
 *	per TX ring
 *
 * If the interface does not have separate RX mini and/or jumbo rings,
 * @rx_mini_max_pending and/or @rx_jumbo_max_pending will be 0.
 *
 * There may also be driver-dependent minimum values for the number
 * of entries per ring.
 */
struct ethtool_ringparam {
	__u32	cmd;
	__u32	rx_max_pending;
	__u32	rx_mini_max_pending;
	__u32	rx_jumbo_max_pending;
	__u32	tx_max_pending;
	__u32	rx_pending;
	__u32	rx_mini_pending;
	__u32	rx_jumbo_pending;
	__u32	tx_pending;
};

struct ethtool_channels {
	__u32	cmd;
	__u32	max_rx;
	__u32	max_tx;
	__u32	max_other;
	__u32	max_combined;
	__u32	rx_count;
	__u32	tx_count;
	__u32	other_count;
	__u32	combined_count;
};

/**
 * struct ethtool_pauseparam - Ethernet pause (flow control) parameters
 * @cmd: Command number = %ETHTOOL_GPAUSEPARAM or %ETHTOOL_SPAUSEPARAM
 * @autoneg: Flag to enable autonegotiation of pause frame use
 * @rx_pause: Flag to enable reception of pause frames
 * @tx_pause: Flag to enable transmission of pause frames
 *
 * Drivers should reject a non-zero setting of @autoneg when
 * autoneogotiation is disabled (or not supported) for the link.
 *
 * If the link is autonegotiated, drivers should use
 * mii_advertise_flowctrl() or similar code to set the advertised
 * pause frame capabilities based on the @rx_pause and @tx_pause flags,
 * even if @autoneg is zero.  They should also allow the advertised
 * pause frame capabilities to be controlled directly through the
 * advertising field of &struct ethtool_cmd.
 *
 * If @autoneg is non-zero, the MAC is configured to send and/or
 * receive pause frames according to the result of autonegotiation.
 * Otherwise, it is configured directly based on the @rx_pause and
 * @tx_pause flags.
 */
struct ethtool_pauseparam {
	__u32	cmd;
	__u32	autoneg;
	__u32	rx_pause;
	__u32	tx_pause;
};

/**
 * struct ethtool_test - device self-test invocation
 * @cmd: Command number = %ETHTOOL_TEST
 * @flags: A bitmask of flags from &enum ethtool_test_flags.  Some
 *	flags may be set by the user on entry; others may be set by
 *	the driver on return.
 * @len: On return, the number of test results
 * @data: Array of test results
 *
 * Users must use %ETHTOOL_GSSET_INFO or %ETHTOOL_GDRVINFO to find the
 * number of test results that will be returned.  They must allocate a
 * buffer of the appropriate size (8 * number of results) immediately
 * following this structure.
 */
struct ethtool_test {
	__u32	cmd;
	__u32	flags;
	__u32	reserved;
	__u32	len;
	__u64	data[0];
};

/**
 * struct ethtool_stats - device-specific statistics
 * @cmd: Command number = %ETHTOOL_GSTATS
 * @n_stats: On return, the number of statistics
 * @data: Array of statistics
 *
 * Users must use %ETHTOOL_GSSET_INFO or %ETHTOOL_GDRVINFO to find the
 * number of statistics that will be returned.  They must allocate a
 * buffer of the appropriate size (8 * number of statistics)
 * immediately following this structure.
 */
struct ethtool_stats {
	__u32	cmd;
	__u32	n_stats;
	__u64	data[0];
};

/**
 * struct ethtool_tcpip4_spec - flow specification for TCP/IPv4 etc.
 * @ip4src: Source host
 * @ip4dst: Destination host
 * @psrc: Source port
 * @pdst: Destination port
 * @tos: Type-of-service
 *
 * This can be used to specify a TCP/IPv4, UDP/IPv4 or SCTP/IPv4 flow.
 */
struct ethtool_tcpip4_spec {
	__be32	ip4src;
	__be32	ip4dst;
	__be16	psrc;
	__be16	pdst;
	__u8    tos;
};

/**
 * struct ethtool_ah_espip4_spec - flow specification for IPsec/IPv4
 * @ip4src: Source host
 * @ip4dst: Destination host
 * @spi: Security parameters index
 * @tos: Type-of-service
 *
 * This can be used to specify an IPsec transport or tunnel over IPv4.
 */
struct ethtool_ah_espip4_spec {
	__be32	ip4src;
	__be32	ip4dst;
	__be32	spi;
	__u8    tos;
};

/**
 * struct ethtool_usrip4_spec - general flow specification for IPv4
 * @ip4src: Source host
 * @ip4dst: Destination host
 * @l4_4_bytes: First 4 bytes of transport (layer 4) header
 * @tos: Type-of-service
 * @ip_ver: Value must be %ETH_RX_NFC_IP4; mask must be 0
 * @proto: Transport protocol number; mask must be 0
 */
struct ethtool_usrip4_spec {
	__be32	ip4src;
	__be32	ip4dst;
	__be32	l4_4_bytes;
	__u8    tos;
	__u8    ip_ver;
	__u8    proto;
};

union ethtool_flow_union {
	struct ethtool_tcpip4_spec		tcp_ip4_spec;
	struct ethtool_tcpip4_spec		udp_ip4_spec;
	struct ethtool_tcpip4_spec		sctp_ip4_spec;
	struct ethtool_ah_espip4_spec		ah_ip4_spec;
	struct ethtool_ah_espip4_spec		esp_ip4_spec;
	struct ethtool_usrip4_spec		usr_ip4_spec;
	struct ethhdr				ether_spec;
	__u8					hdata[52];
};

/**
 * struct ethtool_flow_ext - additional RX flow fields
 * @h_dest: destination MAC address
 * @vlan_etype: VLAN EtherType
 * @vlan_tci: VLAN tag control information
 * @data: user defined data
 *
 * Note, @vlan_etype, @vlan_tci, and @data are only valid if %FLOW_EXT
 * is set in &struct ethtool_rx_flow_spec @flow_type.
 * @h_dest is valid if %FLOW_MAC_EXT is set.
 */
struct ethtool_flow_ext {
	__u8		padding[2];
	unsigned char	h_dest[ETH_ALEN];
	__be16		vlan_etype;
	__be16		vlan_tci;
	__be32		data[2];
};

/**
 * struct ethtool_rx_flow_spec - classification rule for RX flows
 * @flow_type: Type of match to perform, e.g. %TCP_V4_FLOW
 * @h_u: Flow fields to match (dependent on @flow_type)
 * @h_ext: Additional fields to match
 * @m_u: Masks for flow field bits to be matched
 * @m_ext: Masks for additional field bits to be matched
 *	Note, all additional fields must be ignored unless @flow_type
 *	includes the %FLOW_EXT or %FLOW_MAC_EXT flag
 *	(see &struct ethtool_flow_ext description).
 * @ring_cookie: RX ring/queue index to deliver to, or %RX_CLS_FLOW_DISC
 *	if packets should be discarded
 * @location: Location of rule in the table.  Locations must be
 *	numbered such that a flow matching multiple rules will be
 *	classified according to the first (lowest numbered) rule.
 */
struct ethtool_rx_flow_spec {
	__u32		flow_type;
	union ethtool_flow_union h_u;
	struct ethtool_flow_ext h_ext;
	union ethtool_flow_union m_u;
	struct ethtool_flow_ext m_ext;
	__u64		ring_cookie;
	__u32		location;
};

/**
 * struct ethtool_rxnfc - command to get or set RX flow classification rules
 * @cmd: Specific command number - %ETHTOOL_GRXFH, %ETHTOOL_SRXFH,
 *	%ETHTOOL_GRXRINGS, %ETHTOOL_GRXCLSRLCNT, %ETHTOOL_GRXCLSRULE,
 *	%ETHTOOL_GRXCLSRLALL, %ETHTOOL_SRXCLSRLDEL or %ETHTOOL_SRXCLSRLINS
 * @flow_type: Type of flow to be affected, e.g. %TCP_V4_FLOW
 * @data: Command-dependent value
 * @fs: Flow classification rule
 * @rule_cnt: Number of rules to be affected
 * @rule_locs: Array of used rule locations
 *
 * For %ETHTOOL_GRXFH and %ETHTOOL_SRXFH, @data is a bitmask indicating
 * the fields included in the flow hash, e.g. %RXH_IP_SRC.  The following
 * structure fields must not be used.
 *
 * For %ETHTOOL_GRXRINGS, @data is set to the number of RX rings/queues
 * on return.
 *
 * For %ETHTOOL_GRXCLSRLCNT, @rule_cnt is set to the number of defined
 * rules on return.  If @data is non-zero on return then it is the
 * size of the rule table, plus the flag %RX_CLS_LOC_SPECIAL if the
 * driver supports any special location values.  If that flag is not
 * set in @data then special location values should not be used.
 *
 * For %ETHTOOL_GRXCLSRULE, @fs.@location specifies the location of an
 * existing rule on entry and @fs contains the rule on return.
 *
 * For %ETHTOOL_GRXCLSRLALL, @rule_cnt specifies the array size of the
 * user buffer for @rule_locs on entry.  On return, @data is the size
 * of the rule table, @rule_cnt is the number of defined rules, and
 * @rule_locs contains the locations of the defined rules.  Drivers
 * must use the second parameter to get_rxnfc() instead of @rule_locs.
 *
 * For %ETHTOOL_SRXCLSRLINS, @fs specifies the rule to add or update.
 * @fs.@location either specifies the location to use or is a special
 * location value with %RX_CLS_LOC_SPECIAL flag set.  On return,
 * @fs.@location is the actual rule location.
 *
 * For %ETHTOOL_SRXCLSRLDEL, @fs.@location specifies the location of an
 * existing rule on entry.
 *
 * A driver supporting the special location values for
 * %ETHTOOL_SRXCLSRLINS may add the rule at any suitable unused
 * location, and may remove a rule at a later location (lower
 * priority) that matches exactly the same set of flows.  The special
 * values are %RX_CLS_LOC_ANY, selecting any location;
 * %RX_CLS_LOC_FIRST, selecting the first suitable location (maximum
 * priority); and %RX_CLS_LOC_LAST, selecting the last suitable
 * location (minimum priority).  Additional special values may be
 * defined in future and drivers must return -%EINVAL for any
 * unrecognised value.
 */
struct ethtool_rxnfc {
	__u32				cmd;
	__u32				flow_type;
	__u64				data;
	struct ethtool_rx_flow_spec	fs;
	__u32				rule_cnt;
	__u32				rule_locs[0];
};

#define ETHTOOL_FLASH_MAX_FILENAME	128

struct ethtool_flash {
	__u32	cmd;
	__u32	region;
	char	data[ETHTOOL_FLASH_MAX_FILENAME];
};

/**
 * struct ethtool_dump - used for retrieving, setting device dump
 * @cmd: Command number - %ETHTOOL_GET_DUMP_FLAG, %ETHTOOL_GET_DUMP_DATA, or
 * 	%ETHTOOL_SET_DUMP
 * @version: FW version of the dump, filled in by driver
 * @flag: driver dependent flag for dump setting, filled in by driver during
 *        get and filled in by ethtool for set operation.
 *        flag must be initialized by macro ETH_FW_DUMP_DISABLE value when
 *        firmware dump is disabled.
 * @len: length of dump data, used as the length of the user buffer on entry to
 * 	 %ETHTOOL_GET_DUMP_DATA and this is returned as dump length by driver
 * 	 for %ETHTOOL_GET_DUMP_FLAG command
 * @data: data collected for get dump data operation
 */
struct ethtool_dump {
	__u32	cmd;
	__u32	version;
	__u32	flag;
	__u32	len;
	__u8	data[0];
};

/**
 * struct ethtool_ts_info - holds a device's timestamping and PHC association
 * @cmd: command number = %ETHTOOL_GET_TS_INFO
 * @so_timestamping: bit mask of the sum of the supported SO_TIMESTAMPING flags
 * @phc_index: device index of the associated PHC, or -1 if there is none
 * @tx_types: bit mask of the supported hwtstamp_tx_types enumeration values
 * @rx_filters: bit mask of the supported hwtstamp_rx_filters enumeration values
 *
 * The bits in the 'tx_types' and 'rx_filters' fields correspond to
 * the 'hwtstamp_tx_types' and 'hwtstamp_rx_filters' enumeration values,
 * respectively.  For example, if the device supports HWTSTAMP_TX_ON,
 * then (1 << HWTSTAMP_TX_ON) in 'tx_types' will be set.
 */
struct ethtool_ts_info {
	__u32	cmd;
	__u32	so_timestamping;
	__s32	phc_index;
	__u32	tx_types;
	__u32	tx_reserved[3];
	__u32	rx_filters;
	__u32	rx_reserved[3];
};

#endif /* ! __UAPI_LINUX_ETHTOOL_H__ */
