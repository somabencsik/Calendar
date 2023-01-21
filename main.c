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

void printMonth(int year, int month)
{
	//int spacing = 21 - strlen(getMonthName(month));
	//char* spaces = malloc(sizeof(char) * spacing + 1);
	//for (int i = 0; i < spacing; ++i)
	//	spaces[i] = ' ';
	//spaces[spacing] = '\0';
	
	//printf(" %s %s %s\n", getMonthName(month), spaces, getMonthName(month+1) );
	printf(" %s\n", getMonthName(month));
	for (int i = 0; i < 7; ++i)
	{
		printf(" %c ", getDayName(i)[0] );
	}
	
	printf("\n");

	int currentFirstDay = firstDayOfMonth(year, month);	
		
	for (int j = 0; j < currentFirstDay; ++j)
	{
		printf("   ");
	}
	printf(" 1 ");

	for (int j = 1; j < getNumberOfDaysAMonth(year, month); ++j )
	{
		if (( j - currentFirstDay + ( currentFirstDay * 2 ) ) % 7 == 0 && j != 0)
			printf("\t\n");
	
		if (j < 9)
			printf(" %d ", j+1);
		else if (j == 9)
			printf(" \b%d", j+1);
		else
			if (j == 10)
			{
				if (( 10 - currentFirstDay + ( currentFirstDay * 2 ) ) % 7 == 0 && 10 != 0) 
					printf("11 ");
				else
					printf(" 11 ");
			}
			else
				printf("%d ", j+1);
	}
	printf("\n");

	//memset(spaces, 0, sizeof(char) * spacing);
}

int main(void)
{
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int currentYear = tm.tm_year + 1900;
	int currentMonth = tm.tm_mon + 1;
	int currentDay = tm.tm_mday;
	
	printf("Current date: %d, %s, %s\n", currentYear, getMonthName(currentMonth), getDayName(currentDay) );
	printf("Start day of year: %s\n", getDayName( firstDayOfMonth(currentYear, 1) ) );
	printf("Days of current month: %d\n", getNumberOfDaysAMonth(currentYear, currentMonth) );

	printf("\n");

	for (int i = 0; i < 12; ++i)
	{
		printMonth(currentYear, i + 1);
	}

	return 0;
}
