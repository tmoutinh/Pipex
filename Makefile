NAME = pipex

NAME_BONUS = pipex_bonus

SRCS = srcs/pipex.c srcs/pipex_utils.c
SRCS_BONUS = srcs/pipex_bonus.c srcs/pipex_utils_bonus.c srcs/command_execution_bonus.c

FLAGS = -Wall -Werror -Wextra -g

CC = cc

RM = rm -f

LIBFT_PATH = libs/

LIBFT = -L $(LIBFT_PATH) -lft

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(SRCS_BONUS:.c=.o)

%.o:%.c
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
	$(RM) $(NAME_BONUS)

re: fclean all

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	make -C $(LIBFT_PATH)
	$(CC) $(FLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS)

.PHONY:all clean fclean re bonus
