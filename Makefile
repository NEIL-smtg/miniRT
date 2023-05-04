NAME			=	miniRT
LIBFT_DIR		=	Libft/
LIBFT			=	libft.a
SRCS_DIR		=	srcs/
OBJS_DIR		=	objs/
FILES			=	main ft_atof color validator
# MLXFLAGS		=	-L lib/minilibx-linux/libmlx_Linux.a -lmlx -lXext -lX11
MLXFLAGS		=	-L lib/minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit -lz
SRCS			=	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS			=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra
# CFLAGS			+=	-lm
CFLAGS			+=	-fsanitize=address -g3
RM				=	rm -rf
INCL			=	-I include/
MLX_H			=	-I /usr/X11/include

all:
	@mkdir -p $(OBJS_DIR)
	@make $(LIBFT)
	make $(NAME)

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
	$(CC) $(CFLAGS) $(INCL) $(MLX_H) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(INCL) $(MLX_H) $(MLXFLAGS) -o $(NAME) $(OBJS) $(LIBFT_DIR)$(LIBFT)

clean:
	$(RM) $(OBJS_DIR)

fclean : clean libclean
	$(RM) $(NAME)

libclean:
	make fclean -C $(LIBFT_DIR)

re: fclean libclean clean all

norm:
	@norminette -R CheckForbiddenSourceHeader $(SRCS)