# Makefile for libgnl.a

# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Source files
SRC = get_next_line.c get_next_line_utils.c

# Object files
OBJ = $(SRC:.c=.o)

# Library name
NAME = libgnl.a

# ---- Rules ----

all: $(NAME)

# Build the static library
$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

# Compile each .c into .o
%.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJ)

# Remove the library and objects
fclean: clean
	rm -f $(NAME)

# Rebuild
re: fclean all