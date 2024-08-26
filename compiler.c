#include "compiler.h"
#include <stdarg.h>
#include <stdlib.h>

struct lex_process_functions compiler_lex_functions = {
	.next_char = compile_process_next_char,
	.peek_char = compile_process_peek_char,
	.push_char = compile_process_push_char
};

void compiler_error(struct compile_process* compiler, const char* msg, ...)
{
	va_list args;
	va_start(args, msg);	//初始化va_list类型的变量args，msg为可最后一个固定参数，用于帮助args指向第一个可变参数
	vfprintf(stderr, msg, args);	//将可变参数写入msg中，并输出到stderr
	va_end(args);	//结束可变参数的处理，释放资源
	fprintf(stderr, "在文件 %s 的 %i 行 %i 列\n", compiler->pos.filename, compiler->pos.line, compiler->pos.col);
	exit(-1);
}

void compiler_warning(struct compile_process* compiler, const char* msg, ...)
{
	va_list args;
	va_start(args, msg);
	vfprintf(stderr, msg, args);
	va_end(args);
	fprintf(stderr, "在文件 %s 的 %i 行 %i 列\n", compiler->pos.filename, compiler->pos.line, compiler->pos.col);
}

int compile_file(const char* filename, const char* out_filename, int flags)
{
	struct compile_process* process = compile_process_create(filename, out_filename, flags);
	if(!process)	//内存分配失败
		return COMPILER_FAILED_WITH_ERRORS;
	
	//词法分析，变为tokens
	struct lex_process* lex_process = lex_process_create(process, &compiler_lex_functions, NULL);
	if(!lex_process)
	{
		return COMPILER_FAILED_WITH_ERRORS;
	}

	if(lex(lex_process) != LEXICAL_ANALYSIS_ALL_OK)
	{
		return COMPILER_FAILED_WITH_ERRORS;
	}
	//解析产生抽象语法
	//树代码生成
	return COMPILER_FILE_COMPILED_OK;
}