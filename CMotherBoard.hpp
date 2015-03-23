//------------------<< Including libraries >>-------------------------------------
#include <iostream>
#include "CStack.hpp"
#include "CVarStack.hpp"
#include "CCompiler.hpp"
#include "CCash.hpp"
#include "CMemBlock.hpp"
#include "CCPU.hpp"

//------------------<< MotherBoardError >>----------------------------------------
int MotherBoardError = 0;

//------------------<< Constants >>-----------------------------------------------
enum error_MB
{
    READ_FAILED         = 1,
    COMPILE_FAILED      = 2,
    EMPTY_INSTRUCTIONS  = 3,
    SET_PROGRAMM_FAILED = 4,
    BAD_CPU_CONDITION   = 5,
    EXECUTION_FAILED    = 6
};

//------------------<< MotherBoard class >>---------------------------------------
class CMotherBoard
{
public:
//------------------<< Setup >>---------------------------------------------------
    CMotherBoard ();
    ~CMotherBoard();
//------------------<< run method >>----------------------------------------------
    int  built_and_run(const char * input);
//------------------<< Debug && Info >>-------------------------------------------
    void dump ();
    void man  ();
private:
//------------------<< class objects >>-------------------------------------------
    CCompiler Compiler_;
    CCPU      CPU_;
    CCash     Cash_;
    CMemBlock Memory_;
};

CMotherBoard::CMotherBoard ()
{
    /*---//---*/
}

CMotherBoard::~CMotherBoard()
{
    /*---//---*/
}

int CMotherBoard::built_and_run(const char * input)
{
    if (!Compiler_.read(input)) {
        MotherBoardError = READ_FAILED;
        return 0;
    }
    printf("Red succsessfully\n");

    if (!Compiler_.compile()) {
        MotherBoardError = COMPILE_FAILED;
        return 0;
    }
    printf("Compiled succsessfully\n");

    Compiler_.dump();

    if (!Cash_.set_Cash_Programm(Compiler_.MashineCode())) {
        MotherBoardError = SET_PROGRAMM_FAILED;
        return 0;
    }
    printf("Programm set succsessfully\n");

    CPU_.set_Cash_ptr   (& Cash_);
    CPU_.set_Memory_ptr (& Memory_);

    if (!CPU_.check()) {
        MotherBoardError = BAD_CPU_CONDITION;
        return 0;
    }
    printf("CPU ready\n");

    if (!CPU_.execute()) {
        MotherBoardError = EXECUTION_FAILED;
        return 0;
    }
    printf("Executed succsessfully!\n");

    return 1;
}
//--------------------------------------------------------------------------------