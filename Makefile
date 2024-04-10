
NAME		:= so_long

LIBS_DIR	:= external_libs
LIBFT		:= $(LIBS_DIR)/42_libs/libft.a
MLX42_DIR	:= $(LIBS_DIR)/MLX42
MLX42		:= $(MLX42_DIR)/build/libmlx42.a
LIBS		:= $(LIBFT) $(MLX42) -ldl -lglfw -pthread -lm

SUBMOD_FLAG	:= $(MLX42_DIR)/README.md

SRC_DIR		:= src
SRCS		:= $(shell find $(SRC_DIR) -iname "*.c")

OBJ_DIR		:= .build
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC			:= cc
CFLAGS		:= -Wall -Werror -Wextra -Wunused -Wuninitialized -Wunreachable-code -g -MMD
RM			:= rm -rf

all: $(NAME)

-include $(OBJS:.o=.d)

$(NAME): $(SUBMOD_FLAG) $(LIBFT) $(MLX42) $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@printf "$(CREATED)" $@ $(CUR_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(SUBMOD_FLAG):
	git submodule init
	git submodule update

$(LIBFT):
	$(MAKE) -C $(@D) all

$(MLX42):	
	cmake $(MLX42_DIR) -B $(dir $(MLX42)) && make -C $(dir $(MLX42)) -j4
	@printf "$(CREATED)" $@ $(dir $(abspath $(MLX42)))

clean:
	$(MAKE) -C $(dir $(LIBFT)) clean
	$(RM) $(dir $(MLX42))
	@printf "$(REMOVED)" "build" "$(dir $(abspath $(MLX42_DIR)))"
	$(RM) $(OBJ_DIR)
	@printf "$(REMOVED)" $(OBJ_DIR) $(CUR_DIR)

fclean: clean
	$(MAKE) -C $(dir $(LIBFT)) fclean
	$(RM) $(NAME)
	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)

re:
	$(MAKE) fclean
	$(MAKE) all

info-%:
	$(info $($*))

.PHONY: clean fclean re

# ----------------------------------- colors --------------------------------- #

BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

# ----------------------------------- messages ------------------------------- #

CUR_DIR := $(dir $(abspath $(firstword $(MAKEFILE_LIST))))
REMOVED	:= $(MAGENTA) $(BOLD) REMOVED %s (%s) $(RESET)\n\n
CREATED	:= $(GREEN) $(BOLD) CREATED %s (%s) $(RESET)\n\n
UPDATED	:= $(GREEN) $(BOLD) CREATED OR UPDATED %s (%s) $(RESET)\n\n
