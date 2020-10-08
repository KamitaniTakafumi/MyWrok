
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
	int _start;			// Å¶ÇP
	int _startpad;		// Å¶ÇP

	int _starttime;		// Å¶ÇP
	int _stocktime;		// Å¶ÇP
}; 
