
class ModeTitle : public ModeBase
{
	typedef ModeBase base;
public:
	virtual bool Initialize();
	virtual bool Terminate();
	virtual bool Process();
	virtual bool Render();

protected:
	int _cg;
	int _start;			// ���P
	int _startpad;		// ���P

	int _starttime;		// ���P
	int _stocktime;		// ���P
}; 
