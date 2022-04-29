// Fill out your copyright notice in the Description page of Project Settings.


#include "MengerSpongeFractalBox.h"

FMengerSpongeFractalBox::FMengerSpongeFractalBox(float x, float y, float z, float size, float boundsSize)
{
	Position = FVector(x, y, z);
	this->BoundsSize = boundsSize;
	this->Size = size;
}

FTransform FMengerSpongeFractalBox::Show()
{
	return FTransform(FRotator::ZeroRotator, Position, FVector(Size / BoundsSize));
}

TArray<TSharedPtr<FMengerSpongeFractalBox>> FMengerSpongeFractalBox::Generate()
{
	TArray<TSharedPtr<FMengerSpongeFractalBox>> boxes;
	float newSize = Size / 3;

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

				float posX = Position.X + x * newSize;
				float posY = Position.Y + y * newSize;
				float posZ = Position.Z + z * newSize;
				TSharedPtr<FMengerSpongeFractalBox> box(new FMengerSpongeFractalBox(posX, posY, posZ, newSize, BoundsSize));

				boxes.Add(box);
			}
		}
	}

	return boxes;
}
