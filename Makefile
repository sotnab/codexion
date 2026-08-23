# Escape sequences
ESC			:= $(shell printf '\033')
RESET		:= $(ESC)[0m
DIM			:= $(ESC)[2m

# Colors
GREEN		:=	$(ESC)[32m
YELLOW		:=	$(ESC)[33m
BLUE		:=	$(ESC)[34m
MAGENTA		:=	$(ESC)[35m
CYAN		:=	$(ESC)[36m
WHITE		:=	$(ESC)[37m

# Project settings
NAME		:=	codexion

# Suppress printing "Entering/Leaving directory"
MAKEFLAGS	+=	--no-print-directory

# Compiler config
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra -I. -pthread -g

# Source files
HEADERS 	:=	codexion.h

SRCS_PATH	:=	./src
SRCS		:=	main.c \
				$(SRCS_PATH)/codexion.c \
				$(SRCS_PATH)/threads.c \
				$(SRCS_PATH)/parsing/is_valid_uint.c \
				$(SRCS_PATH)/parsing/parse_arguments.c \
				$(SRCS_PATH)/init/init_codexion.c \
				$(SRCS_PATH)/init/init_coders.c \
				$(SRCS_PATH)/init/init_dongles.c \
				$(SRCS_PATH)/init/init_queue.c \
				$(SRCS_PATH)/init/init_mutexes.c \
				$(SRCS_PATH)/coder/coder_request.c \
				$(SRCS_PATH)/coder/coder_routine.c \
				$(SRCS_PATH)/coder/coder_message.c \
				$(SRCS_PATH)/coder/coder_dongle.c \
				$(SRCS_PATH)/monitor/monitor_routine.c \
				$(SRCS_PATH)/monitor/monitor_finish.c \
				$(SRCS_PATH)/queue/queue.c \
				$(SRCS_PATH)/queue/queue_heapify.c \
				$(SRCS_PATH)/utils/get_cpu_ms.c \
				$(SRCS_PATH)/utils/cleanup_codexion.c

# Object files
OBJS		:=	$(SRCS:.c=.o)

# Default rule
all: info $(NAME)

# Information for building
info:
	@echo "$(CYAN)  🚀 Building Project: $(WHITE)$(NAME)$(CYAN)$(RESET)"
	@echo "$(DIM)Compiler: $(RESET)$(CC)"
	@echo "$(DIM)Flags:    $(RESET)$(CFLAGS)"

# Create executable
$(NAME): $(OBJS)
	@echo "$(BLUE)[🔗 Linking]$(RESET) $(WHITE)Generating executable: $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✨ Build successful! [$(NAME) is ready]$(RESET)"

# Compile source files
%.o: %.c $(HEADERS)
	@echo "$(YELLOW)[🛠️ COMPILING]$(RESET) $(DIM)$<$(RESET) -> $@$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Remove object files
clean:
	@echo "$(MAGENTA)[🧹 CLEAN]$(RESET) Removing objects..."
	@rm -rf $(OBJS)
	@echo "$(GREEN)✨ Objects cleanup complete.$(RESET)"

# Remove object files and binaries
fclean:
	@echo "$(MAGENTA)[🧹 CLEAN]$(RESET) Removing binaries and objects..."
	@rm -rf $(OBJS) $(NAME)
	@echo "$(GREEN)✨ Full cleanup complete.$(RESET)"

# Rebuild whole project
re: fclean all

.PHONY: all info clean fclean re
