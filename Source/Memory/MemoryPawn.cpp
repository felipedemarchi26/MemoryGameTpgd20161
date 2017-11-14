// Fill out your copyright notice in the Description page of Project Settings.

#include "MemoryPawn.h"
#include "Camera/CameraComponent.h"
#include "Card.h"
#include "Kismet/GameplayStatics.h"
#include "MemorySaveGame.h"
#include "MemoryGameInstance.h"
#include "Engine/World.h"


// Sets default values
AMemoryPawn::AMemoryPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->ProjectionMode = ECameraProjectionMode::Orthographic;
	Camera->OrthoWidth = 2048.0f;
	Camera->SetupAttachment(RootComponent);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMemoryPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMemoryPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMemoryPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Load", IE_Pressed, this, &AMemoryPawn::LoadGame);
}

void AMemoryPawn::LoadGame() {
	//https://docs.unrealengine.com/latest/INT/Gameplay/SaveGame/Code/
	//Obtém uma instância do SaveGame
	UMemorySaveGame* LoadGameInstance =
		Cast<UMemorySaveGame>(
			UGameplayStatics::CreateSaveGameObject(UMemorySaveGame::StaticClass()));
	
	//Carrega o jogo salvo pelo SlotName e UserIndex
	LoadGameInstance = Cast<UMemorySaveGame>(
		UGameplayStatics::LoadGameFromSlot(
			LoadGameInstance->SaveSlotName, 
			LoadGameInstance->UserIndex));

	UWorld* World = GetWorld();
	if (World) {
		UGameInstance* Instance = UGameplayStatics::GetGameInstance(World);
		if (Instance) {
			UMemoryGameInstance* MemoryInstance = Cast<UMemoryGameInstance>(Instance);
			if (MemoryInstance) {
				MemoryInstance->SetErros(LoadGameInstance->Erros);
				MemoryInstance->SetPontuacao(LoadGameInstance->Pontos);
			}
		}
	}

}