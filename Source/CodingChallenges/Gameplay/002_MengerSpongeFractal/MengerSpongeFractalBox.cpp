// Fill out your copyright notice in the Description page of Project Settings.


#include "MengerSpongeFractalBox.h"

AMengerSpongeFractalBox::AMengerSpongeFractalBox()
{
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	RootComponent = Box;
}

TArray<AMengerSpongeFractalBox*> AMengerSpongeFractalBox::Generate(AActor* owner)
{
	TArray<AMengerSpongeFractalBox*> boxes;

	FVector min;
	FVector max;
	Box->GetLocalBounds(min, max);
	float offset = ((max.X * 2) / 3) * GetActorScale3D().X;

	for(int x = -1; x < 2; x++)
	{
		for(int y = -1; y < 2; y++)
		{
			for(int z = -1; z < 2; z++)
			{
				int sum = FMath::Abs(x) + FMath::Abs(y) + FMath::Abs(z);

				if(sum <= 1)
				{
					continue;
				}

				FActorSpawnParameters param;
				param.Owner = owner;
				param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				float posX = RootComponent->GetRelativeLocation().X + x * offset;
				float posY = RootComponent->GetRelativeLocation().Y + y * offset;
				float posZ = RootComponent->GetRelativeLocation().Z + z * offset;
				FVector position = FVector(posX, posY, posZ);
				FVector scale = GetActorScale3D() / 3;
				FTransform spawnTransform = FTransform(FRotator::ZeroRotator, position, scale);

				AMengerSpongeFractalBox* box = GetWorld()->SpawnActor<AMengerSpongeFractalBox>(GetClass(), spawnTransform, param);
				box->AttachToActor(owner, FAttachmentTransformRules::KeepRelativeTransform);
				boxes.Add(box);
			}
		}
	}

	return boxes;
}
