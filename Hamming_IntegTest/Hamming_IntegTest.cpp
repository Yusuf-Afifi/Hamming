#include "stdafx.h"
#include "CppUnitTest.h"
#include "CommandPipe.h"
#include "StrUtilities.h"
#include <string>
#include "RandomString.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Hamming_IntegTest
{		
	TEST_CLASS(Hamming_IntegTest)
	{
		TEST_CLASS_INITIALIZE(methodName)
		{
			// we can save this seed to a file if we ever want to reproduce the exam same random test cases
			srand(time(NULL) % UINT_MAX);//to prevent warning and possible data loss
		}
	private:
		void Hamming_Assert_cmd(const std::string& _str1, const std::string& _str2, bool _binMode, bool _fileMode, int _expected, const char* _expected_str = NULL)
		{
			try
			{
				std::string initCommand = "Hamming";
				if (_binMode) initCommand += " -bin";
				if (_fileMode) initCommand += " -file";

				if (_expected_str)
				{
					auto res = CommandPipe::execute_str_res(initCommand, _str1, _str2);
					auto findRes = res.find(_expected_str);
					if (findRes != std::string::npos)
						Assert::IsTrue(true);
					else
					{
						Assert::Fail((std::wstring() + L"Result string (" + quote(to_wchar(res)) + L") doesn't contain expected string : " + quote(to_wchar(_expected_str))).c_str());
					}
				}
				else
				{
					auto res = CommandPipe::execute(initCommand, _str1, _str2);
					Assert::AreEqual(res, _expected, to_wchar(_str1).c_str());
				}
			}
			catch (const std::exception& ex)
			{
				Assert::Fail(to_wchar(ex.what()).c_str());
			}
			catch (...)
			{
				Assert::Fail(L"Unkown Error Occured");
			}
		}

		
	public:

		TEST_METHOD(TestExact)
		{
			Hamming_Assert_cmd("Test Me", "Test Me", false, false, 0);
		}

		TEST_METHOD(TestSingle)
		{
			Hamming_Assert_cmd("Test Me", "Test me", false, false, 1);
		}

		TEST_METHOD(TestUnEqualLength)
		{
			Hamming_Assert_cmd("Test Me", "Test    me", false, false, NULL, "different in length");
		}
		
		TEST_METHOD(RandomString)
		{
			auto str = RandomString::generate();
			auto copy = str;
			auto hamming_dist = RandomString::alter(copy);
			Hamming_Assert_cmd(str, copy, false, false, hamming_dist);
		}

		TEST_METHOD(RandomString_loop)
		{
			for (int i = 0; i < 30; i++)
			{
				auto str = RandomString::generate(i*100);
				auto copy = str;
				auto hamming_dist = RandomString::alter(copy);
				Hamming_Assert_cmd(str, copy, false, false, hamming_dist);
			}
		}

		TEST_METHOD(RandomBin)
		{
			auto str = RandomBlob::generate();
			auto copy = str;
			auto hamming_dist = RandomBlob::alter(copy);

			RandomBlob::save(str, "A_dump.bin");
			RandomBlob::save(copy, "B_dump.bin");
			Hamming_Assert_cmd("A_dump.bin", "B_dump.bin", true, true, hamming_dist);
		}



		TEST_METHOD(RandomBin_loop)
		{
			for (int i = 0; i < 30; i++)
			{
				auto str = RandomBlob::generate(i * 100);
				auto copy = str;
				auto hamming_dist = RandomBlob::alter(copy);

				RandomBlob::save(str, "A_dump.bin");
				RandomBlob::save(copy, "B_dump.bin");
				Hamming_Assert_cmd("A_dump.bin", "B_dump.bin", true, true, hamming_dist);
			}
		}

	};
}