#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<termios.h>

#include"header.h"
#include"conio.h"

void main_menu()
{	
	//clear screen 
	system("clear");
	
	puts("---------------------------------------------------------------");
	puts("_______  _______  _       _________          _______  _       ");
	puts("(  ____ \\(  ___  )( (    /|\\__    _/|\\     /|(  ___  )( (    /|");
	puts("| (    \\/| (   ) ||  \\  ( |   )  (  | )   ( || (   ) ||  \\  ( |");
	puts("| (_____ | (___) ||   \\ | |   |  |  | |   | || (___) ||   \\ | |");
	puts("(_____  )|  ___  || (\\ \\) |   |  |  | |   | ||  ___  || (\\ \\) |");
	puts("      ) || (   ) || | \\   |   |  |  | |   | || (   ) || | \\   |");
	puts("/\\____) || )   ( || )  \\  ||\\_)  )  | (___) || )   ( || )  \\  |");
	puts("\\_______)|/     \\||/    )_)(____/   (_______)|/     \\||/    )_)");
	puts("---------------------------------------------------------------");
	puts("");
	puts("                           1. Play                               ");
	puts("                          2. Options                             ");
	puts("                        3. Introduction                          ");
	puts("                           0. Exit                               ");
	return;
}

void setting(game_setting *set)
{
	char *pError_mes = NULL;
	while(1){
		system("clear");
		char opt = 0;		
	
		if(set -> difficulty == 0){
			printf("Difficulty: Normal\nNumbers of the players: %u\n", set->players);
		}
		else if(set -> difficulty == 1){
			printf("Difficulty: Easy\nNumbers of the players: %u\n", set->players);
		}
		else{
			printf("Difficulty: Ultimately Easy\nNumbers of the players: %u\n", set->players);
		}
		
		if(set -> cheat){
			puts("Cheating mode: on.");
		}
		else{
			puts("Cheating mode: off.");	
		}
		puts("---------------------");
		puts("1. Change difficulty");
		puts("2. Increase players");
		puts("3. Decrease players");
		puts("0. Back");
		if(pError_mes){
			puts("---------------------");
			printf("%s\n", pError_mes);
		}
		
		opt = getch();
		if(opt == '1'){
			set -> difficulty++;
			if(set -> difficulty > 2){
				set -> difficulty = 0;
			}
			/*
			if(set -> difficulty == 0){
				set->difficulty++;
				pError_mes = NULL;
			}
			else{
				set->difficulty--;
				pError_mes = NULL;
			}
			*/
		}
		else if(opt == '2'){
			if(set -> players < 4){
				set->players++;
				pError_mes = NULL;
			}	
			else{
				pError_mes = "The maximum of the players is 4";
			}
				
		}
		else if(opt == '3'){			
			if(set -> players > 2){
				set->players--;
				pError_mes = NULL;
			}
			else{
				pError_mes = "The minimum of the players is 4";
			}
		
		}
		else if(opt == '0'){			
			return;
		}
		else{
			continue;
		}
	}
}

void intro()
{
	system("clear");
	puts("Hello there!");
	puts("Here are some guidelines for you.");
	pause();
	
	system("clear");
	puts("About the interface:");
	puts("Following is an example of gaming interface.");
	puts("");
	ex();
	pause();
	
	system("clear");
	puts("About the interface:");
	puts("The first line tell you who is the governor and numbers of the supply and the discard.");
	puts("");
	ex();
	pause();
	
	system("clear");
	puts("About the interface:");
	puts("Next, it tells you which roles are able to be selected.");
	puts("");
	ex();
	pause();
	
	system("clear");
	puts("About the interface:");
	puts("Then, there is the building area, so you could know the buildings have been built.");
	puts("");
	ex();
	pause();
	
	system("clear");
	puts("About the interface:");
	puts("And let's lood at hand.");
	puts("It shows the cards you own now and the cost of each card in the middle of the curly brackets.");
	puts("");
	ex();
	pause();
	
	system("clear");
	puts("About the interface:");
	puts("Last but not least, there is the system information helps you to realize what to do at the bottom.");
	puts("");
	ex();
	pause();
	
	system("clear");
	puts("About the game play:");
	puts("When it informs you to select something, you need to press the corresponding key according to the information on the interface.");
	puts("");
	puts("e.g. It tells you \"You need to discard down to 4 cards.\"");
	puts("And cards in your hand are (1)[City hall{6}]   (2)[Gold mine{1}]   (3)[Carpenter{3}]   (4)[Coffee roaster{4}]   (5)[Sugar mill{2}]");
	puts("If you want to discard sugar mill, you need to press the '5' button on your keyboard.");
	puts("From time to time, you also need to confirm your actions by pressing 'y' on your keyboard.");
	puts("");
	puts("Pressing any other key means you would like to cancel.");
	puts("");
	puts("By the way, you have chances to end the game right away and retutn to main menu by pressing Esc while the end of a round.");
	pause();
	
	system("clear");
	puts("About the rules:");
	puts("I reckon you must be a master of Sanjuan, right?");
	puts("Umm... If you say u are new here, please use the following link to get the manual:");
	puts("https://www.fgbradleys.com/rules/rules4/San%20Juan%20-%20rules.");
	pause();
	
	system("clear");
	puts("Anyway, hope you enjoy this game ^^");
	pause();

	return;
}

void bye(){
	system("clear");
	puts(" ______            _______ ");
	puts("(  ___ \\ |\\     /|(  ____ \\");
	puts("| (   ) )( \\   / )| (    \\/");
	puts("| (__/ /  \\ (_) / | (__    ");
	puts("|  __ (    \\   /  |  __)   ");
	puts("| (  \\ \\    ) (   | (      ");
	puts("| )___) )   | |   | (____/\\");
	puts("|/ \\___/    \\_/   (_______/");
	
	return;
}

int32_t initList( sList *pList )
{
    if( pList == NULL )
    {
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return -1;
    }
    
    pList -> size = 0;
    pList -> pHead = NULL; 
    pList -> pTail = NULL; 
    
    return 0;
}

void delAllNode(sList *pList)
{
	if( pList == NULL )
   	{
       		printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        	return;
    	} 
    
	sListNode *pNode = pList->pHead;
	sListNode *pNextNode = NULL;
	while(pNode){
		pNextNode = pNode->pNext;
		free( pNode );
		pNode = pNextNode;
	}
	pList -> size = 0;
	pList -> pHead = NULL;
	pList -> pHead = NULL;
	return;
}

int32_t addNode(sList *pList, int32_t val)
{
    if( pList == NULL )
    {
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return -1;
    }    
    
    //printf("%d\n", val);
    
    sListNode *pNewNode = calloc( 1, sizeof( sListNode ) );
    pNewNode -> data = val;
    pNewNode -> pNext = NULL;
    
    if( pList -> size == 0 )
    {
        pList -> pHead = pNewNode;
        pList -> pTail = pNewNode;
        pList -> size++;
        return 0;
    }
    
    sListNode *pNode = pList -> pHead;
    
    if(pNewNode->data >= pList->pHead->data){
    	pList->pHead = pNewNode;
    	pNewNode->pNext = pNode;
    	pList -> size += 1;
    }
    else if(pNewNode->data <= pList->pTail->data){
    	pList->pTail->pNext = pNewNode;
    	pList->pTail = pNewNode;
    	pList -> size += 1;
    }
    else{
    	while(pNode){
    		if(pNode->data >= val && pNode->pNext->data <= val){
    			pNewNode->pNext = pNode->pNext;
    			pNode->pNext = pNewNode;
    			break;
    		}
    		
    		pNode = pNode->pNext;
   	 	}
   	 	pList -> size += 1;
   	}
   	return 0;
}

int32_t getMax(sList *pList)
{
	if(pList -> pHead == NULL || pList -> size == 0){
		return 29;
	}
	return pList->pHead->data;
}

int32_t getMin(sList *pList)
{
	if(pList -> pTail == NULL || pList -> size == 0){
		return 29;
	}
	return pList->pTail->data;
}

int32_t delNode( sList *pList, int32_t val )
{
    // Return 0 if successful removing the element.
    // Return -1 if NULL pointer or not found.
    
    if( pList == NULL )
    {
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return -1;
    } 
    
    if( pList -> size == 0 )
    {
        return -1;
    }
    
    sListNode *pNode = pList -> pHead;
    sListNode *pPreNode = NULL;
    
    if( pNode -> data == val )
    {
        if( pList -> pHead == pList -> pTail )
        {
            free( pList -> pHead );
            pList -> pHead = NULL;
            pList -> pTail = NULL;
        }
        else
        {
            pList -> pHead = pNode -> pNext;
            free( pNode );
        }
        pList -> size -= 1;
        return 0;
    }
        
    while ( pNode != NULL && pNode -> data != val ) 
    { 
        pPreNode = pNode; 
        pNode = pNode -> pNext; 
    } 
    
    if( pNode )
    {
        pPreNode -> pNext = pNode -> pNext;
        
        if( pList -> pTail == pNode )
        {
            pList -> pTail = pPreNode;
        }
        
        free( pNode );
        pList -> size -= 1;
        return 0;
    }
    
    return -1;
}

int32_t getListSize( sList *pList )
{
    return pList -> size;
}

int32_t printList( sList *pList )
{
    if( pList == NULL )
    {
        printf( "%s(%d) %s: NULL pointer!\n", __FILE__, __LINE__, __FUNCTION__ );
        return -1;
    } 
    
    int32_t counter = 0;
    sListNode *pNode = pList -> pHead;
    
    while( pNode )
    {
        printf( "%d -> ", pNode -> data );
        
        counter++;
        if( counter % 8 == 0 )
        {
            printf( "\n" );
        }
        
        pNode = pNode -> pNext;
    }
    
    printf( "NULL\n" );
    
    return 0;
}

static struct termios old, current;
void initTermios(int echo) 
{
    tcgetattr(0, &old); 
    current = old; 
    current.c_lflag &= ~ICANON; 
    if (echo) {
        current.c_lflag |= ECHO; 
    }
    else {
        current.c_lflag &= ~ECHO; 
    }
    tcsetattr(0, TCSANOW, &current); 
}


void resetTermios(void) 
{
    tcsetattr(0, TCSANOW, &old);
}


char getch_(int echo) 
{
    char ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}


char getch(void) 
{
    return getch_(0);
}


char getche(void) 
{
    return getch_(1);
}

void shuffle(int32_t deck[], int32_t size, uint8_t pNum)
{
	
	int32_t x = 0;
	int32_t y = 0;
	for(int i = 0; i < 7414; i++){
		while(1){
			x = rand() % size;
			if(x >= pNum){
				break;
			}
		}
		while(1){
			y = rand() % size;
			if(y >= pNum && y != x){
				break;
			}
		}
		deck[x] ^= deck[y];
		deck[y] ^= deck[x];
		deck[x] ^= deck[y];
	}
	return;
}
void end_game(int32_t **construction, int8_t **ability, sList *hand, int32_t *chapel, int32_t *num_of_good, uint8_t pNum)
{
	system("clear");
	uint32_t all_points[pNum];
	memset(all_points,0,pNum);
	
	for(int i = 0; i < pNum; i++){
	
		all_points[i] = count_points(construction[i],ability[i],chapel[i]);
		
		if(i == 0){
			printf("Victory Points of player 1 (You): %u\n",all_points[i]);
		}
		else{
			printf("Victory Points of player %d: %u\n",i + 1,all_points[i]);
		}
	}
	puts("-------------------------------------");
	
	uint32_t max = 0;
	uint8_t counter = 0;
	uint8_t winner = 0;
	
	for(int i = 0; i < pNum; i++){
		if(all_points[i] > max){
			max = all_points[i];
		}
	}
	
	for(int i = 0; i < pNum; i++){
		if(all_points[i] == max){
			counter++;
		}
	}
	
	if(counter == 1){
		for(int i = 0; i < pNum; i++){
			if(all_points[i] == max){
				winner = i;
			}
		}
	}
	else{
		uint32_t bonus[pNum];
		memset(all_points,0,pNum);
		
		for(int i = 0; i < pNum; i++){
			if(all_points[i] == max){
				bonus[i] = num_of_good[i] + hand[i].size;
			}
		}
		
		for(int i = 0; i < pNum; i++){
			if(all_points[i] > max){
				max = bonus[i];
			}
		}
		
		for(int i = 0; i < pNum; i++){
			if(all_points[i] == max){
				winner = i;
				break;
			}
		}
		
	}
	
	
	if(winner == 0){
			puts("You are the winner!");
		}
		else{
			printf("CPU %hhu is the winner.", winner);
		}
	pause();
	return;
}
uint32_t count_points(int32_t *construction, int8_t *ability, int32_t chapel)
{
	uint8_t point[29] = {1,1,2,2,3,2,2,1,1,1,1,2,2,1,2,1,2,1,1,2,1,3,3,4,5,0,0,0,0};
	uint32_t counter = 0;
	for(int i = 0; i < 12 && construction[i] != -1; i++){
		counter += point[construction[i]];
	}
	counter += chapel;
	
	if(ability[TRIUMPHAL_ARCH]){
		uint8_t kind = 0;
		if(ability[STATUE]){
			kind++;
		}
		if(ability[VICTORY_COLUMN]){
			kind++;
		}
		if(ability[HERO]){
			kind++;
		}
		
		switch(kind){
			case 1:
				counter += 4;
			break;
			case 2:
				counter += 6;
			break;
			case 3:
				counter += 8;
			break;
			default:
			
			break;
		}
		
	}
	
	if(ability[GUILD_HALL]){
		for(int i = 0; i < 12 && construction[i] != -1; i++){
			if(construction[i] <= SILVER_SMELTER){
				counter += 2;
			}
		}
	}
	
	if(ability[CITY_HALL]){
		for(int i = 0; i < 12 && construction[i] != -1; i++){
			if(construction[i] >= TOWER){
				counter++;
			}
		}
	}
	
	if(ability[PALACE]){
		counter += counter / 4;
	}
	
	return counter;
}

void print_building(int32_t **construction, int32_t **good, uint8_t pNum, int32_t chapel[])
{

	for(int i = 0; i < pNum; i++){
		if(i == 0){
			puts("Your buildings: ");
		}
		else{
			printf("CPU %d's buildings: \n",i);
		}
		
		for(int j = 0; j < 12 && construction[i][j] != -1; j++){
			if(j + 1 <= 9){
				printf("(%d)", j + 1);
			}
			else{
				printf("(%c)", j - 9 + 'a');
			}
			switch(construction[i][j]){
				case INDIGO_PLANT: //0
					if(good[i][j] >= 0){
						printf("\033[34m%s[good]   \033[0m",pa);
					}
					else{
						printf("\033[34m%s   \033[0m",pa);
					}
				break;
				case SUGAR_MILL: //1
					if(good[i][j] >= 0){
						printf("\033[37m%s[good]   \033[0m",pb);
					}
					else{
						printf("\033[37m%s   \033[0m",pb);
					}
				break;
				case TOBACCO_STORAGE: //2
					if(good[i][j] >= 0){
						printf("\033[33m%s[good]   \033[0m",pc);
					}
					else{
						printf("\033[33m%s   \033[0m",pc);
					}
				break;
				case COFFEE_ROASTER: //3
					if(good[i][j] >= 0){
						printf("\033[31m%s[good]   \033[0m",pd);
					}
					else{
						printf("\033[31m%s   \033[0m",pd);
					}
				break;
				case SILVER_SMELTER: //4
					if(good[i][j] >= 0){
						printf("\033[36m%s[good]   \033[0m",pe);
					}
					else{
						printf("\033[36m%s   \033[0m",pe);
					}
				break;
				case TOWER: //5
					printf("\033[35m%s   \033[0m",sa);
				break;
				case CHAPEL: //6
					printf("\033[35m%s[%d]   \033[0m",sb,chapel[i]);
				break;
				case SMITHY: //7
					printf("\033[35m%s   \033[0m",sc);
				break;
				case POOR_HOUSE: //8
					printf("\033[35m%s   \033[0m",sd);
				break;
				case BLACK_MARKET: //9
					printf("\033[35m%s   \033[0m",se);
				break;
				case CRANE: //10
					printf("\033[35m%s   \033[0m",sf);
				break;
				case CARPENTER: //11
					printf("\033[35m%s   \033[0m",sg);
				break;
				case QUARRY: //12
					printf("\033[35m%s   \033[0m",sh);
				break;
				case WELL: //13
					printf("\033[35m%s   \033[0m",si);
				break;
				case AQUEDUCT: //14
					printf("\033[35m%s   \033[0m",sj);
				break;
				case MARKET_STAND: //15
					printf("\033[35m%s   \033[0m",sk);
				break;
				case MARKET_HALL: //16
					printf("\033[35m%s   \033[0m",sl);
				break;
				case TRADING_POST: //17
					printf("\033[35m%s   \033[0m",sm);
				break;
				case ARCHIVE: //18
					printf("\033[35m%s   \033[0m",sn);
				break;
				case PREFECTURE: //19
					printf("\033[35m%s   \033[0m",so);
				break;
				case GOLD_MINE: //20
					printf("\033[35m%s   \033[0m",sp);
				break;
				case LIBRARY: //21
					printf("\033[35m%s   \033[0m",sq);
				break;
				case STATUE: //22
					printf("\033[35m%s   \033[0m",sr);
				break;
				case VICTORY_COLUMN: //23
					printf("\033[35m%s   \033[0m",ss);
				break;
				case HERO: //24
					printf("\033[35m%s   \033[0m",st);
				break;
				case GUILD_HALL: //25
					printf("\033[35m%s   \033[0m",su);
				break;
				case CITY_HALL: //26
					printf("\033[35m%s   \033[0m",sv);
				break;
				case TRIUMPHAL_ARCH: //27
					printf("\033[35m%s   \033[0m",sw);
				break;
				case PALACE: //28
					printf("\033[35m%s   \033[0m",sx);
				break;
			}
			if((j + 1) % 4 == 0){
				puts("");
			}
		}
		puts("");
		puts("------------------------------------------------------------------------");
	}
	printf("\033[0m");
	return;
}

void print_hand(sList *hand, uint8_t *cost)
{
	sListNode *pNode = hand -> pHead;
	uint8_t counter = 1;
	while(pNode){
		if(counter <= 9){
				printf("(%hhu)", counter);
			}
			else{
				printf("(%c)", counter - 10 + 'a');
			}
		switch(pNode -> data){
			case INDIGO_PLANT: //0
				printf("\033[34m[%s{%hhu}]   \033[0m", pa, cost[INDIGO_PLANT]);
			break;
			case SUGAR_MILL: //1
				printf("\033[37m[%s{%hhu}]   \033[0m", pb, cost[SUGAR_MILL]);
			break;
			case TOBACCO_STORAGE: //2
				printf("\033[33m[%s{%hhu}]   \033[0m", pc, cost[TOBACCO_STORAGE]);
			break;
			case COFFEE_ROASTER: //3
				printf("\033[31m[%s{%hhu}]   \033[0m", pd, cost[COFFEE_ROASTER]);
			break;
			case SILVER_SMELTER: //4
				printf("\033[36m[%s{%hhu}]   \033[0m", pe, cost[SILVER_SMELTER]);
			break;
			case TOWER: //5
				printf("\033[35m[%s{%hhu}]   \033[0m", sa, cost[TOWER]);
			break;
			case CHAPEL: //6
				printf("\033[35m[%s{%hhu}]   \033[0m", sb, cost[CHAPEL]);
			break;
			case SMITHY: //7
				printf("\033[35m[%s{%hhu}]   \033[0m", sc, cost[SMITHY]);
			break;
			case POOR_HOUSE: //8
				printf("\033[35m[%s{%hhu}]   \033[0m", sd, cost[POOR_HOUSE]);
			break;
			case BLACK_MARKET: //9
				printf("\033[35m[%s{%hhu}]   \033[0m", se, cost[BLACK_MARKET]);
			break;
			case CRANE: //10
				printf("\033[35m[%s{%hhu}]   \033[0m", sf, cost[CRANE]);
			break;
			case CARPENTER: //11
				printf("\033[35m[%s{%hhu}]   \033[0m", sg, cost[CARPENTER]);
			break;
			case QUARRY: //12
				printf("\033[35m[%s{%hhu}]   \033[0m", sh, cost[QUARRY]);
			break;
			case WELL: //13
				printf("\033[35m[%s{%hhu}]   \033[0m", si, cost[WELL]);
			break;
			case AQUEDUCT: //14
				printf("\033[35m[%s{%hhu}]   \033[0m", sj, cost[AQUEDUCT]);
			break;
			case MARKET_STAND: //15
				printf("\033[35m[%s{%hhu}]   \033[0m", sk, cost[MARKET_STAND]);
			break;
			case MARKET_HALL: //16
				printf("\033[35m[%s{%hhu}]   \033[0m", sl, cost[MARKET_HALL]);
			break;
			case TRADING_POST: //17
				printf("\033[35m[%s{%hhu}]   \033[0m", sm, cost[TRADING_POST]);
			break;
			case ARCHIVE: //18
				printf("\033[35m[%s{%hhu}]   \033[0m", sn, cost[ARCHIVE]);
			break;
			case PREFECTURE: //19
				printf("\033[35m[%s{%hhu}]   \033[0m", so, cost[PREFECTURE]);
			break;
			case GOLD_MINE: //20
				printf("\033[35m[%s{%hhu}]   \033[0m", sp, cost[GOLD_MINE]);
			break;
			case LIBRARY: //21
				printf("\033[35m[%s{%hhu}]   \033[0m", sq, cost[LIBRARY]);
			break;
			case STATUE: //22
				printf("\033[35m[%s{%hhu}]   \033[0m", sr, cost[STATUE]);
			break;
			case VICTORY_COLUMN: //23
				printf("\033[35m[%s{%hhu}]   \033[0m", ss, cost[VICTORY_COLUMN]);
			break;
			case HERO: //24
				printf("\033[35m[%s{%hhu}]   \033[0m", st, cost[HERO]);
			break;
			case GUILD_HALL: //25
				printf("\033[35m[%s{%hhu}]   \033[0m", su, cost[GUILD_HALL]);
			break;
			case CITY_HALL: //26
				printf("\033[35m[%s{%hhu}]   \033[0m", sv, cost[CITY_HALL]);
			break;
			case TRIUMPHAL_ARCH: //27
				printf("\033[35m[%s{%hhu}]   \033[0m", sw, cost[TRIUMPHAL_ARCH]);
			break;
			case PALACE: //28
				printf("\033[35m[%s{%hhu}]   \033[0m", sx, cost[PALACE]);
			break;
		}
		counter++;
		pNode = pNode -> pNext;
	}
	puts("");
	
	return;
}

void discard(sList* hand, sList* dis)
{	
	char opt = '\0';
	int32_t cho = 0;
	puts("Please choose one card to discard from your hand.");
	
	while(1){
		opt = getch();
		if(opt >= 'a' && opt <= 'z'){
			cho = (int32_t)(opt - 'a' + 10);
		}
		else{
			cho = (int32_t)(opt - '0');
		}
		sListNode *pNode = hand -> pHead;
		if(cho > hand -> size || cho < 1){
			continue;
		}
		else{
			for(int i = 1; i < cho; i++){
				pNode = pNode -> pNext;
			}
			addNode(dis,pNode -> data);
			delNode(hand,pNode -> data);
				
			break;
		}
	}
	
	return;
}

void chapel_card(int32_t *pChapel, sList *hand, sList *dis)
{
	if(hand -> size > 0){
		char opt = '\0';
		int32_t cho = 0;
		puts("Please choose one card to put in chapel or press 0 to cancel.");
		while(1){
			opt = getch();
			if(opt >= 'a' && opt <= 'z'){
				cho = (int32_t)(opt - 'a' + 10);
			}
			else{
				cho = (int32_t)(opt - '0');
			}
			sListNode *pNode = hand -> pHead;
			if(cho == 0){
				break;
			}
			else if(cho > hand -> size || cho < 0){
				continue;
			}
			else{
				for(int i = 1; i < cho; i++){
					pNode = pNode -> pNext;
				}
				addNode(dis,pNode -> data);
				delNode(hand,pNode -> data);
				
				(*pChapel)++;
				break;
			}
		}
	}
	
	return;
}

void build(sList *hand, int32_t **construction, int32_t *pNum_of_con, int32_t *pNum_of_emp, int32_t **good, int32_t *pNum_of_good, int8_t *ability, uint8_t phase, uint8_t governor, int8_t role[], game_setting *set, int32_t *pDeck_size, int32_t *pCard_using, int32_t deck[], sList *dis, int32_t chapel[], uint8_t lib)
{
	uint8_t cost[29] = {1,2,3,4,5,3,3,1,2,2,2,3,4,2,3,2,4,2,1,3,1,5,3,4,5,6,6,6,6};
	uint8_t point[29] = {1,1,2,2,3,2,2,1,1,1,1,2,2,1,2,1,2,1,1,2,1,3,3,4,5,0,0,0,0};
	char opt = '\0';
	int32_t cho = 0;
	while(1){
		print_screen();
		puts("Please select a card to build, or press '0' to skip");
		opt = getch();
		if(opt >= 'a' && opt <= 'z'){
			cho = (int32_t)(opt - 'a' + 10);
		}
		else{
			cho = (int32_t)(opt - '0');
		}
		
		sListNode *pNode = hand -> pHead;
		if(cho > hand -> size || cho < 0){
			continue;
		}
		else if(cho == 0){
				return;
		}
		else{
			for(int i = 0; i < cho - 1; i++){
				pNode = pNode -> pNext;
			}
			print_screen();
			switch(pNode -> data){
				case INDIGO_PLANT: //0
					puts(ipa);
				break;
				case SUGAR_MILL: //1
					puts(ipb);
				break;
				case TOBACCO_STORAGE: //2
					puts(ipc);
				break;
				case COFFEE_ROASTER: //3
					puts(ipd);
				break;
				case SILVER_SMELTER: //4
					puts(ipe);
				break;
				case TOWER: //5
					puts(isa);
				break;
				case CHAPEL: //6
					puts(isb);	
				break;
				case SMITHY: //7
					puts(isc);
				break;
				case POOR_HOUSE: //8
					puts(isd);
				break;
				case BLACK_MARKET: //9
					puts(ise);
				break;
				case CRANE: //10
					puts(isf);
				break;
				case CARPENTER: //11
					puts(isg);
				break;
				case QUARRY: //12
					puts(ish);
				break;
				case WELL: //13
					puts(isi);
				break;
				case AQUEDUCT: //14
					puts(isj);
				break;
				case MARKET_STAND: //15
					puts(isk);
				break;
				case MARKET_HALL: //16
					puts(isl);
				break;
				case TRADING_POST: //17
					puts(ism);
				break;
				case ARCHIVE: //18
					puts(isn);
				break;
				case PREFECTURE: //19
					puts(iso);
				break;
				case GOLD_MINE: //20
					puts(isp);
				break;
				case LIBRARY: //21
					puts(isq);
				break;
				case STATUE: //22
					puts(isr);
				break;
				case VICTORY_COLUMN: //23
					puts(iss);
				break;
				case HERO: //24
					puts(ist);
				break;
				case GUILD_HALL: //25
					puts(isu);
				break;
				case CITY_HALL: //26
					puts(isv);
				break;
				case TRIUMPHAL_ARCH: //27
					puts(isw);
				break;
				case PALACE: //28
					puts(isx);
				break;
			}		
			if(point[pNode -> data]){
				printf("The points of this building: %hhu\n", point[pNode -> data]);
			}
			else{
				puts("The points of this building: ?");
			}
			puts("");
			puts("Do you want to build this one? press 'y' for yes, else for no.");
			opt = getch();
			if(opt == 'y'){
				uint8_t using = (cost[pNode -> data] - (phase == 0 ? 1 + (ability[LIBRARY] * lib) : 0) - (ability[QUARRY] && (pNode -> data >= TOWER) ? 1 : 0));
				if(pNode -> data <= SILVER_SMELTER && ability[SMITHY]){
					using--;
				} 
				if(ability[CRANE]){
					uint8_t crane = 1;
					while(crane){
						print_screen();
						puts("Do you want to use the ability of crane? press 'y' for yes, else for no.");
						opt = getch();
						if(opt == 'y' && crane){
							while(crane){
								print_screen();
								puts("Please select a building or press '0' to cancel.");
								opt = getch();
								if(opt >= 'a' && opt <= 'z'){
									cho = (int32_t)(opt - 'a' + 10);
								}
								else{
									cho = (int32_t)(opt - '0');
								}
								if(cho == 0){
									crane = 0;
									break;
								}
								else if(cho > *pNum_of_con || cho < 1){
									continue;
								}
								else{
									int32_t sub = cho - 1;
									using -= cost[construction[0][sub]];
									if(ability[BLACK_MARKET] && *pNum_of_good > 0){
										print_screen();
										puts("Do you want to use the ability of black market? press 'y' for yes, else for no.");
										while(1){
											opt = getch();
											if(opt == 'y'){
												for(int i = 0; *pNum_of_good > 0 && i < 2 && using >= 0;){
													print_screen();
													puts("Please select a good or press '0' to cancel");
													opt = getch();
													if(opt >= 'a' && opt <= 'z'){
														cho = (int32_t)(opt - 'a' + 10);
													}
													else{
														cho = (int32_t)(opt - '0');
													}
													if(cho == 0){
														break;
													}
													if(cho > 12 || cho < 1 || good[0][cho - 1] == -1){
														continue;
													}
													else{
														good[0][cho - 1] = -1;
														(*pNum_of_good)--;
														(*pNum_of_emp)++;
														print_screen();
														puts("You use one good to pay.");
														pause();
														using--;
														addNode(dis,good[0][cho - 1]);
														i++;
													}
												}
											}
											else{
												break;
											}
										}
									}
									if((hand -> size - 1) < using){
										print_screen();
										puts("You do not have enough cards to pay.");
										pause();
										continue;
									}
									else if(pNode -> data >= TOWER && ability[pNode -> data]){
										print_screen();
										puts("You cannot build the special building you have had.");
										pause();
										continue;
									}
									else{
										ability[construction[0][sub]]--;
										if(construction[0][sub] <= SILVER_SMELTER){
											if(good[0][sub] >= 0){
												(*pNum_of_good)--;
											}
											else{
												(*pNum_of_emp)--;
											}
							
										}
										
										construction[0][sub] = pNode -> data;
										if(construction[0][sub] <= SILVER_SMELTER){
											(*pNum_of_emp)++;
										}
										ability[pNode -> data]++;
										
										
										if(hand -> size == using){
											delAllNode(hand);	
										}
										else{
											for(int i = 0; i < using; i++){
												print_screen();
												printf("You still need to discard %hhu times to pay):\n",using - i);
												discard(hand,dis);
											}
										}
										if(ability[CARPENTER] && pNode -> data >= TOWER && pNode -> data != CARPENTER){
											print_screen();
											addNode(hand,deck[*pCard_using]);
											(*pCard_using)++;
											puts("You draw a card because of carpenter.");
											pause();
											reshuffle();
										}
										if(ability[POOR_HOUSE] && hand -> size <= 1 && pNode -> data != POOR_HOUSE){
											print_screen();
											addNode(hand,deck[*pCard_using]);
											(*pCard_using)++;
											puts("You draw a card because of poor house.");
											pause();
											reshuffle();
											}
											return;
										
									}
								}
							}
						}
						else{
							break;
						}
					}
				}
				if(ability[BLACK_MARKET] && *pNum_of_good > 0){
					print_screen();
					puts("Do you want to use the ability of black market? press 'y' for yes, else for no.");
					while(1){
						opt = getch();
						if(opt == 'y'){
							for(int i = 0; *pNum_of_good > 0 && i < 2 && using >= 0;){
								print_screen();
								puts("Please select a good or press '0' to cancel");
								opt = getch();
								if(opt >= 'a' && opt <= 'z'){
									cho = (int32_t)(opt - 'a' + 10);
								}
								else{
									cho = (int32_t)(opt - '0');
								}
								if(cho == 0){
									break;
								}
								if(cho > 12 || cho < 1 || good[0][cho - 1] == -1){
									continue;
								}
								else{
									addNode(dis,good[0][cho - 1]);
									good[0][cho - 1] = -1;
									(*pNum_of_good)--;
									(*pNum_of_emp)++;
									print_screen();
									puts("You use one good to pay.");
									pause();
									using--;
									i++;
								}
							}
						}
						else{
							break;
						}
					}
				}
				if((hand -> size - 1) < using){
					print_screen();
					puts("You do not have enough cards to pay.");
					pause();
					continue;
				}
				else if(pNode -> data >= TOWER && ability[pNode -> data]){
					print_screen();
					puts("You cannot build the special building you have had.");
					pause();
					continue;
				}
				else{
				
					#ifdef DEBUG
					printf("cost: %hhu\n", using);
					pause();
					#endif
					
					construction[0][*pNum_of_con] = pNode -> data;
					if(construction[0][*pNum_of_con] <= SILVER_SMELTER){
						(*pNum_of_emp)++;
					}
					(*pNum_of_con)++;
					ability[pNode -> data]++;
					delNode(hand,pNode -> data);
					
					#ifdef DEBUG
					printf("hand size: %hhu\n", hand -> size);
					pause();
					#endif
					
					if(hand -> size == using){
						delAllNode(hand);	
					}
					else{
						for(int i = 0; i < using; i++){
							print_screen();
							printf("You still need to discard %hhu times to pay.\n",using - i);
							discard(hand,dis);
						}
					}
					
					if(ability[CARPENTER] && pNode -> data >= TOWER && pNode -> data != CARPENTER){
						print_screen();
						addNode(hand,deck[*pCard_using]);
						(*pCard_using)++;
						puts("You draw a card because of carpenter.");
						pause();
						reshuffle();
					}
					if(ability[POOR_HOUSE] && hand -> size <= 1 && pNode -> data != POOR_HOUSE){
						print_screen();
						addNode(hand,deck[*pCard_using]);
						(*pCard_using)++;
						puts("You draw a card because of poor house.");
						pause();
						reshuffle();
					}
					
					break;
				}
			}
			else{
				continue;
			}
		}						
	}
		return;
}

void council(sList *hand, int32_t **construction, int32_t *pNum_of_con, int32_t *pNum_of_emp, int32_t **good, int32_t *pNum_of_good, int8_t *ability, uint8_t phase, uint8_t governor, int8_t role[], game_setting *set, int32_t *pDeck_size, int32_t *pCard_using, int32_t deck[], sList *dis, int32_t chapel[], uint8_t lib)
{
	uint8_t cost[29] = {1,2,3,4,5,3,3,1,2,2,2,3,4,2,3,2,4,2,1,3,1,5,3,4,5,6,6,6,6};
	uint8_t draw = 2;
	uint8_t get = 1;
	if(phase == 0){
		draw += 3;
			if(ability[LIBRARY] && lib){
				draw += 3;
			}
	}

	if(ability[PREFECTURE]){
		get = 2;
	}
	if(ability[ARCHIVE]){
		for(int i = 0; i < draw; i++){
			addNode(hand,deck[*pCard_using]);
			(*pCard_using)++;
			reshuffle();
		}
		
		for(int i = 0; i < draw - get; i++){
			print_screen();
			printf("You still need to discard %d times.\n", draw - get - i);
			discard(hand,dis);
			
		}
	}
	else{
		char opt = '\0';
		int32_t cho = 0;
		sList temp;
		initList(&temp);
		for(int i = 0; i < draw; i++){
			addNode(&temp,deck[*pCard_using]);
			(*pCard_using)++;
			reshuffle();
		}
		
		for(int i = 0; i < get; i++){
			print_screen();
			if(i == 0){
				puts("You need to select one of these following cards:");
			}
			else{
				puts("You can select another one because of prefecture:");
			}
			print_hand(&temp,cost);
			while(1){
				opt = getch();
				if(opt >= 'a' && opt <= 'z'){
					cho = (int32_t)(opt - 'a' + 10);
				}
				else{
					cho = (int32_t)(opt - '0');
				}
				if(cho < 1 || cho > draw - i){
					continue;
				}			
				else{
					sListNode *pNode = temp.pHead;
					for(int i = 0; i < cho - 1; i++){
						pNode = pNode -> pNext;
					}
					addNode(hand,pNode -> data);
					delNode(&temp,pNode -> data);
					break;
				}
			}
		}
		sListNode *pNode = temp.pHead;
		while(pNode){
			addNode(dis,pNode -> data);
			delNode(&temp,pNode -> data);
			pNode = pNode-> pNext;
		}
	}
	return;
}
void prospect(sList *hand, int32_t **construction, int32_t *pNum_of_con, int32_t *pNum_of_emp, int32_t **good, int32_t *pNum_of_good, int8_t *ability, uint8_t phase, uint8_t governor, int8_t role[], game_setting *set, int32_t *pDeck_size, int32_t *pCard_using, int32_t deck[], sList *dis, int32_t chapel[], uint8_t lib)
{
	uint8_t cost[29] = {1,2,3,4,5,3,3,1,2,2,2,3,4,2,3,2,4,2,1,3,1,5,3,4,5,6,6,6,6};
	if(phase == 0){
		print_screen();
		
		if(ability[LIBRARY] && lib){
			for(int i = 0; i < 2; i++){
				addNode(hand,deck[*pCard_using]);
				(*pCard_using)++;
				reshuffle();
			}
			puts("You draw 2 cards because of library.");
			pause();
		}
		else{
			addNode(hand,deck[*pCard_using]);
			(*pCard_using)++;
			
			puts("You draw one card.");
			pause();
			reshuffle();
			
		}
	}
	else{
		print_screen();
		puts("You do nothing.");
		pause();
	
	}
	return;
}

void produce(sList *hand, int32_t **construction, int32_t *pNum_of_con, int32_t *pNum_of_emp, int32_t **good, int32_t *pNum_of_good, int8_t *ability, uint8_t phase, uint8_t governor, int8_t role[], game_setting *set, int32_t *pDeck_size, int32_t *pCard_using, int32_t deck[], sList *dis, int32_t chapel[], uint8_t lib)
{
	uint8_t cost[29] = {1,2,3,4,5,3,3,1,2,2,2,3,4,2,3,2,4,2,1,3,1,5,3,4,5,6,6,6,6};
	int32_t already = 0;
	int32_t produce = 1;
	if(ability[AQUEDUCT]){
		if(ability[LIBRARY] && lib){
			if(phase == 0){
				produce = 4;
			}
		}
		else{
			if(phase == 0){
				produce = 2;
			}
			else{
				produce = 3;
			}
		}
	}
	else{
		if(phase == 0){
			produce++;
			if(ability[LIBRARY] && lib){
				produce++;
			}
		}
	}
	
	char opt = '\0';
	int32_t cho = 0;
	
	for(int i = 0; i < produce; i++){
		
		while(1){
			print_screen();
			if(*pNum_of_emp == 0){
				puts("You do not have any empty production building.");
				pause();
				i = produce;
				break;
			}
			printf("You still can produce %d goods and have %d empty production buildings.\n", produce - i, *pNum_of_emp);
			puts("Choose one production building to produce good or press '0' to skip.");
			opt = getch();
			if(opt >= 'a' && opt <= 'z'){
				cho = (int32_t)(opt - 'a' + 10);
			}
			else{
				cho = (int32_t)(opt - '0');
			}
			
			
			if(cho == 0){
				i = produce;
				break;
			}
			else if(cho < 1 || cho > *pNum_of_con){
				continue;
			}
			else if(construction[0][cho - 1] >= TOWER){
				print_screen();
				puts("It is not a production building.");
				pause();
				continue;
			}
			else if(good[0][cho - 1] >= 0){
				print_screen();
				puts("A prodution building can only produce one good.");
				pause();
				continue;
			}
			else{
				good[0][cho - 1] = deck[*pCard_using];
				(*pNum_of_good)++;
				(*pNum_of_emp)--;
				(*pCard_using)++;
				already++;
				reshuffle();
				break;
			}
			
			
		}
	}	
		
	if(ability[WELL] && already >= 2){
		print_screen();
		addNode(hand,deck[*pCard_using]);
		(*pCard_using)++;
		puts("You draw a card because of well.");
		pause();
		reshuffle();
	}
	return;
}
void trade(sList *hand, int32_t **construction, int32_t *pNum_of_con, int32_t *pNum_of_emp, int32_t **good, int32_t *pNum_of_good, int8_t *ability, uint8_t phase, uint8_t governor, int8_t role[], game_setting *set, int32_t *pDeck_size, int32_t *pCard_using, int32_t deck[], sList *dis, int32_t chapel[], uint8_t title, uint8_t lib)
{
	uint8_t cost[29] = {1,2,3,4,5,3,3,1,2,2,2,3,4,2,3,2,4,2,1,3,1,5,3,4,5,6,6,6,6};
	int32_t already = 0;
	int32_t trade = 1;
	uint8_t price[5][5] = {{1,1,1,2,2},{1,1,2,2,2},{1,1,2,2,3},{1,2,2,2,3},{1,2,2,3,3}};
	
	if(ability[TRADING_POST]){
		if(ability[LIBRARY] && lib){
			if(phase == 0){
				trade = 4;
			}
		}
		else{
			if(phase == 0){
				trade = 2;
			}
			else{
				trade = 3;
			}
		}
	}
	else{
		if(phase == 0){
			trade++;
			if(ability[LIBRARY] && lib){
				trade++;
			}
		}
	}
	
	char opt = '\0';
	int32_t cho = 0;
	
	for(int i = 0; i < trade; i++){
		
		while(1){
			print_screen();
			if(*pNum_of_good == 0){
				puts("You do not hace any good.");
				pause();
				i = trade;
				break;
			}
			printf("You still can sell %d goods and have %d goods.\n", trade - i, *pNum_of_good);
			puts("Price on this phase:");
			for(int j = 0; j < 5; j++){
				switch(j){
					case INDIGO_PLANT: //0
						printf("\033[34mIndigo[%hhu]   \033[0m",price[title][j]);
					break;
					case SUGAR_MILL: //1
						printf("\033[37mSugar[%hhu]   \033[0m",price[title][j]);
					break;
					case TOBACCO_STORAGE: //2
						printf("\033[33mTobacco[%hhu]   \033[0m",price[title][j]);
					break;
					case COFFEE_ROASTER: //3
						printf("\033[31mCoffee[%hhu]   \033[0m",price[title][j]);
					break;
					case SILVER_SMELTER: //4
						printf("\033[36mSilver[%hhu]   \033[0m",price[title][j]);
				}
				
			}
			
			puts("");
			puts("Choose one building with good to sell or press '0' to skip.");
			
			opt = getch();
			if(opt >= 'a' && opt <= 'z'){
				cho = (int32_t)(opt - 'a' + 10);
			}
			else{
				cho = (int32_t)(opt - '0');
			}
			
			if(cho == 0){
				i = trade;
				break;
			}
			else if(cho < 1 || cho > *pNum_of_con){
				continue;
			}
			else if(construction[0][cho - 1] >= TOWER){
				print_screen();
				puts("It is not a production building.");
				pause();
				continue;
			}
			else if(good[0][cho - 1] == -1){
				print_screen();
				puts("There is no good.");
				pause();
				continue;
			}
			else{
				print_screen();
				printf("You sell ");
				switch(construction[0][cho - 1]){
					case INDIGO_PLANT: //0
						printf("\033[34mIndigo\033[0m");
					break;
					case SUGAR_MILL: //1
						printf("\033[37mSugar\033[0m");
					break;
					case TOBACCO_STORAGE: //2
						printf("\033[33mTobacco\033[0m");
					break;
					case COFFEE_ROASTER: //3
						printf("\033[31mCoffee\033[0m");
					break;
					case SILVER_SMELTER: //4
						printf("\033[36mSilver\033[0m");
					break;
				}
				printf(", so you draw %hhu cards.\n", price[title][construction[0][cho - 1]]);
				for(int j = 0; j < price[title][construction[0][cho - 1]]; j++){
					addNode(hand,deck[*pCard_using]);
					(*pCard_using)++;
					reshuffle();
				}
				addNode(dis,good[0][cho - 1]);
				good[0][cho - 1] = -1;
				(*pNum_of_good)--;
				(*pNum_of_emp)++;
				pause();
				break;
			}
			
		}
	
		if(ability[MARKET_HALL] && already >= 1){
			print_screen();
			addNode(hand,deck[*pCard_using]);
			(*pCard_using)++;
			puts("You draw a card because of market hall.");
			pause();
			reshuffle();
		}
		if(ability[MARKET_STAND] && already >= 2){
			print_screen();
			addNode(hand,deck[*pCard_using]);
			(*pCard_using)++;
			puts("You draw a card because of market stand.");
			pause();
			reshuffle();
		}
	}
	return;
}
