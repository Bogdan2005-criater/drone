#!/bin/bash

# Ваш файл с исходным кодом
source_file="main.c"

# Имя для создаваемого исполняемого файла
executable="main"


# Проверка успешности компиляции
if [ $? -eq 0 ]; then
    # Запуск исполняемого файла
    "./$executable"
else
    echo "Ошибка компиляции."
fi
