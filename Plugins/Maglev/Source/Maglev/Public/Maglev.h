// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Components/SceneComponent.h"
#include "Maglev.generated.h"

UCLASS( ClassGroup=(Custom), HideCategories=(Lighting, Collision, Physics) ,meta=(BlueprintSpawnableComponent) )
class MAGLEV_API UMaglev : public UPrimitiveComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMaglev();

	// Called when the game starts
	virtual void BeginPlay() override;

	FCalculateCustomPhysics OnCalculateCustomPhysics;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Simulation") bool Substep;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Simulation") float Distance = 100.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Simulation") float Radius = 5.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Simulation") float Thrust = 100000.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Simulation") float OpenAirThrustPerc = 0.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Simulation") float Damping = 1.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Simulation") bool ProgressiveDamping = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Simulation") bool BidirectionalDamping;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Simulation") TArray<TEnumAsByte<ECollisionChannel>> CollisionChannels;

#ifdef WITH_EDITOR
	virtual FPrimitiveSceneProxy* CreateSceneProxy() override;
#endif

private:
	float PreviousPosition=1.0f;

	void CustomPhysics(float DeltaTime, FBodyInstance* BodyInst);
};