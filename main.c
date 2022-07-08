#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#include"header.h"
#include"conio.h"

int main()
{	
	atexit(bye);
	srand(time(NULL));
	game_setting set =
	{
		.difficulty = 0,
		.players = 4,
		.cheat = 0
	
	};
	
	char opt = '\0';
	while(1){
		main_menu();
		opt = getch();
		if(opt == '1'){
			game(&set);
		}
		else if(opt == '2'){
		
			setting(&set);
				
		}
		else if(opt == '3'){
			intro();
		}
		else if(opt == '0'){	
				
			return 0;
		}
		else{
			
			continue;
		}
		
		
	}
	

	return 0;
}

void game(game_setting *set)
{
	system("clear");
	int8_t governor = 0;
	int8_t role[5] = {0};
	/*
	* 0 is builder 
	* 1 is councillor
	* 2 is producer
	* 3 is prospector
	* 4 is trader
	*/
	
	//all cards
	int32_t deck[110] = {
		INDIGO_PLANT,0,0,0,0,0,0,0,0,0,
		SUGAR_MILL,1,1,1,1,1,1,1,
		TOBACCO_STORAGE,2,2,2,2,2,2,2,
		COFFEE_ROASTER,3,3,3,3,3,3,3,
		SILVER_SMELTER,4,4,4,4,4,4,4,
		TOWER,5,5,
		CHAPEL,6,6,
		SMITHY,7,7,
		POOR_HOUSE,8,8,
		BLACK_MARKET,9,9,
		CRANE,10,10,
		CARPENTER,11,11,
		QUARRY,12,12,
		WELL,13,13,
		AQUEDUCT,14,14,
		MARKET_STAND,15,15,
		MARKET_HALL,16,16,
		TRADING_POST,17,17,
		ARCHIVE,18,18,
		PREFECTURE,19,19,
		GOLD_MINE,20,20,
		LIBRARY,21,21,
		STATUE,22,22,
		VICTORY_COLUMN,23,23,
		HERO,24,24,
		GUILD_HALL,25,
		CITY_HALL,26,
		TRIUMPHAL_ARCH,27,
		PALACE,28	
	};
	
	int32_t deck_size = 110;
	int32_t *pDeck_size = &deck_size;
	//counter for deck
	int32_t card_using = set ->  players;
	int32_t *pCard_using = &card_using;
	
	sList d;
	sList *dis = &d;
	initList(dis);
	
	shuffle(deck,deck_size,set -> players);
	
	#ifdef DEBUG
	for(int i = 0; i < 110; i++){
		printf("%d %d\t", deck[i], i);
		if((i + 1) % 4 == 0){
			puts("");
			
		}
	}
	puts("");
	#endif
	
	uint8_t cost[30] = {1,2,3,4,5,3,3,1,2,2,2,3,4,2,3,2,4,2,1,3,1,5,3,4,5,6,6,6,6,100};
	
	uint8_t price[5][5] = {{1,1,1,2,2},{1,1,2,2,2},{1,1,2,2,3},{1,2,2,2,3},{1,2,2,3,3}};
	
	//create players' hand cards linked list
	sList hand[4];
	//distribute the cards
	for(int i = 0; i < set -> players; i++){
		initList( &(hand[i]));
		for(int j = 0; j < 5 + i; j++, card_using++){
			addNode(&(hand[i]),deck[card_using]);
		}
	}
	
	//calloc points gotton form chapel
	int32_t *chapel = calloc(set -> players,sizeof(int32_t));
	for(int i = 0; i < set -> players; i++){
		chapel[i] = 0;
	}
	
	//calloc platers' abilities 
	int8_t **ability = calloc(set -> players,sizeof(int8_t *));
	for(int i = 0; i < set -> players; i++){
		ability[i] = calloc(29,sizeof(int8_t));
		for(int j = 0; j < 29; j++){
			ability[i][j] = 0;
		}
	}
	
	//calloc construction
	int32_t **construction = calloc(set -> players,sizeof(int32_t *));
	for(int i = 0; i < set -> players; i++){
		construction[i] = calloc(12,sizeof(int32_t));
		
		for(int j = 1; j < 12; j++){
			construction[i][j] = -1;
		}
	}
	
	//calloc numbers of constructions
	int32_t *num_of_con = calloc(set -> players,sizeof(int32_t));
	for(int i = 0; i < set -> players; i++){
		num_of_con[i] = 1;
	}
	
	//calloc numbers of empty prodution budings
	int32_t *num_of_emp = calloc(set -> players,sizeof(int32_t));
	for(int i = 0; i < set -> players; i++){
		num_of_emp[i] = 1;
	}
	
	//calloc the good of construction
	int32_t **good = calloc(set -> players,sizeof(int32_t *));
	for(int i = 0; i < set -> players; i++){
		good[i] = calloc(12,sizeof(int32_t));
		
		for(int j = 0; j < 12; j++){
			good[i][j] = -1;
		}
	}
	
	//calloc numbers of goods
	int32_t *num_of_good = calloc(set -> players,sizeof(int32_t));
	for(int i = 0; i < set -> players; i++){
		num_of_good[i] = 0;
	}
	
	#ifdef DEBUG
	/*
	for(int i = 0; i < set -> players; i++){
		for(int j = 0; j < 12; j++){
			printf("%d", construction[i][j]);
		}
		puts("");
	}
	
	for(int i = 0; i < set -> players; i++){
		for(int j = 1; j < 12; j++){
			construction[i][j] = rand() % 29;
		}
	}
	
	puts("-----------------------------------------");
	for(int i = 0; i < set -> players; i++){
		for(int j = 0; j < 12; j++){
			printf("%d  ", construction[i][j]);
		}
		puts("");
	}
	*/
	printf("hand[0].size: %d\n",hand[0].size);
	#endif
	
	
	uint8_t title = rand() % 4;
	char opt = '\0';
	uint32_t round = 1;
	uint8_t rNow = 0; //role now
	uint8_t phase = 0; // 0 is player 1, 2, 3 are CPU
	uint8_t lib = 1;
	
	while(1){
	
		if(ability[0][CHAPEL]){
			print_screen();
			chapel_card(&chapel[0],&(hand[0]),dis);
		}
		
		for(int i = 1; i < set -> players; i++){
			if(ability[i][CHAPEL] == 1 && hand[i].size > 1){
				if(construction[i][3] == -1){
					addNode(dis,getMax(&(hand[i])));
					delNode(&(hand[i]),getMax(&(hand[i])));
				}
				else{
					addNode(dis,getMin(&(hand[i])));
					delNode(&(hand[i]),getMin(&(hand[i])));
				}
				
				chapel[i]++;
					
			}
		}

		
		
		//reset roles can be choosed
		memset(role,1,5);
		
		print_screen();
		
		//first round discard
		if(round == 1){
	
				puts("You need to discard down to 4 cards.");
				discard(&(hand[0]),dis);
				print_screen();
		
			
			for(int i = 1; i < set -> players; i++){
				for(int j = 0; j < i + 1; j++){
					addNode(dis,getMax(&(hand[i])));
					delNode(&(hand[i]),getMax(&(hand[i])));
				}
				printf("CPU %d discards down to 4 cards.\n", i);
				pause();
				print_screen();
			}
		}
		//else round discard
		else{
			for(int i = hand[0].size; i > (ability[0][TOWER] ? 12 : 7); i--){
				print_screen();
				printf("You need to discard down to %d cards.\n", (ability[0][TOWER] ? 12 : 7));
				discard(&(hand[0]),dis);
			}
			for(int i = 1; i < set -> players; i++){
			
				for(int j = hand[i].size, k = 0; j > (ability[i][TOWER] ? 12 : 7); j--, k++){
					if(k == 0){
						printf("CPU %d discards.\n", i);
						pause();
						print_screen();
					}
					if(num_of_emp[i] >= 3){
						addNode(dis,getMax(&(hand[i])));
						delNode(&(hand[i]),getMax(&(hand[i])));
					}
					else{
						addNode(dis,getMin(&(hand[i])));
						delNode(&(hand[i]),getMin(&(hand[i])));
					}
				}
				
			}
		}
		
		
		
		
		phase = governor;
		for(int i = 0; i < set -> players; i++){
			
			print_screen();
			if(phase == 0){
				
				while(1){
					print_screen();
					puts("Please choose a role: ");
					opt = getch();
					int32_t cho = opt - '0';
					if(cho > 0 && cho < 6){
						if(role[cho - 1]){
							print_screen();
							switch(cho - 1){
								case BUILDER:
									puts("Builder");
									puts("Action: each player can build one building.");
									puts("Privilige: bulilder pay one card less.");
								break;
								case COUNCILLOR:
									puts("Councillor");
									puts("Action: each player chooses one of two cards.");
									puts("Privilige: councillor draw additional three card.");
								break;
								case PRODUCER:
									puts("Producer");
									puts("Action: each player can produce one good.");
									puts("Privilige: Producer can produce one additional good.");
								break;
								case PROSPECTOR:
									puts("Prospector");
									puts("Action: none.");
									puts("Privilige: prospector draw one card.");
								break;
								case TRADER:
									puts("Trader");
									puts("Action: each player can sell one good.");
									puts("Privilige: trader can sell one additional good.");
								break;
							}
							puts("");
							puts("Do you want to choose this one? press 'y' for yes, else for no.");
							opt = getch();
							if(opt == 'y'){
								rNow = cho - 1;
								role[cho - 1] = 0;
								print_screen();
								//printf("rNow: %hhu\n", rNow);
								break;
							}
							else{
								continue;
							}
						}
					}
					
				}
					
			}
			else{
				if(set -> difficulty){
				
					if(role[PROSPECTOR]){
						
						role[PROSPECTOR] = 0;
						rNow = PROSPECTOR;
						print_screen();
						printf("CPU %hhu chooses to be prospector.\n", phase);
						pause();
					}
					else if(role[COUNCILLOR]){
						role[COUNCILLOR] = 0;
						rNow = COUNCILLOR;
						print_screen();
						printf("CPU %hhu chooses to be councillor.\n", phase);
						pause();
					}
					else if(role[TRADER]){
						role[TRADER] = 0;
						rNow = TRADER;
						print_screen();
						printf("CPU %hhu chooses to be trader.\n", phase);
						pause();
					}
					else if(role[PRODUCER]){
						role[PRODUCER] = 0;
						rNow = PRODUCER;
						print_screen();
						printf("CPU %hhu chooses to be producer.\n", phase);
						pause();
					}
					else{
						role[BUILDER] = 0;
						rNow = BUILDER;
						print_screen();
						printf("CPU %hhu chooses to be builder.\n", phase);
						pause();
					}
				
				}
				else{
					if(role[PROSPECTOR]){
						
						role[PROSPECTOR] = 0;
						rNow = PROSPECTOR;
						print_screen();
						printf("CPU %hhu chooses to be prospector.\n", phase);
						pause();
					}
					else if(hand[phase].size > cost[getMin(&(hand[phase]))] && role[BUILDER]){
						
						role[BUILDER] = 0;
						rNow = BUILDER;
						print_screen();
						printf("CPU %hhu chooses to be builder.\n", phase);
						pause();
					}
					else if(num_of_emp[phase] > 1 && role[PRODUCER]){
						
						role[PRODUCER] = 0;
						rNow = PRODUCER;
						print_screen();
						printf("CPU %hhu chooses to be producer.\n", phase);
						pause();
					}
					else if(num_of_good[phase] > 1 && role[TRADER]){
						
						role[TRADER] = 0;
						rNow = TRADER;
						print_screen();
						printf("CPU %hhu chooses to be trader.\n", phase);
						pause();
					}
					else if(role[COUNCILLOR]){
						role[COUNCILLOR] = 0;
						rNow = COUNCILLOR;
						print_screen();
						printf("CPU %hhu chooses to be councillor.\n", phase);
						pause();
					}
					else if(hand[phase].size > 0 && role[BUILDER]){
					
						role[BUILDER] = 0;
						rNow = BUILDER;
						print_screen();
						printf("CPU %hhu chooses to be builder.\n", phase);
						pause();
					
					}
					else if(num_of_good[phase] && role[TRADER]){
						role[TRADER] = 0;
						rNow = TRADER;
						print_screen();
						printf("CPU %hhu chooses to be trader.\n", phase);
						pause();
					}
					else if(role[PRODUCER]){
						role[PRODUCER] = 0;
						rNow = PRODUCER;
						print_screen();
						printf("CPU %hhu chooses to be producer.\n", phase);
						pause();
					}
					else if(role[TRADER]){
						role[TRADER] = 0;
						rNow = TRADER;
						print_screen();
						printf("CPU %hhu chooses to be trader.\n", phase);
						pause();
					}
					else{
						
						role[BUILDER] = 0;
						rNow = 0;
						print_screen();
						printf("CPU %hhu chooses to be builder.\n", phase);
						pause();
					}
					
				}
			}
			
			for(int j = 0, act = phase; j < set -> players; j++){
				
				switch(rNow){
					case BUILDER:
						if(act == 0){
							build(parameter);	
						}
						else{
						
						
							if(set -> difficulty == 2){
								print_screen();
								printf("CPU %hhu builds nothing.\n", act);
								pause();
								if(act < set -> players - 1){
									act++;
								}
								else{
									act = 0;
								}
								continue;
							}
							
							sListNode *pNode = hand[act].pHead; ;
							uint8_t using;
							if(hand[act].size == 0){
								print_screen();
								printf("CPU %hhu builds nothing.\n", act);
								pause();
								if(act < set -> players - 1){
									act++;
								}
								else{
									act = 0;
								}
								continue;
							}
							
							if(num_of_emp[act] < 2){
							
								if(pNode == NULL){
									print_screen();
									printf("CPU %hhu builds nothing.\n", act);
									pause();
									if(act < set -> players - 1){
										act++;
									}
									else{
										act = 0;
									}
									continue;
								}
								
								while(pNode -> data > SILVER_SMELTER && pNode){
									pNode = pNode -> pNext;
									if(pNode == NULL){
										break;
									}
								}
								
								if(pNode == NULL){
									print_screen();
									printf("CPU %hhu builds nothing.\n", act);
									pause();
									if(act < set -> players - 1){
										act++;
									}
									else{
										act = 0;
									}
									continue;
								}
								
								using = (cost[pNode -> data] - (phase == act ? 1 + (ability[act][LIBRARY] * lib): 0) - (ability[act][QUARRY] && (pNode -> data >= TOWER) ? 1 : 0));
								if(pNode -> data <= SILVER_SMELTER && ability[act][SMITHY]){
									using--;
								}
								
								while(using > hand[act].size && pNode){
									pNode = pNode -> pNext;
									
									if(pNode == NULL){
										break;
									}
									
									using = (cost[pNode -> data] - (phase == act ? 1 + ability[act][LIBRARY] * lib : 0) - (ability[act][QUARRY] && (pNode -> data >= TOWER) ? 1 : 0));
									if(pNode -> data <= SILVER_SMELTER && ability[act][SMITHY]){
										using--;
									}
								}
								
								if(pNode == NULL){
									print_screen();
									printf("CPU %hhu builds nothing.\n", act);
									pause();
									if(act < set -> players - 1){
										act++;
									}
									else{
										act = 0;
									}
									continue;
								}
							}
							else{
							
								if(pNode == NULL){
									print_screen();
									printf("CPU %hhu builds nothing.\n", act);
									pause();
									if(act < set -> players - 1){
										act++;
									}
									else{
										act = 0;
									}
									continue;
								}
								
								using = (cost[pNode -> data] - (phase == act ? 1 + (ability[act][LIBRARY] * lib) : 0) - (ability[act][QUARRY] && (pNode -> data >= TOWER) ? 1 : 0));
								if(pNode -> data <= SILVER_SMELTER && ability[act][SMITHY]){
									using--;
								}
								
								while(cost[pNode -> data] >= hand[act].size && ability[pNode -> data] && pNode){
									pNode = pNode -> pNext;
									if(pNode == NULL){
										break;
									}
									using = (cost[pNode -> data] - (phase == act ? 1 + (ability[act][LIBRARY] * lib) : 0) - (ability[act][QUARRY] && (pNode -> data >= TOWER) ? 1 : 0));
									if(pNode -> data <= SILVER_SMELTER && ability[act][SMITHY]){
										using--;
									}
								}
								
							}
							
							if(pNode == NULL){
								print_screen();
								printf("CPU %hhu builds nothing.\n", act);
								pause();
								if(act < set -> players - 1){
									act++;
								}
								else{
									act = 0;
								}
								continue;
							}
							
							construction[act][num_of_con[act]] = pNode -> data;
							if(construction[act][num_of_con[act]] <= SILVER_SMELTER){
								num_of_emp[act]++;
							}
							num_of_con[act]++;
							ability[act][pNode -> data]++;
							delNode(&(hand[act]),pNode -> data);
							
							if(hand[act].size == using){
								delAllNode(&(hand[act]));	
							}
							else{
							
								for(int k = 0; k < using; k++){
									if(hand[act].size - using > 2){
										delNode(&(hand[act]),getMax(&(hand[act])));
									}
									else{
										delNode(&(hand[act]),getMin(&(hand[act])));
									}
								}
								
							}
							
							print_screen();
							printf("CPU %hhu builds.\n", act);
							pause();
							
							
							if(ability[act][CARPENTER] && pNode -> data >= TOWER && pNode -> data != CARPENTER){
								addNode(&(hand[act]),deck[card_using]);
								card_using++;
								reshuffle();
							}
							if(ability[POOR_HOUSE] && hand -> size <= 1 && pNode -> data != POOR_HOUSE){
								print_screen();
								addNode(hand,deck[card_using]);
								card_using++;
								reshuffle();
							}	
									
						}				
						
						
					break;
					case COUNCILLOR:
						if(act == 0){
							council(parameter);
						}
						else{
							uint8_t draw = 2;
							uint8_t get = 1;
							
							if(act == phase){
								draw += 3;
								if(ability[act][LIBRARY] && lib){
									draw += 3;
								}
							}
							
							if(ability[act][PREFECTURE]){
								get = 2;
							}
							
							if(ability[act][ARCHIVE]){
								for(int k = 0; k < draw; k++){
									addNode(&(hand[act]),deck[card_using]);
									card_using++;
									reshuffle();
								}
								
								for(int k = 0; k < draw - get; k++){
									if(num_of_emp[act] >= 2){
										addNode(dis,getMax(&(hand[act])));
										delNode(&(hand[act]),getMax(&(hand[act])));
									}
									else{
										addNode(dis,getMin(&(hand[act])));
										delNode(&(hand[act]),getMin(&(hand[act])));
									}
								}
								
								
							}
							else{
								sList temp;
								initList(&temp);
								for(int i = 0; i < draw; i++){
									addNode(&temp,deck[card_using]);
									(card_using)++;
									reshuffle();
								}
								sListNode *pNode;
								for(int i = 0; i < get; i++){
									
									if(num_of_emp[act] >= 2){
										pNode = temp.pHead;
									}
									else{
										pNode = temp.pTail;
									}
									addNode(&(hand[act]),pNode -> data);
									delNode(&temp,pNode -> data);
								}
								
								pNode = temp.pHead;
								while(pNode){
									addNode(dis,pNode -> data);
									delNode(&temp,pNode -> data);
									pNode = pNode-> pNext;
								}
							}
							
							print_screen();
							printf("CPU %hhu draws %hhu cards and keeps %hhu\n",act,draw,get);
							pause();
						}
					break;
					case PRODUCER:
						if(act == 0){
							produce(parameter);
						}
						else{
						
							int32_t already = 0;
							int32_t produce = 1;
							if(ability[act][AQUEDUCT]){
								if(ability[act][LIBRARY] && lib){
									if(phase == act){
										produce = 4;
									}
								}
								else{
									if(phase == act){
										produce = 2;
									}
									else{
										produce = 3;
									}
								}
							}
							else{
								if(phase == act){
									produce++;
									if(ability[act][LIBRARY] && lib){
										produce++;
									}
								}
							}
							
							if(set -> difficulty == 2){
								produce = 0;	
								print_screen();
								printf("CPU %hhu produces nothing.\n", act);
								pause();
							}
							else if(set -> difficulty){
								produce = 1;
							}
							
							for(int k = 0; k < produce; k++){
							
								if(num_of_emp[act] == 0 && k == 0){
									print_screen();
									printf("CPU %hhu produces nothing.\n", act);
									pause();
									break;
								}
								else if(num_of_emp[act] == 0){
									break;
								}
								
								for(int l = 11; l >= 0; l--){
									if(construction[act][l] != -1 && construction[act][l] <= SILVER_SMELTER && good[act][l] == -1){
										#ifdef DEBUG
											print_screen();
											puts("DEBUG");
											printf("construction[act][l]: %d\n",construction[act][l]);
											printf("l: %d  act: %hhu\n", l, act);
											printf("good[act][l]: %d\n",good[act][l]);
									
											pause();
										#endif
										good[act][l] = deck[card_using];
										num_of_good[act]++;
										num_of_emp[act]--;
										card_using++;
										already++;
										reshuffle();
										break;
									}
								}
								
							}
							
							if(already > 0){
								print_screen();
								printf("CPU %hhu produces %d goods.\n", act, already);
								pause();
							}
							
							
							if(ability[act][WELL] && already >= 2){
								addNode(&(hand[act]),deck[card_using]);
								card_using++;
								reshuffle();
							}
						}
							
					break;
					case PROSPECTOR:
						if(act == 0){
							prospect(parameter);
						}
						else{
						
							if(act == phase){
								print_screen();
								if(ability[act][LIBRARY] && lib){
									printf("CPU %hhu draws 2 cards because of library.\n", act);
									pause();
									for(int i = 0; i < 2; i++){
										addNode(&(hand[act]),deck[card_using]);
										card_using++;
										reshuffle();
									}
								}
								else{
									printf("CPU %hhu draws one card.\n", act);
									pause();
									addNode(&(hand[act]),deck[card_using]);
									card_using++;
									reshuffle();
								}
								
							}
							else{
								print_screen();
								printf("CPU %hhu does nothing.\n", act);
								pause();
							}
							
						}
						
					break;
					case TRADER:
						if(act == 0){
							trade(parameter,title);
						}
						else{
							//CPU////////////////////////////////////////////////////
							int32_t already = 0;
							int32_t trade = 1;
							
							if(ability[act][TRADING_POST]){
								if(ability[act][LIBRARY] && lib){
									if(phase == act){
										trade = 4;
									}
								}
								else{
									if(phase == act){
										trade = 2;
									}
									else{
										trade = 3;
									}
								}
							}
							else{
								if(phase == act){
									trade++;
									if(ability[act][LIBRARY] && lib){
										trade++;
									}
								}
							}
							
							if(set -> difficulty == 2){
								trade = 0;
								print_screen();
								printf("CPU %hhu sells nothing.\n", act);
								pause();	
							}
							else if(set -> difficulty){
								trade = 1;
							}
							
							for(int k = 0; k < trade; k++){
								if(num_of_good[act] == 0 && k == 0){
									print_screen();
									printf("CPU %hhu trades nothing.\n", act);
									pause();
									break;
								}
								else if(num_of_good[act] == 0){
									break;
								}
								
								for(int l = 11; l >= 0; l--){
								
									if(good[act][l] >= 0){
										print_screen()
										printf("CPU %hhu sells ", act);
										switch(construction[act][l]){
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
										puts("");
										
										for(int j = 0; j < price[title][construction[act][l]]; j++){
											addNode(&(hand[act]),deck[card_using]);
											card_using++;
											reshuffle();
										}
										addNode(dis,good[act][l]);
										good[act][l] = -1;
										num_of_good[act]--;
										num_of_emp[act]++;
										pause();
									
										break;
									}
								}
							}
							
							if(ability[act][MARKET_HALL] && already >= 1){
								addNode(&(hand[act]),deck[*pCard_using]);
								card_using++;
								reshuffle();
							}
							if(ability[act][MARKET_STAND] && already >= 2){
								addNode(&(hand[act]),deck[*pCard_using]);
								card_using++;
								reshuffle();								
							}						
														
						}
						
					break;
					 
				}
				
				
				
				if(act < set -> players - 1){
					act++;
				}
				else{
					act = 0;
				}
			}
			
			if(rNow == BUILDER){
				for(int k = 0; k < set -> players; k++){
					if(num_of_con[i] == 12){
						print_screen();
						puts("Some players have built 12 buildings.");
						pause();
						goto end;
					}
				}
			}
			else if(rNow == TRADER){
			
				title++;
				if(title > 4){
					title = 0;
				}	
				
			}
			else if(rNow == PROSPECTOR){
				for(int j = phase, k = 0; k < set -> players; k++){
					if(ability[j][GOLD_MINE]){
						sList temp;
						initList(&temp);
						for(int i = 0; i < 4; i++){
							addNode(&temp,deck[card_using]);
							card_using++;
							reshuffle();
						}
						print_screen();
						if(j == 0){
							puts("you draw 4 cards because of gold mine.");
							print_hand(&temp,cost);
						}
						sListNode *pNode = temp.pHead;
						int32_t check[4] = {0};
						int32_t counter = 0;
						for(int i = 0; i < 4; i++){
							check[i] =  cost[pNode -> data];
							pNode = pNode -> pNext;
						}
						pNode = temp.pHead;
						for(int l = 0; l < 4; l++){
							if(check[l % 4] != check[(l + 1) % 4]){
								counter++;	
							}
						}
						if(counter == 4){
							if(j == 0){
								puts("Congratulations! You can gain one of them. ");
								char opt = '\0';
								int32_t cho = 0;
								while(1){
									opt = getch();
									cho = (int32_t)opt - '0';
									if(cho < 1 || cho > 4){
										continue;
									}
									else{
										pNode = temp.pHead;
										for(int i = 0; i < cho - 1; i++){
											pNode = pNode -> pNext;
										}
										addNode(&(hand[0]),pNode -> data);
										delNode(&temp,pNode -> data);
										
										pNode = temp.pHead;
										for(int k = 0 ; k < 3; k++){
											addNode(dis,pNode -> data);
										}
										delAllNode(&temp);
										break;
									}
								}
							}
							else{
								printf("CPU %d finds gold.\n", j);
								if(hand[j].size > (ability[j][TOWER] ? 5 : 3)){
									addNode(&(hand[j]),getMax(&temp));	
									delNode(&temp,getMax(&temp));
								}
								else{
									addNode(&(hand[j]),getMin(&temp));	
									delNode(&temp,getMin(&temp));
								}
								pause();
								pNode = temp.pHead;
								for(int k = 0 ; k < 3; k++){
									addNode(dis,pNode -> data);
								}
								delAllNode(&temp);
								
							}
						}
						else{
							if(j == 0){
								puts("Failed. You gain nothing.");
							}
							else{
								printf("CPU %d failed to mine.\n", j);
							}
							pause();
							while(pNode){
								addNode(dis,pNode -> data);
								delNode(&temp,pNode -> data);
								pNode = pNode-> pNext;
							}
						}
					}
					if(j < set -> players - 1){
						j++;
					}
					else{
						j = 0;
					}
		
				}
			}
			#ifdef DEBUG
					puts("");
					printf("hand[0].size: %d\n",hand[0].size);
					for(int i = 0; i < set -> players; i++){
						printf("%i\n",i);
						print_hand(&(hand[i]),cost);
						printf("con%d emp%d good%d\n", num_of_con[i], num_of_emp[i], num_of_good[i]);
					}
					puts("");
					printList(dis);
				
					// leave for debug
					puts("now press 0 to leave");
					opt = getch();
					if(opt == '0'){
						break;
					}
			#endif
			if(set -> players == 2){
				if(i == 1 && lib){
					i--; // one more time
					lib = 0;
				}
				else if(i == 1 && lib == 0){
					lib = 1;
				}
				
			}
			
			if(phase < set -> players - 1){
				phase++;
			}
			else{
				phase = 0;
			}
			
		}
		
		if(governor < set -> players - 1){
			governor++;
		}
		else{
			governor = 0;
		}
		round++;
		print_screen();
		puts("This round ends. Press Esc to return to main menu or else to continue...");
		opt = getch();
		if(opt == 27){
			goto esc;
		}
	}
	
	end:
	end_game(construction,ability,hand,chapel,num_of_good,set -> players);
	esc:
	for(int i = 0; i < set -> players; i++){
		free(construction[i]);
		free(good[i]);
		free(ability[i]);
		delAllNode(&(hand[i]));
	}
	free(chapel);
	free(construction);
	free(good);
	free(ability);
	free(num_of_con);
	free(num_of_emp);
	free(num_of_good);
	return;
}
