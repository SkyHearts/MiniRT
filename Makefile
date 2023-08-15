NAME	= miniRT
CC		= gcc
FSAN	= -fsanitize=address
CFLAGS	= -Wall -Wextra -Werror $(INCLUDES) -g3
INCLUDES = -I inc -I ${LIBFT_DIR} ${FSAN}
MINILIB = -lmlx -framework OpenGL -framework AppKit

#XPATH_MACOS=minilibx-opengl
#XFLAGS_MACOS=-I$(XPATH_MACOS) -L$(XPATH_MACOS) -lmlx -framework OpenGL -framework Appkit
#XPATH_LINUX=minilibx-linux
#XFLAGS_LINUX=-I$(XPATH_LINUX) -L$(XPATH_LINUX) -lmlx -lXext -lX11

MINIRT_SRCS	=	main.c free.c
MINIRT_SRCS_DIR	= src/
MINIRT_OBJS = $(addprefix $(MINIRT_SRCS_DIR), $(MINIRT_SRCS:.c=.o))

PARSE_SRC = nodes.c nodes_utils.c nodes_utils2.c nodes_utils3.c add_scene.c parsing.c parsing_utils.c parsing_utils2.c isspace_split.c 
PARSE_DIR = src/parsing/
PARSE_OBJS = $(addprefix $(PARSE_DIR), $(PARSE_SRC:.c=.o))

PRINT_SRC = print_scene.c print_scene_utils.c print_cam.c
PRINT_DIR = src/printdata/
PRINT_OBJS = $(addprefix $(PRINT_DIR), $(PRINT_SRC:.c=.o))

RENDER_SRC = render.c render_utils.c color_utils.c color.c image.c hit_obj.c hit_intersect.c hit_utils.c hit_cone.c
RENDER_DIR = src/render/
RENDER_OBJS = $(addprefix $(RENDER_DIR), $(RENDER_SRC:.c=.o))

VECTORS_SRC = vector1.c vector2.c vector3.c vector4.c vector5.c
VECTORS_DIR = src/vectors/
VECTORS_OBJS = $(addprefix $(VECTORS_DIR), $(VECTORS_SRC:.c=.o))

HOOKS_SRC = key_hooks.c key_moves.c key_moves2.c mouse_hooks.c fps.c
HOOKS_DIR = src/hooks/
HOOKS_OBJS = $(addprefix $(HOOKS_DIR), $(HOOKS_SRC:.c=.o))

#UTILS_SRC = env.c free.c utils.c utils_2.c utils_3.c utils_4.c utils_5.c
#UTILS_DIR = src/utils/
#UTILS_OBJS = $(addprefix $(UTILS_DIR), $(UTILS_SRC:.c=.o))

LIBFT_DIR		= utils/libft
LIBFT_LIB		= libft.a
LIB             = -L$(LIBFT_DIR) -lft

all:  ${NAME} 

${NAME}:	${LIBFT_DIR}/${LIBFT_LIB} ${MINIRT_OBJS} ${PARSE_OBJS} ${PRINT_OBJS} ${HOOKS_OBJS} ${VECTORS_OBJS} ${RENDER_OBJS}
	@echo "Compiling minirt"
	${CC} ${CFLAGS} ${MINIRT_OBJS} ${PARSE_OBJS} ${PRINT_OBJS} ${HOOKS_OBJS} ${VECTORS_OBJS} ${RENDER_OBJS} -o ${NAME} ${LIB} ${MINILIB}
#${XFLAGS_MACOS}
	
${LIBFT_DIR}/${LIBFT_LIB}:
	@make -C ${LIBFT_DIR}

clean:
	@echo "cleaning files"
	@make clean -C ${LIBFT_DIR}
	@rm -rf ${MINIRT_OBJS}
	@rm -rf ${PARSE_OBJS}
	@rm -rf ${PRINT_OBJS}
	@rm -rf ${HOOKS_OBJS}
	@rm -rf ${VECTORS_OBJS}
	@rm -rf ${RENDER_OBJS}

#@rm -rf ${UTILS_OBJS}

fclean: clean
	@make fclean -C ${LIBFT_DIR}
	@rm -rf ${NAME}

re: clean all
.PHONY:	all clean fclean re
