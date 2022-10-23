/*
 * Copyright (c) 2022.
 * Created by Alpatov Softworks with love in Russia.
 */

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