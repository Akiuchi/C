#include <stdio.h>
#include <string.h>

#define MAX_NUM (32)
#define A_NUMBER (0)
#define B_NUMBER (1)
#define C_NUMBER (2)
#define D_NUMBER (3)
#define E_NUMBER (4)

static int ConvertQuinaryToDecimal(const int*, int);
static int ConvertStringToQuinary(const char*, int*);
static void ConvertDecimalToString(int ,char*);
static bool checkInputParam(const char*, char*, char*);

 int main(void)
 {
	char inputString[MAX_NUM] = "";
	char calculatedString[MAX_NUM] = "";
	char string1[MAX_NUM] = "";
	char string2[MAX_NUM] = "";
	int firstQuinary[MAX_NUM] = {};
	int secondQuinary[MAX_NUM] = {};
	int firstDecimal = 0;
	int secondDecimal = 0;
	int fullDecimal = 0;
	int firstStringLength = 0;
	int secondStringLength = 0;

	printf_s("Input\n");
	fgets(inputString, sizeof(inputString), stdin);
	if (strlen(inputString) == 0 || !checkInputParam(inputString, string1, string2)) {
		printf_s("Pleas Input Correct Param\n");
		return 0;
	}
	firstStringLength = ConvertStringToQuinary(string1, firstQuinary);
	secondStringLength = ConvertStringToQuinary(string2, secondQuinary);

	firstDecimal = ConvertQuinaryToDecimal(firstQuinary, firstStringLength);
	secondDecimal = ConvertQuinaryToDecimal(secondQuinary, secondStringLength);

	fullDecimal = firstDecimal + secondDecimal;

	ConvertDecimalToString(fullDecimal, calculatedString);

	printf("%s", calculatedString);

	return 0;
};

static bool checkInputParam(const char *inputString, char* string1, char* string2)
{
	int inputStringLength = strlen(inputString);
	int count = 0;
	int name_count = 0;
	int hour_count = 0;

	//スペースまで読み込み、s_1とs_2を分割
	for (int firstCount = 0; count < inputStringLength && inputString[count] != ' '; count++, firstCount++) {
		string1[firstCount] = inputString[count];
	}
	count++;
	for (int secondCount = 0 ; count < inputStringLength && inputString[count] != '\n'; count++, secondCount++) {
		string2[secondCount] = inputString[count];
	}

	if (strlen(string1) == 0 || (strlen(string1) > 1 && string1[strlen(string1)] == 'A')) {
		return false;
	}

	if (strlen(string2) == 0 || (strlen(string2) == 1 && string2[strlen(string2)] == 'A')) {
		return false;
	}

	return true;
}

static int ConvertStringToQuinary(const char *string, int *quinary) {
	int stringLength = strlen(string);
	for (int count = 0; count < stringLength; count++) {
		switch (string[count]) {
			case 'A':
				quinary[count] = A_NUMBER;
				break;
			case 'B':
				quinary[count] = B_NUMBER;
				break;
			case 'C':
				quinary[count] = C_NUMBER;
				break;
			case 'D':
				quinary[count] = D_NUMBER;
				break;
			case 'E':
				quinary[count] = E_NUMBER;
				break;
		}
	}
	return stringLength;
}

static int ConvertQuinaryToDecimal(const int *quinary, int quinaryLength)
{
	int decimal = 0;
	for (int count = 0; count < quinaryLength; count++) {
		decimal += ((quinaryLength - count) * 5) * quinary[count];

	}
	return decimal;
}

static void ConvertDecimalToString(int fullDecimal, char *string)
{
	int mod = 0;
	int devide = fullDecimal;
	int tempNumbers[MAX_NUM];
	int count = 0;
	int decimalLength = 0;

	while (1) {
		mod = devide % 5;
		devide /= 5;
		tempNumbers[count] = mod;
		if (devide <= 5) {
			tempNumbers[count] = devide;
			break;
		} else {
			count++;
		}
	}

	decimalLength = sizeof tempNumbers / sizeof tempNumbers[0];

	for (int stringCount = 0; decimalLength >= 0; decimalLength--, stringCount++) {
		switch (tempNumbers[decimalLength]) {
		case A_NUMBER:
			string[stringCount] = 'A';
			break;
		case B_NUMBER:
			string[stringCount] = 'B';
			break;
		case C_NUMBER:
			string[stringCount] = 'C';
			break;
		case D_NUMBER:
			string[stringCount] = 'D';
			break;
		case E_NUMBER:
			string[stringCount] = 'E';
			break;
		}
	}
}