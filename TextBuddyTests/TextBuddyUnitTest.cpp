#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TextBuddyTests
{		
	TEST_CLASS(TextBuddyPositiveTest)
	{
	public:
		
		const string filename = "heytemp123.txt";
		const string testLongString = "sample text";
		const string testShortString = "sample ";
		const string testEmptyString = "";
		const string testLooksEmptyString = " ";

		TEST_METHOD(checkInvalidInputTest) {
			Assert::IsTrue(TextBuddy::checkInvalidInput(testEmptyString));
			Assert::IsTrue(TextBuddy::checkInvalidInput(testLooksEmptyString));

			Assert::IsFalse(TextBuddy::checkInvalidInput(testLongString));
		}

		TEST_METHOD(getFirstWordTest) {
			Assert::AreEqual("sample", TextBuddy::getFirstWord(testLongString).c_str());
			Assert::AreEqual("sample", TextBuddy::getFirstWord(testShortString).c_str());

			Assert::AreEqual("", TextBuddy::getFirstWord(testEmptyString).c_str());
			Assert::AreEqual("", TextBuddy::getFirstWord(testLooksEmptyString).c_str());

		}

		TEST_METHOD(determineCommandTypeTest) {

			const string add = "add";
			const string clear = "clear";
			const string deleteLine = "delete";
			const string display = "display";
			const string invalid = "invalid";

			Assert::AreEqual(
				add, 
				TextBuddy::checkCommandType(
					TextBuddy::determineCommandType("Add"))
			);
			Assert::AreEqual(
				add, 
				TextBuddy::checkCommandType(
					TextBuddy::determineCommandType("add"))
			);
			Assert::AreEqual(
				clear, 
				TextBuddy::checkCommandType(
					TextBuddy::determineCommandType("clear"))
			);
			Assert::AreEqual(
				deleteLine, 
				TextBuddy::checkCommandType(
					TextBuddy::determineCommandType("delete"))
			);
			Assert::AreEqual(
				display, 
				TextBuddy::checkCommandType(
					TextBuddy::determineCommandType("display"))
			);
			Assert::AreEqual(
				invalid, 
				TextBuddy::checkCommandType(
					TextBuddy::determineCommandType(testLongString))
			);
			Assert::AreEqual(
				invalid,
				TextBuddy::checkCommandType(
					TextBuddy::determineCommandType(testShortString))
			);
			Assert::AreNotEqual(
				add, 
				TextBuddy::checkCommandType(
					TextBuddy::determineCommandType(testLooksEmptyString))
			);
			Assert::AreNotEqual(
				add,
				TextBuddy::checkCommandType(
					TextBuddy::determineCommandType(testLongString))
			);


		}

		TEST_METHOD(clearAllTest) {
			const string ExpOutput = "all content deleted from heytemp123.txt";

			Assert::AreEqual(ExpOutput, TextBuddy::clearAll(filename));
		}

		TEST_METHOD(addLineTest) {

			const string addInput = "hello there!";
			const string ExpOutput = "added to heytemp123.txt: \"hello there!\"";

			Assert::AreEqual(ExpOutput, TextBuddy::addLine(filename, addInput));
		}


		TEST_METHOD(displayAllTest) {

			const string ExpEmptyOutput = "heytemp123.txt is empty";
			const string ExpOutput = "";

			//clear file
			TextBuddy::clearAll(filename);
			TextBuddy::writeToFile(filename);

			Assert::AreEqual(ExpEmptyOutput, TextBuddy::displayAll(filename));

			//set up file
			TextBuddy::addLine(filename, testLongString);
			TextBuddy::addLine(filename, testShortString);
			TextBuddy::writeToFile(filename);

			Assert::AreEqual(ExpOutput, TextBuddy::displayAll(filename));

			//clear file
			TextBuddy::clearAll(filename);
			TextBuddy::writeToFile(filename);
		}

		TEST_METHOD(deleteLineTest) {
			const string ExpOutput = "deleted from heytemp123.txt: \"sample \"";

			//set up file
			TextBuddy::addLine(filename, testLongString);
			TextBuddy::addLine(filename, testShortString);
			TextBuddy::writeToFile(filename);

			Assert::AreEqual(ExpOutput, TextBuddy::deleteLine(filename, "2"));

			//clear file
			TextBuddy::clearAll(filename);
			TextBuddy::writeToFile(filename);
		}

		TEST_METHOD(sortAlphaTest) {

			const string ExpOutput = "all content in heytemp123.txt sorted alphabetically";

			Assert::AreEqual(ExpOutput, TextBuddy::sortAlphabetical(filename));

		}

		TEST_METHOD(searchFileTest) {
			const string ExpOutput1 = "found 2 result(s) in heytemp123.txt";
			const string ExpOutput2 = "found 1 result(s) in heytemp123.txt";
			const string ExpOutput3 = "found 0 result(s) in heytemp123.txt";

			//set up file
			TextBuddy::addLine(filename, testLongString);
			TextBuddy::addLine(filename, testShortString);
			TextBuddy::writeToFile(filename);

			Assert::AreEqual(ExpOutput1, TextBuddy::searchFile(filename, "sample"));
			Assert::AreEqual(ExpOutput2, TextBuddy::searchFile(filename, "sample text"));
			Assert::AreEqual(ExpOutput2, TextBuddy::searchFile(filename, "text"));
			Assert::AreEqual(ExpOutput3, TextBuddy::searchFile(filename, "hello"));

			//clear file
			TextBuddy::clearAll(filename);
			TextBuddy::writeToFile(filename);
		}
	};
}