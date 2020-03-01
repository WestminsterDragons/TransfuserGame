// Fill out your copyright notice in the Description page of Project Settings.


#include "LeaderBoard.h"
#include <string>
#include <fstream> 
#include <iostream> 
#include <list> 
#include <sstream> 
#include <vector> 
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "PlatformFilemanager.h"
using namespace std;
vector<string> content;

int counter = 0; // number of lines
bool NotAvailable = false;

FString tmp= FPaths::GameSourceDir();
string Path = (TCHAR_TO_UTF8(*tmp)) ;
string PathScore = Path + "/TransfuserGame/Score.txt";
string PathScores = Path + "/TransfuserGame/Scores.txt";
string PathFolder = Path + "/TransfuserGame";


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
	
	stream.open(PathScore);

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


void SetLeaderboards(int Index, int PlayerScore, FString Player, int& Num, FString& Name, int& Score)
{
	string line = "";
	fstream stream;
	string output;
	bool found = false;
	int lastN;

	stream.open(PathScore );

	if (!stream) {
		NotAvailable = true;
	}
	int i = 0; //line number
	while (getline(stream, line) && !NotAvailable)
	{
		SplitInWords(line); //Divide each words of the the line and it puts its value in the vector read





		if ((content[3].compare(TCHAR_TO_UTF8(*Player))==0)) // at the begin of each line 

		{
			size_t len = content[5].length();
			stringstream tmp(content[5]);
			int value = 0;
			tmp >> value;

			
				if (PlayerScore > value) {
					size_t pos = line.find(to_string(value));
					if (pos != string::npos)
					{
						line.replace(pos, len, to_string(PlayerScore ));
						found = true;
					}
					
						
				}
				
			

		}
		
		stringstream tmp(content[1]);
		tmp >> lastN;
		output.append(line + " \n");

		
	}
	if (!found)
	{
		output.append("- " + to_string(lastN+1) + " | " + TCHAR_TO_UTF8(*Player) + " | " + to_string(PlayerScore) + "\n");
	}

	stream.close(); //close text file
	FString SaveDirectory = (PathFolder.c_str());
	FString FileName = FString("Scores.txt");
	FString TextToSave = (output.c_str());
	bool AllowOverwriting = true;

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	// CreateDirectoryTree returns true if the destination
	// directory existed prior to call or has been created
	// during the call.
	if (PlatformFile.CreateDirectoryTree(*SaveDirectory))
	{
		// Get absolute file path
		FString AbsoluteFilePath = SaveDirectory + "/" + FileName;

		// Allow overwriting or file doesn't already exist
		if (AllowOverwriting || !PlatformFile.FileExists(*AbsoluteFilePath))
		{
			FFileHelper::SaveStringToFile(TextToSave, *AbsoluteFilePath);
		}
	}
	remove((PathScore.c_str()));
	rename((PathScores.c_str()), (PathScore.c_str()));
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
void ULeaderBoard::SetLeaderboard(int Index, int PlayerScore, FString Player, int &Num, FString &Name, int &Score)
{

	Num = 0;

	Score = 0;
	Name = "";
	SetLeaderboards(Index, PlayerScore, Player, Num, Name, Score);
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