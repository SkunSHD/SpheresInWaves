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

	UPROPERTY(BlueprintReadOnly, Category = "Wave")
	int32 WaveNumber;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	float SphereOffsetSize;

	float SphereSizeWithOffset();

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	int32 RequiredNrOfSpheresToDestroyDuringWave;

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

	void BeforeWaveSpawn();

	void SpawnNewSpheres(TArray<FVector> SpheresToSpawn);

	float SphereDefaultZ;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	TSubclassOf<ABSphere> SphereClass;

	UPROPERTY(BlueprintReadWrite, Category = "Wave")
	int32 NrOfSpheresDestroyedDuringWave;

public:
	virtual void StartPlay() override;

	void BeforeSphereDestroyed(FVector SphereToDestroyLoc);

};



