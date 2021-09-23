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

	UPROPERTY(EditDefaultsOnly, Category = "Spheres")
	float SphereOffsetSize;

	UPROPERTY(EditDefaultsOnly, Category = "Spheres")
	float SpheresScaleDecreasePercent;

	UPROPERTY(EditDefaultsOnly, Category = "Spheres")
	float MinSphereScale;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	bool ShowDebugDrawings;

	float SphereSize;

	UPROPERTY(BlueprintReadOnly, Category = "Wave")
	int32 WaveNumber;

	float SphereSizeWithOffset();

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	int32 RequiredNrOfSpheresToDestroyDuringWave;

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	int32 DefaultNrOfSpheresToSpawn;

	int32 GetNrOfSpheresToSpawn();

	UPROPERTY(EditDefaultsOnly, Category = "Wave")
	int32 SphereNrIncreasePercent;

	FVector SpawnCenterLoc;

	void UpdateSpawnCenterLoc();

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

	FVector GetSphereScaleVectorBySpawnIndex(int32 index);

	void DrawRadiusDebugSpheres();

public:
	virtual void StartPlay() override;

	void BeforeSphereDestroyed(FVector SphereToDestroyLoc);

};