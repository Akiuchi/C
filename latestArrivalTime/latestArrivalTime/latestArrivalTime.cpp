#include <stdio.h>
#include <string.h>

#define	MAX_ARRAY	(32)

static bool checkInputParam(const char*, char*, char*);

int main(void) {

	char arrivalTimeInfo;					//�o�Ђ̎��ԏ��
	char departureTime[MAX_ARRAY] = "";		//�w���o�����鎞��
	int trainNum;							//�d�Ԃ̖{��

	//�o�Ђɂ����鎞�Ԃ����
	fgets(&arrivalTimeInfo, sizeof(arrivalTimeInfo), stdin);

	//�d�Ԃ̖{�������
	scanf_s("%d", &trainNum);

	return 0;
}

static bool checkInputParam(const char *country_info, char* country_name, char* country_hour)
{
	int country_info_length = strlen(country_info);
	int count = 0;
	int name_count = 0;
	int hour_count = 0;

	//�X�y�[�X�܂œǂݍ��݁A�����Ǝ��Ԃ𕪊�
	for (name_count = 0; count < country_info_length && country_info[count] != ' '; count++, name_count++) {
		country_name[name_count] = country_info[count];
	}

	for (count++, hour_count = 0; count < country_info_length && country_info[count] != '\n'; count++, hour_count++) {
		country_hour[hour_count] = country_info[count];
	}

	return true;
}