// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "AimCube.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"

TArray<AActor*> aimCubes; //Global array for all of the aim cubes
extern int numberOfTargets;
bool hasStarted = false; //Bool which shows if the player has started the training or not
bool canStartTimer = true;
bool canShoot = false;
FTimerHandle CourseTimer;

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
}

void AAimCube::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) //When the cube gets hit
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && (canShoot)) //If we hit an actor that is not itself
	{
		hasStarted = true;
		if (canStartTimer)
		{
			AAimCube::TimerHandle();
		}

		int x;
		FVector Scale;
		do //Ensuring the new cube to be spawned is not already full scale on the wall
		{
			x = FMath::RandRange(0, 26); //Selecting random number from the range of cubes
			Scale = aimCubes[x]->GetActorScale3D();
		} while (Scale == FVector(1.f, 1.f, 1.f));
		aimCubes[x]->SetActorScale3D(FVector(1.f, 1.f, 1.f)); //Setting random cube back to full scale
	}
}

void AAimCube::TimerHandle() //Handles starting the timer for the course
{
	canStartTimer = false;
	GetWorld()->GetTimerManager().SetTimer(CourseTimer, this, &AAimCube::TimerReset, 20.f, false);
}

void AAimCube::TimerReset()
{
	hasStarted = false;
	canShoot = false;
	GetWorldTimerManager().ClearTimer(CourseTimer);
}

void AAimCube::Target1()
{
	canShoot = true;
	for (int i = 0; i < 27; i++)
	{
		aimCubes[i]->SetActorScale3D(FVector(.1f, .1f, .1f));
	}
	aimCubes[13]->SetActorScale3D(FVector(1.f, 1.f, 1.f)); //Set one cube to be shown
}

void AAimCube::Target2(int x)
{
	canShoot = true;
	for (int i = 0; i < 27; i++)
	{
		aimCubes[i]->SetActorScale3D(FVector(.1f, .1f, .1f));
	}
	aimCubes[13]->SetActorScale3D(FVector(1.f, 1.f, 1.f));
	aimCubes[x]->SetActorScale3D(FVector(1.f, 1.f, 1.f));
	
}

void AAimCube::Target3(int x, int y)
{
	canShoot = true;
	for (int i = 0; i < 27; i++)
	{
		aimCubes[i]->SetActorScale3D(FVector(.1f, .1f, .1f));
	}
	aimCubes[13]->SetActorScale3D(FVector(1.f, 1.f, 1.f));
	aimCubes[x]->SetActorScale3D(FVector(1.f, 1.f, 1.f));
	aimCubes[y]->SetActorScale3D(FVector(1.f, 1.f, 1.f));
}

void AAimCube::Target4(int x, int y, int z)
{
	canShoot = true;
	for (int i = 0; i < 27; i++)
	{
		aimCubes[i]->SetActorScale3D(FVector(.1f, .1f, .1f));
	}
	aimCubes[13]->SetActorScale3D(FVector(1.f, 1.f, 1.f));
	aimCubes[x]->SetActorScale3D(FVector(1.f, 1.f, 1.f));
	aimCubes[y]->SetActorScale3D(FVector(1.f, 1.f, 1.f));
	aimCubes[z]->SetActorScale3D(FVector(1.f, 1.f, 1.f));
}

// Called every frame
void AAimCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Warning, TEXT("targets = %d"), numberOfTargets);
}