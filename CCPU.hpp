//------------------------<< Including libraries >>--------------------------------
#include <math.h>

using namespace std;

//------------------------<< Defining macros >>------------------------------------
//#define ERROR_DETECT(CONDITION, IN_FUNC);   \
if (!CONDITION)                             \
{                                           \
    printf("--cpu--\n");                    \
    printf("ERROR IN FUNCTION : ");         \
    printf(IN_FUNC);                        \
    printf("\n");                           \
    cpu_dump();                             \
    assert(0);                              \
}                                           \

//------------------------<< Constants >>------------------------------------------
const int STOP       = 0;
const int SKIP_CMD   = -1;
const int INT_TYPE   = 1;
const int FLOAT_TYPE = 2;



//------------------------<< CPU class >>------------------------------------------
class CCPU
{
public:
//------------------------<< Setup >>----------------------------------------------
    CCPU  ();
    ~CCPU ();
//------------------------<< Main execution method >>------------------------------
    int execute ();
//------------------------<< Debug && Info >>--------------------------------------
    int cpu_dump ();
//------------------------<< Outer set methods >>----------------------------------
    int set_Programm   (vector<int> * MashineCode);
    int set_Memory_ptr (CMemBlock * mem_ptr);
private:
//------------------------<< Mashine commands >>-----------------------------------
    int exe_stop  ();


    int reg_scn   (int arg_1, int arg_2);
    int reg_prt   (int arg_1, int arg_2);

    int reg_set   (int arg_1, int arg_2);
    int reg_mov   (int arg_1, int arg_2);
    int reg_cmp   (int arg_1, int arg_2);

    int reg_add   (int arg_1, int arg_2);
    int reg_mul   (int arg_1, int arg_2);
    int reg_div   (int arg_1, int arg_2);
    int reg_and   (int arg_1, int arg_2);
    int reg_or    (int arg_1, int arg_2);
    int reg_xor   (int arg_1, int arg_2);

    int reg_set_f (int arg_1, int arg_2);
    int reg_cmp_f (int arg_1, int arg_2);

    int reg_add_f (int arg_1, int arg_2);
    int reg_mul_f (int arg_1, int arg_2);
    int reg_div_f (int arg_1, int arg_2);

    int prg_jmp   (int arg_1);
    int prg_jee   (int arg_1);
    int prg_jne   (int arg_1);
    int prg_jle   (int arg_1);
    int prg_jme   (int arg_1);

    int func_call (int arg_1);
    int func_ret  ();


    int var_dec   (int arg_1, int arg_2);
    int var_set_v (int arg_1, int arg_2);
    int var_pop_v (int arg_1, int arg_2);
    int var_psh_v (int arg_1, int arg_2);

    int var_set_vf(int arg_1, int arg_2);

    int arg_psh   (int arg_1);
    int arg_pop   (int arg_1);
//------------------------<< Local acsess methods >>-------------------------------
    int * get_reg_ptr (int reg);

//------------------------<< int registers >>--------------------------------------
    int AX_;
    int BX_;
    int CX_;
    int DX_;
//------------------------<< float registers >>------------------------------------
    int EX_;
    int FX_;
//------------------------<< compare result register >>----------------------------
    int CMPX_;
//------------------------<< IP register >>----------------------------------------
    int IP_;
//------------------------<< base register >>--------------------------------------
    int BPX_;
//------------------------<< mashine code && call stack >>-------------------------
    vector<int> Programm_;
    CStack<int> CallStk_;
//------------------------<< memory block >>---------------------------------------
    CMemBlock * Memory_;
};

//------------------------<< Setup >>----------------------------------------------
CCPU::CCPU ():
AX_(0), BX_(0),
CX_(0), DX_(0),
EX_(0), FX_(0),
CMPX_(0), IP_(0),
BPX_(0)
{
    Memory_ = nullptr;
}

CCPU::~CCPU ()
{
    Memory_ = nullptr;
}

//------------------------<< Main execution method >>------------------------------
int CCPU::execute()
{
    int cmd;

    int arg_1;
    int arg_2;

    do
    {
        cmd = Programm_[IP_++];

        if (cmd == STOP)     continue;
        if (cmd == SKIP_CMD) continue;

        #define COMMAND(NAME, NUMBER, ARG, ACTION, DESCRIPTION) \
        if (cmd == NUMBER)                                      \
        {                                                       \
            switch(ARG)                                         \
            {                                                   \
            case(0):                                            \
                {                                               \
                    break;                                      \
                }                                               \
            case(1):                                            \
                {                                               \
                    arg_1 = Programm_[IP_++];                   \
                    break;                                      \
                }                                               \
            case(2):                                            \
                {                                               \
                    arg_1 = Programm_[IP_++];                   \
                    arg_2 = Programm_[IP_++];                   \
                    break;                                      \
                }                                               \
            }                                                   \
                                                                \
            ACTION                                              \
            continue;                                           \
        }                                                       \

        #include "CMDList.hpp"
        #undef COMMAND

    }
    while (cmd != STOP);

    return 1;
}

//------------------------<< Debug && Info >>--------------------------------------
int CCPU::cpu_dump ()
{
    printf("AX : %d\n", AX_);
    printf("BX : %d\n", BX_);
    printf("CX : %d\n", CX_);
    printf("DX : %d\n", DX_);

    UNN buf;

    buf.INT = EX_;
    printf("EX : %f\n", buf.FLOAT);

    buf.INT = FX_;
    printf("FX : %f\n", buf.FLOAT);

    printf("CMPX : %d\n", CMPX_);

    printf("BPX : %d\n", BPX_);

    Memory_->VarStk_.dump();
    Memory_->ArgStk_.dump();
    return 1;
}

//------------------------<< Outer set methods >>----------------------------------
int CCPU::set_Programm(vector<int> * MashineCode)
{
    vector<int> &buf_vector = * MashineCode;

    Programm_ = buf_vector;
    return 1;
}

int CCPU::set_Memory_ptr (CMemBlock * mem_ptr)
{
    Memory_ = mem_ptr;   // assert if nullptr!!
    return 1;
}

//------------------------<< Mashine commands >>-----------------------------------
int CCPU::exe_stop  ()
{
    printf("END OF PROGRAMM\n");

    return 1;
}

//------------------------<< Registers commands >>---------------------------------
int CCPU::reg_scn   (int arg_1, int arg_2)
{
    int * adr = get_reg_ptr(arg_1);
    ERROR_DETECT((adr), "reg_scn")

    if (arg_2 == INT_TYPE)
    {
        scanf("%d", adr);
    }
    if (arg_2 == FLOAT_TYPE)
    {
        UNN buf;

        scanf("%f", &buf.FLOAT);
        * adr = buf.INT;
    }

    ERROR_DETECT((1), "reg_scn");
    return 1;
}
int CCPU::reg_prt   (int arg_1, int arg_2)
{
    int * adr = get_reg_ptr(arg_1);
    ERROR_DETECT((adr), "CPU_SCN")

    if (arg_2 == INT_TYPE)
    {
        printf("%d\n", * adr);
    }
    if (arg_2 == FLOAT_TYPE)
    {
        UNN buf;
        buf.INT = * adr;

        printf("%f\n", buf.FLOAT);
    }

    ERROR_DETECT((1), "CPU_PRT");
    return 1;
}

int CCPU::reg_set   (int arg_1, int arg_2)
{
    int * adr = get_reg_ptr(arg_1);
    ERROR_DETECT((adr), "CPU_SET");

    * adr = arg_2;
    return 1;
}
int CCPU::reg_mov   (int arg_1, int arg_2)
{
    int * adr_1 = get_reg_ptr(arg_1);
    int * adr_2 = get_reg_ptr(arg_2);
    ERROR_DETECT((adr_1 && adr_2), "CPU_MOV");

    * adr_2 = * adr_1;
    return 1;
}
int CCPU::reg_cmp   (int arg_1, int arg_2)
{
    int * adr_1 = get_reg_ptr(arg_1);
    int * adr_2 = get_reg_ptr(arg_2);
    ERROR_DETECT((adr_1 && adr_2), "CPU_CMP");

    if (* adr_1 <= * adr_2)
    {
        CMPX_ = -1;
        return 1;
    }
    if (* adr_2 == * adr_1)
    {
        CMPX_ = 0;
        return 1;
    }
    if (* adr_1 >= * adr_2)
    {
        CMPX_ = 1;
        return 1;
    }

    return 1;
}
//---------------------------------------------------------------------------------

#define ARITHMETICS(arg_1, OPERATION, arg_2);       \
int * adr_1 = get_reg_ptr(arg_1);                   \
int * adr_2 = get_reg_ptr(arg_2);                   \
ERROR_DETECT((adr_1 && adr_2), "ARITHMETICS INT");  \
                                                    \
* adr_2 = (* adr_1) OPERATION (* adr_2);            \

int CCPU::reg_add   (int arg_1, int arg_2)
{
    ARITHMETICS(arg_1, +, arg_2);
    return 1;
}
int CCPU::reg_mul   (int arg_1, int arg_2)
{
    ARITHMETICS(arg_1, *, arg_2);
    return 1;
}
int CCPU::reg_div   (int arg_1, int arg_2)
{
    ARITHMETICS(arg_1, /, arg_2);
    return 1;
}
int CCPU::reg_and   (int arg_1, int arg_2)
{
    ARITHMETICS(arg_1, &, arg_2);
    return 1;
}
int CCPU::reg_or    (int arg_1, int arg_2)
{
    ARITHMETICS(arg_1, |, arg_2);
    return 1;
}
int CCPU::reg_xor   (int arg_1, int arg_2)
{
    ARITHMETICS(arg_1, ^, arg_2);
    return 1;
}

#undef ARITHMETICS
//---------------------------------------------------------------------------------

int CCPU::reg_set_f (int arg_1, int arg_2)
{
    int * adr = get_reg_ptr(arg_1);
    ERROR_DETECT((adr), "CPU_SET");

    * adr = arg_2;
    return 1;
}
int CCPU::reg_cmp_f (int arg_1, int arg_2)
{
    int * adr_1 = get_reg_ptr(arg_1);
    int * adr_2 = get_reg_ptr(arg_2);
    ERROR_DETECT((adr_1 && adr_2), "CPU_CMP_F");

    UNN buf;

    buf.INT = * adr_1;
    float buf_1 = buf.FLOAT;

    buf.INT = * adr_2;
    float buf_2 = buf.FLOAT;

    if (buf_1 <= buf_2)
    {
        CMPX_ = -1;
        return 1;
    }
    if (buf_1 == buf_2)
    {
        CMPX_ = 0;
        return 1;
    }
    if (buf_1 >= buf_2)
    {
        CMPX_ = 1;
        return 1;
    }

    return 1;
}
//---------------------------------------------------------------------------------

#define ARITHMETICS(arg_1, OPERATION, arg_2);       \
int * adr_1 = get_reg_ptr(arg_1);                   \
int * adr_2 = get_reg_ptr(arg_2);                   \
ERROR_DETECT((adr_1 && adr_2), "ARITHMETICS FLOAT");\
                                                    \
UNN buf;                                            \
                                                    \
buf.INT = * adr_1;                                  \
float buf_1 = buf.FLOAT;                            \
                                                    \
buf.INT = * adr_2;                                  \
float buf_2 = buf.FLOAT;                            \
                                                    \
buf_2 = buf_1 OPERATION buf_2;                      \
buf.FLOAT = buf_2;                                  \
                                                    \
* adr_2 = buf.INT;                                  \

int CCPU::reg_add_f (int arg_1, int arg_2)
{
    ARITHMETICS(arg_1, +, arg_2);
    return 1;
}
int CCPU::reg_mul_f (int arg_1, int arg_2)
{
    ARITHMETICS(arg_1, *, arg_2);
    return 1;
}
int CCPU::reg_div_f (int arg_1, int arg_2)
{
    ARITHMETICS(arg_1, /, arg_2);
    return 1;
}
//---------------------------------------------------------------------------------
//------------------------<< Jumps >>----------------------------------------------
int CCPU::prg_jmp (int arg_1)
{
    IP_ = arg_1;
    return 1;
}
int CCPU::prg_jee (int arg_1)
{
    if (CMPX_ == 0) IP_ = arg_1;
    return 1;
}
int CCPU::prg_jne (int arg_1)
{
    if (CMPX_ != 0) IP_ = arg_1;
    return 1;
}
int CCPU::prg_jle (int arg_1)
{
    if (CMPX_ == -1) IP_ = arg_1;
    return 1;
}
int CCPU::prg_jme (int arg_1)
{
    if (CMPX_ == 1) IP_ = arg_1;
    return 1;
}

//------------------------<< Functions >>------------------------------------------
int CCPU::func_call (int arg_1)
{
    CallStk_.push(BPX_);
    BPX_ = Memory_->VarStk_.top();

    CallStk_.push(IP_);
    IP_  = arg_1;

    return 1;
}
int CCPU::func_ret  ()
{
    IP_  = CallStk_.pop();
    BPX_ = CallStk_.pop();

    Memory_->VarStk_.set_top(BPX_);

    return 1;
}

//------------------------<< memory commands >>------------------------------------
//------------------------<< Variables >>------------------------------------------
int CCPU::var_dec (int arg_1, int arg_2)
{
    assert(Memory_->VarStk_.top() == arg_1 + BPX_);

    Memory_->VarStk_.push(0);
    return 1;
}
int CCPU::var_set_v (int arg_1, int arg_2)
{
    Memory_->VarStk_.set_val_at_id(arg_2, arg_1 + BPX_);

    return 1;
}
int CCPU::var_pop_v (int arg_1, int arg_2)
{
    int * ptr = get_reg_ptr(arg_2);
    * ptr = (Memory_->VarStk_.get_val_at_id(arg_1 + BPX_));

    return 1;
}
int CCPU::var_psh_v (int arg_1, int arg_2)
{
    int * ptr = get_reg_ptr(arg_2);

    Memory_->VarStk_.set_val_at_id(* ptr, arg_1 + BPX_);

    return 1;
}

int CCPU::var_set_vf(int arg_1, int arg_2)
{
    Memory_->VarStk_.set_val_at_id(arg_2, arg_1 + BPX_);

    return 1;
}

int CCPU::arg_psh (int arg_1)
{
    int * ptr = get_reg_ptr(arg_1);
    Memory_->ArgStk_.push(* ptr);

    return 1;
}
int CCPU::arg_pop (int arg_1)
{
    int * ptr = get_reg_ptr(arg_1);
    * ptr = Memory_->ArgStk_.pop();

    return 1;
}

//------------------------<< Local acsess methods >>-------------------------------
int * CCPU::get_reg_ptr  (int reg)
{
    switch(reg)
    {
    case(1):
        {
            return &AX_;
        }
    case(2):
        {
            return &BX_;
        }
    case(3):
        {
            return &CX_;
        }
    case(4):
        {
            return &DX_;
        }
    case(5):
        {
            return &EX_;
        }
    case(6):
        {
            return &FX_;
        }
    }

    return nullptr;
}

#undef ERROR_DETECT
//---------------------------------------------------------------------------------
