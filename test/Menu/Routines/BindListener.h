#pragma once

namespace Routines
{
	class CBindListener
	{
	public:
		CBindListener()
		{
			m_pVirtualKeyValue = nullptr;
			m_pShowKeyBinderDialog = nullptr;
		}
		CBindListener(int* pVirtualKeyValue, bool* pShowKeyBinderDialog);
		int* m_pVirtualKeyValue;
		bool* m_pShowKeyBinderDialog;

		void Listen();
	private:
		void RutineThread();
		void ChromaEffect(int keyNum);

	};
}
