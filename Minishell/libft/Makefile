SRCS	= 	ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_strlen.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_atoi.c \
			ft_strjoin_qua.c \
			ft_memset.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strnstr.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_strdup.c \
			ft_bzero.c \
			ft_strcmp.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_calloc.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strjoin_bis.c \
			ft_strjoin_ter.c \
			ft_strtrim.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_itoa.c \
			ft_split.c \
			ft_printf.c \
			ft_printf_n.c \
			ft_printf_base.c \
			ft_printf_utils.c \
			get_next_line.c \
			get_next_line_utils.c \
			ft_lstnew.c \
	  		ft_lstadd_front.c \
	  		ft_lstlast.c \
	  		ft_lstadd_back.c \
	  		ft_lstiter.c \
	  		ft_lstsize.c \
	  		ft_lstclear.c \
	  		ft_lstdelone.c \
			ft_lstmap.c

OBJS_DIR = objs

OBJS	= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

INCS		= -I include

DEPS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.d))

DEPSFLAGS	= -MMD -MF $(@:.o=.d)

RM	= rm -rf

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

NAME	= libft.a

all:	${NAME}

$(OBJS_DIR)/%.o:	%.c
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -o $@ -c $< $(DEPSFLAGS) $(INCS)

${NAME}: ${OBJS}
	ar -rc ${NAME} ${OBJS}

clean:
	${RM} ${OBJS_DIR} ${DEPS}

fclean: clean
	${RM} ${NAME}

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re bonus