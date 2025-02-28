NAME = so_long
BONUS_NAME = so_long_b
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
MK = make

SRCS = mandatory/main.c mandatory/get_next_line.c mandatory/utils0.c mandatory/free_error.c \
		mandatory/utils1.c mandatory/utils2.c mandatory/utils3.c mandatory/utils4.c \
		mandatory/utils5.c mandatory/utils6.c
SRCS_B = bonus/main_bonus.c bonus/get_next_line_bonus.c bonus/utils0_bonus.c bonus/free_error_bonus.c \
		bonus/utils1_bonus.c bonus/utils2_bonus.c bonus/utils3_bonus.c bonus/utils4_bonus.c

OBJS = $(SRCS:.c=.o)

OBJS_B = $(SRCS_B:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
		$(MK) -C ./Libft
		$(CC) $(CFLAGS) $(OBJS) -lmlx -lX11 -lXext ./Libft/libft.a -o $(NAME)

bonus : $(BONUS_NAME)

$(BONUS_NAME): $(OBJS_B)
		$(MK) -C ./Libft
		$(CC) $(CFLAGS) $(OBJS_B) -lmlx -lX11 -lXext ./Libft/libft.a -o $(BONUS_NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		$(MK) clean -C ./Libft
		${RM} ${OBJS} $(OBJS_B)

fclean: clean
		$(MK) fclean -C ./Libft
		$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus

