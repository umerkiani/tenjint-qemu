/*
 * QEMU KVM VMI API
 *
 * Copyright BedRock Systems, Inc. 2020
 *
 * Authors:
 *  Jonas Pfoh     <jonas@bedrocksystems.com>
 *  Sebastian Vogl <sebastian@bedrocksystems.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 *
 */
#ifndef VMI_API_H
#define VMI_API_H
#include <linux/kvm_vmi.h>
#include <asm/kvm_vmi.h>

#define VMI_ARCH_UNSUPPORTED    -1
#define VMI_ARCH_X86_64         0
#define VMI_ARCH_AARCH64        1

#define VMI_EVENT_KVM           0
#define VMI_EVENT_STOP          1
#define VMI_EVENT_VM_READY      2
#define VMI_EVENT_VM_SHUTDOWN   3

struct vmi_event {
    uint32_t type;
    int32_t arch;
    union {
        union kvm_vmi_event *kvm_vmi_event;
    };
};

extern int vmi_api_init(void);
extern void vmi_api_uninit(void);

extern void vmi_api_request_stop(void);
extern void vmi_api_request_shutdown(void);

extern struct vmi_event* vmi_api_get_event(void);
extern int vmi_api_start_vm(void);
extern int vmi_api_wait_event(time_t secs);
extern void vmi_api_stop_vm(void);

extern int vmi_api_feature_update_all(union kvm_vmi_feature *feature);
extern int vmi_api_feature_update_single(uint32_t cpu_num,
                                         union kvm_vmi_feature *feature);

extern int vmi_api_slp_update_all(struct kvm_vmi_slp_perm *slp_perm);
extern int vmi_api_slp_update_single(uint32_t cpu_num,
                                     struct kvm_vmi_slp_perm *slp_perm);

extern uint64_t vmi_api_get_num_cpus(void);

extern uint64_t vmi_api_get_ram_size(void);
extern int vmi_api_read_phys_mem(uint64_t addr, void *buf, uint64_t len);
extern int vmi_api_write_phys_mem(uint64_t addr, const void *buf, uint64_t len);

extern uint32_t vmi_api_get_page_bits(void);
extern uint32_t vmi_api_get_page_size(void);

uint64_t vmi_api_arch_vtop(uint64_t addr, uint64_t dtb);
extern uint64_t vmi_api_vtop(uint64_t addr, uint64_t dtb);

extern void vmi_api_mouse_out(void);
#endif
