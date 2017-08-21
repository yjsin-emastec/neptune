#ifndef _OUTPUT_DEBUG
#define _OUTPUT_DEBUG

#ifdef __cplusplus
extern "C"{
#endif

int set_debug_level(int level);
void err_log( int level, char* file, int line, const char* str, ...);

#ifdef __cplusplus
}
#endif

#endif// _OUTPUT_DEBUG
