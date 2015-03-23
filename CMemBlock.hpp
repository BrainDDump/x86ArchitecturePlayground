//------------------<< MemBlock class >>-------------------------------------------
class CMemBlock
{
public:
	CMemBlock();
	~CMemBlock();

	CVarStack         VarStk_;
	CVarStack::CStack ArgStk_;
};

CMemBlock::CMemBlock()
{
	/*---//---*/
}
CMemBlock::~CMemBlock()
{
	/*---//---*/
}
