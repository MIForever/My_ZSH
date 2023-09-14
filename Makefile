CC = gcc
CFLAGS = -g  -Wall -Wextra -Werror
SOURCES = my_zsh.c src/*.c
TARGET = my_zsh

$(TARGET) : $(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:
	fclean

fclean:
	@rm -f $(OBJECTS) $(TARGET)