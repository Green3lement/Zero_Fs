#include "Maglev.h"

void UMaglev::CustomPhysics(float DeltaTime, FBodyInstance* BodyInst)
{
	//simulate
	FTransform Transform = GetComponentTransform();
	FHitResult result;
	FCollisionObjectQueryParams objParams;

	for (TEnumAsByte<ECollisionChannel> col : CollisionChannels) {
		objParams.AddObjectTypesToQuery(col);
	};

	FCollisionQueryParams queryParams;
	queryParams.AddIgnoredActor(GetOwner());

	FVector Direction = Transform.GetUnitAxis(EAxis::X);
	bool Hit = GetWorld()->SweepSingleByObjectType(
		result,
		Transform.GetTranslation(),
		Transform.GetTranslation() + Direction*Distance,
		FQuat(1, 0, 0, 1),
		objParams,
		FCollisionShape::MakeSphere(Radius),
		queryParams);

	FVector TotalForce = FVector(0, 0, 0);
	FVector ThrustVector = -Direction;
	if (Hit) {
		TotalForce = ThrustVector*(Thrust*(1.0f - result.Time)*(1.0f-OpenAirThrustPerc));

		float DampSpeed = (PreviousPosition- result.Time) / DeltaTime;

		if (ProgressiveDamping) {
			DampSpeed *= (1.0f - result.Time);
		}
		if (!BidirectionalDamping) {
			DampSpeed = FMath::Max(DampSpeed, 0.0f);
		}

		TotalForce += ThrustVector*DampSpeed*Damping*Thrust;

		PreviousPosition = result.Time;
	}
	else {
		PreviousPosition = 1.0f;
	}

	TotalForce += ThrustVector*Thrust*OpenAirThrustPerc;

	BodyInst->AddForceAtPosition(TotalForce, Transform.GetTranslation(), false);
}