// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MemorySaveGame.generated.h"

/**
 * 
 */
UCLASS()
class MEMORY_API UMemorySaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UMemorySaveGame();

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int32 Erros;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		int32 Pontos;
	
	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	
};
