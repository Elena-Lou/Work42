# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elouisia <elouisia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/26 14:08:47 by elouisia          #+#    #+#              #
#    Updated: 2021/12/08 15:26:08 by elouisia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_calloc.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_itoa.c \
			ft_split.c

BONUS_SRCS =	ft_lstnew.c \
	  		ft_lstadd_front.c \
	  		ft_lstlast.c \
	  		ft_lstadd_back.c \
	  		ft_lstiter.c \
	  		ft_lstsize.c \
	  		ft_lstclear.c \
	  		ft_lstdelone.c \
			ft_lstmap.c

OBJS	= ${SRCS:.c=.o}

OBJS_BONUS = ${BONUS_SRCS:.c=.o}

RM	= rm -rf

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

NAME	= libft.a

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	ar -rc ${NAME} ${OBJS}

all:	${NAME}

bonus: ${OBJS} ${OBJS_BONUS}
	ar -rc ${NAME} ${OBJS} ${OBJS_BONUS}

clean:
	${RM} ${OBJS} ${OBJS_BONUS}

fclean: clean
	${RM} ${NAME}

re: fclean all

#so:
#	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS) $(BONUS_SRC)
#	gcc -nostartfiles -shared -o libft.so $(OBJS) $(OBJS_BONUS)

.PHONY: all clean fclean re bonus
