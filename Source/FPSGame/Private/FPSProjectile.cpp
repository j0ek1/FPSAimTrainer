// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

extern int score;
extern bool hasStarted;
int targetsMiss = 0;

AFPSProjectile::AFPSProjectile() 
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp")); //Setting sphere component values
	CollisionComp->InitSphereRadius(0.05f);
	CollisionComp->SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);	//Setting up the on hit detection function

	//Set that players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	//Set as root component
	RootComponent = CollisionComp;

	//Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 1000000.f; //Could have used a raytracing/hitscan method instead of a projectile
	ProjectileMovement->MaxSpeed = 1000000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	//Die after 0.2 seconds by default
	InitialLifeSpan = 0.2f;
}


void AFPSProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics()) //If we hit an actor that is not itself and is simulating physics
	{
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		FVector Scale = OtherComp->GetComponentScale(); //Set the actors scale to 10%
		Scale *= 0.1f;
		OtherComp->SetWorldScale3D(Scale);

		Destroy();
	}
	if (!(OtherComp->IsSimulatingPhysics()) && hasStarted) //If they hit the wall (not a cube)
	{
		score--;
		targetsMiss++;
	}
	if (OtherActor == this) //If the bullet hits itself, destroy
	{
		Destroy();
	}
}