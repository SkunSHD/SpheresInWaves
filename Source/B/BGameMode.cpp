// Copyright Epic Games, Inc. All Rights Reserved.

#include "BGameMode.h"
#include "BSphere.h"
#include "BHUD.h"
#include "BCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "DrawDebugHelpers.h"


ABGameMode::ABGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ABHUD::StaticClass();

	// Sphere settings:
	SphereDefaultZ = 50.0f;
	SphereOffsetSize = 80.0f;
	SphereSize = 100.0f;

	// Wave settins:
	WaveNumber = 1;
	NrOfSpheresToKill = 10;
	DefaultNrOfSpheresToSpawn = 15;

	RadiusIncreasePercent = 5.0f;
	SphereIncreasePercent = 10.0f;

	DefaultMinRadius = 1500.0f;
	DefaultMaxRadius = 2000.0f;
}


void ABGameMode::StartPlay()
{
	Super::StartPlay();
	SpawnWave();
	DrawDebugSphere(GetWorld(), SpawnCenterLoc, GetMinRadius(), 12, FColor::Yellow, false, 99999.0f, 0, 5.0f);
	DrawDebugSphere(GetWorld(), SpawnCenterLoc, GetMaxRadius(), 12, FColor::Green, false, 99999.0f, 0, 5.0f);
}


float ABGameMode::SphereSizeWithOffset()
{
	return SphereSize + SphereOffsetSize;
}


void ABGameMode::UpdateSpawnCenterLoc()
{
	SpawnCenterLoc = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
}


float ABGameMode::GetMinRadius()
{
	return (RadiusIncreasePercent * DefaultMinRadius * (WaveNumber - 1) / 100) + DefaultMinRadius;
}


float ABGameMode::GetMaxRadius()
{
	return (RadiusIncreasePercent * DefaultMaxRadius * (WaveNumber - 1) / 100) + DefaultMaxRadius;
}


bool ABGameMode::IsNewSphereCloseToSome(FVector NewSphere, TArray<FVector> OtherSpheres, float RequiredDistance)
{
	for (int i = 0; i < OtherSpheres.Num(); i++)
	{
		const FVector OtherSphere = OtherSpheres[i];
		const float distance = FVector::Dist(NewSphere, OtherSphere);
		if (distance < RequiredDistance)
		{
			return true;
		}
	}

	return false;
}


int32 ABGameMode::GetNrOfSpheresToSpawn() {
	return (DefaultNrOfSpheresToSpawn * SphereIncreasePercent * (WaveNumber - 1) / 100) + DefaultNrOfSpheresToSpawn;
}


bool ABGameMode::IsCenterSpawning(TArray<FVector> SpheresToSpawn) {
	return SpheresToSpawn.Num() <= NrOfSpheresToKill;
}


void ABGameMode::SpawnWave()
{
	UpdateSpawnCenterLoc();

	TArray<FVector> SpheresToSpawnLoc;
	while (SpheresToSpawnLoc.Num() < GetNrOfSpheresToSpawn())
	{
		float CurrentRadius = (IsCenterSpawning(SpheresToSpawnLoc) ? GetMinRadius() : GetMaxRadius()) - SphereSizeWithOffset();
		float X = FMath::RandRange(-CurrentRadius, CurrentRadius);
		float Y = FMath::RandRange(-CurrentRadius, CurrentRadius);
		FVector NewSphereLoc = FVector(X, Y, SphereDefaultZ) + SpawnCenterLoc;

		UE_LOG(LogTemp, Warning, TEXT("NewSphereLoc %s"), *NewSphereLoc.ToString())

		// validate new sphere location
		if (SpheresToSpawnLoc.Contains(NewSphereLoc))
		{
			continue;
		}
		if (IsNewSphereCloseToSome(NewSphereLoc, SpheresToSpawnLoc, SphereSizeWithOffset()))
		{
			continue;
		}
		if (IsNewSphereCloseToSome(NewSphereLoc, SpawnedSpheresLoc, SphereSizeWithOffset()))
		{
			continue;
		}

		// add new validated location
		SpheresToSpawnLoc.Add(NewSphereLoc);
	}

	SpawnNewSpheres(SpheresToSpawnLoc);
}


void ABGameMode::SpawnNewSpheres(TArray<FVector> SpheresToSpawnLoc)
{
	if (!SphereClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("SphereClass hasn't been set!"))
	}

	FActorSpawnParameters SpawnParams;
	for (int i = 0; i < SpheresToSpawnLoc.Num(); i++)
	{
		FVector SphereToSpawnLoc = SpheresToSpawnLoc[i];
		GetWorld()->SpawnActor<ABSphere>(SphereClass, SphereToSpawnLoc, FRotator::ZeroRotator, SpawnParams);

		DrawDebugSphere(GetWorld(), SphereToSpawnLoc, SphereSizeWithOffset(), 12, FColor::Purple, false, 99999.0f, 0, 1.0f);

		SpawnedSpheresLoc.Add(SphereToSpawnLoc);
	}
}

