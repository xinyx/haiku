#include <generated/autoconf.h>
#ifndef __ASM_DMA_MAPPING_H__
#define __ASM_DMA_MAPPING_H__

#include <linux/kmemcheck.h>
#include <linux/scatterlist.h>
#include <linux/dma-debug.h>
#include <linux/dma-attrs.h>
#include <asm/io.h>
#include <asm/swiotlb.h>
#include <asm-generic/dma-coherent.h>
#include <linux/dma-contiguous.h>

#define DMA_ERROR_CODE	0

extern struct device x86_dma_fallback_dev;

extern struct dma_map_ops *dma_ops;

static inline struct dma_map_ops *get_dma_ops(struct device *dev)
{
#ifndef CONFIG_X86_DEV_DMA_OPS
	return dma_ops;
#else
	if (unlikely(!dev) || !dev->archdata.dma_ops)
		return dma_ops;
	else
		return dev->archdata.dma_ops;
#endif
}

#include <asm-generic/dma-mapping-common.h>

extern int dma_supported(struct device *hwdev, u64 mask);
extern int dma_set_mask(struct device *dev, u64 mask);

static inline unsigned long dma_alloc_coherent_mask(struct device *dev,
						    gfp_t gfp)
{
	unsigned long dma_mask = 0;

	dma_mask = dev->coherent_dma_mask;
	if (!dma_mask)
		dma_mask = (gfp & GFP_DMA) ? DMA_BIT_MASK(24) : DMA_BIT_MASK(32);

	return dma_mask;
}

static inline gfp_t dma_alloc_coherent_gfp_flags(struct device *dev, gfp_t gfp)
{
	unsigned long dma_mask = dma_alloc_coherent_mask(dev, gfp);

	if (dma_mask <= DMA_BIT_MASK(24))
		gfp |= GFP_DMA;
#ifdef CONFIG_X86_64
	if (dma_mask <= DMA_BIT_MASK(32) && !(gfp & GFP_DMA))
		gfp |= GFP_DMA32;
#endif
       return gfp;
}

#define dma_alloc_coherent(d,s,h,f)	dma_alloc_attrs(d,s,h,f,NULL)

static inline void *
dma_alloc_attrs(struct device *dev, size_t size, dma_addr_t *dma_handle,
		gfp_t gfp, struct dma_attrs *attrs)
{
	struct dma_map_ops *ops = get_dma_ops(dev);
	void *memory;

	gfp &= ~(__GFP_DMA | __GFP_HIGHMEM | __GFP_DMA32);

	if (dma_alloc_from_coherent(dev, size, dma_handle, &memory))
		return memory;

	if (!dev)
		dev = &x86_dma_fallback_dev;

	if (!is_device_dma_capable(dev))
		return NULL;

	if (!ops->alloc)
		return NULL;

	memory = ops->alloc(dev, size, dma_handle,
			    dma_alloc_coherent_gfp_flags(dev, gfp), attrs);
	debug_dma_alloc_coherent(dev, size, *dma_handle, memory);

	return memory;
}

#endif /* ! __ASM_DMA_MAPPING_H__ */
