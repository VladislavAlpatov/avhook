#pragma once
#include "../IBaseInterface.h"


namespace SSDK
{
	class ConVar : public SSDK::IBaseInterface
	{
	public:
		ConVar*     m_pNext;
		bool        m_bIsRegistered;
		const char* m_Name;
		const char* m_HelpString;
		int         m_iFlags;
		uintptr_t   papd_2;
		ConVar*     m_pParentCvar;
		const char* m_DeafaultValue;
		char*       m_String;
		int         m_iStrigLength;
		float       m_fValue;
		int         m_iValue;
		bool        m_bHasMin;
		float       m_fMinValue;
		bool        m_bHasMax;
		float       m_fMaxValue;

		std::string    GetCvarName()     const;
		float          GetValueAsFloat() const;
		int            GetValueAsInt()   const;
		inline bool    GetValueAsBool()  const {return GetValueAsInt();}

		std::string GetString() const;

		void SetValue(const char* value);

		void SetValue(float value);
		void SetValue(int value);
	};

}

