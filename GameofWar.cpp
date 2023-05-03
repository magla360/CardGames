#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

	
string ranks[13] = {"Ace", "2", "3","4",
                 	"5","6","7","8",
                    "9","10","Jack","Queen","King"};

string suits[4] = {"Spades", "Hearts", "Clubs", "Diamonds"};
                    
bool p1hand[52] =  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool p2hand[52] =  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
bool p1hold[52] =  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool p2hold[52] =  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
bool warhold[52] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int p1card_temp, p2card_temp;
bool wartime = false;

bool deck_ofcards[52] = {}; //deck of cards

void reset(bool deck[]){
	for(int i = 0; i < 52; i++){
		deck[i] = false; //false is NOT PRESENT; true is PRESENT
	}
}

//function that prints out the rank and suit of an integer
void printCard(int cardnum){
	int rankIndex = cardnum % 13;
    int suitIndex = cardnum / 13;
    deck_ofcards[cardnum] = false;
    cout << ranks[rankIndex] << " of " << suits[suitIndex];
}

//counts the number of cards left in a certain deck
int cardsLeft(bool deck[]){
	int counter = 0;
	for(int i = 0; i < 52; i++){
		if(deck[i] == true){
			counter++;
		}
	}
	return counter;
}

void transfer(bool str[], bool des[]){ //transfers the cards in one array over to another
	for(int i = 0; i < 52; i++){
		if(str[i] == 1){
			des[i] = 1;
			str[i] = 0;
		}
	}
}

//returns a unique card from a certain deck
int dealCard(bool deck[]){
	int cardnumber;
	int card_of;
	if(cardsLeft(p1hand) < 1){ //transfer hold to hand when its empty (player 1)
		transfer(p1hold, p1hand);
	}
		
	if(cardsLeft(p2hand) < 1){ //transfer hold to hand when its empty (player 2)
		transfer(p2hold, p2hand);
	}	

	do{
	    cardnumber = rand() % 52;
	}while(deck[cardnumber] == false);
	
	deck[cardnumber] = false;

	return cardnumber;
}

//prints out the whole boolean array (can be used for testing)
void printArray(bool arr[]){
	for(int i = 0; i < 52; i++){ 
		cout << arr[i];
	}
	cout << endl;
}

int rankof(int cardnum){
	return cardnum % 13;  // this returns the rank of the card
}

int compare(int a, int b){ //function that compares the two cards
	if(rankof(a) == 0 && b != 0) //when card is ACE
		return 1;
	if(rankof(b) == 0 && a != 0) //Also when card is ACE
		return 2;
	if(rankof(a) > rankof(b)) //if card (a) is greater than card (b)
		return 1;
	else if(rankof(a) < rankof(b)) //if card (b) is greater than card (a)
		return 2;
	else
		return 0; //tie
}

//After the comparision of the cards, it goes into the winner's array
void cardBeats(int n){
	if(n == 1){
		p1hold[p2card_temp] = 1;
		p1hold[p1card_temp] = 1;
		p2hand[p2card_temp] = 0;
		cout << "Player 1's card beats Player 2's card!" << endl;
		wartime = false;
	}
	
	else if(n == 2){// when user 2 deals higher card
		p2hold[p1card_temp] = 1;
		p2hold[p2card_temp] = 1;
		p1hand[p1card_temp] = 0;
		cout << "Player 2's card beats Player 1's card" << endl;
		wartime = false;
	}
	
	else{
		warhold[p1card_temp] = 1; //takes in the cards that went into war
		warhold[p2card_temp] = 1;
		wartime = true;
	}
}



int main(){
	srand(time(0));
	int rounds = 1;
	bool war_again = false;
	bool p1_won = false;
	bool p2_won = false;
	bool winner_found = false;
	
	do{
		do{

			cout << endl;
			cout << "Round: " << rounds << endl; //prints out rounds
			cout << "P1HAND: " << cardsLeft(p1hand) << " | P1HOLD: " << cardsLeft(p1hold) << endl;
			cout << "P2HAND: " << cardsLeft(p2hand) << " | P2HOLD: " << cardsLeft(p2hold) << endl;
			
			//if one player has no more cards, then end game
			if((cardsLeft(p1hand) + cardsLeft(p1hold) == 0) || (cardsLeft(p2hand) + cardsLeft(p2hold) == 0)){
				wartime = true;
				winner_found = true;
			}
			else{
				p1card_temp = dealCard(p1hand); 
				cout << "Player one has drawn ";
				printCard(p1card_temp);
						
				p2card_temp = dealCard(p2hand);
				cout << "\nPlayer two has drawn ";
				printCard(p2card_temp);
				cout << endl;
			
				cardBeats(compare(p1card_temp, p2card_temp)); // printing out who beats who			
				rounds++; //round increase by one
				cout << "\n\n====================================================\n";
			}

		}while(!wartime); //when two cards are the same, war time starts
		
		//printing out the winner/loser
		if ((cardsLeft(p1hand) + cardsLeft(p1hold) == 0)){
			winner_found = true;
			cout << "PLAYER 1 HAS NO MORE CARDS!" << endl;
			cout << "GAME OVER! **PLAYER 2 WINS!!!**";	
		}
			
		else if((cardsLeft(p2hold) + cardsLeft(p2hand) == 0)){
			winner_found = true;
			cout << "PLAYER 2 HAS NO MORE CARDS!" << endl;
			cout << "GAME OVER! **PLAYER 1 WINS!!!**";
		}
		else{
		//when players don't have enough cards to go into war
		if(cardsLeft(p1hand) + cardsLeft(p1hold) < 4){
			winner_found = true;
			cout << "PLAYER 1 ONLY HAS " << cardsLeft(p1hand) + cardsLeft(p1hold) << " CARDS LEFT!" << endl;
			cout << "PLAYER 1 DOESN'T HAVE ENOUGH CARDS TO GO INTO WAR!" << endl;
			cout << "GAME OVER! **PLAYER 2 WINS**";
		}
		else if(cardsLeft(p2hand) + cardsLeft(p2hold) < 4){
			winner_found = true;
			cout << "PLAYER 2 ONLY HAS " << cardsLeft(p2hand) + cardsLeft(p2hold) << " CARDS LEFT!" << endl;
			cout << "PLAYER 2 DOESN'T HAVE ENOUGH CARDS TO GO INTO WAR!" << endl;
			cout << "GAME OVER! **PLAYER 1 WINS**";
		}
		else{
			do{
				//war starts 
				cout << "I DECLARE WAR!" << endl;
				for(int i = 0; i < 3; i++){ //player 1 takes out their cards
					p1card_temp = dealCard(p1hand); 
					cout << "\nPlayer one has anted ";
					printCard(p1card_temp);
					warhold[p1card_temp] = 1; //puts p1 cards into warhold array
				}
				
				for(int i = 0; i < 3; i++){//player 2 takes out their cards
					p2card_temp = dealCard(p2hand);
					cout << "\nPlayer two has anted ";
					printCard(p2card_temp);
					warhold[p2card_temp] = 1;
				}
				
				p1card_temp = dealCard(p1hand); 
				cout << "\nPlayer one has anted ";
				printCard(p1card_temp); //takes out the card that will be comparing 
				warhold[p1card_temp] = 1;

				p2card_temp = dealCard(p2hand);
				cout << "\nPlayer two has anted ";
				printCard(p2card_temp);
				warhold[p2card_temp] = 1;
				
				cout << endl;
				
				if(compare(p1card_temp, p2card_temp) == 1){ //compares the last two cards
					cout << "Player 1 won the war!";
					transfer(warhold, p1hand); //transfers all the cards into the winner's hand
					war_again = false; 
				}
				else if(compare(p1card_temp, p2card_temp) == 2){
					cout << "Player 2 won the war!";
					transfer(warhold, p2hand);
					war_again = false; //no need to keep looping for another war
				}
				else
					war_again = true;
				
				cout << endl;
				rounds++;
				cout << "\n\n====================================================\n";
			}while(war_again == true); //keeps looping when the last two anted cards are the same
		}
	}		 
	}while(!winner_found); //keeps looping until someone runs out of cards
}
