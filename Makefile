SRCS_DIR	= src/

SRCS_BONUS_DIR	= bonus/

SRCS		= ./src/ft_pipex.c \
			./src/ft_pipex_utils.c \

SRCS_BONUS	= ./bonus/ft_pipex_bonus.c \
			./bonus/ft_pipex_utils_bonus.c \

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

LIB_NAME	= libft/libft.a

INCS		= -I include -I libft

PURPLE		= \033[1;35m

CYAN		= \033[1;36m

GREEN		= \033[1;32m

ORANGE		= \033[1;33m

NO_COLOUR	= \033[m


all:	$(NAME)
	@make $(NAME) -q && echo "$(GREEN)All good here !$(NO_COLOUR)"


%.o:	%.c
		$(CC) $(CFLAGS) -o $@ -c $< $(DEPSFLAGS) $(INCS)

$(LIB_NAME):
		@make --no-print-directory -s -C ./libft/ all
		@echo	"$(PURPLE)\nLibft $(CYAN)compiled\n$(NO_COLOUR)"

$(NAME): $(LIB_NAME) $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $@ $(INCS) $(LIB_NAME)
		@echo "$(ORANGE)Pipex$(CYAN) is ready$(NO_COLOUR)"

$(BONUS_NAME): $(LIB_NAME) $(OBJS_BONUS)
		$(CC) $(CFLAGS) -o $@ $(OBJS_BONUS) $(LIB_NAME) $(INCS)
		@echo "$(ORANGE)Pipexbonus$(CYAN) is ready$(NO_COLOUR)"

makelib: $(LIB_NAME)

bonus: $(BONUS_NAME)

clean:
		$(RM) $(OBJS) $(DEPS) $(OBJS_BONUS) $(DEPS_BONUS)

fclean:	clean fcleanlib
		$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

cleanlib:
		@make --no-print-directory -s -C ./libft/ clean
		@echo	"$(PURPLE)\nLibft $(CYAN)-o removed\n$(NO_COLOUR)"

fcleanlib: cleanlib
		@make --no-print-directory -s -C ./libft/ fclean
		@echo	"$(PURPLE)\nLibft $(CYAN)-o && .a removed\n$(NO_COLOUR)"

# -include $(DEPS)
.PHONY: all clean fclean re cleanlib fcleanlib bonus