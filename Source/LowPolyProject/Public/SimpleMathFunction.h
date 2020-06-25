// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SimpleMathFunction.generated.h"

/**
 * 
 */
UCLASS()
class LOWPOLYPROJECT_API USimpleMathFunction : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
		
public:
	UFUNCTION(BlueprintCallable, Category = "SimpleMath")
		static void IsChangingSector(const FVector PositionToLook,const int32 NatureSizeChunk, int32 &NewStep);

public:
	UFUNCTION(BlueprintCallable, Category = "SimpleMath")
		static void GetCirclePoint(const int32 Index, const int32 NumberPoints, const float Radius, const FVector Center, FVector &CirclePosition);
		
};
