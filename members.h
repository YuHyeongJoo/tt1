#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 10      // 저장할 수 있는 회원 레코드 최대 갯수
//T_Record* members[MAX_MEMBERS]; // 회원정보데이터 (전역)

// 회원 정보 레코드의 데이터 타입을 정의함
typedef struct st_member {
    int id;
    char name[20];          // 회원이름
    char membership[20];   // 회원등급
    char phone[20];         // 회원전화번호
    int birthdate;          // 회원생년
    char city[20];          // 회원거주도시
} T_Record;

// 라이브러리 함수 원형을 선언함
int m_is_available();       // 현재 추가할 수 있는 데이터 공간이 있는가?
int m_first_available();    // 추가할 수 있는 가장 빠른 포인터 배열의 인덱스 찾기
int m_count();              // 현재 저장된 회원 레코드의 갯수 가져오기
void m_create(int i, char* n, char* m, char* ph, int b, char* c);   // 회원정보로 신규 회원 레코드 추가
T_Record* m_search_by_id(int id);                // 회원번호가 일치하는 회원 레코드 포인터 찾기
T_Record* m_search_by_name(char* n);             // 이름이 일치하는 회원 레코드 포인터 찾기
T_Record* m_search_by_membership(char* m);       // 회원등급이 일치하는 회원 레코드 포인터 찾기
void m_update(T_Record* p, char* n, char* m, char* ph, int b, char* c);  // 특정 회원 레코드의 정보 업데이트
void m_delete(T_Record* p);     // 특정 회원 레코드의 회원정보 제거
T_Record** m_get_records();     // 회원 레코드 리턴
void m_get_all(T_Record* a[]);  // 회원정보가 들어있는 모든 레코드 포인터의 배열을 만들기
void m_get_all2(T_Record* a[]);  // 모든 레코드 포인터의 배열을 만들기 (for debug)
char* m_to_string(T_Record* p); // 특정 회원 레코드의 내용을 문자열로 가져오기
int m_getid(T_Record* p);       // 특정 회원 레코드의 회원번호 가져오기
char* m_getname(T_Record* p);   // 특정 회원 레코드의 회원이름 가져오기
char* m_getmembership(T_Record* p); // 특정 회원 레코드의 회원등급 가져오기
char* m_getphone(T_Record* p);  // 특정 회원 레코드의 회원전화번호 가져오기
int m_getbirthdate(T_Record* p);// 특정 회원 레코드의 회원생년월일 가져오기
char* m_getcity(T_Record* p);   // 특정 회원 레코드의 회원거주도시 가져오기
int m_get_all_by_id(T_Record* a[], int n);    // 회원번호가 일치하는 모든 레코드 포인터의 배열 만들기 
int m_get_all_by_name(T_Record* a[], char* n);  // 회원이름에 문자열이 포함된 모든 레코드 포인터의 배열 만들기 
int m_get_all_by_membership(T_Record* a[], char* n);    // 회원등급이 일치하는 모든 레코드 포인터의 배열 만들기
void m_init(); // 모든 레코드 제거
char* m_to_string_save(T_Record* p); // 특정 회원 레코드의 내용을 파일저장용 문자열로 가져오기
void m_read_file(T_Record* p, char* filename);  // 회원 레코드 포인터 배열을 가져와 파일에 쓴다
void m_defrag(T_Record* a[]);   // 회원 레코드 포인터 배열에 조각모음을 실시
void m_sort_record_by_id(T_Record* a[], int size);  // 회원 레코드 포인터 배열을 회원번호 오름차순으로 정렬
void m_sort_record_by_name(T_Record* a[], int size);  // 회원 레코드 포인터 배열을 이름 오름차순으로 정렬
void m_sort_record_by_membership(T_Record* a[], int size);  // 회원 레코드 포인터 배열을 회원등급 내림차순으로 정렬
void m_swap_record(T_Record* a, T_Record* b);   // (m_sort_record 헬프함수) 레코드의 내용을 교환
int m_membership_grade(char* m);                // (m_sort_record 헬프함수) 회원등급을 매김
char* m_to_string_stats(T_Record* a[]); // 회원 레코드 통계를 잡아 문자열로 리턴
