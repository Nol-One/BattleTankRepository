// Copyright N01 Ltda.

#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

ASprungWheel::ASprungWheel()
{
	PrimaryActorTick.bCanEverTick = true; // set true in order for tick to work.
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	MassAxleConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassAxleConstraint"));
	SetRootComponent(MassAxleConstraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(MassAxleConstraint);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->SetupAttachment(Axle);

	AxleWheelConstraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstraint"));
	AxleWheelConstraint->SetupAttachment(Axle);
}

void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();	

	SetupConstraint();

	// setting up what the delegate will call
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
}

void ASprungWheel::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalForceThisFrame = 0.0;
	}
}

void ASprungWheel::SetupConstraint()
{
	if(!GetAttachParentActor()) return;
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) return;
	
	MassAxleConstraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleWheelConstraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

void ASprungWheel::AddDrivingForce(float Force)
{
	TotalForceThisFrame += Force;
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Wheel->AddForce(Axle->GetForwardVector() * TotalForceThisFrame);
}


