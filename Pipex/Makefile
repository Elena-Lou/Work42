SRCS_DIR	= src/

SRCS_BONUS_DIR	= bonus/

SRCS		= ./src/ft_pipex.c \
			./src/ft_pipex_utils.c \
			./src/ft_putstr_fd.c	\
			./src/ft_split.c	\
			./src/ft_strdup.c	\
			./src/ft_strjoin.c	\
			./src/ft_strnstr.c 	\
			./src/ft_substr.c 	\

SRCS_BONUS	= ./bonus/ft_pipex_bonus.c \
			./bonus/ft_pipex_utils_bonus.c \
			./src/ft_putstr_fd.c	\
			./src/ft_split.c	\
			./src/ft_strdup.c	\
			./src/ft_strjoin.c	\
			./src/ft_strnstr.c 	\
			./src/ft_substr.c 	\


OBJS		= $(SRCS:.c=.o)

OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

DEPS		= $(SRCS:.c=.d)

DEPS_BONUS	= $(SRCS_BONUS:.c=.d)

DEPSFLAGS	= -MMD -MF $(@:.o=.d)

RM			= rm -rf

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -g3

NAME		= pipex

BONUS_NAME	= pipex_bonus

INCS		= -I include

PURPLE		= \033[1;35m

CYAN		= \033[1;36m

GREEN		= \033[1;32m

ORANGE		= \033[1;33m

NO_COLOUR	= \033[m


all:	$(NAME)
	@make $(NAME) -q && echo "$(GREEN)All good here !$(NO_COLOUR)"

-include $(DEPS)

%.o:	%.c
		$(CC) $(CFLAGS) -o $@ -c $< $(DEPSFLAGS) $(INCS)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $^ -o $@ $(INCS)
		@echo "$(ORANGE)Pipex$(CYAN) is ready$(NO_COLOUR)"

$(BONUS_NAME): $(OBJS_BONUS)
		$(CC) $(CFLAGS) $^ -o $@ $(INCS)
		@echo "$(ORANGE)Pipex_bonus$(CYAN) is ready$(NO_COLOUR)"

bonus: $(BONUS_NAME)

clean:
		$(RM) $(OBJS) $(DEPS) $(OBJS_BONUS) $(DEPS_BONUS)

fclean:	clean 
		$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re bonus rebonus