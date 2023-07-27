NAME	= minirt
CC		= gcc
FSAN	= -fsanitize=address
CFLAGS	= -Wall -Wextra -Werror $(INCLUDES) -g3
INCLUDES = -I inc -I ${LIBFT_DIR} 
# MINILIB = -lmlx -framework OpenGL -framework AppKit

XPATH_MACOS=minilibx-opengl
XFLAGS_MACOS=-I$(XPATH_MACOS) -L$(XPATH_MACOS) -lmlx -framework OpenGL -framework Appkit
XPATH_LINUX=minilibx-linux
XFLAGS_LINUX=-I$(XPATH_LINUX) -L$(XPATH_LINUX) -lmlx -lXext -lX11

MINIRT_SRCS	=	main.c print_scene.c vector3.c free.c
MINIRT_SRCS_DIR	= src/
MINIRT_OBJS = $(addprefix $(MINIRT_SRCS_DIR), $(MINIRT_SRCS:.c=.o))

PARSE_SRC = nodes.c parsing.c parsing_utils.c isspace_split.c
PARSE_DIR = src/parsing/
PARSE_OBJS = $(addprefix $(PARSE_DIR), $(PARSE_SRC:.c=.o))

RENDER_SRC = render.c sphere_hit.c
RENDER_DIR = src/render/
RENDER_OBJS = $(addprefix $(RENDER_DIR), $(RENDER_SRC:.c=.o))

HOOKS_SRC = key_hooks.c
HOOKS_DIR = src/hooks/
HOOKS_OBJS = $(addprefix $(HOOKS_DIR), $(HOOKS_SRC:.c=.o))

#UTILS_SRC = env.c free.c utils.c utils_2.c utils_3.c utils_4.c utils_5.c
#UTILS_DIR = src/utils/
#UTILS_OBJS = $(addprefix $(UTILS_DIR), $(UTILS_SRC:.c=.o))

LIBFT_DIR		= utils/libft
LIBFT_LIB		= libft.a
LIB             = -L$(LIBFT_DIR) -lft

all:  ${NAME} 

${NAME}:	${LIBFT_DIR}/${LIBFT_LIB} ${MINIRT_OBJS} ${PARSE_OBJS} ${HOOKS_OBJS} ${RENDER_OBJS}
	@echo "Compiling minirt"
	${CC} ${CFLAGS} ${MINIRT_OBJS} ${PARSE_OBJS} ${HOOKS_OBJS} ${RENDER_OBJS} -o ${NAME} ${LIB} ${XFLAGS_MACOS}
# ${MINILIB}
	
${LIBFT_DIR}/${LIBFT_LIB}:
	@make -C ${LIBFT_DIR}

clean:
	@echo "cleaning files"
	@make clean -C ${LIBFT_DIR}
	@rm -rf ${MINIRT_OBJS}
	@rm -rf ${PARSE_OBJS}
	@rm -rf ${HOOKS_OBJS}
	@rm -rf ${RENDER_OBJS}
#@rm -rf ${UTILS_OBJS}

fclean: clean
	@make fclean -C ${LIBFT_DIR}
	@rm -rf ${NAME}

re: clean all

.PHONY:	all clean fclean re 