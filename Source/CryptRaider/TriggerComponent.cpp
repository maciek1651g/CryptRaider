// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor *Actor = GetAcceptableActor();
    if (Actor)
    {
        UPrimitiveComponent *Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent());
        if (Component)
        {
            if (!Actor->ActorHasTag("Grabbed"))
            {
                Component->SetSimulatePhysics(false);
                Actor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
                Mover->SetShouldMove(true);
            }
            else
            {
                Component->SetSimulatePhysics(true);
                Actor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
                Mover->SetShouldMove(false);
            }
        }
    }
    else
    {
        Mover->SetShouldMove(false);
    }
}

AActor *UTriggerComponent::GetAcceptableActor() const
{
    TArray<AActor *> Actors;
    GetOverlappingActors(Actors);

    for (AActor *Actor : Actors)
    {
        if (Actor->ActorHasTag(UnlockTag))
        {
            return Actor;
        }
    }

    return nullptr;
}

void UTriggerComponent::SetMover(UMover *NewMover)
{
    Mover = NewMover;
}