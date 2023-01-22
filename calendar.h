#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

char* getDayName(int num)
{
	switch (num%7)
	{
		case 0:
		{
			return "Monday";
		} break;
		case 1:
		{
			return "Tuesday";
		} break;
		case 2:
		{
			return "Wednesday";
		} break;
		case 3:
		{
			return "Thursday";
		} break;
		case 4:
		{
			return "Friday";
		} break;
		case 5:
		{
			return "Saturday";
		} break;
		case 6:
		{
			return "Sunday";
		} break;
	}
	return "Wrong Number";
}

char* getMonthName(int num)
{
	switch (num)
	{
		case 1:
		{
			return "January";
		} break;
		case 2:
		{
			return "February";
		} break;
		case 3:
		{
			return "March";
		} break;
		case 4:
		{
			return "April";
		} break;
		case 5:
		{
			return "May";
		} break;
		case 6:
		{
			return "June";
		} break;
		case 7:
		{
			return "July";
		} break;
		case 8:
		{
			return "August";
		} break;
		case 9:
		{
			return "September";
		} break;
		case 10:
		{
			return "October";
		} break;
		case 11:
		{
			return "November";
		} break;
		case 12:
		{
			return "December";
		} break;
	}
	return "Wrong Number";
}

int firstDayOfMonth(int year, int month)
{
	if (month == 1 || month == 2)
	{
		month = 12 + month;
		--year;
	}
	int day = 1 + 2*(month) + 3*(month + 1)/5 + year + (year / 4) - (year / 100) + (year / 400) + 2;
	day = (day + 5) % 7;
	return day;
}

int getNumberOfDaysAMonth(int year, int month)
{
	if (month == 2)
	{
		if (year % 4 == 0)
			return 29;
		else
			return 28;
	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
		return 30;
	else
		return 31;
}

void printOutWeekDays(int times, char* spaces)
{
	for (int i = 0; i < times; ++i)
	{
		for (int j = 0; j < 7; ++j)
		{
			printf(" %c ", getDayName(j)[0] );
		}
		printf("%s", spaces);
	}
}

char* getMonthRow(int year, int month, int row)
{
	char* monthRow = malloc(sizeof(char) * 21);
	int currChar = 0;
 
	int currentFirstDay = firstDayOfMonth(year, month);

	if (row == 0)
	{
		for (int i = 0; i < currentFirstDay; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				monthRow[currChar] = ' ';
				++currChar;
			}
		}
		monthRow[currChar] = ' ';
		monthRow[currChar + 1] = '1';
		monthRow[currChar + 2] = ' ';
		currChar += 3;
	}
	int currRow = 0;
	for (int j = 1; j < getNumberOfDaysAMonth(year, month); ++j )
	{
		if (( j - currentFirstDay + ( currentFirstDay * 2 ) ) % 7 == 0 && j != 0)
			++currRow;

		if (currRow != row)
			continue;

		if (j < 9)
		{
			monthRow[currChar] = ' ';
			monthRow[currChar + 1] = (j + 1) + '0';
			monthRow[currChar + 2] = ' ';
			currChar += 3;
		}
		else if (j == 9)
		{
			monthRow[currChar] = ' ';
			monthRow[currChar + 1] = '\b';
			monthRow[currChar + 2] = '1';
			monthRow[currChar + 3] = '0';
			currChar += 4;
		}
		else
			if (j == 10)
			{
				if (( 10 - currentFirstDay + ( currentFirstDay * 2 ) ) % 7 == 0 && 10 != 0) 
				{
					monthRow[currChar] = '1';
					monthRow[currChar + 1] = '1';
					monthRow[currChar + 2] = ' ';
					currChar += 3;
				}
				else
				{
					monthRow[currChar] = ' ';
					monthRow[currChar + 1] = '1';
					monthRow[currChar + 2] = '1';	
					monthRow[currChar + 3] = ' ';
					currChar += 4;
				}
			}
			else
			{
				char str[3];
				sprintf(str, "%d", j + 1);
				
				monthRow[currChar] = str[0];
				monthRow[currChar + 1] = str[1];
				monthRow[currChar + 2] = ' ';
				currChar += 3;
			}
	}

	monthRow[currChar] = '\0';
	return monthRow;
}

void printMonth(int year, int month, int times)
{
	int spacing = 24 - strlen(getMonthName(month));
	char* spaces = malloc(sizeof(char) * spacing);
	for (int i = 0; i < spacing; ++i)
		spaces[i] = ' ';
	spaces[spacing] = '\0';
	
	for (int i = 0; i < times; ++i)
	{
		printf(" %s", getMonthName(month + i) );
		spacing = 20 - strlen(getMonthName(month + i)) + 1;
		char* spaces = malloc(sizeof(char) * spacing);
		for (int i = 0; i < spacing; ++i)
			spaces[i] = ' ';
		spaces[spacing] = '\0';
		printf("%s", spaces);
	}
	printf("\n");

	spacing = 1;
	spaces = malloc(sizeof(char) * spacing);
	for (int i = 0; i < spacing; ++i)
		spaces[i] = ' ';
	spaces[spacing] = '\0';
	
	printOutWeekDays(times, spaces);
	printf("\n");
	
	int currentFirstDay = firstDayOfMonth(year, month);	

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < times; ++j)
		{
			char* row = getMonthRow(year, month + j, i);
			printf("%s", row);

			spacing = 20 - strlen(row);

			if (i == 4)
				spacing += 2;

			for (int k = 0; k < spacing; ++k)
				spaces[k] = ' ';
			spaces[spacing] = '\0';

			printf("%s", spaces);
		}
		printf("\n");
	}	

	printf("\n");
	memset(spaces, 0, sizeof(char) * (spacing + 1) );
}

void printCalendar(int year)
{
	int monthsInRow = 3;
	for (int i = 0; i < 12; i = i + monthsInRow)
		printMonth(year, i + 1, monthsInRow);
}

int getCurrentYear(void)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	return tm.tm_year + 1900;
}

int getCurrentMonth(void)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	return tm.tm_mon + 1;
}

int getCurrentDay(void)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	return tm.tm_mday;
}
