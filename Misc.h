#pragma once
#include "SDK.h"

class CMisc
{
public:

	void Run(CBaseEntity* pLocal, CUserCmd* pCommand);
	bool Spam;

private:

	//Other funcs

	void NoisemakerSpam(PVOID kv);
};

extern CMisc gMisc;