// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HUBPortal.generated.h"

class UNiagaraComponent;
class UBoxComponent;
class UTextRenderComponent;

UCLASS()
class CODINGCHALLENGES_API AHUBPortal : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UNiagaraComponent* Effect;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UStaticMeshComponent* SignBoard;

	UPROPERTY(VisibleAnywhere, meta = (Hidden))
	UTextRenderComponent* LevelName;

	UPROPERTY(EditInstanceOnly, Category = "_Settings")
	TSoftObjectPtr<UWorld> Level;

public:	
	AHUBPortal();

	void OnConstruction(const FTransform& Transform) override;

protected:
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* overlappedComponent, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UFUNCTION()
	void OnChangeLevel();
};
