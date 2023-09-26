#include "pch.h"
#include "CppUnitTest.h"
#include "../ConsoleApplication1/ConsoleApplication1.cpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
            TEST_METHOD(TestClearDisplayCommand)
            {
                Command command;
                command.action = "clear display";
                command.parameters.push_back("color");

                executeCommand(command);
            }

            TEST_METHOD(TestDrawPixelCommand)
            {
                Command command;
                command.action = "draw pixel";
                command.parameters.push_back("10");
                command.parameters.push_back("20");
                command.parameters.push_back("red");

                executeCommand(command);
            }
            TEST_METHOD(TestDrawRectangle)
            {
                Command command;
                command.action = "draw rectangle";
                command.parameters.push_back("10");
                command.parameters.push_back("20");
                command.parameters.push_back("40");
                command.parameters.push_back("30");
                command.parameters.push_back("green");

                executeCommand(command);
            }
	};
}
