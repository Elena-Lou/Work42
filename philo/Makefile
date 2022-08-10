CC = gcc

OBJS_DIR = objs

# CFLAGS = -Wall -Werror -Wextra

# CFLAGS = -Wall -Werror -Wextra -g3

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=thread

NAME = philo

SRCS_DIR = ./srcs

SRCS = main.c \
		struct_init.c	\
		utils.c \
		arg_checks.c \
		time_management.c \
		routine.c	\
		prints.c	\
		are_you_dead.c	\
		hades.c	\
		banquet.c

OBJS 		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

DEPS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.d))

DEPSFLAGS	= -MMD -MF $(@:.o=.d)

INCS		= -I include 

RM			= rm -rf

PURPLE		= \033[1;35m

CYAN		= \033[1;36m

GREEN		= \033[1;32m

ORANGE		= \033[1;33m

NO_COLOUR	= \033[m

all:	$(NAME)
	@make $(NAME) -q && echo "$(GREEN)All good here !$(NO_COLOUR)"

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -o $@ -c $< $(DEPSFLAGS) $(INCS)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $@ $(INCS) -lpthread
		@echo "$(ORANGE)philo$(CYAN) is ready$(NO_COLOUR)"

clean : $(OBJS_DIR)
		$(RM) $(OBJS_DIR)

fclean : clean
		$(RM) $(NAME)

re : fclean all

-include $(DEPS)

.PHONY: all clean fclean re 
