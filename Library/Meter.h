/*
  Copyright (C) 2001 Kimmo Pekkola

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef __METER_H__
#define __METER_H__

#include <windows.h>
#include <list>
#include <gdiplus.h>
#include "Litestep.h"
#include "MeterWindow.h"

class CMeasure;

class CMeter
{
public:
	CMeter(CMeterWindow* meterWindow);
	virtual ~CMeter();

	virtual void ReadConfig(const WCHAR* section);
	virtual void Initialize();
	virtual bool Update();
	virtual bool Draw();
	virtual void BindMeasure(std::list<CMeasure*>& measures);

	virtual int GetH() { return m_Hidden ? 0 : m_H; };
	virtual int GetW() { return m_Hidden ? 0 : m_W; };
	virtual int GetX(bool abs = false);
	virtual int GetY(bool abs = false);

	void SetX(int x) { m_X = x; m_RelativeX = POSITION_ABSOLUTE; };
	void SetY(int y) { m_Y = y; m_RelativeY = POSITION_ABSOLUTE; };

	std::wstring& GetRightMouseDownAction() { return m_RightMouseDownAction; };
	std::wstring& GetRightMouseUpAction() { return m_RightMouseUpAction; };
	std::wstring& GetLeftMouseDownAction() { return m_LeftMouseDownAction; };
	std::wstring& GetLeftMouseUpAction() { return m_LeftMouseUpAction; };
	std::wstring& GetMouseOverAction() { return m_MouseOverAction; };
	std::wstring& GetMouseLeaveAction() { return m_MouseLeaveAction; };

	void Hide() { m_Hidden = true; };
	void Show() { m_Hidden = false; };
	bool IsHidden() { return m_Hidden; };

	virtual bool HitTest(int x, int y);

	void SetMouseOver(bool over) { m_MouseOver = over; }
	bool IsMouseOver() { return m_MouseOver; }

	void SetName(const WCHAR* name) { m_Name = name; };
	const WCHAR* GetName() { return m_Name.c_str(); };

	static CMeter* Create(const WCHAR* meter, CMeterWindow* meterWindow);
	static WCHAR* ConvertToWide(const char* string);

	static void DrawBevel(Gdiplus::Graphics& graphics, Gdiplus::Rect& rect, Gdiplus::Pen& light, Gdiplus::Pen& dark);

protected:

	enum METER_ALIGNMENT
	{
		ALIGN_LEFT,
		ALIGN_RIGHT,
		ALIGN_CENTER
	};

	enum METER_POSITION
	{
		POSITION_ABSOLUTE,
		POSITION_RELATIVE_TL,
		POSITION_RELATIVE_BR
	};

	std::wstring m_Name;			// Name of the meter
	std::wstring m_MeasureName;	// Name of the measure this is bound to
	CMeasure* m_Measure;		// Pointer to the measure this meter is bound to
	int	m_X;					// X-position of the meter
	int	m_Y;					// Y-position of the meter
	int	m_W;					// Width of the meter
	int	m_H;					// Height of the meter
	bool m_Hidden;				// Status of the meter
	CMeter*	m_RelativeMeter;

	static int c_OldX;
	static int c_OldY;

	std::wstring m_RightMouseDownAction;	// Actions for left and right mouse buttons
	std::wstring m_RightMouseUpAction;
	std::wstring m_LeftMouseDownAction;
	std::wstring m_LeftMouseUpAction;
	std::wstring m_MouseOverAction;
	std::wstring m_MouseLeaveAction;

	bool m_MouseOver;
	METER_POSITION m_RelativeX;
	METER_POSITION m_RelativeY;

	UINT m_UpdateDivider;			// Divider for the update
	UINT m_UpdateCounter;			// Current update counter

	BEVELTYPE m_SolidBevel;
	Gdiplus::Color m_SolidColor;
	Gdiplus::Color m_SolidColor2;
	Gdiplus::REAL m_SolidAngle;

	CMeterWindow* m_MeterWindow;
};

#endif