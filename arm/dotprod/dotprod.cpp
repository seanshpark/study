#include <iostream>
#include <cstdint>
#include <stdlib.h>
#include <time.h>

#include "arm_neon.h"

void __attribute__((noinline)) clear_sum(uint32_t *sum)
{
  for (int i = 0; i < 4; i++)
    sum[i] = 0;
}

void __attribute__((noinline)) dot_product(const uint8_t *a, const uint8_t *b, uint32_t *sum)
{
  for (int i = 0; i < 4; i++) {
    int ii = i * 4;
    const uint8_t *aa = &a[ii];
    const uint8_t *bb = &b[ii];
    for (int j = 0; j < 4; j++) {
      sum[i] += aa[j] * bb[j];
    }
  }
}

void __attribute__((noinline)) dot_product_v(const uint8_t *a, const uint8_t *b, uint32_t *sum)
{
  uint8x16_t va = vld1q_u8(a);
  uint8x16_t vb = vld1q_u8(b);
  uint32x4_t vs = vld1q_u32(sum);

  vs = vdotq_u32(vs, va, vb);

  vst1q_u32(sum, vs);
}

void fill_rand(uint8_t *a, int num, int max)
{
  for (int i = 0; i < num; ++i)
    a[i] = rand() % max;
}

int main(void)
{
  srand(time(NULL)); 

  uint8_t *a, *b;
  uint32_t sum[4];

  a = new uint8_t[16];
  b = new uint8_t[16];
  fill_rand(a, 16, 10);
  fill_rand(b, 16, 10);

  clear_sum(sum);
  dot_product(a, b, sum);
  for (int i = 0; i < 4; ++i)
    std::cout << "Sum " << i << " is " << sum[i] << std::endl;

  clear_sum(sum);
  dot_product_v(a, b, sum);
  for (int i = 0; i < 4; ++i)
    std::cout << "Sum " << i << " is " << sum[i] << std::endl;

  delete [] a;
  delete [] b;

  return 0;
}
