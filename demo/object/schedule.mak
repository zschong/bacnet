#Makefile to build test case
CC = gcc 
{
TARGET} 
SRCS:.c =.o} 
TARGET}:$ {
OBJS} 
CC} -o $ @ $ {
OBJS} 
CC} -c $ {
CFLAGS} $ *.c - o $ @ 
CC} -MM $ {
CFLAGS} *.c >>.depend 
TARGET} $(OBJS) 