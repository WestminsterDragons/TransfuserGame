// Fill out your copyright notice in the Description page of Project Settings.


#include "LeaderBoard.h"
#include <string>
#include <fstream> 
#include <iostream> 
#include <list> 
#include <sstream> 
#include <vector> 
#include "FileHelpers.h"
using namespace std;
vector<string> content;
int Pos = 0; // number of lines
int counter = 0; // number of lines
bool NotAvailable = false;
bool NotAvailablea = false;
bool found = false;

void SplitInWords(string in) //Splits string into each word and places each word in a new vector position
{

	content.clear();

	string str(in);				//Get the string content
	string buf;                 // read from and write to string objects.

	stringstream ss(str);       // Put string in a stream

	while (ss >> buf)
		content.push_back(buf);
}


void CountItems() //Opens the text file and counts the number of Items
{
	string line = "";

	fstream stream;
	stream.open("C:\\Users\\w1641650\\Documents\\GitHub\\TransfuserGame\\Source\\TransfuserGame\\Score.txt");

	while (getline(stream, line))
	{
		SplitInWords(line);

		if ((content[0]) == "-") // increment the counter items for each number that it finds in the text file
			Pos++;

	}
	stream.close();
}



void ReadFile(int Index, FString Player,int &Num, FString &Name, int &Score)
{
	string line = "";

	fstream stream;

	stream.open("C:\\Users\\w1641650\\Documents\\GitHub\\TransfuserGame\\Source\\TransfuserGame\\Score.txt");

	if (!stream) {
		NotAvailable = true;
	}
	int i = 0;
	while (getline(stream, line) && !NotAvailable && !NotAvailablea && !found)
	{
		SplitInWords(line); //Divide each words of the the line and it puts its value in the vector read

		
		if (i == Index) 
		{

			if (content.size() > 1) //if the line contains more than one word it means that it's the description of the item
			{
				if ((content[0] == "-")) // at the begin of each line 
				{
					
					Num = (stoi(content[1]));
					
					Score = (stoi(content[5]));
					Name = content[3].c_str();
				}
				if (Player.Equals(content[3].c_str()))
				{
					//found = true;
				}

			}
			else {
				NotAvailablea = true;
			}
			
		}
		i++;
	}
	
	stream.close(); //close text file

}


void ULeaderBoard::ReadScore(int Index, FString Player, int &Num, FString &Name, int &Score)
{
	/**/
	CountItems();
	//int num[10];
	//FString user[10];
//	int score[10];
	ReadFile(Index, Player,Num,Name,Score);
	if (NotAvailable) 
	{
		Num = -1;
		Name = "Not Available";
		Score = -2;
	}
	else 
	{
		//Num = -4;

	}

	return;

}