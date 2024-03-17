
NAME		:= so_long

LIBS		:= ft mlx42
LIBS_TARGET	:= \
			   external_libs/42_libs/libft.a \
			   external_libs/MLX42/build/libmlx42.a

LIBS_DIR	:= external_libs
LIBFT		:= 42_libs/libft.a
MLX			:= MLX42/build/libmlx42.a

HEADER_FILE	:= so_long.h

SRC_DIR		:= src
SRCS		:= \
			   main.c init_entities.c free.c \
			   parsing/map_init.c parsing/error_check.c parsing/error_check2.c \
			   utils/utils.c utils/utils_free.c \
			   graphics/load_images.c graphics/sprite.c
SRCS		:= $(SRCS:%=$(SRC_DIR)/%)

OBJ_DIR		:= .build
OBJS		:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC			:= cc
CFLAGS		:= -g -MMD
MLXFLAGS	:= -ldl -lglfw -pthread -lm
LINKERFLAGS	:= $(addprefix -L, $(dir $(LIBS_TARGET))) $(addprefix -l, $(LIBS))
RM			:= rm -rf


all: $(NAME)

-include $(OBJS:.o=.d)

$(NAME): $(OBJS) $(LIBS_TARGET)
	@printf "\n"
	$(CC) $(OBJS) $(LINKERFLAGS) $(MLXFLAGS) -o $(NAME)
	@printf "$(CREATED)" $@ $(CUR_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBS_TARGET):
	$(MAKE) -C $(@D) all

clean:
	for i in $(dir $(LIBS_TARGET)); do $(MAKE) -C $$i clean; done
	$(RM) $(OBJ_DIR)
	@printf "$(REMOVED)" $(OBJ_DIR) $(CUR_DIR)

fclean: clean
	$(MAKE) -C external_libs/42_libs fclean
	$(RM) $(OBJ_DIR)
	$(RM) $(NAME)
	@printf "$(REMOVED)" $(OBJ_DIR) $(CUR_DIR)
	@printf "$(REMOVED)" $(NAME) $(CUR_DIR)

re:
	$(MAKE) fclean
	$(MAKE) all

info-%:
	$(info $($*))

.PHONY: clean flcean re

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
