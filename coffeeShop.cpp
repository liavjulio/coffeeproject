#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

#define MENU_CASES_NUM 6
#define DEPOSITE_MONEY_CASES_NUM 6
#define ADMIN_CASES_NUM 3
#define PIN_CASES_NUM 2
#define ENTER 13
#define Winner 1


#define MAX_COUNT_PIN_INPUT 3

#define SLEEP 50

void showMainMenu(double userBalance, int ESPRESSO_PRICE, int CAPPUCCINO_PRICE, int LATTE_PRICE);
void showDepositeMenu(double userBalance);
void showAdminMenu(double shopBalance, int cups);
void showPinMenu();
void pauseConsole();
void showBalance(double balance);
void showCupsNumber(int cups);
void showWithdrawMoneyMessage(double shopBalance);

int getChoice();

bool isEnoughMoneyToBuy(double userBalance, double coffeePrice);
double buyCoffee(double userBalance, double price, int& countorder);

int inputPIN(int pin);
bool isPinValid(int pin, int& PIN);

int addCups(int addedCups);
bool isNumberAddedCupsCorrect(int addedCups);

void showProgressBar();
void showCursor(bool showCursor);

void showErrorMessage(int errorNum);
void showErrorMessageWithParametr(int errorNum, double parametr);

void Set_Price(double& ESPRESSO_PRICE, double& CAPPUCCINO_PRICE, double& LATTE_PRICE);

void Change_PIN(int& PIN);

bool Check_Winner(double& userBalance, int& countorder);

int main()
{
	double ESPRESSO_PRICE = 1, CAPPUCCINO_PRICE = 1.5, LATTE_PRICE = 1.5;
	int countorder = 0;
	int PIN = 1234;
	int cups = 7, addedCups = 0, pin = 0, countPinInput = 0, menuChoice, depositeChoise, adminChoice, pinChoice;
	double userBalance = 0.0, shopBalance = 0.0;
	bool mainMenu = true, depositeMenu, adminMenu, pinMenu;

	while (mainMenu)
	{
		showMainMenu(userBalance, ESPRESSO_PRICE, CAPPUCCINO_PRICE, LATTE_PRICE);
		menuChoice = getChoice();

		switch (menuChoice)
		{
		case 1:
			if (cups <= 0) {
				showErrorMessage(1);
			}
			else {
				depositeMenu = true;

				while (depositeMenu)
				{
					showDepositeMenu(userBalance);
					depositeChoise = getChoice();

					switch (depositeChoise)
					{
					case 1:
						userBalance += 0.10;
						shopBalance += 0.10;
						break;
					case 2:
						userBalance += 0.20;
						shopBalance += 0.20;
						break;
					case 3:
						userBalance += 0.50;
						shopBalance += 0.50;
						break;
					case 4:
						userBalance += 1.0;
						shopBalance += 1.0;
						break;
					case 5:
						userBalance += 2.0;
						shopBalance += 2.0;
						break;
					case 6:
						depositeMenu = false;
						break;
					default:
						showErrorMessageWithParametr(3, DEPOSITE_MONEY_CASES_NUM);
						break;
					}
				}
			}
			break;
		case 2:
			if (cups <= 0)
			{
				showErrorMessage(1);
			}
			else if (isEnoughMoneyToBuy(userBalance, ESPRESSO_PRICE))
			{
				showProgressBar();
				userBalance = buyCoffee(userBalance, ESPRESSO_PRICE, countorder);
				cups--;
			}
			else
			{
				showErrorMessageWithParametr(1, ESPRESSO_PRICE - userBalance);
			}
			break;
		case 3:
			if (cups <= 0)
			{
				showErrorMessage(1);
			}
			else if (isEnoughMoneyToBuy(userBalance, CAPPUCCINO_PRICE))
			{
				showProgressBar();
				userBalance = buyCoffee(userBalance, CAPPUCCINO_PRICE, countorder);
				cups--;
			}
			else
			{
				showErrorMessageWithParametr(1, CAPPUCCINO_PRICE - userBalance);
			}
			break;
		case 4:
			if (cups <= 0)
			{
				showErrorMessage(1);
			}
			else if (isEnoughMoneyToBuy(userBalance, LATTE_PRICE))
			{
				showProgressBar();
				userBalance = buyCoffee(userBalance, LATTE_PRICE, countorder);
				cups--;
			}
			else
			{
				showErrorMessageWithParametr(1, LATTE_PRICE - userBalance);
			}
			break;
		case 5:
			pinMenu = true;

			while (pinMenu)
			{
				showPinMenu();
				pinChoice = getChoice();

				switch (pinChoice)
				{
				case 1:
					pin = inputPIN(pin);
					adminMenu = isPinValid(pin, PIN);

					if (!adminMenu)
					{
						countPinInput++;
						if (countPinInput >= MAX_COUNT_PIN_INPUT)
						{
							showErrorMessageWithParametr(2, countPinInput);
							showErrorMessage(4);
							return 0;
						}

						showErrorMessageWithParametr(2, countPinInput);
						pauseConsole();
					}

					while (adminMenu)
					{
						showAdminMenu(shopBalance, cups);
						adminChoice = getChoice();

						switch (adminChoice)
						{
						case 1:
							if (shopBalance == 0) {
								showErrorMessage(5);
							}
							else {
								showWithdrawMoneyMessage(shopBalance);
								shopBalance = 0;
								userBalance = 0;
							}
							break;
						case 2:
							addedCups = addCups(addedCups);

							while (!isNumberAddedCupsCorrect(addedCups))
							{
								showErrorMessage(3);
								addedCups = addCups(addedCups);
							}

							cups += addedCups;
							break;
						case 3:
							Set_Price(ESPRESSO_PRICE, CAPPUCCINO_PRICE, LATTE_PRICE);
							break;
						case 4:
							Change_PIN(PIN);
						case 5:
							adminMenu = false;
							pinMenu = false;
							break;
						default:
							showErrorMessageWithParametr(3, ADMIN_CASES_NUM);
							break;
						}
					}
					break;
				case 2:
					pinMenu = false;
					break;
				default:
					showErrorMessageWithParametr(3, PIN_CASES_NUM);
					break;
				}
			}
			break;
		case 6:
			mainMenu = false;
			break;
		default:
			showErrorMessageWithParametr(3, MENU_CASES_NUM);
			break;
		}
	}

	return 0;
}



void showMainMenu(double userBalance, int ESPRESSO_PRICE, int CAPPUCCINO_PRICE, int LATTE_PRICE)
{
	system("cls");
	cout << "Welcome to CoffeeShop!" << endl;
	cout << "------------------------" << endl;
	showBalance(userBalance);
	cout << "------------------------" << endl;
	cout << "1. Deposit money" << endl;
	cout << "2. Espresso  	 " << ESPRESSO_PRICE << " $" << endl;
	cout << "3. Cappuccino	 " << CAPPUCCINO_PRICE << " $" << endl;
	cout << "4. Latte     	 " << LATTE_PRICE << " $" << endl;
	cout << "5. Service" << endl;
	cout << "6. Exit from shop" << endl;
	cout << "------------------------" << endl;
}

void showDepositeMenu(double userBalance)
{
	system("cls");
	cout << "Deposite money!" << endl;
	cout << "The machine doesn't give change!" << endl;
	cout << "------------------------" << endl;
	showBalance(userBalance);
	cout << "------------------------" << endl;
	cout << "1. 0.1 $" << endl;
	cout << "2. 0.2 $" << endl;
	cout << "3. 0.5 $" << endl;
	cout << "4. 1.0 $" << endl;
	cout << "5. 2.0 $" << endl;
	cout << "6. Back to main menu" << endl;
	cout << "------------------------" << endl;
}

void showAdminMenu(double shopBalance, int cups)
{
	system("cls");
	cout << "Admin panel!" << endl;
	cout << "------------------------" << endl;
	showBalance(shopBalance);
	showCupsNumber(cups);
	cout << "------------------------" << endl;
	cout << "1. Take money from shop" << endl;
	cout << "2. Add cups" << endl;
	cout << "3. Change price" << endl;
	cout << "4. Change PIN" << endl;
	cout << "5. Back to main menu" << endl;
	cout << "------------------------" << endl;
}

void showPinMenu()
{
	system("cls");
	cout << "Pin confirmation!" << endl;
	cout << "------------------------" << endl;
	cout << "1. Enter pin" << endl;
	cout << "2. Exit to main menu" << endl;
	cout << "------------------------" << endl;
}

void pauseConsole()
{
	do
	{
		cout << "Press the Enter key to continue." << endl;
	} while (_getch() != ENTER);
}

void showBalance(double balance)
{
	cout << "Current balance: " << balance << " $" << endl;
}

void showCupsNumber(int cups)
{
	cout << "Current cups number: " << cups << endl;
}

void showWithdrawMoneyMessage(double shopBalance)
{
	cout << shopBalance << " $ was received." << endl;
	pauseConsole();
}

int getChoice()
{
	int choice;

	cout << "Your choice: ";
	cin >> choice;

	return choice;
}

bool isEnoughMoneyToBuy(double userBalance, double coffeePrice)
{
	return coffeePrice <= userBalance;
}

double buyCoffee(double userBalance, double price, int& countorder)
{
	if (Check_Winner(userBalance, countorder) == 1)
	{
		return userBalance;
	}
	return userBalance - price;
}

int inputPIN(int pin)
{
	cout << "Input PIN to enter service panel: ";
	cin >> pin;

	return pin;
}

bool isPinValid(int pin, int& PIN)
{
	return pin == PIN;
}

int addCups(int addedCups)
{
	cout << "How many cups do want to add? ";
	cin >> addedCups;

	return addedCups;
}

bool isNumberAddedCupsCorrect(int addedCups)
{
	return addedCups > 0;
}

void showProgressBar()
{
	showCursor(false);
	char chars[] = "|/-\\";

	for (int percent = 0, j = 0; percent <= 100; percent++)
	{
		cout << "Cooking coffee! Progress [" << percent << "%] " << chars[j++] << "\r";
		Sleep(SLEEP);
		if (j == 4) { j = 0; }
	}

	showCursor(true);
	cout << "Coffee done! You can take it.    " << endl;
}

void showCursor(bool visible)
{
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = visible;
	SetConsoleCursorInfo(handle, &structCursorInfo);
}

void showErrorMessage(int errorNum)
{
	switch (errorNum)
	{
	case 1:
		cout << "Sorry we don't have cups. Contact service, please." << endl;
		pauseConsole();
		break;
	case 2:
		cout << "Deposited money can't be less than 1." << endl;
		break;
	case 3:
		cout << "Added number of cups can't be less or equal to 0." << endl;
		break;
	case 4:
		cout << "Coffee Shop is locked. Contact service, please." << endl;
		break;
	case 5:
		cout << "No money on balance." << endl;
		pauseConsole();
		break;
	}
}

void showErrorMessageWithParametr(int errorNum, double parametr)
{
	switch (errorNum)
	{
	case 1:
		cout << "Not enough money to buy coffee!" << endl;
		cout << "To buy, you need to deposit " << parametr << " $ more." << endl;
		pauseConsole();
		break;
	case 2:
		cout << "PIN isn't correct! You have " << MAX_COUNT_PIN_INPUT - parametr << " attempts." << endl;
		break;
	case 3:
		cout << "Incorrect input. Enter number 1..." << parametr << "!" << endl;
		pauseConsole();
		break;
	}
}

void Set_Price(double& ESPRESSO_PRICE, double& CAPPUCCINO_PRICE, double& LATTE_PRICE)
{
	int choise, price;
	cout << "which product you want to change ?" << endl;
	cout << "1- espresso , 2- cappuccino , 3- latte , 4- exit" << endl;
	cin >> choise;
	while (choise != 4)
	{
		if (choise == 1)
		{
			cout << "enter new price" << endl;
			cin >> price;
			ESPRESSO_PRICE = price;
		}
		else if (choise == 2)
		{
			cout << "enter new price" << endl;
			cin >> price;
			CAPPUCCINO_PRICE = price;
		}
		else if (choise == 3)
		{
			cout << "enter new price" << endl;
			cin >> price;
			LATTE_PRICE = price;
		}
		cout << "1- espresso , 2- cappuccino , 3- latte , 4- exit" << endl;
		cin >> choise;
	}


}

void Change_PIN(int& PIN)
{
	cout << "Enter your new PIN" << endl;
	cin >> PIN;
}

bool Check_Winner(double& userBalance, int& countorder)
{
	countorder++;
	if (countorder == Winner)
	{
		cout << "Congratulations you are The 3 custumer now you can order one free coffe" << endl;
		countorder = 0;
		pauseConsole();
		return true;
	}
	pauseConsole();
	return false;
}
