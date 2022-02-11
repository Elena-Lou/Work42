SRCS		= ./src/ft_pipex.c \
			./src/ft_pipex_utils.c \

OBJS		= $(SRCS:.c=.o)

DEPS		= $(SRCS:.c=.d)

DEPSFLAGS	= -MMD -MF $(@:.o=.d)

RM			= rm -rf

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -g3

NAME		= pipex

LIB			= libft/libft.a

INCS		= -I include -I libft

PURPLE		= \033[1;35m

CYAN		= \033[1;36m

GREEN		= \033[1;32m

NO_COLOUR	= \033[m

# -include $(DEPS)

all:	$(NAME)

%.o:	%.c
		$(CC) $(CFLAGS) -o $@ -c $< $(DEPSFLAGS) $(INCS)

makelib:
		@make --no-print-directory -C ./libft/ all
		@echo	"$(PURPLE)\nLibft $(CYAN)compiled\n$(NO_COLOUR)"

$(NAME): makelib $(OBJS)
		$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIB) $(INCS)

test: makelib $(OBJS)
		@gcc -o $(NAME) $(OBJS) $(LIB) $(INCS)
clean:
		$(RM) $(OBJS) $(DEPS)

fclean:	clean fcleanlib
		$(RM) $(NAME)

re: fclean all

cleanlib:
		@make -s --no-print-directory -C ./libft/ clean
		@echo	"$(PURPLE)\nLibft $(CYAN)-o removed\n$(NO_COLOUR)"

fcleanlib: cleanlib
		@make --no-print-directory -s -C ./libft/ fclean
		@echo	"$(PURPLE)\nLibft $(CYAN)-o && .a removed\n$(NO_COLOUR)"

.PHONY: all clean fclean re cleanlib fcleanlib