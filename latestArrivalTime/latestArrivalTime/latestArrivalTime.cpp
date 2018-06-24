#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define	MAX_ARRAY	(64)
#define LATEST_ARRIVAL_TIME_HOUR	(8)
#define LATEST_ARRIVAL_TIME_MINUTE	(59)

static int getArrivalTime(const char*);
static bool splittDepatureTime(const char*, int*, int*);

int main(void) {

	char arrivalTimeInfo[MAX_ARRAY];		//出社の時間情報
	char departureTime[MAX_ARRAY][MAX_ARRAY];		//駅を出発する時間
	int trainNum;							//電車の本数
	int arrivalTime = 0;					//出社にかかる総時間
	int latestHour = 0;						//最遅の出社時間の時
	int latestMinute = 0;					//最遅の出社時間の分

	//出社にかかる時間を入力
	fgets(arrivalTimeInfo, sizeof(arrivalTimeInfo), stdin);
	arrivalTime = getArrivalTime(arrivalTimeInfo);
	if (arrivalTime == 0) {
		printf_s("Invalid Time\n");
		return 0;
	}

	//電車の本数を入力
	scanf_s("%d", &trainNum);
	if (trainNum <= 0 || trainNum > 180) {
		printf_s("Invalid Param\n");
		return 0;
	}
	while (getchar() != '\n'); //標準入力のお掃除

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
 * 入力した出社時間を合計して返却
 * @param	timeInfo		入力した出社時間の情報
 * @return	arrivalTime		出社時間の総合計
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
* 入力した電車が駅を出発する時間を時と分で分割
* @in	depatureInfo	入力した出発時間の情報
* @out	depatureHour	電車が駅を出発する時
* @ou	depatureMinute	電車が駅を出発する分
*/
static bool splittDepatureTime(const char *depatureInfo, int *depatureHour, int *depatureMinute)
{
	int count = 0;
	int secondDecimal = 10;
	bool bMinute = false;

	//スペースまで読み込み、各時間を分割
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