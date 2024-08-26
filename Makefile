#OBJECTS表示编译过程中生成的所有目标文件，通常是.o文件
OBJECTS= ./build/compiler.o ./build/cprocess.o ./build/lexer.o ./build/lex_process.o ./build/helpers/buffer.o ./build/helpers/vector.o
#指定头文件目录为根目录，INCLUDES表示头文件路径
INCLUDES= -I./	#-I指定头文件目录，./表示当前目录

#all是make的一个目标，表示make没有指定目标时的默认目标。${OBJECTS}是这个all目标的依赖项
all: ${OBJECTS}	#运行make时，Makefile会检查每个目标文件的修改时间，若源文件比目标文件更新或目标文件不存在，它就会执行相应的编译命令来生成或更新目标文件。
#-g表示在生成的可执行文件中包含调试信息，这样就可以用gdb等调试器来调试程序；-o表示指定生成的可执行文件路径
	gcc main.c ${INCLUDES} ${OBJECTS} -g -o ./main

./build/compiler.o: ./compiler.c
#-c表示只编译不链接，生成.o文件
	gcc ./compiler.c ${INCLUDES} -o ./build/compiler.o -g -c

./build/cprocess.o: ./cprocess.c
	gcc ./cprocess.c ${INCLUDES} -o ./build/cprocess.o -g -c

./build/lexer.o: ./lexer.c
	gcc ./lexer.c ${INCLUDES} -o ./build/lexer.o -g -c

./build/lex_process.o: ./lex_process.c
	gcc ./lex_process.c ${INCLUDES} -o ./build/lex_process.o -g -c

./build/helpers/buffer.o: ./helpers/buffer.c
	gcc ./helpers/buffer.c ${INCLUDES} -o ./build/helpers/buffer.o -g -c

./build/helpers/vector.o: ./helpers/vector.c
	gcc ./helpers/vector.c ${INCLUDES} -o ./build/helpers/vector.o -g -c
clear:
	rm ./main
	rm -rf ${OBJECTS}