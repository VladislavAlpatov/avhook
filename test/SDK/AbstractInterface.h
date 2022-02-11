#pragma once

class AbstractInterface
{
protected:
	template<typename FuncType>
	FuncType GetVirtualFunction(unsigned int index)
	{
		unsigned int* pVTable         = *reinterpret_cast<unsigned int**>(this);
		unsigned int function_address = pVTable[index];
		return reinterpret_cast<FuncType>(function_address);
	}

};

