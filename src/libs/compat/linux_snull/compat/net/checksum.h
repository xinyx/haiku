#include <generated/autoconf.h>
#ifndef __NET_CHECKSUM_H__
#define __NET_CHECKSUM_H__

#include <linux/errno.h>
#include <asm/types.h>
#include <asm/byteorder.h>
#include <asm/uaccess.h>
#include <asm/checksum.h>

static inline __wsum csum_sub(__wsum csum, __wsum addend)
{
	return csum_add(csum, ~addend);
}

static inline __sum16 csum16_add(__sum16 csum, __be16 addend)
{
	u16 res = (__force u16)csum;

	res += (__force u16)addend;
	return (__force __sum16)(res + (res < (__force u16)addend));
}

static inline __sum16 csum16_sub(__sum16 csum, __be16 addend)
{
	return csum16_add(csum, ~addend);
}

static inline __wsum
csum_block_add(__wsum csum, __wsum csum2, int offset)
{
	u32 sum = (__force u32)csum2;
	if (offset&1)
		sum = ((sum&0xFF00FF)<<8)+((sum>>8)&0xFF00FF);
	return csum_add(csum, (__force __wsum)sum);
}

static inline __wsum csum_unfold(__sum16 n)
{
	return (__force __wsum)n;
}

struct sk_buff;
void inet_proto_csum_replace4(__sum16 *sum, struct sk_buff *skb,
			      __be32 from, __be32 to, int pseudohdr);

#endif /* ! __NET_CHECKSUM_H__ */
