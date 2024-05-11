NAME = pipex
CC = cc
FLAGS = -Wall -Wextra -Werror -g# -fsanitize=address
RM = rm -f
SRC = src/pipex.c \
	src/px_children.c \
	src/px_cmds.c \
	src/px_errors.c \
	src/px_free.c \
	src/px_info.c \
	src/px_open_utils.c \
	src/px_paths.c \
	src/px_utils.c \

B_SRC = bonus/pipex_bonus.c \
	bonus/px_children_bonus.c \
	bonus/px_cmds_bonus.c \
	bonus/px_errors_bonus.c \
	bonus/px_free_bonus.c \
	bonus/px_info_bonus.c \
	bonus/px_open_utils_bonus.c \
	bonus/px_paths_bonus.c \
	bonus/px_utils_bonus.c \

OBJ = $(SRC:src/%.c=obj/%.o)
B_OBJ = $(B_SRC:bonus/%.c=obj/%.o)
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

clean:
	@$(RM) -r obj
	@$(MAKE) -C $(LIBFT_DIR) clean
	@printf "Cleaned object files\n"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@printf "Cleaned executables\n"

re: fclean all

bonus: $(LIBFT) $(B_OBJ)
	@printf "Compiling\n"
	@$(CC) $(FLAGS) $(B_OBJ) -L $(LIBFT_DIR) -lft -o $(NAME)
	@printf "Done\n"

$(OBJ): $(SRC) pipex.h Makefile
	@mkdir -p $(dir $@)
	@printf "Building $@\n"
	@$(CC) $(FLAGS) -c $(@:obj/%.o=src/%.c) -o $@

$(B_OBJ): $(B_SRC) pipex_bonus.h Makefile
	@mkdir -p $(dir $@)
	@printf "Building $@\n"
	@$(CC) $(FLAGS) -c $(@:obj/%bonus.o=bonus/%bonus.c) -o $@

$(NAME): $(LIBFT) $(OBJ)
	@printf "Compiling\n"
	@$(CC) $(FLAGS) $(OBJ) -L $(LIBFT_DIR) -lft -o $(NAME)
	@printf "Done\n"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

.PHONY: libft all re clean fclean
