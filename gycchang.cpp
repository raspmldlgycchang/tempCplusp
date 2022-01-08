#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<cstdlib>
#include<malloc.h>
typedef unsigned int HANDLE;
namespace NUM {
	enum class NUM{
		ROCK,
		SCISSORS,
		PAPER
	};
}
struct HandleData{
	HANDLE h;
	NUM::NUM num_class;
	int IntResult;
	char* mp_string;
};
class gycchang {
private:
	HandleData** mp_users;
	unsigned int m_max_count, m_max_user_cnt;
	unsigned int m_gen_value;
public:
	gycchang(unsigned int a_max_user_cnt = 8, unsigned int a_max_count = 5) {
		m_max_count = a_max_count;
		m_max_user_cnt = a_max_user_cnt;
		m_gen_value = 1;
		mp_users = new HandleData * [m_max_user_cnt];
		for (unsigned int j = 0; j < m_max_user_cnt; j++) {
			*(mp_users + j) = new HandleData[m_max_count];
		}
		
		for (unsigned int j = 0; j < m_max_user_cnt; j++) {
			memset(*(mp_users + j), 0, sizeof(HandleData) * m_max_count);
		}
	}
	~gycchang() {
		//만약mp_string이 있었다면
		HandleData* p_handle = &mp_users[0][0];
		for (unsigned int j = 0; j < m_max_user_cnt; j++) {
			p_handle = &mp_users[j][0];
			for (unsigned int i = 0; i < m_max_count; i++) {
				if (p_handle->h) {
					delete[] p_handle->mp_string;
					p_handle++;
				}
			}
			delete[] * (mp_users + j);
		}
		delete[] mp_users;
	}
	void SetString_enum(NUM::NUM num_class);
	HANDLE SetString(const char* mp_string);
	void PrintString(HANDLE h_str);
};

//구조체포인터배열로 캐스팅하고 구조체요소에 접근
//(int*)((&((HandleData*)p))->IntResult)
void SetString_enum(NUM::NUM num_class)
{
	void* p = NULL;
	//p를 주소연산으로 이동하는 작업이 필요함
	//*(int*)(&((HandleData*)p)->IntResult);
	switch (num_class) {
	case NUM::NUM::ROCK:
		*(int*)(&((HandleData*)p)->IntResult) = 1;
		break;
	case NUM::NUM::SCISSORS:
		*(int*)(&((HandleData*)p)->IntResult) = 1;
		break;
	case NUM::NUM::PAPER:
		*(int*)(&((HandleData*)p)->IntResult) = 1;
		break;
	default:
		break;
	}
}
HANDLE gycchang::SetString(const char* ap_string) {
	int len = strlen(ap_string) + 1;
	HandleData* p_handle = &mp_users[0][0];
	for (unsigned int j = 0; j < m_max_user_cnt; j++) {
		unsigned int i;
		for (i = 0; i < m_max_count; i++) {
			if (p_handle->h == 0)	break;
			else {
				p_handle++;
			}
		}
		if (i < m_max_count) {
			p_handle->mp_string = new char[len];
			memcpy(p_handle->mp_string, ap_string, len);
			p_handle->h = m_gen_value++;
			return p_handle->h;
		}
		else if (j < m_max_user_cnt) {
			p_handle = &mp_users[j++][0];
			for (i = 0; i < m_max_count; i++) {
				if (p_handle->h == 0)	break;
				else {
					p_handle++;
				}
			}
			if (i < m_max_count) {
				p_handle->mp_string = new char[len];
				memcpy(p_handle->mp_string, ap_string, len);
				p_handle->h = m_gen_value++;
				return p_handle->h;
			}
			else {
				printf("아직 증가할 사용자가 남았습니다\n");
				p_handle = &mp_users[j++][0];
				for (unsigned int i = 0; i < m_max_count; i++) {
					if (p_handle->h == 0)	break;
					else {
						p_handle++;
					}
				}
				if (i < m_max_count) {
					p_handle->mp_string = new char[len];
					memcpy(p_handle->mp_string, ap_string, len);
					p_handle->h = m_gen_value++;
					return p_handle->h;
				}
			}
		}
		else {
			printf("지정해주신 사용자를 넘어섰습니다\n");
			return 0xFFFFFFFF;
		}
	}

}
void gycchang::PrintString(HANDLE h_str) {
	HandleData* p_handle = &mp_users[0][0];
	for (unsigned int j = 0; j < m_max_user_cnt; j++) {
		p_handle = &mp_users[j][0];
		unsigned int i;
		for (i = 0; i < m_max_count; i++) {
			if (h_str == p_handle->h) {
				printf("%s : %d번째 사용자의 %d번째 말\n", p_handle->mp_string, j, i);
				return;
			}
			else {
				p_handle++;
			}
		}

	}
	printf("찾으려는 문자열을 찾지 못했습니다\n");
}
int main(void)
{
	gycchang gyc(2, 2);
	HANDLE h_user1_str1 = gyc.SetString("안녕하세요");
	HANDLE h_user1_str2 = gyc.SetString("snsnsnsn");
	HANDLE h_user2_str1 = gyc.SetString("dfsffds");
	HANDLE h_user2_str2 = gyc.SetString(" ds fdssdf");
	HANDLE h_user_error = gyc.SetString("ewfe");

	gyc.PrintString(h_user1_str1);
	gyc.PrintString(h_user1_str2);
	gyc.PrintString(h_user2_str1);
	gyc.PrintString(h_user2_str2);
	gyc.PrintString(h_user_error);


	return 0;
}