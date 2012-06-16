#pragma once
ref class RCP
{
public:
	RCP(RDRAM &ram);
	void decode(const word instr);
private:
	RDRAM &ram;
	ExceptionHandler &ehandler;
};

