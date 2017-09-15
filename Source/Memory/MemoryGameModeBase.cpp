// Fill out your copyright notice in the Description page of Project Settings.

#include "MemoryGameModeBase.h"
#include "PlayerControllerMemory.h"

AMemoryGameModeBase::AMemoryGameModeBase() {
	PlayerControllerClass = APlayerControllerMemory::StaticClass();
}



