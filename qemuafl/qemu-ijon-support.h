//
// Created by wu on 2025/9/30.
//

#ifndef QEMUAFL_QEMU_IJON_SUPPORT_H
#define QEMUAFL_QEMU_IJON_SUPPORT_H


extern uint32_t ijon_hooker_cnt;
extern target_ulong hook_code_addr[0x1000];
extern target_ulong g_var_addr[0x1000];
extern uint32_t g_var_len[0x1000];
extern uint32_t ijon_type[0x1000];


void ijon_max(uint32_t addr, u64 val);
void ijon_min(uint32_t addr, u64 val);
void ijon_set(uint32_t addr, uint32_t val);
void ijon_inc(uint32_t addr, uint32_t val);

/* IJON state management functions */
void ijon_xor_state(uint32_t addr, u64 val);
void ijon_reset_state(uint32_t addr, u64 val);
uint32_t ijon_memdist(char *a, char *b, size_t len);
uint32_t ijon_hashmem(uint32_t old, char *val, size_t len);

#define IJON_LIST                 \
X(ijon_max,        ijon_max)  \
X(ijon_min,        ijon_min)  \
X(ijon_set,        ijon_set)  \
X(ijon_inc,        ijon_inc)  \
X(ijon_xor_state,  ijon_xor_state) \
X(ijon_reset_state, ijon_reset_state)

//
// 定义枚举（带 e_ 前缀）
//
typedef enum {
  #define X(name, func) e_##name,
  IJON_LIST
#undef X
  e_IJON_COUNT
} IJON;

const char* ijon_to_str(IJON v);
IJON str_to_ijon(const char* str);
void ijon_dispatch(IJON v, uint32_t addr, u64 val);

#endif //QEMUAFL_QEMU_IJON_SUPPORT_H