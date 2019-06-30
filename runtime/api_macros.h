
#define NUMARGS(...)  (sizeof((Object*[]){0, ##__VA_ARGS__})/sizeof(int)-1)
#define API_ARGS(...)  (Object*[]) { __VA_ARGS__}, NUMARGS(__VA_ARGS__)
