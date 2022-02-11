SRCS	=	ft_printf.c	\
			ft_printf_utils.c \
			ft_printf_n.c \
			ft_printf_base.c

OBJS	= ${SRCS:.c=.o}

RM		= rm -rf

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

NAME	= libftprintf.a

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
		ar -rc ${NAME} ${OBJS}

all:	${NAME}

clean:
		${RM} ${OBJS}

fclean: clean
		${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re