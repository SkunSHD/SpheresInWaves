// Fill out your copyright notice in the Description page of Project Settings.


#include "BSphere.h"
#include "BProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"


ABSphere::ABSphere()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->InitSphereRadius(50.0f);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Overlap);
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);
}


void ABSphere::PlayEffects()
{
 
}


void ABSphere::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	UE_LOG(LogTemp, Warning, TEXT("NotifyActorBeginOverlap"));

	PlayEffects();

	ABProjectile* MyProjectile = Cast<ABProjectile>(OtherActor);
	if (MyProjectile)
	{
		Destroy();
		MyProjectile->Destroy();
	}
}


