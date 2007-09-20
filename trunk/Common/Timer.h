/*
*   Copyright (C) 2007 Carnegie Mellon University
*   This file is part of the libjingle file transfer  Test Suite.
*
*   The Test Suite is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 3 of the License, or
*   any later version.
*
*   The Test Suite is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*   
*   Contact the original project authors by visiting
*   <http://dogbert.mse.cs.cmu.edu/MSE2007/Projects/Google/team.html>.
*/
#ifndef __timer_h
#define __timer_h

#pragma once
#include "common.h"
#include <sstream>
#include <string>
#include <windows.h>
#include <time.h>

class COMMON_API Timer
{
public:
	Timer(void);
	~Timer(void);

	void StartTimer();
	void StopTimer();
	long GetTime();
	time_t Now();
	std::string GetTimeAsString();

private:
	//Auxiliary Function
	void UpdateElapsed();

	//Member variables
	bool m_bRunning;	
	long m_iStart;
	long m_iElapsed;

	//auxiliary variables
	long m_iCounts;
};

//Auxiliary Function
inline void Timer::UpdateElapsed()
{
	//Transform milliseconds
	m_iCounts = GetTickCount();
	
	m_iElapsed = m_iCounts - m_iStart;
}

#endif