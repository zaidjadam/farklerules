/*
 *                      NOTE
 *    THIS PROGRAM USES SQLITE library, therefore for it to work
 *    you must have SQLite libraries included in the lib directory
 *
 *
 *
 * Comment, Description of the usage and working of the class.
 *
 *
 * no try catch blocks
 *
 *
 * This file contains the main function
 * the player class
 * and the Dice class
 *      Main Class
 * Is where the player object is created and the
 * and call
 *
 *     Dice Class
 *This implements the die object in the game
 *
 *		player
 *This is implements the player object in the game
 * */

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
using namespace std;

/*
 * this class implements the dice object in the game
 * */
class Dice{

private:
	int diceValue[6];
	bool rerollDiceValue[6];
	int rollDieCount;
	int countForReRoll;

public:

	//Constructor
	Dice()
	{

		for(int i= 0; i < 6; i++){   /*Meaningless variables*/
			diceValue[i] = 0;
			rerollDiceValue[i] = false;

		}

		countForReRoll = 0;
		rollDieCount = 0;
	}

	//Roll of six Dice

	void rollTheDice(){

		for(int i = 0; i < 6; i++){

			diceValue[i] = (rand() % 6 + 1);
			if(diceValue[i] != 1 && diceValue[i] != 5){

				rerollDiceValue[i] = true;

			}
		}


	}

	//The re-roll the dice which are no-point dices
	void reRollTheDice(){

		for(int i = 0; i < 6; i++){

			if(rerollDiceValue[i] == true)
				diceValue[i] = (rand() % 6 + 1);

		}


	}

	//Reset the rerollDiceValues to false
	void resetReRoll()
	{
		for(int i = 0; i < 6 ; i++){

			rerollDiceValue[i] = false;

		}

	}

	//Get the scores of the six dices as per the rules  /*No Enough comments*/
	int getRoundScore(){

		int one_Count = 0, two_Count = 0, three_Count = 0,four_Count =0,five_Count = 0, six_Count = 0;
		int score = 0;

		rollDieCount = 0;
		for(int i = 0; i < 6; i++){

			switch(diceValue[i]){
			case 1:
				score += 100;
				one_Count++;
				break;

			case 2:
				two_Count++;
				rollDieCount++;
				break;
			case 3:
				three_Count++;
				rollDieCount++;
				break;
			case 4:
				four_Count++;
				rollDieCount++;
				break;
			case 5:
				score += 50;
				five_Count++;
				break;
			case 6:
				six_Count++;
				rollDieCount++;
				break;
			}

		}

		if(rollDieCount == 6){

			cout << "Farkle!";
			score = 0;

		}else{

			if(one_Count >= 3){

				score = (score - 300) + 1000;

			}else if(two_Count >= 3){

				score += 200;

				for(int i = 0; i < 6; i++){

					if(diceValue[i] == 2){

						rerollDiceValue[i] = false;

					}
				}
				rollDieCount -= 3;

			}else if (three_Count >= 3){

					score += 300;
					for(int i = 0; i < 6 ; i++){

						if(diceValue[i] == 3){

							rerollDiceValue[i] = false;
						}

					}

					rollDieCount -= 3;

			}else if(four_Count >= 3){

				score += 400;
				for(int i =0; i < 6; i++){
					if(diceValue[i] == 4){

						rerollDiceValue[i] = false;
					}
				}

				rollDieCount -= 3;

		    }else if(five_Count >= 3){

		    	score = (score - 150 ) + 500;

		    }else if(six_Count >= 3){
		    	score += 600;
		    	for(int i = 0; i < 6 ; i++){

		    		if(diceValue[i] == 6){

		    			rerollDiceValue[i] = false;

		    		}

		    	}

		    	rollDieCount -=3;
		    }

		}

		return score;
	}

	//Display the six dice values
	void displayDice(){

		for(int i = 0; i < 6; i++){

			cout << diceValue[i] << "  ";

		}
	}

	//Get the rollDieCount
	int getRollDieCount(){

		return rollDieCount;

	}

	//set rollDieCount   /*Meaningless variables value*/
	void setRollDieCount(int value){

		rollDieCount = value;

	}


};

//Player class to hold the each round score and over all scores

class Player{

private:
	string name;
	int score;
	int totalScore;
public:
	//Constructor
	Player(){

		name =  "XXXXX";
		score = 0;
		totalScore = 0;
	}

	//Parameterized constructor
	Player(string name){

		this->name = name;
		score = 0;
		totalScore = 0;

	}

	//Set the name
	void setName(string name){

		this->name = name;

	}
	//get The name  /*Descriptive variables*/
	string getName(){

		return this->name;
	}

	//add score to the total
	void addScore(int roundscore){

		score = roundscore;
		totalScore += roundscore;
	}

	//set the score
	void setScore(int score){

		this -> score = score;

	}

	//Retrieve the total Score
	int getTotalScore(){

		return totalScore;

	}

	//Retrieve the score of each round
	int getScore(){

		return score;

	}

};

//FarkleGame class which holds the each players name,round game statues , and initializes the game for the winner

class FarkleGame{
private:
	Player *players;
	int countPlayers;
	Dice dice;
public:
	//Parametized constructor
	FarkleGame(int numPlayers){

		players = new Player[numPlayers];
		countPlayers = numPlayers;
	}

	//Read the names of the players
	void readNamesOfPlayers(){

		string name;
		for(int i = 0; i < countPlayers; i++){

			cout <<" Enter The name Of Player "<< (i + 1) << " : ";
			cin >> name;
			players[i].setName(name);
		}

	}

	//Roll the dice for each player until the player: scores 1000 or more points
    void playersToEnterGame(){

    	int score = 0;
    	for(int i = 0; i < countPlayers; i++){

    		score = 0;
    		while(score < 1000){

    			dice.rollTheDice();
    			dice.displayDice();
    			score = dice.getRoundScore();
    			cout <<"\t Points Scored: "<< score << endl;

    		}
    		players[i].addScore(score);
    		cout<<players[i].getName() <<" enters the game !" << endl << endl;

    	}

    	dice.setRollDieCount(0);
    	cout << "All players entered the game. Let's begin the game!"<<endl<<endl;

    }

    //Check whether the game score of any player reaches 1000 or more to get the index of winner
    bool winsTheGame(int *index){

    	for(int i = 0; i < countPlayers; i++){

    		if(players[i].getTotalScore() >= 10000){

    			*index = i;
    			return true;
    		}

    	  }
    	return false;
    }

    //Play each round for a player
    void eachPlayerGame(int i){

    	char wouldLikeToReRoll;
    	int score =0;
    	cout << players[i].getName() << " roll's the dice: "<< endl;
    	dice.rollTheDice();
    	dice.displayDice();
    	score = dice.getRoundScore();
    	cout << "\t Points Scored: " << score << endl;
    	players[i].setScore(score);
    	if(dice.getRollDieCount() == 0){

    		cout << "Point-dice scoring! You have got a chance to play one more round again! "<< endl;
    		players[i].addScore(score);
    		dice.reRollTheDice();
    		dice.displayDice();
    		score += dice.getRoundScore();
    		cout << "\t Points Scored: "<< score << endl << endl;
    		players[i].setScore(score);
    	}else if(dice.getRollDieCount() != 6){

    	cout<< endl << "Would you like to reroll the " << dice.getRollDieCount() << " non-point dice ? (Y/N): ";
    	cin >>wouldLikeToReRoll;
    	cout<<endl;
    	  if(wouldLikeToReRoll == 'y' || wouldLikeToReRoll == 'Y'){
    		  dice.reRollTheDice();
    		  dice.displayDice();
    		  score = dice.getRoundScore();
    		  cout << "\t Points Scored: "<< score <<endl <<endl;
    		  if(players[i].getScore() > score)
    			score = players[i].getScore();
    		  players[i].setScore(score);
    	 }else if(wouldLikeToReRoll == 'n' || wouldLikeToReRoll == 'N'){

    		cout << players[i].getName() << " turn is over ...."<<endl << endl;
    		dice.setRollDieCount(0);
    	}
    }

    dice.resetReRoll();
    cout << players[i].getName() << " your score from that round:  "<< players[i].getScore() << endl;
    players[i].addScore(score);
    cout << "Your total score after the round: "<<players[i].getTotalScore()<< endl << endl;
    cout << endl << "========================================================================"<<endl << endl;

    }

    //Play the game for multiple players
    void playEachRound(int index){

    	for(int i = index; i < countPlayers; i++){

    		eachPlayerGame(i);
    	}

    }

    //Begin the game and display the winner strategy
    /*
     * This function makes the game start
     * it has the game winner logic
     * */
    void playTheGame(){

    	int index = 0;
    	while(!winsTheGame(&index)){

    		playEachRound(0);

    	}

    	int count_one = 0;
    	int count_two = 0;
    	for(count_one = index + 1; count_one < countPlayers; count_one++){

    		eachPlayerGame(count_one);
    		count_two++;
    	}

    	if(count_two != countPlayers - 1){

    		for(count_one =0; count_one < index; count_one++)
    			eachPlayerGame(count_one);
    	}

    	int max = 0;
    	//Logic to check for the winner
    	for(int i = 0; i < countPlayers; i++){

    		if(players[i].getTotalScore() > max){

    			max = players[i].getTotalScore();
    			index = i;
    		}

    	}

    	//Display the winner
    	cout << endl << players[index].getName() << " wins the gme !" << endl;

    	//record winner
    	recordWinner(players[index].getName(),players[index].getTotalScore());

    	//add winner to database

    	//addWinner(players[index].getName(),players[index].getTotalScore());

    }

/*
 * This function records winners on a text file
 * Takes winners name and his total score
 * */
    void recordWinner(string name, int score){

    	  ofstream myfile;
    	  myfile.open ("winners.txt",std::ios_base::app);
    	  myfile << "> "<<name <<" \t "<<score<<endl;;
    	  myfile.close();



    }

    /******************************Connection ***********************/

    //Database is alread created, we just access the database tables

    /*bool connect(){

    		sqlite3* DB;
    	    int exit = 0;
    	    exit = sqlite3_open("sqlite/frules.db", &DB);
    	    if (exit) {

    	            return false;
    	     } else{

    	        sqlite3_close(DB);
    	        return true;
    		}
    }

    /****************end of connection **********************************/

    /*************************************/

  /*  void addWinner(string playername,int score){

    		sqlite3* db;
    		char* Error;
    		 int mydb = sqlite3_open("sqlite/frules.db", &db);
    		// get current date/time based on current system
    		   time_t now = time(0);
    		// convert now to string form
    		   char* dt = ctime(&now);
    		//lets check if user name exists

    		 string sql_insert = "INSERT INTO winner VALUES(";
    		 sql_insert += playername;
    		 sql_insert += ",";
    		 sql_insert +=score;
    		 sql_insert += ",";
    		 sql_insert += dt;
    		 sql_insert += ")";
    		 //execute_querry here
    		 mydb = sqlite3_exec(db, sql_insert.c_str(), NULL, 0, &Error);

    		 //check if data is added

    		 if (mydb != SQLITE_OK) {
    		         cerr << "Error Insert" << endl;
    		         sqlite3_free(Error);
    		     }else{
    		         std::cout << "Winner Added Successfully..Into Database!" <<endl;
    		     }
        sqlite3_close(db);



    }



    /**************************************/





};

//Display the rules from the text file
void displayRules(){

	string lineInFile;
	ifstream inputfile;
	inputfile.open("farkleRules.txt");
	while(getline(inputfile,lineInFile)){

		cout << lineInFile << '\n';
	}
	/*inputfile.close;*/

}

//Display the winners from the text file
void displayWinners(){

	cout<<" ***************  Recorded Winners **************************"<<endl;
	cout<<" ------------------------------------------------------------"<<endl;
	string lineInFile;
	ifstream inputfile;
	inputfile.open("winners.txt");
	while(getline(inputfile,lineInFile)){

		cout << lineInFile << '\n';
	}
	/*inputfile.close;*/
	cout<<" ------------------------------------------------------------"<<endl;

}



//Display menu
/*
 * This function will display the menu from which user can choose an option
 * */
void displayMenu(){

		cout <<" Enter q to quit >>"<<endl;
		cout <<" Enter L to list previous Scores >>"<<endl;
		cout <<" Enter b to begin the game >>"<<endl;


}
//check if num playesr is digit
//This function checks if user input is digit
bool checkIsDigit(char numplayer){

	if(isdigit(numplayer)){

		return true;
	}else{

		return false;

	}

}

/*void displayWinnersFromDB(){

		sqlite3* db;
	    char* msgError;
	    int exit = sqlite3_open("sqlite/frules.db", &db);

	    string sql_query = "SELECT * FROM winners";

	    cout << "These Winners Were Stored IN sqlite Database" << endl;
	    //executng select query

	    sqlite3_exec(db,sql_query.c_str(),callback, NULL, NULL);

	    cout<< "End Of SQL database List "<<endl;


}*/


//Main function
int main(string* players[]){

	srand(time(0));
	int numPlayers;

	//Display the rules
	displayRules();

	cout << endl << "*******************************************************************************" << endl << endl;
	cout << endl << "\t\t ===== Let us start the game! ===== "<< endl << endl;

   //display the menu
	displayMenu();

	char choice;

	cin.clear();
	cin.ignore();
	cout << "Please enter Your Choice: " <<endl;
	cin >> choice;


	try{

	while(true){


		if(choice == 'B' || choice == 'b'){

			//Prompt the user for number of players are perticipating in the game
				cout << endl << endl << "Number of players would like to play the game ?";
				cin >> numPlayers;
				while(numPlayers < 2){

					cin.clear();
					cin.ignore();
					cout << "Please enter a whole number" <<endl;

					cin >> numPlayers;


				}


				//Create an object for FarleGame class;
					FarkleGame fg(numPlayers);

					//Call the method readNamesOfPlayers() to read names of players
					fg.readNamesOfPlayers();

					//Call the method playersToEnterGame() to make the each player score 1000 points
					fg.playersToEnterGame();

					//Call the method playTheGame to start the game
					fg.playTheGame();


					//when game come to an end, ask user if he/she wishes to play agai
					cout<<" Do You wish to play again ?: "<<endl;
					//display menu

					displayMenu();





		}else if(choice == 'L' || choice == 'l'){

			//List previous scores from a text file or database
			displayWinners();


			//display winners from database
			//displayWinnersFromDB();

			displayMenu();

			cout<<" Do You wish to play again ?: "<<endl;


			cin>>choice;



		}else if(choice == 'q' || choice == 'Q'){

		    break;

		}else{

			      displayMenu();
		}

	}//

	}catch(exception exc){

		cout<<" Sorry You Entered Wrong Values.... "<<endl;
	}


	system("EXIT");
	return 0;

}
