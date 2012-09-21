#pragma once
ref class RCP
{
public:
	RCP(RDRAM &rdram);
	void decode(const word instr);
private:
	RDRAM &ram;
	ExceptionHandler &ehandler;
};

