enum error_t
{
    #define ERROR(NAME, NUMBER, DESCRIPTION) NAME = NUMBER,
    #include "stk_err.hpp"
    #undef ERROR
    
    UNKNOWN = 8
};

int stack_error = NO_ERROR;

void ERR_PRINT(int number)
{
    #define ERROR(NAME, NUMBER, DESCRIPTION)            \
    if (number == NUMBER)                               \
    {                                                   \
        stack_error = NUMBER;                           \
        printf("ERROR DESCRIPTION : %s\n", DESCRIPTION);\
        return;                                         \
    }                                                   \

    #include "stk_err.hpp"
    #undef ERROR
}
