


# Colors
DEF_COLOR   = \033[0;39m
GRAY        = \033[0;90m
RED         = \033[0;91m
GREEN       = \033[0;92m
YELLOW      = \033[0;93m
BLUE        = \033[0;94m
MAGENTA     = \033[0;95m
CYAN        = \033[0;96m
WHITE       = \033[0;97m
ORANGE      = \033[38;5;214m

# Libft
LIBFT_DIR   = libft/
LIBFT_NAME  = libft.a
LIBFT       = $(LIBFT_DIR)$(LIBFT_NAME)

# Variables
NAMECL      = client
NAMESV      = server
NAMECB      = client_bonus
NAMESB      = server_bonus
CC          = cc
FLAGS       = -Wall -Werror -Wextra
RM          = rm -f
AR          = ar rcs
NORM        = ./includes\
                ./libft/include/\
                ./libft/src_lib
INCLUDE     = -I ./includes/\
                -I ./libft/include/

# Sources
SRC_DIR_MINI = src/

# Instructions
all: $(LIBFT) $(NAMECL) $(NAMESV)

$(LIBFT):
    @echo "$(MAGENTA)Getting libft ready$(DEF_COLOR)"
    @make -s -C $(LIBFT_DIR)

$(NAMECL): $(LIBFT)
    @$(RM) $(NAMECB)
    @$(CC) $(FLAGS) $^ src/client.c -o $@ $(INCLUDE)
    @echo "$(YELLOW)client ready!$(DEF_COLOR)"

$(NAMESV): $(LIBFT)
    @$(RM) $(NAMESB)
    @$(CC) $(FLAGS) $^ src/server.c -o $@ $(INCLUDE)
    @echo "$(ORANGE)server ready!$(DEF_COLOR)"

bonus: $(LIBFT) $(NAMECB) $(NAMESB)

$(NAMECB): $(LIBFT)
    @$(RM) $(NAMECL)
    @$(CC) $(FLAGS) $^ src/client_bonus.c -o $@ $(INCLUDE)
    @echo "$(MAGENTA)client bonus ready!$(DEF_COLOR)"

$(NAMESB): $(LIBFT)
    @$(RM) $(NAMESV)
    @$(CC) $(FLAGS) $^ src/server_bonus.c -o $@ $(INCLUDE)
    @echo "$(CYAN)server bonus ready!$(DEF_COLOR)"

clean:
    @echo "$(YELLOW)Removing libft utils$(DEF_COLOR)"
    @make clean -s -C $(LIBFT_DIR)

fclean: clean
    @echo "$(RED)Removing minitalk...$(DEF_COLOR)"
    @$(RM) $(NAMECL) $(NAMESV) $(NAMECB) $(NAMESB)
    @$(RM) $(LIBFT_DIR)$(LIBFT_NAME)

re: fclean all
    @echo "$(BLUE)Cleaned and rebuilt everything for minitalk.$(DEF_COLOR)"

norm:
    @which norminette > /dev/null && norminette $(SRC_DIR_MINI) $(NORM) $(LIBFT_DIR) | grep -v Norme -B1 || echo "$(RED)Norminette not found$(DEF_COLOR)"
    @echo "Norminet the cat says : $(RED)M$(ORANGE)e$(YELLOW)o$(GREEN)w$(CYAN) !$(BLUE)!$(MAGENTA)!$(DEF_COLOR)"

.PHONY: all clean fclean re norm bonus
