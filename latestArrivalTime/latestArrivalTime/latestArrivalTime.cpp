#include <stdio.h>
#include <string.h>

#define	MAX_ARRAY	(32)

static bool checkInputParam(const char*, char*, char*);

int main(void) {

	char arrivalTimeInfo;					//出社の時間情報
	char departureTime[MAX_ARRAY] = "";		//駅を出発する時間
	int trainNum;							//電車の本数

	//出社にかかる時間を入力
	fgets(&arrivalTimeInfo, sizeof(arrivalTimeInfo), stdin);

	//電車の本数を入力
	scanf_s("%d", &trainNum);

	return 0;
}

static bool checkInputParam(const char *country_info, char* country_name, char* country_hour)
{
	int country_info_length = strlen(country_info);
	int count = 0;
	int name_count = 0;
	int hour_count = 0;

	//スペースまで読み込み、国名と時間を分割
	for (name_count = 0; count < country_info_length && country_info[count] != ' '; count++, name_count++) {
		country_name[name_count] = country_info[count];
	}

	for (count++, hour_count = 0; count < country_info_length && country_info[count] != '\n'; count++, hour_count++) {
		country_hour[hour_count] = country_info[count];
	}

	return true;
}