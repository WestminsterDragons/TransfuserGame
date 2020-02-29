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





void ReadFile(int Index, FString Player,int &Num, FString &Name, int &Score)
{
	string line = "";

	fstream stream;

	stream.open("C:\\Users\\w1641650\\Documents\\GitHub\\TransfuserGame\\Source\\TransfuserGame\\Score.txt");

	if (!stream) {
		NotAvailable = true;
	}
	int i = 0; //line number
	while (getline(stream, line) && !NotAvailable)
	{
		SplitInWords(line); //Divide each words of the the line and it puts its value in the vector read

		
		if (i == Index) 
		{

			
				if ((content[0] == "-")) // at the begin of each line 
				{
					
					Num = (stoi(content[1]));
					
					Score = (stoi(content[5]));
					Name = content[3].c_str();
				}
				

		}
		
			
		i++;
		
		
	}
	
	stream.close(); //close text file

}


void SetLeaderboards(int Index, FString Player, int &Num, FString &Name, int &Score)
{
	string line = "";

	fstream stream;


	stream.open("C:\\Users\\w1641650\\Documents\\GitHub\\TransfuserGame\\Source\\TransfuserGame\\Score.txt");

	if (!stream) {
		NotAvailable = true;
	}
	int i = 0; //line number
	while (getline(stream, line) && !NotAvailable)
	{
		SplitInWords(line); //Divide each words of the the line and it puts its value in the vector read


		if (i == Index)
		{


			if ((content[3]._Equal( /*TCHAR_TO_UTF8(*Player)*/ "Sohaib"))) // at the begin of each line 
			{


				size_t len = content[5].length();
				while (getline(stream, line))
				{
					while (true)
					{
						size_t pos = line.find("1500");
						if (pos != string::npos)
							line.replace(pos, len, content[5]);
						else
							break;
					}

				}


			}


			i++;


		}

		stream.close(); //close text file

	}
}



void ULeaderBoard::ReadScore(int Index, FString Player, int &Num, FString &Name, int &Score)
{
	
	Num = 0;

	Score = 0;
	Name = "";
	ReadFile(Index, Player, Num, Name, Score);

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
void ULeaderBoard::SetLeaderboard(int Index, FString Player, int &Num, FString &Name, int &Score)
{

	Num = 0;

	Score = 0;
	Name = "";
	SetLeaderboards(Index, Player, Num, Name, Score);
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