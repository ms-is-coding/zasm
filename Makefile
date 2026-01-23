NAME = zasm

CC = clang
CFLAGS = -g3 -Wall -Wextra -std=gnu23

SRC = $(addprefix src/, main.c io.c lexer.c parser.c \
			codegen.c syscall.c)
OBJ = $(SRC:%.c=%.o)
DEP = $(OBJ:%.o=%.d)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(NAME) $(OBJ)
