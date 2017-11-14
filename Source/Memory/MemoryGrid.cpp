// Fill out your copyright notice in the Description page of Project Settings.

#include "MemoryGrid.h"
#include "Components/SceneComponent.h"
#include "Card.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "FileHelper.h"
#include "Kismet/GameplayStatics.h"
#include "MemoryGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetBlueprintLibrary.h"
#include "MemorySaveGame.h"

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
	ConstructorHelpers::FObjectFinder<UClass> BananaBP(
		TEXT("Blueprint'/Game/Blueprints/BananaCard.BananaCard_C'"));
	ConstructorHelpers::FObjectFinder<UClass> MacaBP(
		TEXT("Blueprint'/Game/Blueprints/MacaCard.MacaCard_C'"));
	ConstructorHelpers::FObjectFinder<UClass> PeraBP(
		TEXT("Blueprint'/Game/Blueprints/PeraCard.PeraCard_C'"));

	if (AbacaxiBP.Succeeded()) {
		//Seta o TSubclassOf.
		AbacaxiCard = Cast<UClass>(AbacaxiBP.Object);
	}
	if (BananaBP.Succeeded()) {
		BananaCard = Cast<UClass>(BananaBP.Object);
	}
	if (MacaBP.Succeeded()) {
		MacaCard = Cast<UClass>(MacaBP.Object);
	}
	if (PeraBP.Succeeded()) {
		PeraCard = Cast<UClass>(PeraBP.Object);
	}

	ConstructorHelpers::FClassFinder<UUserWidget> HUDLoad(TEXT("WidgetBlueprint'/Game/Blueprints/HUD.HUD_C'"));
	if (HUDLoad.Succeeded()) {
		HUD = HUDLoad.Class;
	}
}

// Called when the game starts or when spawned
void AMemoryGrid::BeginPlay()
{
	Super::BeginPlay();

	ReadFile();
	
	bCanClick = true;

	float LocationX = 0.0f;
	float LocationZ = 0.0f;

	int AbacaxiCount = 0;
	int BananaCount = 0;
	int MacaCount = 0;
	int PeraCount = 0;

	NumPares = 4;

	if (AbacaxiCard && MacaCard && BananaCard && PeraCard) {
		FActorSpawnParameters SpawnParameters;
		UWorld* World = GetWorld();
		if (World) {
			//Repete 8 vezes para fazer o spawn das 8 cartas
			for (int i = 0; i < 8; i++)	{
				//Define a localização da carta
				FVector Location(LocationX, 0, LocationZ);

				//Sorteia qual carta fará o Spawn
				int Rand = FMath::RandRange(0, 3);
				//0 - Abacaxi
				//1 - Banana
				//2 - Maca
				//3 - Pera
				while ((Rand == 0 && AbacaxiCount == 2) ||
					(Rand == 1 && BananaCount == 2) ||
					(Rand == 2 && MacaCount == 2) ||
					(Rand == 3 && PeraCount == 2)) {

					Rand = FMath::RandRange(0, 3);

				}

				ACard* Card;
				switch (Rand) {
				case 0:
					Card = World->SpawnActor<ACard>(AbacaxiCard, Location,
						FRotator::ZeroRotator, SpawnParameters);
					AbacaxiCount++;
					break;
				case 1:
					Card = World->SpawnActor<ACard>(BananaCard, Location,
						FRotator::ZeroRotator, SpawnParameters);
					BananaCount++;
					break;
				case 2:
					Card = World->SpawnActor<ACard>(MacaCard, Location,
						FRotator::ZeroRotator, SpawnParameters);
					MacaCount++;
					break;
				default:
					Card = World->SpawnActor<ACard>(PeraCard, Location,
						FRotator::ZeroRotator, SpawnParameters);
					PeraCount++;
					break;
				}
				if (Card) {
					Card->SetGrid(this);
				}

				LocationX += 200.0f;
				if (LocationX > 600.0f) {
					LocationX = 0.0f;
					LocationZ += 200.0f;
				}

			}

			//Cria o WidgetBlueprint
			APlayerController* Controller = UGameplayStatics::GetPlayerController(World, 0);
			if (Controller) {
				UUserWidget* UserWidget = UWidgetBlueprintLibrary::Create(World, HUD, Controller);
				if (UserWidget) {
					UserWidget->AddToViewport();
				}
			}
			
		}
		
	}
}

// Called every frame
void AMemoryGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMemoryGrid::AddCard(ACard * Card)
{
	if (FirstCard == nullptr) {
		FirstCard = Card;
	}
	else if (SecondCard == nullptr) {
		SecondCard = Card;
	}

}

void AMemoryGrid::CheckCards()
{
	if (FirstCard != nullptr && SecondCard != nullptr) {

		UWorld* World = GetWorld();
		if (World) {
			UGameInstance* Instance = UGameplayStatics::GetGameInstance(World);
			if (Instance) {
				UMemoryGameInstance* MemoryInstance = Cast<UMemoryGameInstance>(Instance);
				if (MemoryInstance) {
					if (FirstCard->GetIndex() == SecondCard->GetIndex()) {
						FirstCard->Destroy();
						SecondCard->Destroy();
						FirstCard = nullptr;
						SecondCard = nullptr;
						MemoryInstance->SetPontuacao(MemoryInstance->GetPontuacao() + 5);
						NumAcertos++;
						if (NumAcertos == NumPares) {
							//Salvar o jogo
							SaveGame(MemoryInstance->GetErros(), MemoryInstance->GetPontuacao());
							//Mudança de Fase
							UGameplayStatics::OpenLevel(World, "MemoryGameDynamic1");
						}
					} else {
						bCanClick = false;
						GetWorldTimerManager().SetTimer(TurnDown, this,
							&AMemoryGrid::TurnCardsDown, 2.0f, false);
						MemoryInstance->SetErros(MemoryInstance->GetErros() + 1);
						if (MemoryInstance->GetErros() == 3) {
							UE_LOG(LogTemp, Warning, TEXT("GAME OVER!"));
						}
					}
				}
			}
		}
	}

}

bool AMemoryGrid::isCanClick()
{
	return bCanClick;
}

TArray<FString> AMemoryGrid::ReadFile()
{
	FString SaveDirectory = FString("C:/Users/Aluno/Documents/leituraarquivo.txt");
	FString TextToRead;

	FFileHelper::LoadFileToString(TextToRead, *SaveDirectory);
	TArray<FString> Lines;
	int32 lineCount = TextToRead.ParseIntoArray(Lines, _T("\n"), true);

	for (int i = 0; i < Lines.Num(); i++) {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Lines[i]);
	}

	return Lines;
}

void AMemoryGrid::TurnCardsDown()
{
	FirstCard->TurnDown();
	SecondCard->TurnDown();
	FirstCard = nullptr;
	SecondCard = nullptr;
	GetWorldTimerManager().ClearTimer(TurnDown);
	bCanClick = true;
}

void AMemoryGrid::SaveGame(int32 Erros, int32 Pontos)
{
	//https://docs.unrealengine.com/latest/INT/Gameplay/SaveGame/Code/
	//Cria uma instância para o SaveGame
	UMemorySaveGame* SaveGameInstance =
		Cast<UMemorySaveGame>(
			UGameplayStatics::CreateSaveGameObject(UMemorySaveGame::StaticClass()));
	
	//Seta os valores a serem salvos
	SaveGameInstance->Erros = Erros;
	SaveGameInstance->Pontos = Pontos;

	//Salva o jogo em um arquivo
	UGameplayStatics::SaveGameToSlot(SaveGameInstance,
		SaveGameInstance->SaveSlotName,
		SaveGameInstance->UserIndex);


}
