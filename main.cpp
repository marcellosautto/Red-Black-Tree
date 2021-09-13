#include "rbt.h"

int main()
{
	rbt rbt;
	cout << "MAKE SURE TO USE FULL SCREEN WHEN RUNNING THE PROGRAM" << endl;
	Sleep(1000);
	cout << endl << "LOADING...";
	Sleep(1000);
	system("cls");
	rbt.menu();
	rbt.run();
	while (rbt.number != 0)
		rbt.run();

	return 0;
}