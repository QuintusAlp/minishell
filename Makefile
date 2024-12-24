
SRCS = 	./srcs/builtins/builtins.c ./srcs/builtins/cd.c ./srcs/builtins/cd_utils.c ./srcs/builtins/echo.c \
		./srcs/builtins/env.c ./srcs/builtins/exit.c ./srcs/builtins/export.c ./srcs/builtins/export_utils.c ./srcs/builtins/export_plusegal.c \
		./srcs/builtins/pwd.c ./srcs/builtins/split_str.c ./srcs/builtins/unset.c ./srcs/builtins/utils.c \
		./srcs/exec/exec_cmd.c ./srcs/exec/exec_cmd_utils.c ./srcs/exec/exec_pipe.c ./srcs/exec/exec_redir.c ./srcs/exec/execute_ast.c  ./srcs/exec/ft_checkredir.c\
		./srcs/lexer/lexer_utils.c ./srcs/lexer/lexer.c ./srcs/lexer/trim_tokens.c ./srcs/lexer/trim_tokens_utils.c  ./srcs/lexer/trim_tokens_utils2.c ./srcs/lexer/checklexing.c\
		./srcs/parser/ast.c ./srcs/parser/parse_cmd.c ./srcs/parser/parse_pipe.c ./srcs/parser/parse_redir.c ./srcs/parser/parse_heredoc.c\
		./srcs/signals/signals.c \
		./srcs/free_ast.c ./srcs/ft_error.c ./srcs/main.c ./srcs/utils.c ./srcs/utils2.c \
		


OBJDIR = objects
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
OBJS_BONNUS = $(SRCS_BONNUS:%.c=$(OBJDIR)/%.o)
LIB = make -C ./libft
INCS = includes
CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

ARCH := $(shell uname -m)

ifeq ($(ARCH),arm64) # command to check the ARCH variable : uname -m
READINC = /opt/homebrew/Cellar/readline/8.2.10/include/
READLIB = /opt/homebrew/Cellar/readline/8.2.10/lib/
else
READINC = /Users/qalpesse/.brew/opt/readline/include
READLIB = /Users/qalpesse/.brew/opt/readline/lib
endif
READLINE = -L$(READLIB) -I$(READINC) -lreadline


FLUO_GREEN = \033[1;92m
YELLOW = \033[0;33m
BLUE = \033[1;34m
NC = \033[0m

all: titre ${NAME}

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR) $(OBJDIR)/srcs $(OBJDIR)/srcs/lexer $(OBJDIR)/srcs/parser $(OBJDIR)/srcs/exec $(OBJDIR)/srcs/builtins $(OBJDIR)/srcs/signals
	@${CC} ${CFLAGS} -I ${INCS} -c $< -o $@

${NAME}: ${OBJS}
	@${LIB}
	@echo "${FLUO_GREEN}compiling minishell...${NC}"
	@${CC} ${CFLAGS} ${OBJS} -L./libft -lft  $(READLINE) -o ${NAME}
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
