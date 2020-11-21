// Fill out your copyright notice in the Description page of Project Settings.

#include "Maglev.h"

// Sets default values for this component's properties
UMaglev::UMaglev()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bHiddenInGame = true;
	PrimaryComponentTick.bCanEverTick = true;
	bUseAttachParentBound = true;
	OnCalculateCustomPhysics.BindUObject(this, &UMaglev::CustomPhysics);
	SetTickGroup(ETickingGroup::TG_PrePhysics);
}


// Called when the game starts
void UMaglev::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UMaglev::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	UPrimitiveComponent *Parent = Cast<UPrimitiveComponent>(GetAttachParent());
	if (!Parent) return;
	if (!Parent->IsSimulatingPhysics()) return;
	FBodyInstance *bodyInst = Parent->GetBodyInstance();

	if (Substep) {
		bodyInst->AddCustomPhysics(OnCalculateCustomPhysics);
	}
	else {
		CustomPhysics(DeltaTime, bodyInst);
	}
}