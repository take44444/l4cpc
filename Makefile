CC=g++
CFLAGS=-Wall -Wpedantic -Wextra -Werror -std=c++17
SRCS=l4cpc.cpp tokenizer/tokenizer.cpp parser/parser.cpp parser/utils.cpp generator/generator.cpp generator/utils.cpp
HEADERS=l4cpc.hpp tokenizer/tokenizer.hpp parser/parser.hpp generator/generator.hpp

.FORCE :

l4cpc : $(SRCS) $(HEADERS) Makefile
	$(CC) $(CFLAGS) -o $@ $(SRCS)