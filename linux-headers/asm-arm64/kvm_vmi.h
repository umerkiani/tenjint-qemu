/*
 * KVM VMI support
 *
 * Copyright (C) 2019 Bedrock Systems, Inc. All Rights Reserved.
 *
 * Authors:
 *  Jonas Pfoh      <jonas@bedrocksystems.com>
 *  Sebastian Vogl  <sebastian@bedrocksystems.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#ifndef _ASM_ARM64_KVM_VMI_H
#define _ASM_ARM64_KVM_VMI_H

#include <linux/types.h>

#define KVM_VMI_FEATURE_TRAP_TASK_SWITCH  0
#define KVM_VMI_FEATURE_SLP               1
#define KVM_VMI_FEATURE_MAX               2

#define KVM_VMI_EVENT_TASK_SWITCH         0
#define KVM_VMI_EVENT_SLP                 1

#define KVM_VMI_TTBR0                     0
#define KVM_VMI_TTBR1                     1
#define KVM_VMI_TCR                       2

struct kvm_vmi_feature_task_switch {
    __u32 feature;
    __u8 enable;
    __u8 reg;
};

struct kvm_vmi_feature_slp {
    __u32 feature;
    __u8 enable;
    __u8 global_req;
    __u64 gfn;
    __u64 num_pages;
    __u64 violation;
};

union kvm_vmi_feature {
    __u32 feature;
    struct kvm_vmi_feature_task_switch ts;
    struct kvm_vmi_feature_slp slp;
};

struct kvm_vmi_event_task_switch {
    __u32 type;
    __u32 cpu_num;
    __u8 reg;
    __u64 old_val;
    __u64 new_val;
};

struct kvm_vmi_event_slp {
    __u32 type;
    __u32 cpu_num;
    __u64 violation;
    __u64 gva;
    __u64 gpa;
    __u8 rwx;
};

union kvm_vmi_event {
    __u32 type;
    struct kvm_vmi_event_task_switch ts;
    struct kvm_vmi_event_slp slp;
};

#endif /* _ASM_ARM64_KVM_VMI_H */

