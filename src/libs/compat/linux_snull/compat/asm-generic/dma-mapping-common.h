#ifndef __ASM_GENERIC_DMA_MAPPING_COMMON_H__
#define __ASM_GENERIC_DMA_MAPPING_COMMON_H__

#include <linux/kmemcheck.h>
#include <linux/bug.h>
#include <linux/scatterlist.h>
#include <linux/dma-debug.h>
#include <linux/dma-attrs.h>

static inline dma_addr_t dma_map_page(struct device *dev, struct page *page,
				      size_t offset, size_t size,
				      enum dma_data_direction dir)
{
	struct dma_map_ops *ops = get_dma_ops(dev);
	dma_addr_t addr;

	kmemcheck_mark_initialized(page_address(page) + offset, size);
	BUG_ON(!valid_dma_direction(dir));
	addr = ops->map_page(dev, page, offset, size, dir, NULL);
	debug_dma_map_page(dev, page, offset, size, dir, addr, false);

	return addr;
}

extern int dma_common_mmap(struct device *dev, struct vm_area_struct *vma,
			   void *cpu_addr, dma_addr_t dma_addr, size_t size);

/**
 * dma_mmap_attrs - map a coherent DMA allocation into user space
 * @dev: valid struct device pointer, or NULL for ISA and EISA-like devices
 * @vma: vm_area_struct describing requested user mapping
 * @cpu_addr: kernel CPU-view address returned from dma_alloc_attrs
 * @handle: device-view address returned from dma_alloc_attrs
 * @size: size of memory originally requested in dma_alloc_attrs
 * @attrs: attributes of mapping properties requested in dma_alloc_attrs
 *
 * Map a coherent DMA buffer previously allocated by dma_alloc_attrs
 * into user space.  The coherent DMA buffer must not be freed by the
 * driver until the user space mapping has been released.
 */
static inline int
dma_mmap_attrs(struct device *dev, struct vm_area_struct *vma, void *cpu_addr,
	       dma_addr_t dma_addr, size_t size, struct dma_attrs *attrs)
{
	struct dma_map_ops *ops = get_dma_ops(dev);
	BUG_ON(!ops);
	if (ops->mmap)
		return ops->mmap(dev, vma, cpu_addr, dma_addr, size, attrs);
	return dma_common_mmap(dev, vma, cpu_addr, dma_addr, size);
}

int
dma_common_get_sgtable(struct device *dev, struct sg_table *sgt,
		       void *cpu_addr, dma_addr_t dma_addr, size_t size);

#endif /* ! __ASM_GENERIC_DMA_MAPPING_COMMON_H__ */
