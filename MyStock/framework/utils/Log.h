#pragma  once



void PrintfDebug(const char *format, ... );
void PrintfDebug2(const char *format, ... );
void PrintfDebug3(const char *format, ... );
void PrintfDebug4(const char *format, ... );
void PrintfWarning(const char *format, ... );
void PrintfDebugError(const char *format, ... );
void PrintfInfo(const char *format,int level, va_list argp );
void PrintfError(const char *format, ... );
void LogFileOpen(void);
void LogFileClose(void);
void LogInit(void);
void LogUnInit(void);