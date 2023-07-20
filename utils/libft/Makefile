NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
AR = ar rcs
RM = rm -f

FILES = 	ft_memset \
			ft_bzero \
			ft_memcpy \
			ft_memmove \
			ft_strlen \
			ft_strchr \
			ft_strrchr \
			ft_strcmp \
			ft_strncmp \
			ft_strlcpy \
			ft_strncpy \
			ft_strlcat \
			ft_isalpha \
			ft_isdigit \
			ft_isalnum \
			ft_isascii \
			ft_isprint \
			ft_toupper \
			ft_tolower \
			ft_memcmp \
			ft_memchr \
			ft_strnstr \
			ft_atoi \
			ft_strdup \
			ft_calloc \
			ft_substr \
			ft_strjoin \
			ft_strtrim \
			ft_split \
			ft_itoa \
			ft_strmapi \
			ft_striteri \
			ft_putchar_fd \
			ft_putstr_fd \
			ft_putendl_fd \
			ft_putnbr_fd \
			get_next_line

FILES_B =	ft_lstnew \
	  		ft_lstadd_front \
	  		ft_lstsize \
	  		ft_lstlast \
	  		ft_lstadd_back \
	  		ft_lstdelone \
	  		ft_lstclear \
	  		ft_lstiter \
	  		ft_lstmap

FILES_PRINT =	ft_printf \
					ft_putchar \
					ft_putnbr_dec \
					ft_putnbr_hex \
					ft_putnbr_uns_dec \
					ft_putptr \
					ft_putstr

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
SRCS_B = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES_B)))
SRCS_PRINT = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES_PRINT)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))
OBJS_B = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES_B)))
OBJS_PRINT = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES_PRINT)))


.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME)

$(NAME): $(OBJS) $(OBJS_B) $(OBJS_PRINT)
	$(AR) $@ $^

clean:
	$(RM) $(OBJS) $(OBJS_B) $(OBJS_PRINT)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: bonus all clean fclean re