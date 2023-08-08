NAME			=	miniRT
LIBFT_DIR		=	Libft/
LIBFT			=	libft.a
SRCS_DIR		=	srcs/
OBJS_DIR		=	objs/

FILES			=	main render hooks \
					edit/edit_property edit/edit_mode edit/edit_utils\
					utils/ft_atof utils/rt_split utils/utils utils/printing\
					color/color color/phong color/edit_mode color/shadows \
					color/phong_utils color/color2\
					checker/validator checker/get_input checker/checkers checker/settings \
					checker/set_cylinder checker/set_plane checker/set_sphere \
					checker/set_cone checker/is_fix checker/set_light\
					vector/vec3 vector/vec3_utils vector/convert vector/vec4 \
					matrix/matrix matrix/matrix2 matrix/matrix4_mul matrix/matrix_inverse \
					matrix/view_matrix matrix/view_matrix2\
					geometry/sphere geometry/plane geometry/cylinder geometry/cone\
					geometry/surface_normal geometry/cube\
					transformation/info transformation/translation transformation/checkerboard\
					transformation/panning transformation/get_uv transformation/xyz\
					quaternion/quaternion \
					texture/bump texture/init_texture texture/texture_uv

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
    COMPILER = $(CC) $(FSAN) $(INCL) $(MLX_H) -o $(NAME) $(SRCS) $(LIBFT_DIR)$(LIBFT) $(APPLE_MLX) $(MATH)
else
    COMPILER = $(CC) $(FSAN) $(INCL) -o $(NAME) $(SRCS) $(LIBFT_DIR)$(LIBFT) $(LINUX_MLX) $(MATH)
endif

all:
	@mkdir -p $(OBJS_DIR) $(OBJS_DIR)/color $(OBJS_DIR)/edit
	@mkdir -p $(OBJS_DIR)checker $(OBJS_DIR)utils $(OBJS_DIR)vector
	@mkdir -p $(OBJS_DIR)matrix $(OBJS_DIR)geometry $(OBJS_DIR)transformation
	@mkdir -p $(OBJS_DIR)quaternion $(OBJS_DIR)texture
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