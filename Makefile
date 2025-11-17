# Makefile para o Jogo War

CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = war_game
TEST_TARGET = test_war
OBJS = main.o war.o
TEST_OBJS = test.o war.o

# Regra principal
all: $(TARGET)

# Compilar o executável principal
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compilar o executável de teste
$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

# Compilar main.o
main.o: main.c war.h
	$(CC) $(CFLAGS) -c main.c

# Compilar test.o
test.o: test.c war.h
	$(CC) $(CFLAGS) -c test.c

# Compilar war.o
war.o: war.c war.h
	$(CC) $(CFLAGS) -c war.c

# Limpar arquivos compilados
clean:
	rm -f $(OBJS) $(TEST_OBJS) $(TARGET) $(TEST_TARGET)

# Executar o programa principal
run: $(TARGET)
	./$(TARGET)

# Executar o programa de teste
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Recompilar tudo
rebuild: clean all

.PHONY: all clean run test rebuild
