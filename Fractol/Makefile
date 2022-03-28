CC = gcc

CFLAGS = -Wall -Werror -Wextra -g3 -O3 -fno-builtin

NAME = fractol

MINILIBX = minilibx

SRCS = main.c \
		utils.c	\
		keys.c	\
		mandel_maths.c	\
		julia_maths.c	\
		colours.c

OBJS = $(SRCS:.c=.o)

DEPS		= $(SRCS:.c=.d)

DEPSFLAGS	= -MMD -MF $(@:.o=.d)

INCS		= -I include -I libft -I minilibx

RM			= rm -rf

LIB_NAME	= libft/libft.a

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

$(LIB_NAME):
		@make --no-print-directory -s -C ./libft/ all
		@echo	"$(PURPLE)\nLibft $(CYAN)compiled\n$(NO_COLOUR)"

$(NAME): $(OBJS) $(LIB_NAME)
		@cd $(MINILIBX) && make --no-print-directory -s
		$(CC) $(CFLAGS) $(OBJS) -o $@ $(INCS) $(LIB_NAME) minilibx/libmlx.a -lm -lbsd -lX11 -lXext
		@echo "$(ORANGE)Fractol$(CYAN) is ready$(NO_COLOUR)"

makelib: $(LIB_NAME)

clean : 
		@cd $(MINILIBX) && make -s $@
		$(RM) $(OBJS) $(DEPS)

fclean : clean fcleanlib
		$(RM) $(NAME)
		$(RM) minilibx/libmlx.a

re : fclean all
		@cd $(MINILIBX) && make -s

cleanlib:
		@make --no-print-directory -s -C ./libft/ clean
		@echo	"$(PURPLE)\nLibft $(CYAN)-o removed\n$(NO_COLOUR)"

fcleanlib: cleanlib
		@make --no-print-directory -s -C ./libft/ fclean
		@echo	"$(PURPLE)\nLibft $(CYAN)-o && .a removed\n$(NO_COLOUR)"

.PHONY: all clean fclean re cleanlib fcleanlib
