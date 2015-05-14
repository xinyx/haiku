#ifndef __ASM_TOPOLOGY_H__
#define __ASM_TOPOLOGY_H__

#  define ENABLE_TOPO_DEFINES

/*
 * to preserve the visibility of NUMA_NO_NODE definition,
 * moved to there from here.  May be used independent of
 * CONFIG_NUMA.
 */
#include <linux/numa.h>

static inline int numa_node_id(void)
{
	return 0;
}
/*
 * indicate override:
 */
#define numa_node_id numa_node_id

#include <asm-generic/topology.h>

#define topology_physical_package_id(cpu)	(cpu_data(cpu).phys_proc_id)
#define topology_core_id(cpu)			(cpu_data(cpu).cpu_core_id)
#define topology_core_cpumask(cpu)		(per_cpu(cpu_core_map, cpu))
#define topology_thread_cpumask(cpu)		(per_cpu(cpu_sibling_map, cpu))

#endif /* ! __ASM_TOPOLOGY_H__ */
