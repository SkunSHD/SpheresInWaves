// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BGameMode.generated.h"

class ABSphere;

UCLASS(minimalapi)
class ABGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABGameMode();

protected:

	float SphereSize;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	float SphereOffsetSize;

	float SphereSizeWithOffset();

	int32 WaveNumber;

	int32 NrOfSpheresToKill;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	int32 DefaultNrOfSpheresToSpawn;

	int32 GetNrOfSpheresToSpawn();

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	int32 SphereIncreasePercent;

	FVector SpawnCenterLoc;

	void UpdateSpawnCenterLoc();

	// radius
	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	float RadiusIncreasePercent;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	float DefaultMinRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	float DefaultMaxRadius;

	float GetMaxRadius();

	float GetMinRadius();

	TArray<FVector> SpawnedSpheresLoc;

	bool IsNewSphereCloseToSome(FVector NewSphere, TArray<FVector> OtherSpheres, float RequiredDistance);

	bool IsCenterSpawning(TArray<FVector> SpheresToSpawn);

	void SpawnWave();

	void SpawnNewSpheres(TArray<FVector> SpheresToSpawn);

	float SphereDefaultZ;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	TSubclassOf<ABSphere> SphereClass;

public:
	virtual void StartPlay() override;

};



