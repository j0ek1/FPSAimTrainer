// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AimCube.generated.h"

UCLASS()
class AAimCube : public AActor
{
	GENERATED_BODY()
	
public:	

	AAimCube(); //Constructor

	UFUNCTION() //Function for when the cube gets hit
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void TimerHandle();
	UFUNCTION()
	void TimerReset();

	UFUNCTION() 
	void Target1();
	UFUNCTION()
	void Target2(int x);
	UFUNCTION()
	void Target3(int x, int y);
	UFUNCTION()
	void Target4(int x, int y, int z);

protected:
	//Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components") //Creating static mesh component for the cubes
	UStaticMeshComponent* StaticMesh;

public:	

	//Called every frame
	virtual void Tick(float DeltaTime) override;

};
