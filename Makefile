# Имя исполняемого файла
TARGET = main

# Компилятор
CC = gcc

# Флаги компилятора
CFLAGS = -lncurses

# Исходный файл
SRC = main.c

# Правило сборки
all: $(TARGET)

# Правило для компиляции исходного кода
$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

# Правило очистки
clean:
	rm -f $(TARGET)

