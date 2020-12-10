// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetNum.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "AimCube.h" //To access AimCube functions

TArray<AActor*> targetNum; //Array of the target number selection cubes
int numberOfTargets = 1; //Players choice of number of targets
extern bool hasStarted;
AAimCube* func;

// Sets default values
ATargetNum::ATargetNum()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent"); //Creating static mesh component for the cubes
	StaticMesh->OnComponentHit.AddDynamic(this, &ATargetNum::OnHit);
}

// Called when the game starts or when spawned
void ATargetNum::BeginPlay()
{
	Super::BeginPlay();

	TSubclassOf<ATargetNum> classToFind; //Getting all actors of class and putting them into one array
	classToFind = ATargetNum::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(this, classToFind, targetNum);

}

void ATargetNum::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) //When the cube gets hit
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && (!hasStarted)) //If we hit an actor that is not itself
	{
		if (this == targetNum[0])
		{
			numberOfTargets = 1;
			func->Target1();
		}
		if (this == targetNum[1])
		{
			numberOfTargets = 2;
			int x;
			do //Ensuring the random values generated are not the same
			{
				x = FMath::RandRange(0, 26);
			} while (x == 13);
			func->Target2(x);
		}
		if (this == targetNum[2])
		{
			numberOfTargets = 3;
			int x;
			do //Ensuring the random values generated are not the same
			{
				x = FMath::RandRange(0, 26);
			} while (x == 13);
			int y;
			do
			{
				y = FMath::RandRange(0, 26);
			}
			while (y == x || y == 13);
			func->Target3(x, y);
		}
		if (this == targetNum[3])
		{
			numberOfTargets = 4;
			int x;
			do //Ensuring the random values generated are not the same
			{
				x = FMath::RandRange(0, 26);
			} while (x == 13);
			int y;
			do
			{
				y = FMath::RandRange(0, 26);
			} while (y == x || y == 13);
			int z;
			do
			{
				z = FMath::RandRange(0, 26);
			} while (z == x || z == y || z == 13);
			func->Target4(x, y, z);
		}
	}
}

// Called every frame
void ATargetNum::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

