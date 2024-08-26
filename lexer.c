/*负责实际的语法分析*/
#include "compiler.h"
#include "helpers/vector.h"
#include "helpers/buffer.h"

#define LEX_GETC_IF(buffer, c, exp)		\
	for(c = peekc(); exp; c = peekc())	\
	{									\
		buffer_write(buffer, c);		\
		nextc();						\
	}

static struct lex_process* lex_process;

static char nextc()
{
	char c = lex_process->functions->next_char(lex_process);
	lex_process->pos.col++;
	if(c == '\n')
	{
		lex_process->pos.line++;
		lex_process->pos.col = 1;
	}
	return c;
}

static char peekc()
{
	return lex_process->functions->peek_char(lex_process);
}

static char pushc(char c)
{
	lex_process->functions->push_char(lex_process, c);
}

const char* read_number_str()
{
	const char* num = NULL;
	struct buffer* buffer = buffer_create();
	char c = peekc();
}
struct token* token_make_number_for_value(unsigned long number)
{

}
struct token* token_make_number()
{
	return token_make_number_for_value(read_number());
}
struct token* read_next_token()
{
	struct token* token = NULL;
	char c = peekc();
	switch (c)
	{
	NUMERIC_CASE:
		token = token_make_number();
		break;
	case EOF:
		break;	//到了文件末尾，分析结束
	default:
		compiler_error(lex_process->compiler, "[未知错误]可能是不支持的编码格式\n");
	}
	return token;
}
int lex(struct lex_process* process)
{
	process->current_expression_count = 0;
	process->parentheses_buffer = NULL;
	lex_process = process;
	process->pos.filename = process->compiler->cfile.abs_path;

	struct token* token = read_next_token();
	while(token)
	{
		vector_push(process->token_vec, token);	//将token压入token_vec
		token = read_next_token();
	}
	return LEXICAL_ANALYSIS_ALL_OK;
}