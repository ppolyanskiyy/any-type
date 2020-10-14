#include "pch.h"
#include "CppUnitTest.h"
#include"..\Any Type\AnyType.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AnyTypeUnitTest
{
	TEST_CLASS(AnyTypeUnitTest)
	{
	public:
		TEST_METHOD(GetTypeIntTest1)
		{
			AnyType to_test(10);
			to_test = 't';
			Assert::AreNotEqual(string("int"), to_test.get_type());
		}
		TEST_METHOD(GetTypeIntTest2)
		{
			AnyType to_test(10);
			Assert::AreEqual(string("int"), to_test.get_type());
		}
		TEST_METHOD(GetTypeCharTest1)
		{
			AnyType to_test('t');
			to_test = true;
			Assert::AreNotEqual(string("char"), to_test.get_type());
		}
		TEST_METHOD(GetTypeCharTest2)
		{
			AnyType to_test('1');
			Assert::AreEqual(string("char"), to_test.get_type());
		}
		TEST_METHOD(GetTypeBoolTest1)
		{
			AnyType to_test(true);
			to_test = 25.5;
			Assert::AreNotEqual(string("bool"), to_test.get_type());
		}
		TEST_METHOD(GetTypeBoolTest2)
		{
			AnyType to_test(true);
			Assert::AreEqual(string("bool"), to_test.get_type());
		}
		TEST_METHOD(GetTypeDoubleTest1)
		{
			AnyType to_test('5');
			Assert::AreNotEqual(string("double"), to_test.get_type());
		}
		TEST_METHOD(GetTypeDoubleTest2)
		{
			AnyType to_test(10.0);
			Assert::AreEqual(string("double"), to_test.get_type());
		}

		TEST_METHOD(ExtractIntTest)
		{
			AnyType to_test(10);
			int data = to_test.extract_value<int>();
			Assert::AreEqual(10, data);
		}
		TEST_METHOD(ExtractCharTest)
		{
			AnyType to_test('a');
			char data = to_test.extract_value<char>();
			Assert::AreEqual('a', data);
		}
		TEST_METHOD(ExtractBoolTest)
		{
			AnyType to_test(true);
			bool data = to_test.extract_value<bool>();
			Assert::AreEqual(true, data);
		}
		TEST_METHOD(ExtractDoubleTest)
		{
			AnyType to_test(10.10);
			double data = to_test.extract_value<double>();
			Assert::AreEqual(10.10, data);
		}
		TEST_METHOD(ExtractValueException1)
		{
			AnyType to_test(10);
			try 
			{
				bool data = to_test.extract_value<bool>();
			}
			catch (exception& ex)
			{
				Assert::AreEqual("bad variant access", ex.what());
			}			
		}
		TEST_METHOD(ExtractValueException2)
		{
			AnyType to_test(true);
			Assert::ExpectException<bad_variant_access>([&] {to_test.extract_value<int>(); });
		}
		TEST_METHOD(ExtractValueException3)
		{
			AnyType to_test(10);
			Assert::ExpectException<bad_cast>([&] {to_test = "bad"; });
		}
	};
}
