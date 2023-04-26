NAME			=	miniRT
LIBFT_DIR		=	Libft/
LIBFT			=	libft.a
SRCS_DIR		=	srcs/
OBJS_DIR		=	objs/
FILES			=	main error ft_atof init set_objs set_scene utils validater
# MLXFLAGS		=	-L lib/minilibx-linux/libmlx_Linux.a -lmlx -lXext -lX11
MLXFLAGS		=	-L lib/minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit -lz
SRCS			=	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS			=	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra
# CFLAGS			+=	-lm
FSAN			=	-fsanitize=address -g3
RM				=	rm -rf
INCL			=	include/

all:
	@mkdir -p $(OBJS_DIR)
	@make $(LIBFT)
	make $(NAME)

$(OBJS_DIR)%.o:$(SRCS_DIR)%.c
	$(CC) $(CFLAGS) -I $(INCL) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) -I $(INCL) $(MLXFLAGS) -o $(NAME) $(OBJS) $(LIBFT_DIR)$(LIBFT)

clean:
	$(RM) $(OBJS_DIR)

fclean : clean
	$(RM) $(NAME)

libclean:
	make fclean -C $(LIBFT_DIR)

re: fclean clean all

norm:
	@norminette -R CheckForbiddenSourceHeader $(SRCS)