// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FastNoise/VoxelFastNoise.h"
#include "VoxelGenerators/VoxelGeneratorHelpers.h"
#include "VoxelMaterialBuilder.h"
#include "MyWorldGenerator.generated.h"

UCLASS(Blueprintable)
class UMyWorldGenerator : public UVoxelGenerator
{
	GENERATED_BODY()


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
		int32 Seed = 1337;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
		float NoiseHeight1 = 10.f;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
		float NoiseHeight2 = 10.f;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
		float NoiseHeightMax = 10.f;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator", meta = (UIMax = "1", UIMin = "0"))
		float _3D_Noise_Frequency1 = 0.1f;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator", meta = (UIMax = "1", UIMin = "0"))
		float _3D_Noise_Frequency2 = 0.5f;
	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
		float DistanceBetweenSteps = 50.f;
	// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
		float OffsetSize = 10000.f;
	// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
		float SmoothNess = 5.f;
	// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
		float Radius = 64.f;
	// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
		int32 Deepness = -4;
	// 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator")
		int32 MaterialNumber;
	// 


	//~ Begin UVoxelWorldGenerator Interface
	virtual TVoxelSharedRef<FVoxelGeneratorInstance> GetInstance() override;
	//~ End UVoxelWorldGenerator Interface
};

class FMyWorldGeneratorInstance : public TVoxelGeneratorInstanceHelper<FMyWorldGeneratorInstance, UMyWorldGenerator>
{
public:
	using Super = TVoxelGeneratorInstanceHelper<FMyWorldGeneratorInstance, UMyWorldGenerator>;

	explicit FMyWorldGeneratorInstance(const UMyWorldGenerator& MyGenerator);

	//~ Begin FVoxelGeneratorInstance Interface
	virtual void Init(const FVoxelGeneratorInit& InitStruct) override;

	v_flt GetValueImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const;
	FVoxelMaterial GetMaterialImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const;

	TVoxelRange<v_flt> GetValueRangeImpl(const FVoxelIntBox& Bounds, int32 LOD, const FVoxelItemStack& Items) const;

	virtual FVector GetUpVector(v_flt X, v_flt Y, v_flt Z) const override final;
	//~ End FVoxelWorldGeneratorInstance Interface

private:
	const int32 Seed;
	float NoiseHeight1;
	float NoiseHeight2;
	float NoiseHeightMax;
	float _3D_Noise_Frequency1;
	float _3D_Noise_Frequency2;
	float DistanceBetweenSteps;
	float OffsetSize;
	float SmoothNess;
	float Radius;
	int32 Deepness;
	int32 MaterialNumber;
	FVoxelFastNoise Noise;
};
