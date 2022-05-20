// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceInvadersShip.h"

ASpaceInvadersShip::ASpaceInvadersShip()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}