#ifndef COMPILER_H
#define COMPILER_H

#include <stdio.h>

enum
{
    COMPILER_FILE_COMPILED_OK,
    COMPILER_FAILED_WITH_ERRORS
};
struct compile_process
{
    int flags;  //如何编译此文件的标志

    struct compile_process_input_file
    {
        FILE* fp;
        cosnt char* abs_path;
    } cfile;

    FILE* ofile;    //输出文件
};

int compile_file(const char* filename, const char* out_filename, int flags);
struct compile_process* compile_process_create(const char* filename, const char* filename_out, int flags);

#endif