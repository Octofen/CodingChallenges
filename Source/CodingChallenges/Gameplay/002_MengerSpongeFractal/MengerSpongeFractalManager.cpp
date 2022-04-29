// Fill out your copyright notice in the Description page of Project Settings.


#include "MengerSpongeFractalManager.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CodingChallenges/Framework/002_Menger_Sponge_Fractal/MengerSpongeFractalPawn.h"
#include "CodingChallenges/Data/002_MengerSpongeFractal/MengerSpongeFractalData.h"

AMengerSpongeFractalManager::AMengerSpongeFractalManager()
{
	PrimaryActorTick.bCanEverTick = true;

	InstancedStaticMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Box Mesh"));
	RootComponent = InstancedStaticMesh;
}

void AMengerSpongeFractalManager::BeginPlay()
{
	Super::BeginPlay();

	if(DataSoft.IsPending())
	{
		DataSoft.LoadSynchronous();
	}

	Data = DataSoft.Get();

	float pitch = FMath::RandRange(-0.1f, 0.1f);
	float yaw = FMath::RandRange(-0.1f, 0.1f);
	float roll = FMath::RandRange(-0.1f, 0.1f);
	RandomRotation = FRotator(pitch, yaw, roll) * Data->RotationSpeed;

	APawn* pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if(AMengerSpongeFractalPawn* mengerSpongeFractalPawn = Cast<AMengerSpongeFractalPawn>(pawn))
	{
		mengerSpongeFractalPawn->GenerateEvent.AddUniqueDynamic(this, &AMengerSpongeFractalManager::OnGenerate);
	}

	FVector min;
	InstancedStaticMesh->GetLocalBounds(min, Bounds);

	Refresh();
}

void AMengerSpongeFractalManager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	RootComponent->AddWorldRotation(RandomRotation);
}

void AMengerSpongeFractalManager::Refresh()
{
	for(TSharedPtr<FMengerSpongeFractalBox> box : Sponge)
	{
		InstancedStaticMesh->RemoveInstance(0);
	}

	Sponge.Empty();

	TSharedPtr<FMengerSpongeFractalBox> box(new FMengerSpongeFractalBox(0.f, 0.f, 0.f, 200.f, Bounds.X * 2));
	InstancedStaticMesh->AddInstance(box->Show());
	Sponge.Add(box);
}

void AMengerSpongeFractalManager::OnGenerate()
{
	NbIterations++;

	if(NbIterations >= 4)
	{
		NbIterations = 0;
		Refresh();
		return;
	}

	TArray<TSharedPtr<FMengerSpongeFractalBox>> next;

	for(TSharedPtr<FMengerSpongeFractalBox> box : Sponge)
	{
		TArray<TSharedPtr<FMengerSpongeFractalBox>> newBoxes = box->Generate();
		next.Append(newBoxes);
		InstancedStaticMesh->RemoveInstance(0);
	}

	for(TSharedPtr<FMengerSpongeFractalBox> box : next)
	{
		InstancedStaticMesh->AddInstance(box->Show());
	}

	InstancedStaticMesh->MarkRenderStateDirty();
	Sponge = next;
}
