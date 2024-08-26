#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"

//准备好源文件和编译输出文件，并在堆上创建并初始化compile_process结构体
struct compile_process* compile_process_create(const char* filename, const char* filename_out, int flags)
{
	FILE* file = fopen(filename, "r");
	if(!file)
	{
		return NULL;
	}

	FILE* out_file = NULL;
	if(filename_out)
	{
		out_file = fopen(filename_out, "w");
		if(!out_file)	//若出错，可能因为权限或空间不足
		{
			return NULL;
		}
	}
	
	struct compile_process* process = calloc(1, sizeof(struct compile_process));	//分配内存空间并全部初始化为0
	process->flags = flags;
	process->cfile.fp = file;
	process->ofile = out_file;
	return process;
}
//将源文件中下个字符提取出来并返回
char compile_process_next_char(struct lex_process* lex_process)
{
	struct compile_process* compiler = lex_process->compiler;
	compiler->pos.col++;
	char c = getc(compiler->cfile.fp);
	if(c == '\n')
	{
		compiler->pos.line++;	//换行
		compiler->pos.col = 1;
	}
	return c;
}

char compile_process_peek_char(struct lex_process* lex_process)
{
	// struct compile_process* compiler = lex_process->compiler;
	char c = getc(lex_process->compiler->cfile.fp);
	ungetc(c, lex_process->compiler->cfile.fp);	//将getc函数从文件流中弹出的字符再放回去
	return c;
}

void compile_process_push_char(struct lex_process* lex_process, char c)
{
	//struct compile_process* compiler = lex_process->compiler;
	ungetc(c, lex_process->compiler->cfile.fp);	//将getc函数从文件流中弹出的字符再放回去
}