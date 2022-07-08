#pragma once
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>

#define pa "Indigo plant"
#define pb "Sugar mill"
#define pc "Tobacco storage"
#define pd "Coffee roaster"
#define pe "Silver smelter"
#define sa "Tower"
#define sb "Chapel"
#define sc "Smithy"
#define sd "Poor house"
#define se "Black market"
#define sf "Crane"
#define sg "Carpenter"
#define sh "Quarry"
#define si "Well"
#define sj "Aqueduct"
#define sk "Market stand"
#define sl "Market hall"
#define sm "Trading post"
#define sn "Archive"
#define so "Prefecture"
#define sp "Gold mine"
#define sq "Library"
#define sr "Statue"
#define ss "Victory column"
#define st "Hero"
#define su "Guild hall"
#define sv "City hall"
#define sw "Triumphal arch"
#define sx "Palace"

#define ipa "Indigo plant:\nProducer phase: Owner produces 1 indigo."
#define ipb "Sugar mill:\nProducer phase: Owner produces 1 sugar."
#define ipc "Tobacco storage:\nProducer phase: Owner produces 1 tobacco."
#define ipd "Coffee roaster:\nProducer phase: Owner produces 1 coffee."
#define ipe "Silver smelter:\nProducer phase: Owner produces 1 silver."
#define isa "Tower:\nEvery turn: Owner can have at most 12 cards in hand."
#define isb "Chapel:\nEvery turn: Owner can put a card in chapel(each card value 1 pt) before discarding."
#define isc "Smithy:\nBuilder phase: Owner pays one card less when building a production building."
#define isd "Poor house:\nBuilder phase: Owner draws 1 card if the owner has only 1 card or less after building."
#define ise "Black market:\nBuilder phase: Owner can use at most 2 goods to pay the cost of the building(1 good for 1 card.)"
#define isf "Crane:\nBuilder phase: Owner can pay the difference between the old and the new building to replace the old one with a new one. The old one lost its effect and its goods but the points still work if it is chapel."
#define isg "Carpenter\nBuilder phase: Owner draws 1 card if the owner builds a special building."
#define ish "Quarry\nBuilder phase: Owner pays one card less if the owner builds a special building."
#define isi "Well\nProducer phase: Owner draws one card if the owner has produced two goods or more."
#define isj "Aqueduct\nProducer phase: Owner can produce 1 more additional good than others."
#define isk "Market stand\nTrader phase: Owner draws 1 card if the owner sells two goods or more."
#define isl "Market hall\nTrader phase: Owner draws 1 card if the owner sells at least one good."
#define ism "Trading post\nTrader phase: Owner can sell 1 more additional good than others."
#define isn "Archive\nCouncillor phase: Owner adds all cards he draws to his hand and discards from entire his hand."
#define iso "Prefecture\nCouncillor phase: Owner chooses addtional 1 card to leave."
#define isp "Gold mine\nProspector phase: Owner draw 4 cards after the action of prospector. If 4 cards are all different, the owner gains one of four cards. Otherwise, the owner gains nothing."
#define isq "Library: double the privileges.\nBuilder phase: Owner pays two card less.\nProducer phase: Owner can produce at most 2 additional goods.\nTrader phase: Owner can sell at most 2 additional goods.\nCouncillor phase: Owner choose 1 card of 8 cards.\nProspector phase: Owner draws 1 additional card."
#define isr "Statue\nNO special effect."
#define iss "Victory column\nNO special effect."
#define ist "Hero\nNO special effect."
#define isu "Guild hall\nAt game end: Owner gains extra 2pts for each built production building"
#define isv "City hall\nAt game end: Owner gains extra 1pt for each built spcial building including this one"
#define isw "Triumphal arch\nAt game end: Owner gains extra 4 pts for having 1 built monument, gains extra 6 pts for having 2 built monuments, or gains extra 8 pts for having 3 built monuments"
#define isx "Palace\nAt game end: Owner gains extra 1 pt for every 4 pts(rounding down) gained by other buildings."

#define parameter &(hand[0]), construction,&num_of_con[0],&num_of_emp[0],good,&num_of_good[0],ability[0],phase,governor,role,set,&deck_size,&card_using,deck,dis,chapel,lib

#define print_screen()\
system("clear");\
if(governor == 0){\
	puts("---------------------");\
	printf("|The governor is you|\t");\
	printf("\tSupply: %d\t", *pDeck_size - *pCard_using);\
	printf("\tDiscard: %d\n", dis -> size);\
	puts("---------------------");\
}\
else{\
	puts(  "------------------------");\
	printf("|The governor is CPU %d|\t",governor);\
	printf("\tSupply: %d\t", *pDeck_size - *pCard_using);\
	printf("\tDiscard: %d\n", dis -> size);\
	puts(  "------------------------");\
}\
puts("Roles can be choosed: ");\
if(role[0] == 1){\
	printf("(1)Builder   ");\
}\
if(role[1] == 1){\
	printf("(2)Councillor   ");\
}\
if(role[2] == 1){\
	printf("(3)Producer   ");\
}\
if(role[3] == 1){\
	printf("(4)Prospector   ");\
}\
if(role[4] == 1){\
	printf("(5)Trader   ");\
}\
puts("");\
puts("");\
print_building(construction,good,set -> players,chapel);\
puts("");\
puts("Hand:");\
print_hand(&(hand[0]),cost);\
puts("");\

#define pause()\
puts("Press any key to continue...");\
getch();\

#define reshuffle()\
if(*pCard_using == *pDeck_size){\
	memset(deck,0,*pDeck_size);\
	sListNode *pNode = dis -> pHead;\
	uint32_t re = 0;\
	while(pNode){\
		deck[re] = pNode -> data;\
		pNode = pNode -> pNext;\
		re++;\
	}\
	*pCard_using = 0;\
	*pDeck_size = dis -> size;\
	delAllNode(dis);\
	shuffle(deck,*pDeck_size,set -> players);\
	puts("Reshuffling. Press any key to continue...");\
	getch();\
}\

#define ex()\
printf("---------------------\n\
|The governor is you|		Supply: 80		Discard: 0\n\
---------------------\n\
Roles can be choosed: \n\
(1)Builder   (2)Councillor   (3)Producer   (4)Prospector   (5)Trader\n\n\
Your buildings:\n\
(1)Indigo plant\n\
------------------------------------------------------------------------\n\
CPU 1's buildings:\n\
(1)Indigo plant\n\
------------------------------------------------------------------------\n\
CPU 2's buildings:\n\
(1)Indigo plant\n\
------------------------------------------------------------------------\n\
CPU 3's buildings:\n\
(1)Indigo plant\n\
------------------------------------------------------------------------\n\
Hand:\n\
(1)[City hall{6}]   (2)[Gold mine{1}]   (3)[Carpenter{3}]   (4)[Coffee roaster{4}]   (5)[Sugar mill{2}]\n\n\
You need to discard down to 4 cards.\n\
Please choose one card to discard from your hand.\n");\
puts("");


typedef struct Game_setting
{
	uint8_t difficulty; //0 for normal, 1 for insane
	uint8_t players;// 2~4
	uint8_t cheat;

}game_setting;
typedef struct _sList
{
    int32_t             size;
    
    struct _sListNode   *pHead;
    struct _sListNode   *pTail;
} sList;

typedef struct _sListNode
{
    int32_t             data;
    struct _sListNode   *pNext;
} sListNode;
/*
typedef struct Property
{
	uint8_t max_card;
	uint8_t chapel;
	uint8_t tower;
	
} property;
*/
typedef enum Card
{
	INDIGO_PLANT,
	SUGAR_MILL,
	TOBACCO_STORAGE,
	COFFEE_ROASTER,
	SILVER_SMELTER,
	TOWER,
	CHAPEL,
	SMITHY,
	POOR_HOUSE,
	BLACK_MARKET,
	CRANE,
	CARPENTER,
	QUARRY,
	WELL,
	AQUEDUCT,
	MARKET_STAND,
	MARKET_HALL,
	TRADING_POST,
	ARCHIVE,
	PREFECTURE,
	GOLD_MINE,
	LIBRARY,
	STATUE,
	VICTORY_COLUMN,
	HERO,
	GUILD_HALL,
	CITY_HALL,
	TRIUMPHAL_ARCH,
	PALACE
}card;

typedef enum Roles
{
	BUILDER,
	COUNCILLOR,
	PRODUCER,
	PROSPECTOR,
	TRADER,
	
}roles;

int32_t initList( sList *pList );
void delAllNode(sList *pList);
int32_t addNode(sList *pList, int32_t val);
int32_t getMax(sList *pList);
int32_t getMin(sList *pList);
int32_t delNode( sList *pList, int32_t val );
int32_t getListSize( sList *pList );
int32_t printList( sList *pList );

void main_menu();
void setting(game_setting *);
void intro();
void bye();
void game(game_setting *);
void shuffle(int32_t [], int32_t , uint8_t);
void end_game(int32_t **, int8_t **, sList *, int32_t *, int32_t *, uint8_t);
uint32_t count_points(int32_t *, int8_t *, int32_t);
void print_building(int32_t **,int32_t **, uint8_t, int32_t []);
void print_hand(sList *, uint8_t *);

void discard(sList *, sList *);
void chapel_card(int32_t *, sList *, sList *);
void build(sList *hand, int32_t **construction, int32_t *pNum_of_con, int32_t *pNum_of_emp, int32_t **good, int32_t *pNum_of_good, int8_t *ability, uint8_t phase, uint8_t governor, int8_t role[], game_setting *set, int32_t *pDeck_size, int32_t *pCard_using, int32_t deck[], sList *dis, int32_t chapel[], uint8_t lib);
void council(sList *hand, int32_t **construction, int32_t *pNum_of_con, int32_t *pNum_of_emp, int32_t **good, int32_t *pNum_of_good, int8_t *ability, uint8_t phase, uint8_t governor, int8_t role[], game_setting *set, int32_t *pDeck_size, int32_t *pCard_using, int32_t deck[], sList *dis, int32_t chapel[], uint8_t lib);
void prospect(sList *hand, int32_t **construction, int32_t *pNum_of_con, int32_t *pNum_of_emp, int32_t **good, int32_t *pNum_of_good, int8_t *ability, uint8_t phase, uint8_t governor, int8_t role[], game_setting *set, int32_t *pDeck_size, int32_t *pCard_using, int32_t deck[], sList *dis, int32_t chapel[], uint8_t lib);
void produce(sList *hand, int32_t **construction, int32_t *pNum_of_con, int32_t *pNum_of_emp, int32_t **good, int32_t *pNum_of_good, int8_t *ability, uint8_t phase, uint8_t governor, int8_t role[], game_setting *set, int32_t *pDeck_size, int32_t *pCard_using, int32_t deck[], sList *dis, int32_t chapel[], uint8_t lib);
void trade(sList *hand, int32_t **construction, int32_t *pNum_of_con, int32_t *pNum_of_emp, int32_t **good, int32_t *pNum_of_good, int8_t *ability, uint8_t phase, uint8_t governor, int8_t role[], game_setting *set, int32_t *pDeck_size, int32_t *pCard_using, int32_t deck[], sList *dis, int32_t chapel[], uint8_t price, uint8_t lib);
