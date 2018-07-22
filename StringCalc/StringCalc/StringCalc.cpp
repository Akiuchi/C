#include <stdio.h>
#include <string.h>
#include <math.h>

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

	printf("%s\n", calculatedString);

	return 0;
};

/*
 *	���͂�����������m�F��s_1, s_2�ɕ����B
 *	������As_1, s_2�̐擪��A�ɂȂ��Ă��Ȃ����m�F
 *	@method	checkInputParam
 *	@in		char[]	inputString	���͂��ꂽ������
 *	@out	char*	string1		���������������1��(s_1�ɑ���)
 *	@out	char*	string2		���������������2��(s_2�ɑ���)
 *	return	boolean	true:��������������̐擪��A�łȂ��Afalse:��������������̐擪��A(�G���[)
 */
static bool checkInputParam(const char *inputString, char* string1, char* string2)
{
	int inputStringLength = strlen(inputString);
	int count = 0;
	int name_count = 0;
	int hour_count = 0;

	//�X�y�[�X�܂œǂݍ��݁As_1��s_2�𕪊�
	for (int firstCount = 0; count < inputStringLength && inputString[count] != ' '; count++, firstCount++) {
		string1[firstCount] = inputString[count];
	}
	count++;
	for (int secondCount = 0 ; count < inputStringLength && inputString[count] != '\n'; count++, secondCount++) {
		string2[secondCount] = inputString[count];
	}

	if (strlen(string1) == 0 || (strlen(string1) > 1 && string1[0] == 'A')) {
		return false;
	}

	if (strlen(string2) == 0 || (strlen(string2) == 1 && string2[0] == 'A')) {
		return false;
	}

	return true;
}

/*
 *	���͂��ꂽ�������5�i���ɕϊ�
 *	@method	ConvertStringToQuinary
 *	@in		char*	string	�������ꂽ������
 *	@out	int*	quinary	�������5�i���ɕϊ�����int�z��
 *
 */
static int ConvertStringToQuinary(const char *string, int *quinary)
{
	// string�œn���Ă����������ǂݍ��݁A�e�����Ɉ�v����NUMBER��quinary�Ɋi�[
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

/*
 *	5�i����10�i���ɕϊ�
 *	@method	ConvertQuinaryToDecimal
 *	@in		int*	quinary			���͂��ꂽ�������5�i���ɕϊ������l���i�[����z��
 *	@out	int		quinaryLength	quinary�̔z��
 */
static int ConvertQuinaryToDecimal(const int *quinary, int quinaryLength)
{
	/* quinary�̒����r�߁Aquinary�̗v�f���̗ݏ��baseNum�Ƃ�
	   baseNum��quinary�̒��̒l���|�����킹�����̂�decimal�ɉ��Z*/
	int decimal = 0;
	int baseNum = 0;
	for (int count = 0; count < quinaryLength; count++) {
		baseNum = pow(5, (quinaryLength - (count + 1)));
		decimal += baseNum * quinary[count];

	}
	return decimal;
}

/**
 *	10�i����5�i���ɑ΂��镶���ɕϊ�
 *	@method ConvertDecimalToString
 *	@in		int		fullDecimal		���͂��ꂽ���������Z����10�i���̒l
 *	@out	char[]	string			10�i����5�i���ɑ΂��镶���ɕϊ�����������
 */
static void ConvertDecimalToString(int fullDecimal, char *string)
{
	int mod = 0;
	int devide = fullDecimal;
	int tempNumbers[MAX_NUM] = {};
	int decimalLength = 1;

	// fullDecimal��5�Ŋ������]��Ə��l��5�i���i�[�p��tempNumbers�ɏ����i�[���Ă���
	while (1) {
		mod = devide % 5;
		devide /= 5;
		tempNumbers[decimalLength] = mod;
		if (devide <= 5) {
			tempNumbers[decimalLength -1] = devide;
			decimalLength++;
			break;
		}
		decimalLength++;
	}

	// 5�i���ɕϊ����ꂽ�l�ɑ΂��镶����string�ɋl�߂Ă���
	for (int stringCount = 0; stringCount < decimalLength; stringCount++) {
		switch (tempNumbers[stringCount]) {
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