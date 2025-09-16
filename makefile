# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phofer <phofer@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/10 13:48:50 by phofer            #+#    #+#              #
#    Updated: 2025/09/15 14:33:22 by phofer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

SRC_DIR		= src

SRCS		= $(SRC_DIR)/main.c \
			  $(SRC_DIR)/game.c \
			  $(SRC_DIR)/game2.c \
			  $(SRC_DIR)/input.c \
			  $(SRC_DIR)/input2.c \
			  $(SRC_DIR)/render.c \
			  $(SRC_DIR)/render2.c \
			  $(SRC_DIR)/draw_text.c \
			  $(SRC_DIR)/cleanup.c \
			  $(SRC_DIR)/map_parser.c \
			  $(SRC_DIR)/map_parser2.c \
			  $(SRC_DIR)/flood_fill.c \
			  $(SRC_DIR)/flood_fill2.c \
			  $(SRC_DIR)/enemy.c \
			  $(SRC_DIR)/enemy2.c \
			  $(SRC_DIR)/helpers.c

OBJS		= $(SRCS:.c=.o)

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
MLXFLAGS	= -lX11 -lXext -lm

# Adjust these paths to match directory structure
LIBFT_DIR	= include/libft
LIBFT		= $(LIBFT_DIR)/libft.a

GNL_DIR		= include/get_next_line
GNL			= $(GNL_DIR)/libgnl.a

PRINTF_DIR	= include/printf
PRINTF		= $(PRINTF_DIR)/libftprintf.a

MLX_DIR		= include/minilibx-linux
MLX			= $(MLX_DIR)/libmlx_Linux.a

INCLUDES	= -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(PRINTF_DIR) -I$(MLX_DIR) -I./

all: $(NAME)

$(NAME): $(LIBFT) $(GNL) $(PRINTF) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(GNL) $(PRINTF) $(MLX) $(MLXFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(GNL):
	make -C $(GNL_DIR)

$(PRINTF):
	make -C $(PRINTF_DIR)

$(MLX):
	make -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	make clean -C $(LIBFT_DIR) 2>/dev/null || true
	make clean -C $(GNL_DIR) 2>/dev/null || true
	make clean -C $(PRINTF_DIR) 2>/dev/null || true
	make clean -C $(MLX_DIR) 2>/dev/null || true

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR) 2>/dev/null || true
	make fclean -C $(GNL_DIR) 2>/dev/null || true
	make fclean -C $(PRINTF_DIR) 2>/dev/null || true

re: fclean all

valgrind:
	@valgrind --leak-check=full --track-origins=yes ./$(NAME) maps/lvl2.ber

.PHONY: all clean fclean re valgrind
