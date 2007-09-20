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
#ifndef __MACRO_HKM__
#define __MACRO_HKM__


/* MFC CString Conversion macros */
#define CASTSTR(str) (char*)CW2A(str)
#define CASTWSTR(str) CW2A(str).m_psz
#define ATOI(str) atoi(CASTSTR(str))
#define ATOF(str) atof(CASTSTR(str))
#define BTOb(str) ((str == TRUE)? true:false)

#define  UP 1
#define  DOWN 2

#define SCENARIO_EXTENSION ".scenario"
#define SCHEDULE_EXTENSION ".scenario"

#define SINGLE_PROTOCOL		 2		/* 1 for 1 x value and 1 for y value */ 
#define COMPARE_TWO_PROTOCOL 3 /* 2 rows for 2 x values and 1 for y value */

#define QUERY_LENGTH	1200 /* 2 sub query + contraints variables */
#define SUB_QUERY_LENGTH 500

#endif