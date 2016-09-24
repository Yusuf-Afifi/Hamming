#include "stdafx.h"
#include "CppUnitTest.h"
#include "CommandPipe.h"
#include "StrUtilities.h"
#include <string>
#include "RandomString.h"
#include "..\HammingDll\HammingDll.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Hamming_UnitTest
{		
	TEST_CLASS(Hamming_UnitTest)
	{
		TEST_CLASS_INITIALIZE(methodName)
		{
			srand(time(NULL) % UINT_MAX); //to prevent warning and possible data loss
		}
	private:

		void Hamming_Assert(const std::string& _str1, const std::string& _str2, int _expected, int _binMode  = false)
		{
			try
			{
				auto res = _binMode ? Hamming_dist_bin(_str1, _str2) : Hamming_dist_char(_str1, _str2);
				Assert::AreEqual(res, _expected, _binMode ? L"wild string" : to_wchar(_str1).c_str());
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
		template <class Itrator>
		void Hamming_Assert(Itrator beginA, Itrator endA, Itrator beginB, Itrator endB, int _expected, int _binMode = false)
		{
			try
			{
				auto res = _binMode ? Hamming_dist_bin_Itr(beginA, endA, beginB, endB) : Hamming_dist_sym_Itr(beginA, endA, beginB, endB);
				Assert::AreEqual(res, _expected);
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

		TEST_METHOD(TestEmpty)
		{
			Hamming_Assert("", "", 0);
		}

		TEST_METHOD(TestEmptyBin)
		{
			Hamming_Assert("", "", 0, true);
		}

		TEST_METHOD(TestExact)
		{
			Hamming_Assert("A", "A", 0, true);
		}

		TEST_METHOD(TestSingleChar)
		{
			Hamming_Assert("Test Me", "Test me", 1);
		}

		TEST_METHOD(TestSingleBit)
		{
			Hamming_Assert("B", "C", 1, true);
		}

		TEST_METHOD(TestUnEqualLength)
		{
			Hamming_Assert("Test Me", "Test    me", -1);
		}

		TEST_METHOD(RandomBlob_01)
		{
			auto str = RandomBlob::generate();
			auto copy = str;
			auto hamming_dist = RandomBlob::alter(copy);
			Hamming_Assert(str, copy, hamming_dist, true);
		}

		TEST_METHOD(RandomBlob_02)
		{
			auto str = RandomBlob::generate();
			auto copy = str;
			auto hamming_dist = RandomBlob::alter(copy);
			Hamming_Assert(str, copy, hamming_dist, true);
		}

		TEST_METHOD(RandomBlob_03_Int)
		{
			auto str = RandomBlob::generate_int();
			auto copy = str;
			auto hamming_dist = RandomBlob::alter_int(copy);
			Hamming_Assert(str.begin(), str.end(), copy.begin(), copy.end(), hamming_dist, true);
		}

		TEST_METHOD(RandomBlob_Loop)
		{
			for (int i = 0; i < 30; i++)
			{

				auto str = RandomBlob::generate(i * 100);
				auto copy = str;
				auto hamming_dist = RandomBlob::alter(copy);
				Hamming_Assert(str, copy, hamming_dist, true);
			}
		}

		TEST_METHOD(RandomBlob_Loop_int)
		{
			for (int i = 1; i < 30; i++)
			{
				auto str = RandomBlob::generate_int(i * 100);
				auto copy = str;
				auto hamming_dist = RandomBlob::alter_int(copy);
				Hamming_Assert(str.begin(), str.end(), copy.begin(), copy.end(), hamming_dist, true);
			}
		}

	};
}