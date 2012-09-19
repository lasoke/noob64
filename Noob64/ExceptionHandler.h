#pragma once


//The class of the Exception Handler allows the emulator
//to trigger and execute exception and interruption
class ExceptionHandler
{
public:
	ExceptionHandler(void);
	void interruption(void);
	void trap(void);
	void syscall(void);
	static void unknownInstruction(word instr);
private:
};

