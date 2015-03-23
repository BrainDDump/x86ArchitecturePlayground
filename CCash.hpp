//------------------<< class Cash >>---------------------------------------------
class CCash
{
public:
	CCash ();
	~CCash ();

	int set_Cash_Programm(vector<int> * MashineCode);

    vector<int> Programm_;
    CStack<int> CallStk_;
};

CCash::CCash()
{
	/*---//---*/
}

CCash::~CCash()
{
	Programm_.erase(Programm_.begin(), Programm_.end());
}

int CCash::set_Cash_Programm(vector<int> * MashineCode)
{
	if (!MashineCode) return 0;

    vector<int> &buf_vector = * MashineCode;
    Programm_ = buf_vector;

    return 1;
}
