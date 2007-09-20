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
#include "stdafx.h"
#include "ReportQuery.h"


CReportQuery::CReportQuery()
{
	/* place initialization code */
	m_dataSource = new list <CString>();
	m_dataSource2 = new list <CString>();
}

CReportQuery::~CReportQuery()
{
	if (m_dataSource) {
		delete m_dataSource;
		m_dataSource = NULL;
	}

	if (m_dataSource2) {
		delete m_dataSource2;
		m_dataSource2 = NULL;
	}
}
