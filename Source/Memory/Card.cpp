// Fill out your copyright notice in the Description page of Project Settings.

#include "Card.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "MemoryPawn.h"
#include "MemoryGrid.h"


// Sets default values
ACard::ACard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	Sprite->OnInputTouchBegin.AddDynamic(this, &ACard::OnTouchBegin);
	RootComponent = Sprite;

}

// Called when the game starts or when spawned
void ACard::BeginPlay()
{
	Super::BeginPlay();
	if (ClosedCard != NULL) {
		Sprite->SetSprite(ClosedCard);
	}
	bTurned = false;
	
}

// Called every frame
void ACard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ACard::GetIndex()
{
	return Index;
}

void ACard::OnTouchBegin(ETouchIndex::Type Type, UPrimitiveComponent * TouchedComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("TOUCH!"));
	if (Grid->isCanClick()) {
		if (bTurned) {
			Sprite->SetSprite(ClosedCard);
		}
		else {
			Sprite->SetSprite(OpenedCard);
			Grid->AddCard(this);
			Grid->CheckCards();
		}
		bTurned = !bTurned;
	}


}

void ACard::SetGrid(AMemoryGrid * NewGrid)
{
	Grid = NewGrid;
}

AMemoryGrid * ACard::GetGrid()
{
	return Grid;
}

void ACard::TurnDown() {
	Sprite->SetSprite(ClosedCard);
	bTurned = false;
}

