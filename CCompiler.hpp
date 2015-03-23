//------------------<< Including libraries >>---------------------------------------------
#include <string>
#include <vector>
#include <fstream>
#include <assert.h>

using namespace std;

//------------------<< structs && unions >>-----------------------------------------------
struct lable
{
    string       NAME;
    unsigned int POINTER;
};

struct func
{
    string       NAME;
    unsigned int POINTER;
};

struct variable
{
    string       NAME;
    unsigned int ADRESS;
};

union UNN
{
    int   INT;
    float FLOAT;
};

//------------------<< Initializing consts && Typedef >>----------------------------------
const int MashineCode_MAX_SIZE = 1000;
const int COMMAND_MAX_SIZE  = 10;

enum ACMCode_RANGE
{
    STP_CMD_FIRST  = 0,

    REG_CMD_FIRST  = 1,
    REG_CMD_LAST   = 16,

    JMP_CMD_FIRST  = 17,
    JMP_CMD_LAST   = 21,

    FUNC_CMD_FIRST = 22,
    FUNC_CMD_LAST  = 23,

    STK_CMD_FIRST  = 24,
    STK_CMD_LAST   = 28,

    ARG_CMD_FIRST  = 29,
    ARG_CMD_LAST   = 30
};

//------------------<< Defining macros >>-------------------------------------------------
#define ERROR_DETECT(CONDITION, IN_FUNC) 	        \
if (!CONDITION)                             		\
{                                         			\
    printf("--EXE MODULE--\n");             		\
    printf("ERROR IN FUNCTION : ");    			    \
    printf(IN_FUNC);                   			    \
    printf("\n");                      			    \
    dump();                            			    \
    assert(0);                         			    \
}                                      			    \

//------------------<< CCompiler class >>-------------------------------------------------
class CCompiler
{
public:
	CCompiler ();
	~CCompiler();

	int           read       (const char * input);
	int           compile    ();
	vector<int> * MashineCode();
//private:
	int get_reg_num (string reg);
    int dump();

	vector<string> ACMCode_;
	vector<int>    MashineCode_;
};

CCompiler::CCompiler()
{
    /*---//---*/
}

CCompiler::~CCompiler()
{
    /*---//---*/
}

int CCompiler::read(const char * input)
{
	ifstream in(input);
	string   buf_cmd;

	if (!in.is_open()) { // error
		return 0;
		assert(0);
	}

	do
    {
        in >> buf_cmd;
        ERROR_DETECT((buf_cmd.length() < COMMAND_MAX_SIZE), "COMPILE (command to big)")
        ACMCode_.push_back(buf_cmd);
    }
    while (buf_cmd != "STOP");

    return 1;
}

int CCompiler::compile()
{
    vector<lable>    lables;
    vector<func>     funcs;
    vector<variable> local_variables;

    vector< vector<variable> > all_variables;

	string   buf_cmd;
    string   buf_arg_1;
    string   buf_arg_2;

//------------------------<< collect general info >>--------------------------------------
    int local_var_counter;

    lable    buf_lbl;
    func buf_func;
    variable buf_var;

	for (int i = 0; i < ACMCode_.size(); i++)
    {
        if (ACMCode_[i][0] == '$')
        {
            buf_cmd = ACMCode_[i].substr(1);

            buf_lbl.NAME    = buf_cmd;
            buf_lbl.POINTER = i;

            lables.push_back(buf_lbl);
        }
    }

    for (int i = 0; i < ACMCode_.size(); i++)
    {
        if (ACMCode_[i][0] == '@')
        {
            buf_cmd = ACMCode_[i].substr(1);

            buf_func.NAME    = buf_cmd;
            buf_func.POINTER = i;

            funcs.push_back(buf_func);
        }
    }

    local_var_counter = 0;
    for (int i = 0; i < ACMCode_.size(); i++)
    {
    	if (ACMCode_[i] == "STOP") break;

    	if (ACMCode_[i][0] == '@')
    	{
    		all_variables.push_back(local_variables);

    		local_variables.erase(local_variables.begin(), local_variables.end());
    		local_var_counter = 0;

    		continue;
    	}

        if (ACMCode_[i] == "DEC")
        {
            buf_cmd = ACMCode_[++i];

            buf_var.NAME    = buf_cmd;
            buf_var.ADRESS  = local_var_counter++;

            local_variables.push_back(buf_var);
        }
    }
    all_variables.push_back(local_variables);

    local_variables = all_variables[0];
    all_variables.erase(all_variables.begin());

//------------------------<< convert commands to mashine code >>--------------------------
    MashineCode_.reserve(ACMCode_.size());

    int flag;
    for (int i = 0; i < ACMCode_.size(); ++i)
    {
        flag = 0;

        buf_cmd = ACMCode_[i];

        if (buf_cmd[0] == '$')
        {
            MashineCode_.push_back(-1);
            continue;
        }

        if (buf_cmd[0] == '@')
        {
            local_variables.erase(local_variables.begin(), local_variables.end());

        	local_variables = all_variables[0];
        	all_variables.erase(all_variables.begin());

        	MashineCode_.push_back(-1);
            continue;
        }

        string NAME = "Empty";
        int    NUMBER;
        int    ARG;

        #define COMMAND(CMD_NAME, CMD_NUMBER, CMD_ARG, CMD_ACTION, CMD_DESCRIPTION) \
        if (buf_cmd == #CMD_NAME)                                                   \
        {                                                                           \
            NAME   = #CMD_NAME;                                                     \
            NUMBER = CMD_NUMBER;                                                    \
            ARG    = CMD_ARG;                                                       \
        }                                                                           \

        #include "CMDList.hpp"
        #undef COMMAND

        if (NAME == "Empty") ERROR_DETECT((0), "COMPILE ERROR! Command not found")

            cout << "NAME : " << NAME << endl;

        MashineCode_.push_back(NUMBER);

        if (NUMBER == STP_CMD_FIRST) break;

        if ((REG_CMD_FIRST <= NUMBER) && (NUMBER <= REG_CMD_LAST))
        {
            buf_arg_1 = ACMCode_[++i];
            buf_arg_2 = ACMCode_[++i];

            MashineCode_.push_back(get_reg_num(buf_arg_1));

            if (NAME == "SET")
            {
                MashineCode_.push_back(stoi(buf_arg_2, nullptr, 10));
                continue;
            }

            if (NAME == "SET_F")
            {
                UNN buf;
                buf.FLOAT = (float)(::atof(buf_arg_2.c_str()));

                MashineCode_.push_back(buf.INT);
                continue;
            }

            if ((NAME == "SCN") || (NAME == "PRT"))
            {
                if (buf_arg_2 == "INT")
                {
                    MashineCode_.push_back(1);
                    continue;
                }
                if (buf_arg_2 == "FLOAT")
                {
                    MashineCode_.push_back(2);
                    continue;
                }

                ERROR_DETECT((0), "UNKNOWN TYPE (SCN || PRT)")
            }
                                                                    // assert if ARGS are incorrect???
            MashineCode_.push_back(get_reg_num(buf_arg_2));
            continue;
        }
      
        if ((JMP_CMD_FIRST <= NUMBER) && (NUMBER <= JMP_CMD_LAST))
        {
            buf_arg_1 = ACMCode_[++i];

            for (int j = 0; j < lables.size(); j++)
            {
                if (lables[j].NAME == buf_arg_1)
                {
                    MashineCode_.push_back(lables[j].POINTER);     // assert if pointer is out of range!!
              
                    flag = 1;
                    break;
                }
            }
            ERROR_DETECT(flag, "LABLE NOT FOUND!")

            continue;
        }

        if ((FUNC_CMD_FIRST <= NUMBER) && (NUMBER <= FUNC_CMD_LAST))
        {
        	if (NAME == "CALL")
        	{
                buf_arg_1 = ACMCode_[++i];

        		for (int j = 0; j < funcs.size(); j++)
            	{
                    cout << "funcs[j].NAME : " << funcs[j].NAME << endl;

                	if (funcs[j].NAME == buf_arg_1)
                	{
                    	MashineCode_.push_back(funcs[j].POINTER);     // assert if pointer is out of range!!
                  
                        flag = 1;
                    	break;
                	}
            	}
            	ERROR_DETECT(flag, "LABLE NOT FOUND!")

            	continue;
        	}

        	if (NAME == "RET") continue;

        	ERROR_DETECT(flag, "NOT A FUNC COMMAND!")
        }

        if ((STK_CMD_FIRST <= NUMBER) && (NUMBER <= STK_CMD_LAST))
        {
            buf_arg_1 = ACMCode_[++i];
            buf_arg_2 = ACMCode_[++i];

            for (int j = 0; j < local_variables.size(); j++)
            {
                if (local_variables[j].NAME == buf_arg_1)
                {
                    MashineCode_.push_back(local_variables[j].ADRESS);

                    flag = 1;
                    break;
                }
            }
            ERROR_DETECT(flag, "variable not found!")

            if (NAME == "SET_V")
            {
                MashineCode_.push_back(stoi(buf_arg_2, nullptr, 10));

                flag = 1;
                continue;
            }
            if (NAME == "SET_VF")
            {
                UNN buf;
                buf.FLOAT = (float)(::atof(buf_arg_2.c_str()));

                MashineCode_.push_back(buf.INT);

                flag = 1;
                continue;
            }
            if (NAME == "DEC")
            {
                if (buf_arg_2 == "INT")
                {
                    MashineCode_.push_back(1);

                    continue;
                }
                if (buf_arg_2 == "FLOAT")
                {
                    MashineCode_.push_back(2);

                    continue;
                }
                ERROR_DETECT((0), "UNKNOWN TYPE (DEC)")
            }

            MashineCode_.push_back(get_reg_num(buf_arg_2));
            continue;
        }

        if ((ARG_CMD_FIRST <= NUMBER) && (NUMBER <= ARG_CMD_LAST))
        {
            buf_arg_1 = ACMCode_[++i];

            MashineCode_.push_back(get_reg_num(buf_arg_1));
            continue;
        }
    }

    return 1;
}

//------------------------<< private methods >>-------------------------------------------
vector<int> * CCompiler::MashineCode()
{
	return (& MashineCode_);
}

int CCompiler::get_reg_num (string reg)
{
    if (reg == "AX")   return 1;
    if (reg == "BX")   return 2;
    if (reg == "CX")   return 3;
    if (reg == "DX")   return 4;
    if (reg == "EX")   return 5;
    if (reg == "FX")   return 6;
    if (reg == "CMPX") return 7;
    if (reg == "BPX")  return 8;

    return 0;
}

int CCompiler::dump()
{
    printf("------COMPILER DUMP-------\n");
    for (int i = 0; i < ACMCode_.size(); ++i)
        cout << ACMCode_[i] << endl;

    printf("\n");

    for (int i = 0; i < MashineCode_.size(); ++i)
        cout << MashineCode_[i] << ' ';

    printf("---END OF COMPILER DUMP---\n");

    return 1;
}

#undef ERROR_DETECT
//----------------------------------------------------------------------------------------