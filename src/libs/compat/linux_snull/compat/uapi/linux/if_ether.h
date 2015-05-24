#ifndef __UAPI_LINUX_IF_ETHER_H__
#define __UAPI_LINUX_IF_ETHER_H__

#include <linux/types.h>

#define ETH_ALEN	6		/* Octets in one ethernet addr	 */
#define ETH_HLEN	14		/* Total octets in header.	 */
#define ETH_ZLEN	60		/* Min. octets in frame sans FCS */
#define ETH_DATA_LEN	1500		/* Max. octets in payload	 */

#define ETH_P_IP	0x0800		/* Internet Protocol packet	*/

#define ETH_P_IPV6	0x86DD		/* IPv6 over bluebook		*/

#define ETH_P_FCOE	0x8906		/* Fibre Channel over Ethernet  */

#define ETH_P_DSA	0x001B		/* Distributed Switch Arch.	*/
#define ETH_P_TRAILER	0x001C		/* Trailer switch tagging	*/

struct ethhdr {
	unsigned char	h_dest[ETH_ALEN];	/* destination eth addr	*/
	unsigned char	h_source[ETH_ALEN];	/* source ether addr	*/
	__be16		h_proto;		/* packet type ID field	*/
} __attribute__((packed));

#endif /* ! __UAPI_LINUX_IF_ETHER_H__ */
