NAME = long
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
MK = make

SRCS = main.c get_next_line.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
		$(MK) -C ./Libft
		$(CC) $(CFLAGS) $(OBJS) ./Libft/libft.a -o $(NAME)

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
