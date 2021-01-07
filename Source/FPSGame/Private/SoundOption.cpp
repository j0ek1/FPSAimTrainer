// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.


#include "SoundOption.h"
#include "Kismet/GameplayStatics.h"
#include "Classes/Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"

bool soundOn; //Determins whether sound is selected to be on of off
TArray<AActor*> soundOption; //Array of the target number selection cubes

//Sets default values
ASoundOption::ASoundOption()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent"); //Creating static mesh component for the cubes
	StaticMesh->OnComponentHit.AddDynamic(this, &ASoundOption::OnHit);
}

//Called when the game starts or when spawned
void ASoundOption::BeginPlay()
{
	Super::BeginPlay();

	soundOn = true; //At start, turn sound on

	TSubclassOf<ASoundOption> classToFind; //Getting all actors of class and putting them into one array
	classToFind = ASoundOption::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(this, classToFind, soundOption);
}

void ASoundOption::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) //When the cube gets hit
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) //If we hit an actor that is not itself
	{
		if (this == soundOption[0]) //Switch to turn sound on or off
		{
			soundOn = true;
		}
		if (this == soundOption[1])
		{
			soundOn = false;
		}
	}
}

//Called every frame
void ASoundOption::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

