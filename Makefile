SRCS = env/createenv.c env/envutils.c env/export.c

MAIN = main.c

DIRECTORYS = srcs/

SRCSD =	$(addprefix ${DIRECTORYS}, $(SRCS))

EFLAGS = -Wall -Wextra -Werror -g

OBJS =	${SRCSD:.c=.o}

OFLAGS = -c

NAME   = minishell

IRL = -I${HOME}/.brew/opt/readline/include

LRL = -L${HOME}/.brew/opt/readline/lib -lreadline

LIBFT = -Llibft -lft

%.o: %.c ${HEADER}
	gcc ${OFLAGS} ${EFLAGS} -o $@ $<

${NAME}: ${OBJS}
	(cd libft && make)
	gcc $(EFLAGS) -o $(NAME) $(MAIN) ${SRCSD} ${LIBFT} ${IRL} ${LRL}
			
all:	${NAME}

clean:
		rm  -f ${OBJS}
		(cd libft && make clean)

fclean:	clean
		rm  -f ${NAME}
		(cd libft && make fclean)

re:		fclean all

.PHONY:	all clean fclean re
