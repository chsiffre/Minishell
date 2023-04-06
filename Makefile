NAME = minishell

CFLAGS = -Wall -Wextra -Werror 

CC = cc

DIR_SRC = ./src/

DIR_OBJ = ./.obj/

DIR_INC = ./include/

LIST_SRC =	main.c \
			parsing.c \
			prompt.c \
			builtins.c \
			init_struct.c \
			b_env.c \
			b_unset.c \
			b_export.c \
			b_echo.c \
			init.c \
			env_utils.c \
			checks.c \
			ft_utils.c \
			exec.c \

LIST_INC = minishell.h

LIST_OBJ = ${LIST_SRC:.c=.o}

SRC = $(addprefix $(DIR_SRC), $(LIST_SRC))

OBJ = $(addprefix $(DIR_OBJ), $(LIST_OBJ))

INC = $(addprefix $(DIR_INC), $(LIST_INC))

DIR_LIBFT = libft

LIBFT = libft/libft.a

all : $(NAME)

$(DIR_OBJ) :
	mkdir -p $(DIR_OBJ)

$(LIBFT) : $(DIR_LIBFT)
	$(MAKE) -C $(DIR_LIBFT)

$(DIR_OBJ)%.o : $(DIR_SRC)%.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(DIR_INC) -I/opt/homebrew/opt/readline/include

$(NAME) : $(DIR_OBJ) $(OBJ) $(INC) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline -L/opt/homebrew/opt/readline/lib

bonus :
	$(MAKE) -C bonus

clean:
	rm -rf $(DIR_OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean $(NAME)

.PHONY : clean fclean re all bonus