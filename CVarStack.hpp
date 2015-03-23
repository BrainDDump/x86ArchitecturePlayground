//------------------<< Defining macros >>------------------------
#define ERROR_DETECT(condition, error_name);\
if (!condition)                             \
{                                           \
    stack_error = error_name;               \
    dump();                                 \
    assert(0);                              \
    return 0;                               \
}                                           \


class CVarStack : public CStack <int>
{
public:
	CVarStack ();
	~CVarStack();

	int top           ();
	int set_top       (int id);
	int get_val_at_id (int id);
	int set_val_at_id (int val, int id);
};

CVarStack::CVarStack ()
{
	/*---//---*/
}
CVarStack::~CVarStack()
{
	/*---//---*/
}

int CVarStack::get_val_at_id (int id)
{
	ERROR_DETECT((id < top_), ERR_WRID);
	return data_[id];
}

int CVarStack::set_val_at_id (int val, int id)
{
	ERROR_DETECT((id < top_), ERR_WRID);
	data_[id] = val;
	return 1;
}

int CVarStack::set_top (int id)
{
	ERROR_DETECT((id < size_), ERR_WRID);
	top_ = id;
	return 1;
}

int CVarStack::top ()
{
	return top_;
}

#undef ERROR_DETECT
//---------------------------------------------------------------
