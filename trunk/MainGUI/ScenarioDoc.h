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
#ifndef __scenariodoc__
#define  __scenariodoc__

#pragma once
// CScenarioDoc document

#include "../Common/Scenario.h"
#include "../TestHelper/ScenarioManager.h"

class CScenarioDoc : public CDocument
{
	DECLARE_DYNCREATE(CScenarioDoc)

public:
	CScenarioDoc();
	virtual ~CScenarioDoc();
#ifndef _WIN32_WCE
	virtual void Serialize(CArchive& ar);   // overridden for document i/o
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

/* member functions */
	int SaveAsFile(CString filename);


/* member variables */
public:

	ScenarioManager m_manager;


protected:
	virtual BOOL OnNewDocument();
	DECLARE_MESSAGE_MAP()
};
#endif