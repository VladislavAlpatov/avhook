#pragma once


namespace UI
{
	class IBaseDrawObject
	{
	public:
		virtual void Show() = 0;
	protected:
		virtual void Render() = 0;
		virtual void KeepWindowInSreenArea() {};
	};
}