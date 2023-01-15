#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HIJK_API __declspec(dllexport)

typedef void (*Hijk_PrologueCallback)(void* target_function, struct Hijk_PrologueContext* context);
typedef void (*Hijk_EpilogueCallback)(void* target_function, struct Hijk_EpilogueContext* context);

// Dynamically instrument `target_function` and call prologue/epilogue callbacks on entry/exit.
HIJK_API bool Hijk_CreateHook(void* target_function, Hijk_PrologueCallback prologue_callback,
                              Hijk_EpilogueCallback epilogue_callback);

HIJK_API bool Hijk_EnableHook(void* target_function);
HIJK_API bool Hijk_EnableAllHooks();

HIJK_API bool Hijk_DisableHook(void* target_function);
HIJK_API bool Hijk_DisableAllHooks();

HIJK_API bool Hijk_RemoveHook(void* target_function);
HIJK_API bool Hijk_RemoveAllHooks();

struct Hijk_PrologData {
  void* asm_prolog_stub;
  void* c_prolog_stub;
  void* asm_epilog_stub;
  void* tramploline_to_original_function;
  void* original_function;
  void* user_callback;
};

struct Hijk_EpilogData {
  void* asm_epilog_stub;
  void* c_prolog_stub;
  void* original_function;
  void* user_callback;
};

#pragma pack(push, 1)
struct Hijk_IntegerRegisters {
  uint64_t regs[16];
};

struct Hijk_Xmm {
  float data[4];
};

struct Hijk_XmmRegisters {
  struct Hijk_Xmm xmm0;
  struct Hijk_Xmm xmm1;
  struct Hijk_Xmm xmm2;
  struct Hijk_Xmm xmm3;
  struct Hijk_Xmm xmm4;
  struct Hijk_Xmm xmm5;
  struct Hijk_Xmm xmm6;
  struct Hijk_Xmm xmm7;
  struct Hijk_Xmm xmm8;
  struct Hijk_Xmm xmm9;
  struct Hijk_Xmm xmm10;
  struct Hijk_Xmm xmm11;
  struct Hijk_Xmm xmm12;
  struct Hijk_Xmm xmm13;
  struct Hijk_Xmm xmm14;
  struct Hijk_Xmm xmm15;
};
#pragma pack(pop)

struct Hijk_PrologueContext {
  Hijk_PrologData* prolog_data;
  Hijk_IntegerRegisters integer_registers;
  Hijk_XmmRegisters xmm_registers;
};

struct Hijk_EpilogueContext {
  Hijk_EpilogData* epilog_data;
  Hijk_IntegerRegisters integer_registers;
  Hijk_XmmRegisters xmm_registers;
};

#ifdef __cplusplus
}
#endif
