#include "AnyType.h"

int main()
{
	AnyType atype1('b');
	cout << "atype1.get_type(): " << atype1.get_type() << endl;

	atype1 = 45;
	cout << "atype1.get_type(): " << atype1.get_type() << endl;

	try
	{
		atype1 = "hello";
		cout << "atype1.get_type(): " << atype1.get_type() << endl;
	}
	catch (bad_cast& exc)
	{
		cout << "\t/TYPE_GETTING ERROR: " << exc.what() << endl;
	}

	cout << "\n-----------------------------------------------------\n";

	try 
	{
		int value = atype1.extract_value<int>();
		cout << "atype1.extract_value(): " << value << endl;
	}
	catch (const bad_cast& ex)
	{
		cout << "\t/EXTRUCTION ERROR: " << ex.what() << endl;
	}

	try 
	{
		bool value = atype1.extract_value<bool>();
		cout << "atype1.extract_value(): " << value << endl;
	}
	catch (const bad_cast& ex) 
	{
		cout << "\t/EXTRUCTION ERROR: " << ex.what() << endl;
	}
	catch (const exception& ex)
	{
		cout << "\t/EXTRUCTION ERROR: " << ex.what() << endl;
	}

	cout << "\n-----------------------------------------------------\n";

	cout << "atype1.get_type(): " << atype1.get_type() << endl;
	AnyType atype2(true);
	cout << "atype2.get_type(): " << atype2.get_type() << endl;
	cout << "atype2 = atype1" << endl;
	atype2 = atype1;
	cout << "atype2.get_type(): " << atype2.get_type() << endl;

	cout << "\n-----------------------------------------------------\n";

	AnyType atype3(20.20);
	AnyType atype4('Y');
	cout << "atype3.get_type(): " << atype3.get_type() << endl;
	cout << "atype4.get_type(): " << atype4.get_type() << endl;
	cout << "atype3.swap(atype4)" << endl;
	atype3.swap(atype4);
	cout << "atype3.get_type(): " << atype3.get_type() << endl;
	cout << "atype4.get_type(): " << atype4.get_type() << endl;


	return 0;
}
