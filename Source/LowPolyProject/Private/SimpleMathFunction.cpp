// Fill out your copyright notice in the Description page of Project Settings.


#include "SimpleMathFunction.h"

void USimpleMathFunction::IsChangingSector(const FVector PositionToLook, const int32 NatureSizeChunk, int32 &NewStep)
{
	NewStep = {FMath::TruncToInt(PositionToLook.Z/NatureSizeChunk) + (int32)FMath::Sign(PositionToLook.Z) - (FMath::Sign(PositionToLook.Z)  == 0)};
}

void USimpleMathFunction::GetCirclePoint(const int32 Index, const int32 NumberPoints, const float Radius, const FVector Center, FVector &CirclePosition)
{
	float Angle = FMath::GetMappedRangeValueClamped({0.f, (float)NumberPoints}, {0.f, 6.283f}, (float)Index);
	FVector Offset = {Radius * FMath::Cos(Angle), Radius * FMath::Sin(Angle), 0};
	CirclePosition = Center + Offset;
}
