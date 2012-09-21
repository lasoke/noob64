#include "StdAfx.h"
#include "RCP.h"

RCP::RCP(RDRAM &rdram) : ram(rdram), ehandler(*new ExceptionHandler())
{
}

void RCP::decode(const word instr) {

}
