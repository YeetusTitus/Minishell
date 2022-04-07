SRCS =	env/createenv.c \
		env/envutils.c \
		env/export.c \
		lexer/lexer.c \
		lexer/get_quote.c \
		lexer/get_command.c \
		lexer/get_variable.c \
		lexer/lst_utils.c \
		lexer/red_n_simple_cmd.c \
		lexer/reddirection.c \

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
