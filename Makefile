SRCS = 	./srcs/main.c ./srcs/ft_error.c \
		./srcs/parse_pipe.c ./srcs/parse_cmd.c ./srcs/parse_redir.c \
		./srcs/parsing.c ./srcs/lexer.c ./srcs/ast.c 


OBJDIR = objets
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
OBJS_BONNUS = $(SRCS_BONNUS:%.c=$(OBJDIR)/%.o)
LIB = make -C ./libft
INCS = includes
CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
NAME = minishell

FLUO_GREEN = \033[1;92m
YELLOW = \033[0;33m
BLUE = \033[1;34m
NC = \033[0m

all: titre ${NAME}

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR) $(OBJDIR)/srcs
	@${CC} ${CFLAGS} -I ${INCS} -c $< -o $@

${NAME}: ${OBJS}
	@${LIB}
	@echo "${FLUO_GREEN}compiling minishell...${NC}"
	@${CC} ${CFLAGS} ${OBJS} -L./libft -lft -lreadline -o ${NAME}
	@printf "\r${YELLOW}Compiling: [${FLUO_GREEN}%-50s${FLUO_GREEN}${YELLOW}] %d/%d${NC}" $$(printf "#%.0s" $$(seq 1 $$(expr $$(find $(OBJDIR) -type f -name '*.o' | wc -l) \* \
	 50 / $(words $(SRCS))))) $$(find $(OBJDIR) -type f -name '*.o' | wc -l) $(words $(SRCS))
	@echo "\n${FLUO_GREEN} ./minishell  ready to use ${NC}"


titre:
	@echo "\n"
	@echo "${FLUO_GREEN} ███▄ ▄███▓ ███ ▒███▄    █  ███  ████████ ██░ ██▓█████  ██▓     ██▓     "
	@echo "▓██▒▀█▀ ██▒▓██▒ ██ ▀█   █ ▓██▒▒██    ▒ ▓██░ ██▓█   ▀  ▓██▒    ▓██▒     "
	@echo "▓██    ▓██░▒██▒▓██  ▀█ ██▒▒██▒░ ▓██▄   ▒██▀▀██▒███    ▒██░    ▒██░     "
	@echo "▒██    ▒██ ░██░▓██▒  ▐▌██▒░██░  ▒   ██▒░▓█ ░██▒▓█  ▄  ▒██░    ▒██░     "
	@echo "▒██▒   ░██▒░██░▒██░   ▓██░░██░▒██████▒▒░▓█▒░██░▒████▒ ░██████▒░██████▒ "
	@echo "░ ▒░   ░  ░░▓  ░ ▒░   ▒ ▒ ░▓  ░ ▒▓▒ ▒ ░ ▒ ░░▒░░░ ▒░ ░ ░ ▒░▓  ░░ ▒░▓  ░"
	@echo "░  ░      ░ ▒ ░░ ░░   ░ ▒░ ▒ ░░ ░▒  ░ ░ ▒ ░▒░ ░░ ░  ░ ░ ░ ▒  ░░ ░ ▒  ░"
	@echo "░      ░    ▒ ░   ░   ░ ░  ▒ ░░  ░  ░   ░  ░░ ░  ░      ░ ░     ░ ░   "
	@echo "       ░    ░           ░  ░        ░   ░  ░  ░  ░  ░    ░  ░    ░  ░ "
	@echo "\n \n"

clean:
	@${RM} -r ${OBJDIR}
	@make clean -C ./libft

fclean: clean
	@${RM} ${NAME}
	@make fclean -C ./libft 

re: fclean all

.PHONY: all clean fclean re
