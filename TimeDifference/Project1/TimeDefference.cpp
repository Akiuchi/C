/*
* Timedefference.cpp
*      Author: akira
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAX_NUM			(32)

typedef struct {
	char	country_hour[MAX_NUM] = "";
	char	country_name[MAX_NUM] = "";
} COUNTRY;

static bool checkInputParam(const char*, char*, char*);
static bool checkCountryName(const char*);
static bool chackCountryHour(const char*);

int main(void) {

	COUNTRY *country_array = NULL;
	int input_num = 0;
	int country_num = 0;
	int base_hour = 0;
	int base_minute = 0;
	char country_info[MAX_NUM] = "";
	char country_name[MAX_NUM] = "";
	char country_hour[MAX_NUM] = "";

	printf_s("How Many Country?> ");
	scanf_s("%d", &country_num);

	if (country_num <= 0 || country_num > 100)
	{
		printf_s("error Param\n");
		return 0;
	}

	country_array = (COUNTRY*)realloc(country_array, country_num);
	while (getchar() != '\n'); //標準入力のお掃除

	printf_s("Input\n");
	for (;input_num != country_num; input_num++) {

		fgets(country_info, sizeof(country_info), stdin);
		if (!checkInputParam(country_info, country_name, country_hour)) {
			printf_s("Pleas Input Correct Param\n");
			return 0;
		}

		strcpy_s(country_array[input_num].country_name, country_name);
		strcpy_s(country_array[input_num].country_hour, country_hour);
	}

	//所在地都市の入力
	fgets(country_info, sizeof(country_info), stdin);
	if (!checkInputParam(country_info, country_name, country_hour)) {
		printf_s("Pleas Input Correct Param\n");
		return 0;
	}

	printf_s("Output\n");

	//基準となる時と分の計算
	for (int hour_count = 0; hour_count < strlen(country_hour); hour_count++) {
		int first_hour_digit	= 0; //時1桁目
		int second_hour_digit	= 0; //時2桁目
		int first_minute_digit	= 0; //分1桁目
		int second_minute_digit = 0; //分2桁目
		if (country_hour[hour_count] == ':') {
			first_hour_digit	= (country_hour[hour_count - 1] - '0');
			second_hour_digit	= (country_hour[hour_count - 2] - '0');
			base_hour += (second_hour_digit*10);
			base_hour += first_hour_digit;

			first_minute_digit	= (country_hour[hour_count + 2] - '0');
			second_minute_digit = (country_hour[hour_count + 1] - '0');
			base_minute += (second_minute_digit * 10);
			base_minute += first_minute_digit;
			break;
		}
	}

	//入力された国、時の出力
	for (int count = 0; count < country_num; count++)
	{
		int fixed_hour = 0; //時間補正用
		int hour_length = strlen(country_array[count].country_hour);
		bool bNegative = false;
		//最後の国以外は時間を補正し、最後の国はそのまま出力。
		if (count != country_num) {
			int first_hour_digit = 0; //時1桁目
			int second_hour_digit = 0; //時2桁目
			if (country_array[count].country_hour[0] == '-') {
				bNegative = true;
			}
			//負判定と時情報の取得
			if (!bNegative && hour_length == 2) {
				second_hour_digit = (country_array[count].country_hour[0] - '0');
				first_hour_digit = (country_array[count].country_hour[1] - '0');
			}else if (!bNegative && hour_length == 2) {
				first_hour_digit = (country_array[count].country_hour[1] - '0');
			}else if (bNegative && hour_length == 3) {
				second_hour_digit = (country_array[count].country_hour[1] - '0');
				first_hour_digit = (country_array[count].country_hour[2] - '0');
			}else if(bNegative && hour_length == 2){
				first_hour_digit = (country_array[count].country_hour[1] - '0');
			}else {
				first_hour_digit = (country_array[count].country_hour[0] - '0');
			}

			fixed_hour += (second_hour_digit * 10);
			if (bNegative && hour_length == 2) {
				fixed_hour -= first_hour_digit;
			}else if (bNegative && hour_length == 3) {
				fixed_hour += first_hour_digit;
				fixed_hour -= (fixed_hour * 2); //符号反転
			}else {
				fixed_hour += first_hour_digit;
			}
			fixed_hour += base_hour;

			//0以下、24以上の時間補正
			if (fixed_hour >= 24) {
				fixed_hour -= 24;
			}else if (fixed_hour < 0) {
				fixed_hour += 24;
			}
			printf_s("%s %02d:%d\n", country_array[count].country_name, fixed_hour, base_minute);
		}
	}
	printf_s("%s %s\n", country_name, country_hour);

	return 0;
};

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
	
	if (!checkCountryName(country_name)) {
		return false;
	}

	if (!chackCountryHour(country_hour)) {
		return false;
	}

	return true;
}

static bool checkCountryName(const char *country_name)
{
	int name_array_length = strlen(country_name);
	int count = 0;
	for (count = 0; count < name_array_length && country_name[count] != '\0'; count++) {
		//大文字判定
		if (country_name[count] >= 'A' && country_name[count] <= 'Z') {
			continue;
		}
		//小文字判定
		else if (country_name[count] >= 'a' && country_name[count] <= 'z') {
			continue;
		}
		else {
			return false;
		}
	}
	if (count == name_array_length)
	{
		return true;
	}
	return false;
};

static bool chackCountryHour(const char *country_hour)
{
	int hour_array_length = strlen(country_hour);
	int count = 0;
	bool bNegative = false;
	bool bColon = false;
	for (count = 0; count < hour_array_length && country_hour[count] != '\0'; count++) {
		// ":"が入力されているが"XX:XX"のフォーマットに準じていない場合はエラー返却
		if (hour_array_length <= 4 && country_hour[count] == ':')
		{
			return false;
		}
		//マイナスの入力があれば負判定フラグをtrueにし次へ
		if (country_hour[count] == '-') {
			bNegative = true;
			continue;
		}
		//countの位置が":"かつ次の位置が5以下であれば次の位置へ
		if (country_hour[count] == ':' && country_hour[count+1] <= '5') {
			count++;
			continue;
		}else if (country_hour[count] == ':' && country_hour[count+1] >= '6'){
			return false;
		}
		//負判定フラグがfalseかつ2桁の入力にもかかわらず"1X"の入力値でなければエラー返却
		if (!bNegative && hour_array_length == 2 && country_hour[count] != '1') {
			return false;
		}

		//数値判定。数値以外の入力があればエラー返却
		if (country_hour[count] >= '0' && country_hour[count] <= '9') {
			continue;
		}
		else {
			return false;
		}

	}
	if (count == hour_array_length)
	{
		return true;
	}
	return false;
};