#pragma once


namespace UI
{
	class IBaseDrawObject
	{
	public:
		virtual void Show() { Render(); }
	protected:
		virtual void Render() = 0;
		virtual void KeepWindowInScreenArea() {}
	};
}