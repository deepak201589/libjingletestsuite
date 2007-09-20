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
/*
* MainGUI/ReportQuery
* a custom class for report query
*/

#ifndef _CHOPCHOP_CPP_REPORTQUERY
#define _CHOPCHOP_CPP_REPORTQUERY

//#include"" <-- include query function
#include <list>

using namespace std;

class CReportQuery 
{

public:
	/* constructor and destructor*/
	CReportQuery();
	~CReportQuery();

	/* member variables */
	CString m_filename;

	/* member variables for X axis value */
	CString m_xType;	// member value for X's value name
	CString m_xValue;	// member value for X's composite value name
	CString m_xValue2;	// member variable for x's composite variable formula
	CString m_xFormula;

	/* member variables for Y axis value */

	CString m_yType;	// member variable for Y's single value
	CString m_yValue;	// member variable for Y's composite value name
	CString m_yValue2;	// member variable for Y's composite value formula
	CString m_yFormula;

	/* screening constraint parameters */
	list <CString> *m_dataSource;
	list <CString> *m_dataSource2;

	CString m_orderby;
	CString m_groupby;
	CString m_rangeFormula;
};


#endif
