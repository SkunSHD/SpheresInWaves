// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BSphere.generated.h"


class UStaticMeshComponent;
class USphereComponent;
class UParticleSystem;


UCLASS()
class B_API ABSphere : public AActor
{
	GENERATED_BODY()
	
public:	
	ABSphere();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* DestroyFX;

	void PlayEffects();

public:	
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
