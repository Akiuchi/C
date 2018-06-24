#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define	MAX_ARRAY	(64)
#define LATEST_ARRIVAL_TIME_HOUR	(8)
#define LATEST_ARRIVAL_TIME_MINUTE	(59)

static int getArrivalTime(const char*);
static bool splittDepatureTime(const char*, int*, int*);

int main(void) {

	char arrivalTimeInfo[MAX_ARRAY];		//�o�Ђ̎��ԏ��
	char departureTime[MAX_ARRAY][MAX_ARRAY];		//�w���o�����鎞��
	int trainNum;							//�d�Ԃ̖{��
	int arrivalTime = 0;					//�o�Ђɂ����鑍����
	int latestHour = 0;						//�Œx�̏o�Ў��Ԃ̎�
	int latestMinute = 0;					//�Œx�̏o�Ў��Ԃ̕�

	//�o�Ђɂ����鎞�Ԃ����
	fgets(arrivalTimeInfo, sizeof(arrivalTimeInfo), stdin);
	arrivalTime = getArrivalTime(arrivalTimeInfo);
	if (arrivalTime == 0) {
		printf_s("Invalid Time\n");
		return 0;
	}

	//�d�Ԃ̖{�������
	scanf_s("%d", &trainNum);
	if (trainNum <= 0 || trainNum > 180) {
		printf_s("Invalid Param\n");
		return 0;
	}
	while (getchar() != '\n'); //�W�����͂̂��|��

	for (int count = 0; count < trainNum; count++) {		
		fgets(departureTime[count], sizeof(departureTime), stdin);
		
	}

	for (int count = 0; count < trainNum; count++) {
		int depatureHour = 0;
		int depatureMinute = 0;
		splittDepatureTime(departureTime[count], &depatureHour, &depatureMinute);
		depatureMinute += arrivalTime;
		if (depatureMinute >= 60) {
			depatureHour++;
			depatureMinute -= 60;
		}
		if (LATEST_ARRIVAL_TIME_HOUR < depatureHour || LATEST_ARRIVAL_TIME_MINUTE < depatureMinute) {
			break;
		} else {
			latestHour = depatureHour;
			latestMinute = depatureMinute;
		}
	}
	printf_s("%02d:%02d", latestHour, latestMinute);

	return 0;
}

/**
 * ���͂����o�Ў��Ԃ����v���ĕԋp
 * @param	timeInfo		���͂����o�Ў��Ԃ̏��
 * @return	arrivalTime		�o�Ў��Ԃ̑����v
*/
static int getArrivalTime(const char *timeInfo)
{
	int count = 0;
	int secondDecimal = 10;
	int arrivalTime = 0;
	int totalArrivalTime = 0;

	while (1) {
		char tempTimeChar = timeInfo[count];
		count++;
		if (tempTimeChar == ' '){
			secondDecimal = 10;
			totalArrivalTime = arrivalTime;
			continue;
		}
		if ( ((tempTimeChar < '0') || (tempTimeChar > '9') ) && tempTimeChar == '\n') {
			break;
		}
		if (timeInfo[count] == ' ' || timeInfo[count] == '\n') {
			secondDecimal = 1;
		}
		int tempTime = ((int)tempTimeChar - '0');
		arrivalTime += tempTime * secondDecimal;
		if (arrivalTime > 30) {
			return 0;
		}
		secondDecimal = 1;
	}
	return totalArrivalTime;
}

/**
* ���͂����d�Ԃ��w���o�����鎞�Ԃ����ƕ��ŕ���
* @in	depatureInfo	���͂����o�����Ԃ̏��
* @out	depatureHour	�d�Ԃ��w���o�����鎞
* @ou	depatureMinute	�d�Ԃ��w���o�����镪
*/
static bool splittDepatureTime(const char *depatureInfo, int *depatureHour, int *depatureMinute)
{
	int count = 0;
	int secondDecimal = 10;
	bool bMinute = false;

	//�X�y�[�X�܂œǂݍ��݁A�e���Ԃ𕪊�
	while (1) {
		char temp = depatureInfo[count];
		count++;
		if (temp == ' ') {
			secondDecimal = 10;
			bMinute = true;
			continue;
		}
		if (((temp < '0') || (temp > '9')) && temp == '\n') {
			break;
		}
		if (depatureInfo[count] == ' ' || depatureInfo[count] == '\n') {
			secondDecimal = 1;
		}
		int tempTime = ((int)temp - '0');
		if (bMinute) {
			*depatureMinute += tempTime * secondDecimal;
		} else {
			*depatureHour += tempTime * secondDecimal;
		}
		secondDecimal = 1;
	}

	return true;
}