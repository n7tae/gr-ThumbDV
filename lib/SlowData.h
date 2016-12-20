#pragma once

/*
 *   Copyright 2016 by Thomas Early AC2IE
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

class CSlowData
{
public:
	CSlowData();
	~CSlowData();
	void Add(const unsigned char *c);
	void ClearType3();
	void Reset();
private:
	enum { nomode, mode3, mode4, mode5 } currentmode;
	int m_headcount;
	unsigned char m_buffer[6];
	char m_header[45];
	char m_message[20];
	char m_type3[100];
	void PrintHeader();
};
