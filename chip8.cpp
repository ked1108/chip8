#include "chip8.h"
#include <cstdint>
#include <cstring>
#include <sys/types.h>

Chip8::Chip8():randGen(std::chrono::system_clock::now().time_since_epoch().count()){
  pc = START_ADDRESS;
  for (unsigned int i = 0; i < FONTSET_SIZE; i++) {
    memory[FONTSET_START_ADR + i] = fontset[i];
  }

  randByte = std::uniform_int_distribution<uint8_t>(0, 255U);
}

void Chip8::LoadROM(char const* filename) {
  std::ifstream file(filename, std::ios::binary | std::ios::ate);

  if (file.is_open()) {
    std::streampos size = file.tellg();
    char* buffer = new char[size];
    file.seekg(0, std::ios::beg);
    file.read(buffer, size);
    file.close();

    for(long int i = 0; i < size; i++){
      memory[START_ADDRESS+i] = buffer[i];
    }

    delete [] buffer;
  }
}

void Chip8::OP_00E0(){
  memset(video, 0, sizeof(video));
}

void Chip8::OP_00EE(){
  pc = memory[--sp];
}

void Chip8::OP_1NNN(){
  pc = opcode & 0x0FFFu; // bit masking
}

void Chip8::OP_2NNN(){
  stack[sp++] = opcode&0x0FFFu; // bit masking
}

void Chip8::OP_3XKK(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t kk = opcode & 0x00FFu;

  if(registers[Vx] == registers[kk]){
    pc += 2;
  }
}

void Chip8::OP_4XKK(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t kk = opcode & 0x00FFu;

  if(registers[Vx] != registers[kk]){
    pc += 2;
  }
}

void Chip8::OP_5XY0(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;

  if(registers[Vx] == registers[Vy]){
    pc += 2;
  }
}

void Chip8::OP_6XKK(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t kk = opcode & 0x00FFu;

  registers[Vx] = kk;
}

void Chip8::OP_7XKK(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t kk = opcode & 0x00FFu;

  registers[Vx] += kk;
}

void Chip8::OP_8XY0(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;

  registers[Vx] = registers[Vy];
}

void Chip8::OP_8XY1(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;

  registers[Vx] |= registers[Vy];
}

void Chip8::OP_8XY2(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;

  registers[Vx] &= registers[Vy];
}

void Chip8::OP_8XY3(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;

  registers[Vx] ^= registers[Vy];
}

void Chip8::OP_8XY4(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;

  uint8_t sum = Vx + Vy;

  registers[0xF] = (sum > 255u) ? 1 : 0;
  registers[Vx] = sum & 0xFFu; // Using bit masking we eliminate the caryy term;
}

void Chip8::OP_8XY5(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;

  registers[0xF] = (registers[Vy] < registers[Vx]) ? 1 : 0;
  registers[Vx] -= registers[Vy];
}

void Chip8::OP_8XY6(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;

  registers[0xF] = (registers[Vx] & 0x1u);
  registers[Vx] >>= 1;
}
void Chip8::OP_8XY7(){
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;

  registers[0xF] = (registers[Vx] & 0x1u);
  registers[Vx] = registers[Vy] - registers[Vx];
}

void Chip8::OP_8XYE() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;

  registers[0xF] = (registers[Vx] & 0x1u);
  registers[Vx] <<= 1;
}

void Chip8::OP_9XY0() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  uint8_t Vy = (opcode & 0x00F0u) >> 4u;

  if (Vx != Vy) {
    pc += 2;
  }
}

void Chip8::OP_ANNN() {
  index = opcode & 0x0FFFu;
}

void Chip8::OP_BNNN() {
  uint8_t adr = opcode & 0x0FFF;
  pc = registers[0] + adr;
}

void Chip8::OP_CXNN() {
  uint8_t Vx = (opcode & 0x0F00u) >> 8u;
  registers[Vx] = randByte();
}
