NAME = zasm

CC = clang
CFLAGS = -g3 -Wall -Wextra -std=gnu23

SRC = $(addprefix src/, main.c io.c lexer.c parser.c \
			codegen.c syscall.c print.c)
OBJ = $(patsubst src/%.c, obj/%.o, $(SRC))
DEP = $(OBJ:%.o=%.d)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(NAME) $(OBJ)
