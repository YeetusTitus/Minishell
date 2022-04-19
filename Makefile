SRCS =	env/createenv.c \
		env/envutils.c \
		env/export.c \
		env/unset.c  \
		env/envutils2.c  \
		utils/utils1.c \
		path/cd.c path/pwd.c \
		signals/exit.c \
		signals/exit_utils.c \
		signals/signals.c \
		echo.c

MAIN = main.c

DIRECTORYS = srcs/

SRCSD =	$(addprefix ${DIRECTORYS}, $(SRCS))

EFLAGS = -Wall -Wextra -Werror -g

OBJS =	${SRCSD:.c=.o}

OFLAGS = -c

NAME   = minishell

IRL = -I${HOME}/.brew/opt/readline/include

LRL = -L${HOME}/.brew/opt/readline/lib -lreadline

DEBUG = -g

INCLUDE = -Iinclude

LIBFT = -Llibft -lft

%.o: %.c ${HEADER}
	gcc ${OFLAGS} -g ${EFLAGS} ${INCLUDE} -o $@ $<

${NAME}: ${OBJS} 
	(cd libft && make)
	gcc $(EFLAGS) -g -o $(NAME) $(MAIN) ${SRCSD} ${INCLUDE} ${LIBFT} ${IRL} ${LRL}
			
all:	${NAME}

clean:
		rm  -f ${OBJS}
		(cd libft && make clean)

fclean:	clean
		rm  -f ${NAME}
		(cd libft && make fclean)

re:		fclean all

.PHONY:	all clean fclean re
