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
#include "StdAfx.h"
#include "Timer.h"

Timer::Timer() : m_iStart(0), m_iElapsed(0), m_bRunning(false)
{
}

Timer::~Timer(void)
{
}

void Timer::StartTimer()
{
	m_iStart = GetTickCount();
	m_bRunning = true;
}

void Timer::StopTimer()
{
	UpdateElapsed();
	m_bRunning = false;
}

long Timer::GetTime()
{
	if(true == m_bRunning)
		UpdateElapsed();
	return m_iElapsed;
}

std::string Timer::GetTimeAsString()
{
	std::ostringstream oss;
	oss << GetTime();

	return oss.str();
}

time_t Timer::Now()
{
	time_t now;
	time(&now);
	return now;
}

