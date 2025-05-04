#include <stdint.h>
#include <stdio.h>

// Mersenne Twister 19937
// 参考维基百科说明
//   https://en.wikipedia.org/wiki/Mersenne_Twister
struct MT19937Ctx {
  uint32_t index;
  uint32_t state[624];
};

void mt19937_init(struct MT19937Ctx *ctx, int seed) {
  ctx->index = 624;

  uint32_t value = seed;
  ctx->state[0] = seed;
  for (int i = 1; i < 624; ++i) {
    value = 0x6C078965 * (value ^ (value >> 30)) + i;
    ctx->state[i] = value;
  }
}

void mt19937_twist(struct MT19937Ctx *ctx) {
  for (uint32_t i = 0; i < 624; ++i) {
    uint32_t y =
        (ctx->state[i] & 0x80000000) | (ctx->state[(i + 1) % 624] & 0x7FFFFFFF);
    uint32_t xor_value = (y & 1) * 0x9908B0DF;
    ctx->state[i] = ctx->state[(i + 397) % 624] ^ (y >> 1) ^ xor_value;
  }
}

uint32_t mt19937_next(struct MT19937Ctx *ctx) {
  if (ctx->index >= 624) {
    mt19937_twist(ctx);
    ctx->index = 0;
  }
  uint32_t result = ctx->state[ctx->index++];

  result ^= result >> 0x0B;
  result ^= (result << 0x07) & 0x9D2C5680;
  result ^= (result << 0x0F) & 0xEFC60000;
  result ^= result >> 0x12;

  return result;
}

int main() {
  struct MT19937Ctx mt19937 = {};
  mt19937_init(&mt19937, 0x44C);

  uint8_t ctf_flag[38] = {0xC2, 0x6C, 0xFC, 0xB3, 0xA7, 0x8E, 0xF5, 0x83,
                          0x81, 0xCB, 0xBF, 0xD5, 0xC2, 0xCE, 0x83, 0xBD,
                          0xE6, 0x6A, 0xA5, 0xA8, 0x44, 0xF5, 0x45, 0x59,
                          0x50, 0xD8, 0x03, 0x98, 0xF7, 0x74, 0x87, 0xAC,
                          0xC5, 0x3E, 0x38, 0x2F, 0x07, 0x68};

  for (int i = 0; i < sizeof(ctf_flag); i++) {
    ctf_flag[i] ^= (uint8_t)(mt19937_next(&mt19937));
  }
  printf("flag: %.38s\n", (char *)&ctf_flag[0]);
}