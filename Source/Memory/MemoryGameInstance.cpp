// Fill out your copyright notice in the Description page of Project Settings.

#include "MemoryGameInstance.h"

void UMemoryGameInstance::SetPontuacao(int32 NewPontuacao) {
	Pontuacao = NewPontuacao;
}

void UMemoryGameInstance::SetErros(int32 NewErros)
{
	Erros = NewErros;
}

int32 UMemoryGameInstance::GetPontuacao()
{
	return Pontuacao;
}

int32 UMemoryGameInstance::GetErros()
{
	return Erros;
}
