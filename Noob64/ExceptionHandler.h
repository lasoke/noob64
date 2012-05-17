#pragma once

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

