NAME = pipex
SRCS = srcs/pipex.c srcs/pipex_utils.c
SRCS_BONUS = srcs/pipex_bonus.c srcs/pipex_utils_bonus.c srcs/command_execution_bonus.c

FLAGS = -Wall -Werror -Wextra -g

CC = cc

RM = rm -f

LIBFT_PATH = libs/

LIBFT = -L $(LIBFT_PATH) -lft

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

.c.o:
		${CC} ${FLAGS} -c $< -o srcs/$(@F)

$(NAME): $(OBJS)
	make -C $(LIBFT_PATH)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)


all: $(NAME)

clean:
	make -C ${LIBFT_PATH} clean
	$(RM) $(OBJS)
	$(RM) $(OBJS_BONUS)

fclean: clean
	make -C ${LIBFT_PATH} fclean
	${RM} ${NAME}

re: fclean all

bonus: $(OBJS_BONUS)
	make -C $(LIBFT_PATH)
	$(CC) $(FLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME)

.PHONY:all clean fclean re bonus
