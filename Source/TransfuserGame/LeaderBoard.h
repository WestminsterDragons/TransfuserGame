// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LeaderBoard.generated.h"

/**
 * 
 */
UCLASS()
class TRANSFUSERGAME_API ULeaderBoard : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		UFUNCTION(BlueprintCallable, Category = "Hello")
		static void ReadScore(int index, FString Player,int &Num, FString &Name, int &Score);
	
};
