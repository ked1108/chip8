#include <cstdint>
#include <chrono>
#include <random>
#include <fstream>
#include <ios>

const unsigned int START_ADDRESS = 0x200;
const unsigned int FONTSET_START_ADR = 0x50;
const unsigned int FONTSET_SIZE = 80;

const uint8_t fontset[FONTSET_SIZE] = {
  // 0 
  0xF0,
  0x90,
  0x90,
  0x90,
  0xF0,

  // 1
  0x20,
  0x60,
  0x20,
  0x20,
  0x70,

  // 2 
  0xF0,
  0x10,
  0xF0,
  0x80,
  0xF0,

  // 3
  0xF0,
  0x10,
  0xF0,
  0x10,
  0xF0,

  // 4
  0x90,
  0x90,
  0xF0,
  0x10,
  0x10,

  // 5
  0xF0,
  0x80,
  0xF0,
  0x10,
  0xF0,

  // 6
  0xF0,
  0x80,
  0xF0,
  0x90,
  0xF0,

  // 7
  0xF0,
  0x10,
  0x20,
  0x40,
  0x40,

  // 8
  0xF0,
  0x90,
  0xF0,
  0x90,
  0xF0,

  // 9
  0xF0,
  0x90,
  0xF0,
  0x10,
  0xF0,

  // A
  0xF0,
  0x90,
  0xF0,
  0x90,
  0x90,

  // B
  0xE0,
  0x90,
  0xE0,
  0x90,
  0xE0,

  // C
  0xF0,
  0x80,
  0x80,
  0x80,
  0xF0,

  // D
  0xE0,
  0x90,
  0x90,
  0x90,
  0xE0,

  // E
  0xF0,
  0x80,
  0xF0,
  0x80,
  0xF0,

  // F
  0xF0,
  0x80,
  0xF0,
  0x80,
  0x80,
};

class Chip8 {
public:
  uint8_t registers[16];
  uint8_t memory[4096];
  uint16_t index;
  uint16_t pc;
  uint16_t stack[16];
  uint8_t sp;
  uint8_t delayTimer;
  uint8_t soundTimer;
  uint8_t keypad[16];
  uint32_t video[64 * 32];
  uint16_t opcode;
  std::default_random_engine randGen;
  std::uniform_int_distribution<> randByte;

  Chip8();
  void LoadROM(char const* filename);
  void OP_00E0();
  void OP_00EE();
  void OP_1NNN();
  void OP_2NNN();
  void OP_3XKK();
  void OP_4XKK();
  void OP_5XY0();
  void OP_6XKK();
  void OP_7XKK();
  void OP_8XY0();
  void OP_8XY1();
  void OP_8XY2();
  void OP_8XY3();
  void OP_8XY4();
  void OP_8XY5();
  void OP_8XY6();
  void OP_8XY7();
  void OP_8XYE();
  void OP_9XY0();
  void OP_ANNN();
  void OP_BNNN();
  void OP_CXNN();
};
