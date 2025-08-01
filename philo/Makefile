NAME = philo

BUILD = ./objs

SRC = ./srcs

SRCS  = $(shell find $(SRC) -name '*.c')

OBJS  = $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SRCS))

INCS = -I./includes

HEADER = ./includes/philo.h

FLAGS = -Wall -Wextra -Werror -g -fsanitize=thread

CC = cc

all: $(BUILD) $(NAME)

$(BUILD)/%.o: $(SRC)/%.c $(HEADER) Makefile
	$(CC) $(FLAGS) $(INCS) -c $< -o $@

${NAME}: ${OBJS}
	$(CC) $(FLAGS) $(OBJS) $(INCS) -o ${NAME}
	@echo "Philo created 😇"

$(BUILD):
	@mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re