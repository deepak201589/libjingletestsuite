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
* Relative Path: /Common/ErrorCode.h
* ErrorCode defined common error codes for the test suite.
* The test suite application should use the error codes given in this file to propagate success/error values.
* To add new errors: Add the error_code to the end of the list after a comma and before '}'
* Keep this as an enum and use these error codes - and not integer values - in your program so that
* you don't have to check back n forth or review the code to prevent erroneous error codes.
*/
#ifndef __errors_h
#define __errors_h

#pragma once

const enum Errors{
	SUCCESS,
	FAILURE,
	OP_NOT_PERMITTED,
	NO_SUCH_FILE_DIR,
	FILE_NOT_FOUND,
	IO_ERROR,
	CANNOT_ALLOCATE_MEM,
	PERM_DENIED,
	FILE_EXISTS,
	INVALID_ARGUMENT,
	ARG_OUT_OF_DOM,
	ARG_OUT_OF_RANGE,
	FILE_NAME_LONG,
	NO_DATA_AVAILABLE,
	MACHINE_NOT_ON_NETWORK,
	COMM_ERROR_ON_SEND,
	BAD_MESSAGE,
	MESSAGE_TOO_LONG,
	OPERATION_NOT_SUPP,
	NETWORK_IS_DOWN,
	NETWORK_IS_UNREACHABLE,
	DISK_QUOTA_EXCEEDED,
	PERMISSION_DENIED,
	FILE_DOES_NOT_EXIST,
	AUTHENTICATION_FAILED,
	FILE_SYSTEM_FULL,
	NULL_POINTER,
	NO_SPACE,
	DB_INIT_FAILED,
	DB_CONNECT_FAILED,
	DB_SETDB_FAILED,
	QUERY_EXEC_FAILED,
	NO_RETURN_ROWS,
};

#endif