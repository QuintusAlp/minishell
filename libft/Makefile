SRCS	= ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
					ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
					ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
					ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c  \
					ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
					ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
					ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_striteri.c \
					printf/ft_printf.c \
					printf/display/display_c.c printf/display/display_di.c printf/display/display_p.c printf/display/display_percent.c \
					printf/display/display_s.c printf/display/display_u.c printf/display/display_xX.c \
					ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
					ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
					ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
					gnl/get_next_line.c gnl/get_next_line_utils.c gnl/get_next_line_bonus.c gnl/get_next_line_utils_bonus.c

OBJDIR = objets
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

INCS	= includes
NAME	= libft.a
LIBC	= ar -rcs
CC		= cc
RM 		= rm -f
CFLAGS 	= -Wall -Wextra -Werror

GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m

all: title ${NAME}
	
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR) $(OBJDIR)/printf $(OBJDIR)/printf/display $(OBJDIR)/gnl
	@${CC}  ${CFLAGS} -I ${INCS} -c $< -o $@
	@printf "\r${YELLOW}Compiling: [${GREEN}%-50s${YELLOW}] %d/%d${NC}" $$(printf "#%.0s" $$(seq 1 $$(expr $$(find $(OBJDIR) -type f -name '*.o' | wc -l) \* \
	 50 / $(words $(SRCS))))) $$(find $(OBJDIR) -type f -name '*.o' | wc -l) $(words $(SRCS))
${NAME}: ${OBJS}
	@${LIBC} ${NAME} ${OBJS}
	@printf "\n"

title:
	@echo "${GREEN}Building $(NAME)...${NC}"


clean:
	@${RM} -r ${OBJDIR}

fclean: clean
	@${RM} ${NAME}

re: fclean all
