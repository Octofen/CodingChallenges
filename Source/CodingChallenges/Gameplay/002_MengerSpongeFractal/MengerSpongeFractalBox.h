// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MengerSpongeFractalBox.generated.h"

UCLASS()
class CODINGCHALLENGES_API AMengerSpongeFractalBox : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UStaticMeshComponent* Box;

public:	
	AMengerSpongeFractalBox();

	TArray<AMengerSpongeFractalBox*> Generate(AActor* owner);
};
