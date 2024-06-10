#include "log.h"


void output(string output, int type)
{
	std::time_t currentTime;
	std::time(&currentTime);
	std::tm* localTime = std::localtime(&currentTime);

	char buffer[20]; // Slightly larger buffer for milliseconds

	// Get current time with milliseconds
	auto now = std::chrono::system_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

	// Format the time including milliseconds
	std::strftime(buffer, sizeof(buffer), "%H:%M:%S", localTime);
	std::sprintf(buffer + 8, ".%03lld", ms.count()); // Append milliseconds to the buffer
	int outputtype = type;
	string message = output;
	switch (outputtype)
	{
	case 1:
	{
		cout << GREEN << "[" << buffer << "]" << RESET  <<  "| " << message << RESET << endl;
		ZeroMemory(&buffer, 20);
		break;
	}
	case 2:
	{
		cout << RED << "[" << buffer << "]" << RESET << "| "  << message << RESET << endl;
		ZeroMemory(&buffer, 20);

		break;
	}
	case 3:
	{
		cout << YELLOW << "[" << buffer << "]" << RESET <<  "| " << message << RESET << endl;
		ZeroMemory(&buffer, 20);

		break;
	}

	default:
	{
		cout << YELLOW << "!!! INVAILD PARAMS !!!" << RESET << endl;
		break;
	}
	}
}
void logger::error(string message, bool getlasterror)
{
	std::string data = message; 

	if (getlasterror) {
		DWORD error = GetLastError();
		data += " Error : " + std::to_string(error);
	}
	// output error
	output(data, 2);
}

void logger::success(string message)
{
	string data = message;
	output(data, 1);
}

void logger::warning(string message)
{
	string data = message;
	output(data,3);
} 

void moduletestfunc()
{
	Sleep(1000);
}
void logger::test()
{
	cout << "!!! MODULE TEST !!!" << endl;
	SetLastError(60000);
	error("A error occured during setup.", true);
	success("Loaded 55 files!");
	warning("User is not logged in but has access to data!");
	trackfunctionspeed(moduletestfunc);
	//threadfunction(moduletestfunc,true);
	Sleep(5000);
	success("All modules worked!");
}

void logger::threadfunction(FuncPtr func,bool detach)
{
	thread t1(func);
	t1.join();
	if (detach == true)
	{
		t1.detach();
	}

}

void logger::trackfunctionspeed(FuncPtr func)
{

	auto start = std::chrono::high_resolution_clock::now();
	func();
	auto end = std::chrono::high_resolution_clock::now();
	chrono::duration<double> timetook = end - start;
	std::time_t currentTime;
	std::time(&currentTime);
	std::tm* localTime = std::localtime(&currentTime);

	char buffer[20];
	auto now = std::chrono::system_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

	std::strftime(buffer, sizeof(buffer), "%H:%M:%S", localTime);
	std::sprintf(buffer + 8, ".%03lld", ms.count());
	

	std::cout << GREEN << "[" << buffer << "]" << RESET << "| "
		<< func << " took : " << timetook.count() << " seconds" << RESET << std::endl;
	ZeroMemory(&buffer, 20);
}