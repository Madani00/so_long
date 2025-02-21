NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
MK = make

SRCS = mandatory/main.c mandatory/get_next_line.c mandatory/utils0.c mandatory/free_error.c \
		mandatory/utils1.c mandatory/utils2.c mandatory/utils3.c mandatory/utils4.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
		$(MK) -C ./Libft
		$(CC) $(CFLAGS) $(OBJS) -lmlx -lX11 -lXext ./Libft/libft.a -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(MK) clean -C ./Libft
		${RM} ${OBJS} $(OBJS_BONUS)

fclean: clean
		$(MK) fclean -C ./Libft
		$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re
