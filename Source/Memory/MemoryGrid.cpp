// Fill out your copyright notice in the Description page of Project Settings.

#include "MemoryGrid.h"
#include "Components/SceneComponent.h"
#include "Card.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/World.h"


// Sets default values
AMemoryGrid::AMemoryGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	//Obtém a referencia para a classe blueprint e seta para a variável local
	//denominada AbacaxiBP.
	ConstructorHelpers::FObjectFinder<UClass> AbacaxiBP(
		TEXT("Blueprint'/Game/Blueprints/AbacaxiCard.AbacaxiCard_C'"));

	if (AbacaxiBP.Succeeded()) {
		//Seta o TSubclassOf.
		AbacaxiCard = Cast<UClass>(AbacaxiBP.Object);
	}
}

// Called when the game starts or when spawned
void AMemoryGrid::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbacaxiCard) {
		FActorSpawnParameters SpawnParameters;
		UWorld* World = GetWorld();
		if (World) {
			World->SpawnActor<ACard>(AbacaxiCard, FVector(0.0f, 0.0f, 0.0f),
				FRotator::ZeroRotator, SpawnParameters);
			World->SpawnActor<ACard>(AbacaxiCard, FVector(200.0f, 0.0f, 0.0f),
				FRotator::ZeroRotator, SpawnParameters);
		}
	}
}

// Called every frame
void AMemoryGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

