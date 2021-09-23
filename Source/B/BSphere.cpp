// Fill out your copyright notice in the Description page of Project Settings.


#include "BSphere.h"
#include "BProjectile.h"
#include "BGameMode.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


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
	if (!DestroyFX)
	{
		UE_LOG(LogTemp, Warning, TEXT("No DestroyFX has been set!"));
		return;
	}
	UGameplayStatics::SpawnEmitterAtLocation(this, DestroyFX, GetActorLocation());
}


void ABSphere::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ABProjectile* MyProjectile = Cast<ABProjectile>(OtherActor);
	if (MyProjectile)
	{
		ABGameMode* GM = Cast<ABGameMode>(GetWorld()->GetAuthGameMode());
		if (GM)
		{
			GM->BeforeSphereDestroyed(GetActorLocation());
		}

		PlayEffects();
		Destroy();
		MyProjectile->Destroy();
	}
}


