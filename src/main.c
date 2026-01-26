#include "zasm.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <fcntl.h>
#include <elf.h>
#include <sys/mman.h>

void zasm_print_ast(zasm_program *p);

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "error: no input files\n");
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
    .e_entry = 0x10150,
    .e_phoff = 0x40,
    .e_shoff = 0x78,
    .e_flags = 0,
    .e_ehsize = sizeof(Elf64_Ehdr),
    .e_phentsize = sizeof(Elf64_Phdr),
    .e_phnum = 1,
    .e_shentsize = sizeof(Elf64_Shdr),
    .e_shnum = 3,
    .e_shstrndx = 1,
  };
  Elf64_Phdr phdr = {
    .p_type = PT_LOAD,
    .p_flags = PF_R | PF_W | PF_X,
    .p_offset = 0x150,
    .p_vaddr = 0x10150,
    .p_paddr = 0,
    .p_filesz = 0x200,
    .p_memsz = 0x200,
    .p_align = 0x1000,
  };
  Elf64_Shdr shstrtab_shdr = {
    .sh_name = 0x1,
    .sh_type = SHT_STRTAB,
    .sh_flags = 0,
    .sh_addr = 0,
    .sh_offset = 0x138,
    .sh_size = 0x18,
    .sh_link = 0,
    .sh_info = 0,
    .sh_addralign = 0,
    .sh_entsize = 0
  };
  Elf64_Shdr text_shdr = {
    .sh_name = 0xb,
    .sh_type = SHT_PROGBITS,
    .sh_flags = SHF_ALLOC | SHF_EXECINSTR,
    .sh_addr = 0x10000,
    .sh_offset = 0x150,
    .sh_size = 0x200,
    .sh_link = 0,
    .sh_info = 0,
    .sh_addralign = 0x10,
    .sh_entsize = 0
  };

  // uint8_t code0[8] = { 0xeb, 0x68 }; // jump to actual code
  // uint8_t code1[14] = {};
  // uint8_t code2[6] = {};
  // uint8_t code3[12] = {};

  zasm_file in = zasm_input(argv[1]);
  if (in.error)
    return 1;

  size_t tok_count;
  zasm_token *tokens = zasm_lex(in, &tok_count);

  zasm_program *p = zasm_parse(in, tokens, tok_count);

  zasm_print_ast(p);

  size_t out_max = 0x400;
  uint8_t out_buf[out_max] = {};

  zasm_codegen(p, out_buf, out_max);

  strrchr(argv[1], '.')[0] = 0;

  zasm_file out = zasm_output(argv[1], sizeof(ehdr)
    + sizeof(phdr)
    + 2 * sizeof(text_shdr)
    + out_max);
  if (out.error)
    return 1;

  uint8_t *ptr = out.data;

  ptr = mempcpy(ptr, &ehdr, sizeof(ehdr));
  ptr = mempcpy(ptr, &phdr, sizeof(phdr));
  ptr = memset(ptr, 0, sizeof(Elf64_Shdr));
  ptr += sizeof(Elf64_Shdr);
  ptr = mempcpy(ptr, &shstrtab_shdr, sizeof(shstrtab_shdr));
  ptr = mempcpy(ptr, &text_shdr, sizeof(text_shdr));
  ptr = mempcpy(ptr, "\00.shstrtab\00.text\00\00", 0x18);

  // memcpy(out.data + 0x08, code0, sizeof(code0));
  // memcpy(out.data + 0x28, code1, sizeof(code1));
  // memcpy(out.data + 0x3a, code2, sizeof(code2));
  // memcpy(out.data + 0x58, code3, sizeof(code3));

  // memcpy(out.data + 0x68, out.data + 0x60, 0x8); // filesz == memsz

  memcpy(ptr, out_buf, out_max);

  zasm_close(in);
  zasm_close(out);

  ; return 0;
}
