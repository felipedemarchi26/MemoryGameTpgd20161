// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MemoryGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MEMORY_API UMemoryGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	void SetPontuacao(int32 NewPontuacao);
	void SetErros(int32 NewErros);
	UFUNCTION(BlueprintCallable, Category = "Settings")
	int32 GetPontuacao();
	UFUNCTION(BlueprintCallable, Category = "Settings")
	int32 GetErros();

private:

	int32 Pontuacao;
	int32 Erros;
	
};
