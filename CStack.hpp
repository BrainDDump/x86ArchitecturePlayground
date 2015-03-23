//------------------<< Including libraries >>--------------------
#include <assert.h>
#include "stk_err_anls.hpp"

//------------------<< Initializing consts && typedef >>---------
const int MAX_STACK_SIZE = 10000;

//------------------<< Defining macros >>------------------------
#define ERROR_DETECT(condition, error_name);\
if (!condition)                             \
{                                           \
    stack_error = error_name;               \
    dump();                                 \
    assert(0);                              \
    return 0;                               \
}                                           \

//------------------<< Stack class >>----------------------------
template <typename Data_T>
class CStack
{
public:
//------------------<< Setup >>----------------------------------
    CStack  ();
    ~CStack ();
//------------------<< Main methods >>---------------------------
    int    push (Data_T val);
    Data_T pop  ();
//------------------<< Main diagnostics >>-----------------------
    int check();
    int dump ();
//------------------<< Debug methods >>--------------------------
    int empty ();
    int full  ();
//------------------<< Variables >>------------------------------
protected:
    Data_T * data_;
    int size_;
    int top_;
};

//------------------<< Setup >>----------------------------------
template <typename Data_T>
CStack<Data_T>::CStack():
data_(new Data_T[10]),
size_(10), top_(0)
{
    /*---//---*/
}

template <typename Data_T>
CStack<Data_T>::~CStack()
{
    delete[] data_;
    top_ = -1;
}

//------------------<< Main methods >>---------------------------
template <typename Data_T>
int CStack<Data_T>::push(Data_T val)
{
    assert(check());

    if (full() == 0)
    {
        size_ *= 2;
        Data_T * buf = new Data_T[size_];

        for (int i = 0; i < size_ / 2; ++i)
            buf[i] = data_[i];

        delete[] data_;
        data_ = buf;
    }
    data_[top_++] = val;

    assert(check());

    return 1;
}

template <typename Data_T>
Data_T CStack<Data_T>::pop()
{
    assert(check());
    assert(empty());

    return data_[--top_];
}

//------------------<< Main diagnostics >>-----------------------
template <typename Data_T>
int CStack<Data_T>::check()
{
    ERROR_DETECT((this != nullptr),        ERR_NULL);
    ERROR_DETECT((data_ != nullptr),       ERR_DATA);
    ERROR_DETECT((top_ <= size_),          ERR_OVFL);
    ERROR_DETECT((top_ >= 0),              ERR_TOP_);
    ERROR_DETECT((size_ < MAX_STACK_SIZE), ERR_MAX_);

    return 1;
}

template <typename Data_T>
int CStack<Data_T>::dump()
{
    printf("\n------STACK INFO-----\n");
    ERR_PRINT(stack_error);
    printf("Pointer to stack : %p\n" , this );
    printf("Pointer to data_ : %p\n" , data_);
    printf("Size of the stack : %d\n", size_);
    printf("Top : %d\n", top_);
    printf("Stack interior : \n");

    if (data_ == nullptr) return 0;
    
    for (int i = 0; i < top_; ++i)
        std::cout << data_[i] << ' ';
    
    for (int i = top_; i < size_; ++i)
        printf("* ");
    
    printf("\n------END OF INFO------\n\n");

    return 1;
}

//------------------<< Debug methods >>--------------------------
template <typename Data_T>
int CStack<Data_T>::empty()
{
    if (top_ == 0)
        return 0;
    
        return 1;
}

template <typename Data_T>
int CStack<Data_T>::full()
{
    if (top_ == size_) return 0;
    else               return 1;
}

#undef ERROR_DETECT
//---------------------------------------------------------------
