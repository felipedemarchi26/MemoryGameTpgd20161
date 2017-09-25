// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MemoryGrid.generated.h"

UCLASS()
class MEMORY_API AMemoryGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMemoryGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere)
		class USceneComponent* Root;

	TSubclassOf<class ACard> AbacaxiCard;
	TSubclassOf<class ACard> BananaCard;
	TSubclassOf<class ACard> MacaCard;
	TSubclassOf<class ACard> PeraCard;
	
	
};
