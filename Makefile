NAME			=	miniRT
LIBFT_DIR		=	Libft/
LIBFT			=	libft.a
SRCS_DIR		=	srcs/
OBJS_DIR		=	objs/

FILES			=	main utils/ft_atof utils/rt_split utils/utils\
					color \
					checker/validator checker/get_input checker/checkers checker/settings \
					checker/set_cylinder checker/set_plane checker/set_sphere \
					vector/vector vector/vector2 \
					matrix/matrix

LINUX_MLX		=	-L lib/minilibx-linux/libmlx_Linux.a -lmlx -lXext -lX11
APPLE_MLX		=	-L lib/minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit -lz
SRCS			=	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS			=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra
MATH			=	-lm
FSAN			=	-fsanitize=address -g3
RM				=	rm -rf
INCL			=	-I include/
MLX_H			=	-I /usr/X11/include
OS				=	$(shell uname -s)

# Define the compilation commands for each operating system
ifeq ($(OS),Darwin)
    COMPILER = $(CC) $(CFLAGS) $(INCL) $(MLX_H) -o $(NAME) $(SRCS) $(LIBFT_DIR)$(LIBFT) $(APPLE_MLX) $(MATH)
else
    COMPILER = $(CC) $(INCL) -o $(NAME) $(SRCS) $(LIBFT_DIR)$(LIBFT) $(LINUX_MLX) $(MATH)
endif

all:
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)checker $(OBJS_DIR)utils $(OBJS_DIR)vector
	@mkdir -p $(OBJS_DIR)matrix
	@make $(LIBFT)
	make $(NAME)

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
	$(CC) $(INCL) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(COMPILER)

clean:
	$(RM) $(OBJS_DIR)

fclean : clean
	$(RM) $(NAME)

libclean:
	make fclean -C $(LIBFT_DIR)

re: fclean clean all

norm:
	@norminette -R CheckForbiddenSourceHeader $(SRCS) include/