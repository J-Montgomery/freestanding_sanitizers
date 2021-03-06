#pragma once

#include "asan_types.h"
#include <sanitizer/interface_utils.h>

#define ASAN_INTERFACE(fname, ...)                                             \
  EXTERN_C ATTR_INTERFACE void __asan_##fname(__VA_ARGS__);

// ASAN_INTERFACE(addr_is_in_fake_stack)
// ASAN_INTERFACE(address_is_poisoned)
// ASAN_INTERFACE(after_dynamic_init)
// ASAN_INTERFACE(alloca_poison)
// ASAN_INTERFACE(allocas_unpoison)
// ASAN_INTERFACE(before_dynamic_init)
// ASAN_INTERFACE(describe_address)
// ASAN_INTERFACE(exp_load1)
// ASAN_INTERFACE(exp_load2)
// ASAN_INTERFACE(exp_load4)
// ASAN_INTERFACE(exp_load8)
// ASAN_INTERFACE(exp_load16)
// ASAN_INTERFACE(exp_loadN)
// ASAN_INTERFACE(exp_store1)
// ASAN_INTERFACE(exp_store2)
// ASAN_INTERFACE(exp_store4)
// ASAN_INTERFACE(exp_store8)
// ASAN_INTERFACE(exp_store16)
// ASAN_INTERFACE(exp_storeN)
// ASAN_INTERFACE(get_alloc_stack)
// ASAN_INTERFACE(get_current_fake_stack)
// ASAN_INTERFACE(get_free_stack)
// ASAN_INTERFACE(get_report_access_size)
// ASAN_INTERFACE(get_report_access_type)
// ASAN_INTERFACE(get_report_address)
// ASAN_INTERFACE(get_report_bp)
// ASAN_INTERFACE(get_report_description)
// ASAN_INTERFACE(get_report_pc)
// ASAN_INTERFACE(get_report_sp)
// ASAN_INTERFACE(get_shadow_mapping)
ASAN_INTERFACE(handle_no_return, void)
// ASAN_INTERFACE(handle_vfork)
ASAN_INTERFACE(init, void)
// ASAN_INTERFACE(load_cxx_array_cookie)
// ASAN_INTERFACE(load1)
// ASAN_INTERFACE(load2)
// ASAN_INTERFACE(load4)
// ASAN_INTERFACE(load8)
// ASAN_INTERFACE(load16)
// ASAN_INTERFACE(loadN)
// ASAN_INTERFACE(load1_noabort)
// ASAN_INTERFACE(load2_noabort)
// ASAN_INTERFACE(load4_noabort)
// ASAN_INTERFACE(load8_noabort)
// ASAN_INTERFACE(load16_noabort)
// ASAN_INTERFACE(loadN_noabort)
// ASAN_INTERFACE(locate_address)
// ASAN_INTERFACE(memcpy)
// ASAN_INTERFACE(memmove)
// ASAN_INTERFACE(memset)
// ASAN_INTERFACE(poison_cxx_array_cookie)
// ASAN_INTERFACE(poison_intra_object_redzone)
// ASAN_INTERFACE(poison_memory_region)
// ASAN_INTERFACE(poison_stack_memory)
// ASAN_INTERFACE(print_accumulated_stats)
// ASAN_INTERFACE(region_is_poisoned)
ASAN_INTERFACE(register_globals, void)
// ASAN_INTERFACE(register_elf_globals)
// ASAN_INTERFACE(register_image_globals)
// ASAN_INTERFACE(report_error)
// ASAN_INTERFACE(report_exp_load1)
// ASAN_INTERFACE(report_exp_load2)
// ASAN_INTERFACE(report_exp_load4)
// ASAN_INTERFACE(report_exp_load8)
// ASAN_INTERFACE(report_exp_load16)
// ASAN_INTERFACE(report_exp_load_n)
// ASAN_INTERFACE(report_exp_store1)
// ASAN_INTERFACE(report_exp_store2)
// ASAN_INTERFACE(report_exp_store4)
// ASAN_INTERFACE(report_exp_store8)
// ASAN_INTERFACE(report_exp_store16)
// ASAN_INTERFACE(report_exp_store_n)
ASAN_INTERFACE(report_load1, void)
// ASAN_INTERFACE(report_load2)
// ASAN_INTERFACE(report_load4)
ASAN_INTERFACE(report_load8, void)
// ASAN_INTERFACE(report_load16)
// ASAN_INTERFACE(report_load_n)
// ASAN_INTERFACE(report_load1_noabort)
// ASAN_INTERFACE(report_load2_noabort)
// ASAN_INTERFACE(report_load4_noabort)
// ASAN_INTERFACE(report_load8_noabort)
// ASAN_INTERFACE(report_load16_noabort)
// ASAN_INTERFACE(report_load_n_noabort)
// ASAN_INTERFACE(report_present)
// ASAN_INTERFACE(report_store1)
// ASAN_INTERFACE(report_store2)
ASAN_INTERFACE(report_store4, void)
// ASAN_INTERFACE(report_store8)
// ASAN_INTERFACE(report_store16)
// ASAN_INTERFACE(report_store_n)
// ASAN_INTERFACE(report_store1_noabort)
// ASAN_INTERFACE(report_store2_noabort)
// ASAN_INTERFACE(report_store4_noabort)
// ASAN_INTERFACE(report_store8_noabort)
// ASAN_INTERFACE(report_store16_noabort)
// ASAN_INTERFACE(report_store_n_noabort)
// ASAN_INTERFACE(set_death_callback)
// ASAN_INTERFACE(set_error_report_callback)
// ASAN_INTERFACE(set_shadow_00)
// ASAN_INTERFACE(set_shadow_f1)
// ASAN_INTERFACE(set_shadow_f2)
// ASAN_INTERFACE(set_shadow_f3)
// ASAN_INTERFACE(set_shadow_f5)
// ASAN_INTERFACE(set_shadow_f8)
// ASAN_INTERFACE(stack_free_0)
// ASAN_INTERFACE(stack_free_1)
// ASAN_INTERFACE(stack_free_2)
// ASAN_INTERFACE(stack_free_3)
// ASAN_INTERFACE(stack_free_4)
// ASAN_INTERFACE(stack_free_5)
// ASAN_INTERFACE(stack_free_6)
// ASAN_INTERFACE(stack_free_7)
// ASAN_INTERFACE(stack_free_8)
// ASAN_INTERFACE(stack_free_9)
// ASAN_INTERFACE(stack_free_10)
// ASAN_INTERFACE(stack_malloc_0)
// ASAN_INTERFACE(stack_malloc_1)
// ASAN_INTERFACE(stack_malloc_2)
// ASAN_INTERFACE(stack_malloc_3)
// ASAN_INTERFACE(stack_malloc_4)
// ASAN_INTERFACE(stack_malloc_5)
// ASAN_INTERFACE(stack_malloc_6)
// ASAN_INTERFACE(stack_malloc_7)
// ASAN_INTERFACE(stack_malloc_8)
// ASAN_INTERFACE(stack_malloc_9)
// ASAN_INTERFACE(stack_malloc_10)
// ASAN_INTERFACE(store1)
// ASAN_INTERFACE(store2)
// ASAN_INTERFACE(store4)
// ASAN_INTERFACE(store8)
// ASAN_INTERFACE(store16)
// ASAN_INTERFACE(storeN)
// ASAN_INTERFACE(store1_noabort)
// ASAN_INTERFACE(store2_noabort)
// ASAN_INTERFACE(store4_noabort)
// ASAN_INTERFACE(store8_noabort)
// ASAN_INTERFACE(store16_noabort)
// ASAN_INTERFACE(storeN_noabort)
// ASAN_INTERFACE(unpoison_intra_object_redzone)
// ASAN_INTERFACE(unpoison_memory_region)
// ASAN_INTERFACE(unpoison_stack_memory)
ASAN_INTERFACE(unregister_globals, void)
// ASAN_INTERFACE(unregister_elf_globals)
// ASAN_INTERFACE(unregister_image_globals)
ASAN_INTERFACE(version_mismatch_check_v8, void)