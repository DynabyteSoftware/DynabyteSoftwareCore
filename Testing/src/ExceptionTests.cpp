#include<iostream>
#include "ExceptionTests.h"
#include "Exception.h"

using namespace DynabyteSoftware::Testing;
using std::cout;
using std::endl;

void ExceptionTests::allTests()
{
	try
	{
		try
		{
			THROW(Exception, "First exception thrown")
		}
		catch (Exception& excp)
		{
			THROW(Exception, "Second exception thrown", &excp)
		}
	}
	catch (Exception& excp)
	{
		cout << excp.what() << endl;
		cout << "Inner:  " << excp.getInnerException()->what() << endl;
	}
}