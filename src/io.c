#include "zasm.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>

zasm_file zasm_input(const char *filename) {
  int fd = open(filename, O_RDONLY);
  zasm_file f = { .name = filename };
  if (fd < 0) {
    perror("open");
    f.error = 1;
    return f;
  }
  off_t len = lseek(fd, 0, SEEK_END);
  if (len < 0) {
    perror("lseek");
    close(fd);
    f.error = 1;
    return f;
  }
  f.data = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);
  if (f.data == (uint8_t *)-1) {
    perror("mmap");
    f.error = 1;
  }
  f.size = len;
  close(fd);
  return f;
}

zasm_file zasm_output(const char *filename, size_t size) {
  int fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0755);
  zasm_file f = { .name = filename };
  if (fd < 0) {
    perror("open");
    f.error = 1;
    return f;
  }
  if (ftruncate(fd, size) == -1) {
    perror("truncate");
    close(fd);
    f.error = 1;
    return f;
  }
  f.data = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (f.data == (uint8_t *)-1) {
    perror("mmap");
    f.error = 1;
  }
  f.size = size;
  close(fd);
  return f;
}

void zasm_close(zasm_file file) {
  munmap(file.data, file.size);
}
