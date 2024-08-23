#include <stdio.h>

struct compile_process* compile_process_create(const char* filename, const char* filename_out, int flags)
{
    FILE* file = fopen(filename, 'r');
    if(!file)
    {
        return NULL;
    }

    FILE* out_file = NULL;
    if(filename_out)
    {
        out_file = fopen(filename_out, 'w');
        if(!out_file)
        {
            return NULL;
        }
    }
}