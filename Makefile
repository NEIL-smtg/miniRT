NAME				=	miniRT
BONUS_NAME			=	bonus_miniRT
LIBFT_DIR			=	Libft/
LIBFT				=	libft.a
SRCS_DIR			=	mandatory/srcs/
OBJS_DIR			=	mandatory/objs/
BONUS_SRCS_DIR		=	bonus/srcs/
BONUS_OBJS_DIR		=	bonus/objs/

FILES				=	main render hooks \
						edit/edit_property edit/edit_mode edit/edit_utils\
						utils/ft_atof utils/rt_split utils/utils utils/printing\
						utils/printing_utils \
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
						transformation/info transformation/translation \
						transformation/panning transformation/xyz transformation/panning_utils\
						checkerboard/checkerboard checkerboard/get_uv \
						quaternion/quaternion \
						texture/bump texture/init_texture texture/texture_uv

BONUS_FILES			=	main render render_utils hooks \
						edit/edit_property edit/edit_mode edit/edit_utils\
						utils/ft_atof utils/rt_split utils/utils utils/printing\
						utils/printing_utils \
						color/color color/phong color/edit_mode color/shadows \
						color/phong_utils color/color2 color/material\
						checker/validator checker/get_input checker/checkers checker/settings \
						checker/set_cylinder checker/set_plane checker/set_sphere \
						checker/set_cone checker/is_fix checker/set_light\
						vector/vec3 vector/vec3_utils vector/convert vector/vec4 \
						matrix/matrix matrix/matrix2 matrix/matrix4_mul matrix/matrix_inverse \
						matrix/view_matrix matrix/view_matrix2\
						geometry/sphere geometry/plane geometry/cylinder geometry/cone\
						geometry/surface_normal geometry/cube\
						transformation/info transformation/translation transformation/panning_utils\
						transformation/panning  transformation/xyz\
						checkerboard/checkerboard checkerboard/get_uv \
						quaternion/quaternion \
						texture/bump texture/init_texture texture/texture_uv

LINUX_MLX			=	-L lib/minilibx-linux/libmlx_Linux.a -lmlx -lXext -lX11
APPLE_MLX			=	-L lib/minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit -lz
SRCS				=	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS				=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
BONUS_SRCS			=	$(addprefix $(BONUS_SRCS_DIR), $(addsuffix .c, $(BONUS_FILES)))
BONUS_OBJS			=	$(addprefix $(BONUS_OBJS_DIR), $(addsuffix .o, $(BONUS_FILES)))
CC					=	gcc
CFLAGS				=	-Wall -Werror -Wextra
MATH				=	-lm
FSAN				=	-fsanitize=address -g3
RM					=	rm -rf
INCL				=	-I mandatory/include/
BONUS_INCL			=	-I bonus/include/
MLX_H				=	-I /usr/X11/include
OS					=	$(shell uname -s)

ifeq ($(OS),Darwin)
	THREADS			=	-D THREAD_NUM=$(shell sysctl -n hw.ncpu)
else
	THREADS			=	-D THREAD_NUM=$(shell nproc)
endif

# Define the compilation commands for each operating system
ifeq ($(OS),Darwin)
    COMPILER	= $(CC) $(FSAN) $(THREADS) $(INCL) $(MLX_H) -o $(NAME) $(SRCS) $(LIBFT_DIR)$(LIBFT) $(APPLE_MLX) $(MATH) -pthread
	COMPILER2	= $(CC) $(FSAN) $(THREADS) $(BONUS_INCL) $(MLX_H) -o $(BONUS_NAME) $(BONUS_SRCS) $(LIBFT_DIR)$(LIBFT) $(APPLE_MLX) $(MATH) -pthread
else
    COMPILER	= $(CC) $(THREADS) $(INCL) -o $(NAME) $(SRCS) $(LIBFT_DIR)$(LIBFT) $(LINUX_MLX) $(MATH) -pthread
	COMPILER2	= $(CC) $(THREADS) $(BONUS_INCL) -o $(BONUS_NAME) $(BONUS_SRCS) $(LIBFT_DIR)$(LIBFT) $(LINUX_MLX) $(MATH) -pthread
endif

.PHONY: bonus all

all: 
	@mkdir -p $(OBJS_DIR) $(OBJS_DIR)/color $(OBJS_DIR)/edit
	@mkdir -p $(OBJS_DIR)checker $(OBJS_DIR)utils $(OBJS_DIR)vector
	@mkdir -p $(OBJS_DIR)matrix $(OBJS_DIR)geometry $(OBJS_DIR)transformation
	@mkdir -p $(OBJS_DIR)quaternion $(OBJS_DIR)texture $(OBJS_DIR)checkerboard
	@make $(LIBFT)
	make $(NAME)

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
	$(CC) $(INCL) -c $< -o $@

$(NAME): $(OBJS)
	$(COMPILER)

clean:
	$(RM) $(OBJS_DIR)
	@$(RM) miniRT.dSYM/

fclean : clean
	$(RM) $(NAME)

bonus:
	@mkdir -p $(BONUS_OBJS_DIR) $(BONUS_OBJS_DIR)/color $(BONUS_OBJS_DIR)/edit
	@mkdir -p $(BONUS_OBJS_DIR)checker $(BONUS_OBJS_DIR)utils $(BONUS_OBJS_DIR)vector
	@mkdir -p $(BONUS_OBJS_DIR)matrix $(BONUS_OBJS_DIR)geometry $(BONUS_OBJS_DIR)transformation
	@mkdir -p $(BONUS_OBJS_DIR)quaternion $(BONUS_OBJS_DIR)texture $(BONUS_OBJS_DIR)checkerboard
	@make $(LIBFT)
	make $(BONUS_NAME)

$(BONUS_OBJS_DIR)%.o:$(SRCS_DIR)%.c
	$(CC) $(BONUS_INCL) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(BONUS_NAME): $(BONUS_SRCS_DIR)
	$(COMPILER2)

bclean:
	$(RM) $(BONUS_OBJS_DIR)

bfclean : bclean
	$(RM) $(BONUS_NAME)
	@$(RM) bonus_miniRT.dSYM/

libclean:
	make fclean -C $(LIBFT_DIR)

re: fclean clean all

bre: bfclean bclean bonus

norm:
	@norminette -R CheckForbiddenSourceHeader $(SRCS) mandatory/include/

bnorm:
	@norminette -R CheckForbiddenSourceHeader $(BONUS_SRCS) bonus/include/