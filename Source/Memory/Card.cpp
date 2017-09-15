// Fill out your copyright notice in the Description page of Project Settings.

#include "Card.h"
#include "PaperSprite.h"
#include "PaperSpriteComponent.h"


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
	
}

// Called every frame
void ACard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACard::OnTouchBegin(ETouchIndex::Type Type, UPrimitiveComponent * TouchedComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("TOUCH!"));
}

