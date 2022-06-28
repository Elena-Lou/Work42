CC = gcc

OBJS_DIR = objs

CFLAGS = -Wall -Werror -Wextra -g3

NAME = minishell

LIB = libft

SRCS_DIR = ./srcs

SRCS = main.c \
		$(addprefix env/, \
			lst_env.c \
			var_env_to_value.c \
			var_env_to_value_utils.c \
			var_env_to_value_utils_bis.c \
			var_env_to_value_utils_ter.c) \
		$(addprefix pipes/, \
			check_infile_outfile.c \
			check_infile_outfile_utils.c \
			lst_pipe_utils_bis.c \
			exec_pipe.c \
			exec_pipe_utils.c \
			exec_pipe_utils_bis.c \
			exec_pipe_utils_ter.c \
			here_doc.c	\
			lst_pipe.c \
			lst_pipe_utils_ter.c \
			lst_pipe_utils.c) \
		$(addprefix checks/, \
			check_error.c \
			check_syntaxe.c \
			check_syntaxe_utils.c) \
		$(addprefix exec/, \
			exec.c \
			exec_utils.c \
			exec_utils_bis.c \
			lst_token.c \
			exec_utils_ter.c \
			exec_utils_qua.c \
			get_type.c) \
		$(addprefix utils/, \
			lst_utils_bis.c \
			lst_utils.c \
			init_struct.c \
			prompt.c) \
		$(addprefix cmds/, \
			lst_cmd.c \
			lst_cmd_utils.c \
			lst_simple_cmd.c \
			lst_simple_cmd_utils.c) \
		$(addprefix builtins/, \
			builtin_pwd.c \
			builtin_env.c \
			builtin_echo.c \
			builtin_exit.c \
			builtin_exit_utils.c \
			builtin_cd.c	\
			builtin_cd_utils.c \
			builtin_unset.c \
			builtin_unset_utils.c \
			builtin_export.c \
			builtin_export_utils.c) \

OBJS 		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

DEPS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.d))

DEPSFLAGS	= -MMD -MF $(@:.o=.d)

INCS		= -I includes -I libft/include

RM			= rm -rf

LIB_NAME	= libft/libft.a

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

$(LIB_NAME):
		@make --no-print-directory -s -C ./libft/ all
		@echo	"$(PURPLE)\nLibft $(CYAN)compiled\n$(NO_COLOUR)"

$(NAME): $(OBJS) $(LIB_NAME)
		$(CC) $(CFLAGS) $(OBJS) -o $@ -lreadline $(INCS) $(LIB_NAME)
		@echo "$(ORANGE)minishell$(CYAN) is ready$(NO_COLOUR)"

makelib: $(LIB_NAME)

clean : 
		@cd $(LIB) && make -s $@
		$(RM) $(OBJS_DIR)

fclean : clean
		$(RM) $(NAME)
		$(RM) libft/libft.a

re : fclean all

-include $(DEPS)

.PHONY: all clean fclean re 