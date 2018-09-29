NAME = computor

GCC = g++

FLAGS = -Wall -Wextra -Werror -g

FILES = src/*.cpp

OUTPUT = -o

all: $(NAME)

$(NAME):
	@$(GCC) $(FLAGS) $(FILES) $(OUTPUT) $(NAME)
	@echo "Compile Success"

clean:
	@rm $(NAME)
	@echo "Cleaning files"

fclean:
	@rm -rf $(NAME)
	@echo "Force Clean"

re: fclean all

.PHONY: re
