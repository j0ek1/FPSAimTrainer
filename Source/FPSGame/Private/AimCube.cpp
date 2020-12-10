// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AimCube.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

TArray<AActor*> aimCubes; //Global array for all of the aim cubes

// Sets default values
AAimCube::AAimCube()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent"); //Creating static mesh component for the cubes
	StaticMesh->OnComponentHit.AddDynamic(this, &AAimCube::OnHit);
}

// Called when the game starts or when spawned
void AAimCube::BeginPlay()
{
	Super::BeginPlay();

	TSubclassOf<AAimCube> classToFind; //Getting all actors of class and putting them into one array
	classToFind = AAimCube::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(this, classToFind, aimCubes);
	aimCubes[13]->SetActorScale3D(FVector(1.f, 1.f, 1.f)); //Set first cube to be full scale
}

void AAimCube::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) //When the cube gets hit
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) //If we hit an actor that is not itself
	{
		int x = FMath::RandRange(0, 26); //Selecting random number from the range of cubes
		aimCubes[x]->SetActorScale3D(FVector(1.f, 1.f, 1.f)); //Setting random cube back to full scale
	}
}

//// Called every frame
//void AAimCube::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}