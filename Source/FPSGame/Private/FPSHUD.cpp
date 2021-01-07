// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/HUD.h"

float time = 20.f;
UFont* arial;
extern bool hasStarted;
extern int score;
extern int targetsHit;
extern int targetsMiss;

AFPSHUD::AFPSHUD()
{
	//Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshairTexObj(TEXT("/Game/UI/FirstPersonCrosshair"));
	CrosshairTex = CrosshairTexObj.Object;
	//Set the HUD font
	static ConstructorHelpers::FObjectFinder<UFont> uiFontAsset(TEXT("/Game/UI/HUDFont"));
	arial = uiFontAsset.Object;
}


void AFPSHUD::DrawHUD()
{
	Super::DrawHUD();

	//Find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	//Offset by half the texture's dimensions so that the center of the texture aligns with the center of the Canvas
	const FVector2D CrosshairDrawPosition(Center.X - (CrosshairTex->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTex->GetSurfaceHeight() * 0.5f));

	//Draw the crosshair
	FCanvasTileItem TileItem( CrosshairDrawPosition, CrosshairTex->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem( TileItem );

	int timeInt = FMath::FloorToInt(time); //Converting the time to int
	FString timeValue = FString::FromInt(timeInt); //Converting the time int to a string to be displayed
	FString timeText = "Time:";
	FString scoreValue = FString::FromInt(score); //Converting the score to a string to be displayed
	FString scoreText = "Score:";
	DrawText(timeText, FColor::White, 25.f, 20.f, arial, .25f, false); //Drawing the timer on the HUD
	DrawText(timeValue, FColor::White, 90.f, 20.f, arial, .25f, false);
	DrawText(scoreText, FColor::White, 1080.f, 20.f, arial, .25f, false); //Drawing the score on the HUD
	DrawText(scoreValue, FColor::White, 1155.f, 20.f, arial, .25f, false);

	FString hitValue = FString::FromInt(targetsHit); //Converting the targets hit to a string to be displayed
	FString hitText = "Targets hit:";
	FString missValue = FString::FromInt(targetsMiss); //Converting the targets missed to a string to be displayed
	FString missText = "Targets missed:";
	DrawText(hitText, FColor::White, 1030.f, 50.f, arial, .25f, false); //Displaying targets hit and targets missed
	DrawText(hitValue, FColor::White, 1155.f, 50.f, arial, .25f, false);
	DrawText(missText, FColor::White, 980.f, 80.f, arial, .25f, false);
	DrawText(missValue, FColor::White, 1155.f, 80.f, arial, .25f, false);
}

void AFPSHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (hasStarted)
	{
		time -= DeltaTime;
	}
	else
	{
		time = 20.f;
	}
}
