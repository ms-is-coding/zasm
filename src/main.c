#include "zasm.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <fcntl.h>
#include <elf.h>
#include <sys/mman.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <file.zasm>\n", argv[0]);
    return 1;
  }

  Elf64_Ehdr ehdr = {
    .e_ident = {
      ELFMAG0, ELFMAG1, ELFMAG2, ELFMAG3,
      ELFCLASS64, ELFDATA2LSB, EV_CURRENT, ELFOSABI_NONE,
    },
    .e_type = ET_EXEC,
    .e_machine = EM_X86_64,
    .e_version = EV_CURRENT,
    .e_entry = 0x10008,
    .e_phoff = 0x40,
    .e_shoff = 0,
    .e_flags = 0,
    .e_ehsize = sizeof(Elf64_Ehdr),
    .e_phentsize = sizeof(Elf64_Phdr),
    .e_phnum = 1,
    .e_shentsize = 0,
    .e_shnum = 0,
    .e_shstrndx = 0,
  };
  Elf64_Phdr phdr = {
    .p_type = PT_LOAD,
    .p_flags = PF_R | PF_W | PF_X,
    .p_offset = 0,
    .p_vaddr = 0x10000,
    .p_paddr = 0,
    .p_filesz = 0x78,
    .p_memsz = 0x78,
    .p_align = 0x1000,
  };

  uint8_t code0[8] = {};
  uint8_t code1[14] = {};
  uint8_t code2[6] = {};
  uint8_t code3[12] = {};

  zasm_file in = zasm_input(argv[1]);

  size_t tok_count;
  zasm_token *tokens = zasm_lex(in, &tok_count);
  zasm_parse(tokens, tok_count);

  return 0;

  strrchr(argv[1], '.')[0] = 0;

  zasm_file out = zasm_output(argv[1], 0x78);

  memcpy(out.data + 0x00, &ehdr, sizeof(ehdr));
  memcpy(out.data + 0x40, &phdr, sizeof(phdr));

  memcpy(out.data + 0x08, code0, sizeof(code0));
  memcpy(out.data + 0x28, code1, sizeof(code1));
  memcpy(out.data + 0x3a, code2, sizeof(code2));
  memcpy(out.data + 0x58, code3, sizeof(code3));

  memcpy(out.data + 0x68, out.data + 0x60, 0x8); // filesz == memsz

  zasm_close(in);
  zasm_close(out);

  ; return 0;
}
