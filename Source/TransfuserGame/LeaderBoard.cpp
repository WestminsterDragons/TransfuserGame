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
string LeadContainer[11][2];

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
		size_t len = content[5].length();
		stringstream tmp(content[5]);
		int value = 0;
		tmp >> value;



		if ((content[3].compare(TCHAR_TO_UTF8(*Player))==0)) // at the begin of each line 

		{
			
			

			
				if (PlayerScore > value) {
					size_t pos = line.find(to_string(value));
					if (pos != string::npos)
					{
						line.replace(pos, len, to_string(PlayerScore ));
						found = true;
					}
					
						
				}
				
			

		}
		else 
		{
			
		}
		
		stringstream tmps(content[1]);
		tmps >> lastN;
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

void sorting() {
	string temp = "";
	int i=0, n = 11, j = 0;
	for (i = 0; i < n; i++)
	{
		for (j = i + 1; j < n; j++)
		{
			stringstream tmps(LeadContainer[i][1]);
			stringstream tm(LeadContainer[j][1]);
			int value1 = 0;
			int value2 = 0;
			tmps >> value1;
			tm >> value2;
			if (value1 < value2 && LeadContainer[i][0] !="")
			{
				temp = LeadContainer[i][1];
				LeadContainer[i][1] = LeadContainer[j][1];
				LeadContainer[j][1] = temp;
				temp = LeadContainer[i][0];
				LeadContainer[i][0] = LeadContainer[j][0];
				LeadContainer[j][0] = temp;
			}
		}
	}
}

void SortLeads(int PlayerScore, FString Player)
{
	string line = "";
	fstream stream;
	string output;
	
	

	stream.open(PathScore);

	if (!stream) {
		NotAvailable = true;
	}
	
	int index = 0;
	while (getline(stream, line) && !NotAvailable)
	{
		SplitInWords(line); //Divide each words of the the line and it puts its value in the vector read
		

		if (index <= 9) {
			LeadContainer[index][1] = content[5];
			LeadContainer[index][0] = content[3];
			index++;
		}
		else {
			LeadContainer[10][0] = TCHAR_TO_UTF8(*Player);
			LeadContainer[10][1] = to_string(PlayerScore);
		}

	}

	sorting();
	
	for (int ix = 0; ix < (sizeof(LeadContainer)/sizeof(*LeadContainer)); ix++) {
		if (!LeadContainer[ix][0].empty())
		{
			output.append("- " + to_string(ix) + " | " + LeadContainer[ix][0] + " | " + LeadContainer[ix][1] + "\n");
		}
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
	

	return;

}

void ULeaderBoard::SortLead(int PlayerScore, FString Player)
{


	SortLeads(PlayerScore,Player);

	

	return;

}
void ULeaderBoard::SetLeaderboard(int Index, int PlayerScore, FString Player, int &Num, FString &Name, int &Score)
{

	 
		SetLeaderboards(Index, PlayerScore, Player, Num, Name, Score);
	
	if (NotAvailable)
	{
		Num = -1;
		Name = "Not Available";
		Score = -2;
	}
	
	return;

}