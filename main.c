#include "members.h"

void create_record();
void read_record();
void list_record();
void search_record();
void search_record_by_id();
void search_record_by_name();
void search_record_by_membership();
void update_record();
void delete_record();
void delete_record_all();
void load_file();
void save_file();
void defrag_record();
void sort_record();
void sort_record_by_id();
void sort_record_by_name();
void sort_record_by_membership();
void sort_save_record();
void sort_save_record_by_id();
void sort_save_record_by_name();
void sort_save_record_by_membership();
void print_stats();
void save_stats();
void make_stats(int *stats_count, int* stats_membership_c, int* stats_age);


void debug_records(); // for debug  

int main(){
    m_init();
    int menu;
    while(1){
        printf("\nMenu : 1.Create 2.List 3.Search 4.Update 5.Delete 6.Delete(all) \n7.Load 8.Save 9.Defrag 10.Sort 11.Sort&Save 12.Stats 13.Stats&Save 0.Quit > ");
        scanf("%d", &menu);
        printf("\n");
        switch(menu){
            case 1: 
                create_record();
                break;
            case 2: 
                list_record();
                break;
            case 3: 
                search_record();
                break;
            case 4: 
                update_record();
                break;
            case 5: 
                delete_record();
                break;
            case 6: 
                delete_record_all();
                break;
            case 7: 
                load_file();
                break;
            case 8: 
                save_file();
                break;
            case 9: 
                defrag_record();
                break;
            case 10:
                sort_record();
                break;
            case 11:
                sort_save_record();
                break;
            case 12:
                print_stats();
                break;
            case 13:
                save_stats();
                break;
            case 14: 
                debug_records();
                break;
            case 0: 
            default: 
                return 0;
        }
    }
    return 0;
}

void create_record(){
    if(!m_is_available()) {
        printf("There is no space!\n");
        return;
    }
    int id;
    char name[20], membership[20], phone[20], city[20];
    int date;  
    printf("Enter a new member's info.\n");
    printf("Name > ");
    scanf("%s", name);
    if(m_search_by_name(name)) {
        printf("Duplicated name!\n");
        return;
    }
    printf("ID > ");
    scanf("%d", &id);
    if(m_search_by_name(name)) {
        printf("Duplicated name!\n");
        return;
    }
    printf("Membership > ");
    scanf("%s", membership);
    printf("Phone > ");
    scanf("%s", phone);
    printf("Birthdate > ");
    scanf("%d", &date);
    printf("City > ");
    scanf("%s", city);
    m_create(id, name, membership, phone, date, city);
}

void list_record(){
    // 전체 리스트 출력
    printf("All records.\n");
    int size = m_count();
    T_Record* records[MAX_MEMBERS];
    m_get_all(records);
    for(int i=0; i<size; i++){
        T_Record* p = records[i];
        printf("%d. %s\n", i+1, m_to_string(p));
    }
}

void search_record() {
    int condition;
    printf("Search: 1.ID 2.Name 3.Membership 4.Cancel > ");
    scanf("%d", &condition);

    switch (condition) {
        case 1:
            search_record_by_id();
            break;
        case 2:
            search_record_by_name();
            break;
        case 3:
            search_record_by_membership();
            break;
        case 4:
        default:
            break;
    }
}

void search_record_by_id(){
    //회원번호로 검색
    int id;
    printf("Enter ID > ");
    scanf("%d", &id);

    T_Record* records[MAX_MEMBERS];
    int size = m_get_all_by_id(records, id);
    printf("%d records found.\n", size);
    for(int i=0; i<size; i++){
        T_Record* p = records[i];
        printf("%d. %s\n", i+1, m_to_string(p));
    }
}

void search_record_by_name(){
    //이름 일부문자열로 검색
    char name[20];
    printf("Enter a name > ");
    scanf("%s", name);

    T_Record* records[MAX_MEMBERS];
    int size = m_get_all_by_name(records, name);
    printf("%d records found.\n", size);
    for(int i=0; i<size; i++){
        T_Record* p = records[i];
        printf("%d. %s\n", i+1, m_to_string(p));
    }
}

void search_record_by_membership(){
    // 회원등급으로 검색
    char membership[20];
    printf("Enter membership > ");
    scanf("%s", membership);

    T_Record* records[MAX_MEMBERS];
    int size = m_get_all_by_membership(records, membership);
    printf("%d records found.\n", size);
    for(int i=0; i<size; i++){
        T_Record* p = records[i];
        printf("%d. %s\n", i+1, m_to_string(p));
    }
}

void update_record(){
    printf("Not implemented yet\n");
    /*
    char name[20], phone[20], city[20];
    int year;  
    printf("Enter a name > ");
    scanf("%s", name);

    T_Record* p = m_search_by_name(name);
    if(p) {
        printf("Enter a updated info.\n");
        printf("Phone > ");
        scanf("%s", phone);
        printf("Birth year > ");
        scanf("%d", &year);
        printf("City > ");
        scanf("%s", city);

        m_update(p, phone, year, city);
    }
    else {
        printf("No such member!\n");
    }
    */
}

void delete_record(){
    printf("Not implemented yet\n");
    /*
    char name[20];
    printf("Enter a name > ");
    scanf("%s", name);

    T_Record* p = m_search_by_name(name);
    if(p) {
        m_delete(p);
        printf("The record is deleted!\n");
    }
    else {
        printf("No such member!\n");
    }
    */
}

void delete_record_all() {
    printf("Not implemented yet\n");
}

void load_file(){
    // 데이터파일 읽기
    printf("All data will be deleted and new records will be reloaded.\n");
    printf("1.Yes 0.No > ");
    int yesno;
    scanf("%d", &yesno);
    if (yesno == 0) return;
    m_init();   // 레코드 모두 제거 

    FILE* f = fopen("members.txt", "r");
#ifdef DEBUG
    if (f == NULL)
        printf("[load_file] file not opend\n");
#endif
    char name[20], membership[20], phone[20], city[20];
    int id, date;  
    while(!feof(f)){
        if(!m_is_available()) {
            printf("[Load] There is no space!\n");
            break;
        }
        int n = fscanf(f,"%d %s %s %s %d %s", &id, name, membership, phone, &date, city);
        if (n<6) break;     // 빠진 데이터가 있으면 중단
        if(m_search_by_id(id)) {
            printf("[Load] Duplicated id(%s)! loading.\n", name);
            continue;
        }
        m_create(id, name, membership, phone, date, city);
#ifdef DEBUG
        printf("[Load] load %s\n", name);
#endif
    }
#ifdef DEBUG
    printf("%d records are read from file!\n", m_count());    
#endif
    fclose(f);
}

void save_file(){
    // 데이터파일 저장
    FILE* f = fopen("members.txt", "w");
#ifdef DEBUG
    if (f == NULL)
        printf("[load_file] file not opend\n");
#endif
    printf("All records were saved.\n");
    int size = m_count();
    T_Record* records[MAX_MEMBERS];
    m_get_all(records);
    for(int i=0; i<size; i++){
        T_Record* p = records[i];
        fprintf(f,"%s\n", m_to_string_save(p));
#ifdef DEBUG
        printf("[Save] write %s\n", records[i]->name);
#endif
    }
    fclose(f);
}

void defrag_record() {
    printf("Not implemented yet\n");
}

void sort_record() {
    printf("Not implemented yet\n");
}

void sort_save_record() {
    printf("Not implemented yet\n");
}

void print_stats() {
    /* Stats consist of 
     * 1. number of members
     * 2. numbers for each membership (VIP, Gold, Silver, Family)
     * 3. age distribution (-19, 20-29, 30-39, 40-49, 50-59, 60+)
     */  

    // Prepare stats
    int count = m_count();
    int membership_count[4];        
    int age_dist[6] = {0}; 

    make_stats(&count, membership_count, age_dist);

    // Print
    printf("1. Total members: %d\n", count);
    printf("2. Numbers for each membership:\n");
    printf("\tVIP   : %d\n", membership_count[0]);
    printf("\tGold  : %d\n", membership_count[1]);
    printf("\tSilver: %d\n", membership_count[2]);
    printf("\tFamily: %d\n", membership_count[3]);
    printf("3: Age distribution:\n");
    printf("\t0-19 : %d\n", age_dist[0]);
    printf("\t20-29: %d\n", age_dist[1]);
    printf("\t30-39: %d\n", age_dist[2]);
    printf("\t40-49: %d\n", age_dist[3]);
    printf("\t50-59: %d\n", age_dist[4]);
    printf("\t60+  : %d\n", age_dist[5]);
}

void make_stats(int *stats_count, int* stats_membership, int* stats_age) {
    // always pass 
    // stats_count: int
    // stats_membership_c: int [4]
    // stats_age: int [6] = {0}
    *stats_count = m_count();       // Stat for 1

    T_Record* records[*stats_count];
    m_get_all(records);
    T_Record* temp[*stats_count];   // not used; only for counting
    
    // Stat for 2
    // go through memberships
    for (int i = 0; i < *stats_count; i++) {
        int count_VIP = m_get_all_by_membership(temp, "VIP");
        int count_Gold = m_get_all_by_membership(temp, "Gold");
        int count_Silver = m_get_all_by_membership(temp, "Silver");
        int count_Family = m_get_all_by_membership(temp, "Family");

        stats_membership[0] = count_VIP;
        stats_membership[1] = count_Gold;
        stats_membership[2] = count_Silver;
        stats_membership[3] = count_Family;
    }

    // Stat for 3
    // go through age
    for (int i = 0; i < *stats_count; i++) {
        
        int age = 2020 - (records[i]->birthdate/10000) + 1;
            // korean age = current year - birth year + 1
#ifdef DEBUG
        printf("[make_stats(age)] %s: %d\n", records[i]->name, age);
#endif
        
        if (age <= 19) {
            stats_age[0]++;
        }
        else if (age <= 29) {
            stats_age[1]++;
        }
        else if (age <= 39) {
            stats_age[2]++;
        }
        else if (age <= 49) {
            stats_age[3]++;
        }
        else if (age <= 59) {
            stats_age[4]++;
        }
        else {
            stats_age[5]++;
        }
    }
}

void save_stats() {
    /* Stats consist of 
     * 1. number of members
     * 2. numbers for each membership (VIP, Gold, Silver, Family)
     * 3. age distribution (-19, 20-29, 30-39, 40-49, 50-59, 60+)
     */  

    // Prepare stats
    int count = m_count();
    int membership_count[4];        
    int age_dist[6] = {0}; 

    make_stats(&count, membership_count, age_dist);

    // Write
    FILE* f = fopen("stats.txt", "w");
#ifdef DEBUG
    if (f == NULL)
        printf("[load_file] file not opend\n");
#endif

    fprintf(f, "1. Total members: %d\n", count);
    fprintf(f, "2. Numbers for each membership:\n");
    fprintf(f, "\tVIP: %d\n", membership_count[0]);
    fprintf(f, "\tGold: %d\n", membership_count[1]);
    fprintf(f, "\tSilver: %d\n", membership_count[2]);
    fprintf(f, "\tFamily: %d\n", membership_count[3]);
    fprintf(f, "3: Age distribution:\n");
    fprintf(f, "\t0-19: %d\n", age_dist[0]);
    fprintf(f, "\t20-29: %d\n", age_dist[1]);
    fprintf(f, "\t30-39: %d\n", age_dist[2]);
    fprintf(f, "\t40-49: %d\n", age_dist[3]);
    fprintf(f, "\t50-59: %d\n", age_dist[4]);
    fprintf(f, "\t60+: %d\n", age_dist[5]);
    fclose(f);
}

void debug_records(){
    // for debug  
    T_Record* records[MAX_MEMBERS]={0};
    m_get_all2(records);
    for(int i=0; i<MAX_MEMBERS; i++){
        printf("%d - %p\n",i, records[i]);
    }    
}
