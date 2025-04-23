CC		:= cc
CFLAGS	:= -Werror -Wextra -Wall -g3 -pthread -fsanitize=thread

# Name of the final executable
NAME	:= philo

# All needed files
SRC		:=	src/utils/atoi.c\
			src/utils/errors.c\
			src/utils/sleep_utils.c\
			src/utils/print.c\
			src/death.c\
			src/deathmonitor.c\
			src/utils.c\
			src/init.c\
			src/routine.c\
			src/philo.c\

OBJ		:= $(SRC:.c=.o)

# Colors for differents prints
GREEN	:= "\033[0m\033[1;32m"
CYAN	:= "\033[0m\033[1;36m"
YELLOW	:= "\033[0m\033[1;33m\033[3;33m"
RESET	:= "\033[0m"

# Compile all .c files
.c.o:
	@printf $(GREEN)"\r\033[KCompiling objects... "$(YELLOW)"<$<> ⏳ "$(RESET)
	@$(CC) $(CFLAGS) -c $< -o $@

# Compile all .o files
$(NAME): $(OBJ)
	@printf $(GREEN)"\r\033[KObjects compiled succesfully ✅\n"$(RESET)
	@printf $(CYAN)"\r\033[KCompiling '$(NAME)'... ⏳"$(RESET)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@printf $(GREEN)"\r\033[KSuccess compiling '$(NAME)' ✅\n"$(RESET)
	@printf "\n"
	@printf "██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗\n"
	@printf "██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝\n"
	@printf "██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗\n"
	@printf "██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║\n"
	@printf "██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║\n"
	@printf "╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝\n"

# Default command to launch
all: $(NAME)

# Compile and run philo
run: all
	@./$(NAME) 4 410 200 200

# Clean all .o files
clean:
	@printf $(CYAN)"\r\033[KErasing objects... "$(RESET)"⏳ "
	@rm -f $(OBJ)
	@printf $(GREEN)"\r\033[Kcleaned 🗑\n"$(RESET)

# Same as 'clean' but clean philo too
fclean: clean
	@printf $(CYAN)"\r\033[KErasing binary file... "$(RESET)"⏳ "
	@rm -f $(NAME)
	@printf $(GREEN)"\r\033[KBinary file cleaned 🗑\n"$(RESET)
	@printf $(GREEN)"\r\033[KForce cleaned 🗑\n"$(RESET)

# Clean all and recompile philo
re: fclean all

.PHONY: all clean fclean re run