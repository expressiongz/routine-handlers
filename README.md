# routine-handlers
argumented and unargumented routine handlers.

# example usage:
```cpp
#include <iostream>
#include <Windows.h>
#include "argumented_routine_handler.h"
#include "routine_handler.h"
int main()
{
	argumented_routine_handler<void(const char*, const char*)> arg_routine_handler{};
	routine_handler<void()> reg_routine_handler{};
	std::tuple args{ "exprssn's", "argumented routine handler!" };
	arg_routine_handler.insert_routine("print", std::make_pair([](const char* str1, const char* str2)
	{
			std::cout << str1 << " " << str2 << "\n";
	}, &args));

	arg_routine_handler.call_routine<const char*, const char*>("print");
	std::cout << "argumented routine handler object currently has " << arg_routine_handler.return_routine_map_sz() << " routine(s)\n";


	reg_routine_handler.add_routine("set_console_title", []
	{
		SetConsoleTitleA("exprssn's routine handlers");
		std::cout << "set_console_title called\n";
	});

	reg_routine_handler.add_routine("unset_console_title", []
	{
			SetConsoleTitleA("sxspectgzzly.");
			std::cout << "unset_console_title called\n";
	});

	std::cout << "routine handler object currently has " << reg_routine_handler.return_routine_map_sz() << " routine(s)\n";

	reg_routine_handler.call_routine("set_console_title");
	Sleep(1750);
	reg_routine_handler.call_routine("unset_console_title");
	system("pause");	
	return 0;
}
```
