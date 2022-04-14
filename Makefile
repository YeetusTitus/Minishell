SRCS =  env/createenv.c \
        env/envutils.c \
        env/export.c \
        env/unset.c  \
        env/envutils2.c  \
        utils/utils1.c \
        path/cd.c \
		path/pwd.c \
        signals/exit.c \
        signals/exit_utils.c \
        signals/signals.c \
        echo.c \
		execution/redirection.c \
		execution/execution_1.c \
		execution/execution_2.c \
		execution/get_command.c \
		execution/get_array_exec.c \
		parsing/get_quote.c \
		parsing/get_variable.c \
		parsing/get_variable_in_quote.c \
		parsing/red_n_simple_cmd.c \
		parsing/utils.c \
		lexer/lexer.c \
		lexer/lst_utils.c \
		lexer/simple_quote.c \
		lexer/double_quote.c \
		lexer/utils.c \

MAIN = main.c

DIRECTORYS = srcs/

SRCSD =	$(addprefix ${DIRECTORYS}, $(SRCS))

EFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address 

OBJS =	${SRCSD:.c=.o}

OFLAGS = -c

NAME   = minishell

IRL = -I${HOME}/.brew/opt/readline/include

LRL = -L${HOME}/.brew/opt/readline/lib -lreadline

LIBFT = -Lft_libft -lft

%.o: %.c ${HEADER}
	gcc ${OFLAGS} ${EFLAGS} -o $@ $<

${NAME}: ${OBJS}
	(cd ft_libft && make)
	gcc $(EFLAGS) -o $(NAME) $(MAIN) ${SRCSD} ${LIBFT} ${IRL} ${LRL}
			
all:	${NAME}

clean:
		rm  -f ${OBJS}
		(cd ft_libft && make clean)

fclean:	clean
		rm  -f ${NAME}
		(cd ft_libft && make fclean)

re:		fclean all

.PHONY:	all clean fclean re
