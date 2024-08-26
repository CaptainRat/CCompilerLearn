#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>
#include <stdbool.h>

struct pos
{
	int line;
	int col;
	const char* filename;
};  //token在文件中的位置

#define NUMERIC_CASE\
	case '0': 		\
	case '1': 		\
	case '2': 		\
	case '3': 		\
	case '4': 		\
	case '5': 		\
	case '6': 		\
	case '7': 		\
	case '8': 		\
	case '9'

enum
{
	LEXICAL_ANALYSIS_ALL_OK,
	LEXICAL_ANALYSIS_INPUT_ERROR
};

enum
{
	TOKEN_TYPE_IDENTIFIER,
	TOKEN_TYPE_KEYWORD,
	TOKEN_TYPE_OPERATOR,
	TOKEN_TYPE_SYMBOL,
	TOKEN_TYPE_NUMBER,
	TOKEN_TYPE_STRING,
	TOKEN_TYPE_COMMENT,
	TOKEN_TYPE_NEWLINE
};
struct token
{
	int type;
	int flags;

	union
	{
		char cval;
		const char* sval;
		unsigned int inum;
		unsigned long lnum;
		unsigned long long llnum;
		void* any;
	};

	bool whitespace;    //是否是空格
	const char* between_brackets;    //小括号()？之间的内容。bracket特指方括号
};

struct lex_process; //声明lex_process结构体
//(*LEX_PROCESS_NEXT_CHAR)用于定义为函数指针，返回值类型为char。括号是必须的，用于区分函数指针和返回指针的函数声明
//(struct lex_process* process)表示函数指针的形参类型为struct lex_process*
typedef char (*LEX_PROCESS_NEXT_CHAR) (struct lex_process* process);
typedef char (*LEX_PROCESS_PEEK_CHAR) (struct lex_process* process);
typedef void (*LEX_PROCESS_PUSH_CHAR) (struct lex_process* process, char c);

struct lex_process_functions
{
	LEX_PROCESS_NEXT_CHAR next_char;
	LEX_PROCESS_PEEK_CHAR peek_char;
	LEX_PROCESS_PUSH_CHAR push_char;
};

struct lex_process
{
	struct pos pos;
	struct vector* token_vec;
	struct compile_process* compiler;

	int current_expression_count;   //当前表达式数量。如((a+b)+c)需要记录刚开始的两个左括号数量
	struct buffer* parentheses_buffer;    //括号缓冲区，特指小圆括号
	struct lex_process_functions* functions;

	void* private;  //语法分析器lexer不理解的数据
};

enum
{
	COMPILER_FILE_COMPILED_OK,
	COMPILER_FAILED_WITH_ERRORS
};

//指示编译出入文件和编译标志，并控制编译过程，指示当前解析的字符在源文件的位置
struct compile_process
{
	int flags;  //如何编译此文件的标志

	struct pos pos;	//当前编译字符在源文件的位置
	struct compile_process_input_file
	{
		FILE* fp;
		const char* abs_path;
	} cfile;

	FILE* ofile;    //输出文件
};

int compile_file(const char* filename, const char* out_filename, int flags);
struct compile_process* compile_process_create(const char* filename, const char* filename_out, int flags);

char compile_process_next_char(struct lex_process* lex_process);
char compile_process_peek_char(struct lex_process* lex_process);
void compile_process_push_char(struct lex_process* lex_process, char c);

void compiler_error(struct compile_process* compiler, const char* msg, ...);
void compiler_warning(struct compile_process* compiler, const char* msg, ...);

struct lex_process* lex_process_create(struct compile_process* compiler, struct lex_process_functions* functions, void* private);
void lex_process_free(struct lex_process* process);
void* lex_process_private(struct lex_process* process);
struct vector* lex_process_tokens(struct lex_process* process);
int lex(struct lex_process* process);
void compiler_error(struct compile_process* compiler, const char* msg, ...);
#endif