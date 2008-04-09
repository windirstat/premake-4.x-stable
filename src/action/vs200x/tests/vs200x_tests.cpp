/**
 * \file   vs200x_tests.cpp
 * \brief  Automated tests for VS200x support functions.
 * \author Copyright (c) 2008 Jason Perkins and the Premake project
 */

#include "premake.h"
#include "testing/testing.h"
extern "C" {
#include "action/vs200x/vs200x.h"
}

struct FxVs200x
{
	Session sess;

	FxVs200x()
	{
		sess = session_create();
	}

	~FxVs200x()
	{
		session_destroy(sess);
	}
};

SUITE(action)
{
	/**********************************************************************
	 * Version identification tests
	 **********************************************************************/

	TEST_FIXTURE(FxVs200x, GetTargetVersion_Returns2002_OnVs2002)
	{
		session_set_action(sess, "vs2002");
		int result = vs200x_get_target_version(sess);
		CHECK(result == 2002);
	}

	TEST_FIXTURE(FxVs200x, GetTargetVersion_Returns2003_OnVs2003)
	{
		session_set_action(sess, "vs2003");
		int result = vs200x_get_target_version(sess);
		CHECK(result == 2003);
	}

	TEST_FIXTURE(FxVs200x, GetTargetVersion_Returns2005_OnVs2005)
	{
		session_set_action(sess, "vs2005");
		int result = vs200x_get_target_version(sess);
		CHECK(result == 2005);
	}
}
