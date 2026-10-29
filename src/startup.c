#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);

void Reset_Handler(void)
{
  uint32_t *src = &_sidata;
  uint32_t *dst = &_sdata;

  for (; dst < &_edata;) {
    *dst++ = *src++;  
  }

  for (uint32_t *bss_ptr = &_sbss; bss_ptr < &_ebss;) {
    *bss_ptr++ = 0;
  }

  main();

  while(1);
}

void Default_Handler(void)
{
  while(1);  
}

__attribute__((section(".isr_vector"), used))
const uint32_t vector_table[16] = {
  (uint32_t)&_estack,
  (uint32_t)Reset_Handler,
  (uint32_t)Default_Handler,
  (uint32_t)Default_Handler,
  (uint32_t)Default_Handler,
  (uint32_t)Default_Handler,
  (uint32_t)Default_Handler,
  0,
  0,
  0,
  0,
  (uint32_t)Default_Handler,
  0,
  0,
  (uint32_t)Default_Handler,
  (uint32_t)Default_Handler
};
