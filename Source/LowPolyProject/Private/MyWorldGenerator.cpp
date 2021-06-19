#include "MyWorldGenerator.h"
#include "FastNoise/VoxelFastNoise.inl"

TVoxelSharedRef<FVoxelGeneratorInstance> UMyWorldGenerator::GetInstance()
{
	return MakeVoxelShared<FMyWorldGeneratorInstance>(*this);
}

///////////////////////////////////////////////////////////////////////////////

FMyWorldGeneratorInstance::FMyWorldGeneratorInstance(const UMyWorldGenerator& MyGenerator)
	: Super(&MyGenerator)
	, Seed(MyGenerator.Seed)
	, NoiseHeight1(MyGenerator.NoiseHeight1)
	, NoiseHeight2(MyGenerator.NoiseHeight2)
	, NoiseHeightMax(MyGenerator.NoiseHeightMax)
	, _3D_Noise_Frequency1(MyGenerator._3D_Noise_Frequency1)
	, _3D_Noise_Frequency2(MyGenerator._3D_Noise_Frequency2)
	, DistanceBetweenSteps(MyGenerator.DistanceBetweenSteps)
	, OffsetSize(MyGenerator.OffsetSize)
	, SmoothNess(MyGenerator.SmoothNess)
	, MaterialNumber(MyGenerator.MaterialNumber)
	, Radius(MyGenerator.Radius)
	, Deepness(MyGenerator.Deepness)
{
}


void FMyWorldGeneratorInstance::Init(const FVoxelGeneratorInit& InitStruct)
{
	Noise.SetSeed(Seed);
}

v_flt FMyWorldGeneratorInstance::GetValueImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const
{
	if (Z >= DistanceBetweenSteps / 2 || FVector(X, Y, 0).Size() >= Radius)
		return 1;

	const int Step = std::roundf(Z / DistanceBetweenSteps);
	if (Step < Deepness)
		return 1;

	const float Offset = OffsetSize * Step;
	const float Height1 = Noise.GetPerlin_2D(X + Offset, Y + Offset, _3D_Noise_Frequency1) * NoiseHeight1;
	const float Height2 = Noise.GetPerlin_2D(X + Offset, Y + Offset, _3D_Noise_Frequency2) * NoiseHeight2;

	if (Height1 <= Height2)
	{
		if ((Z - Step * DistanceBetweenSteps) <= Height2 && (Z - Step * DistanceBetweenSteps) >= Height1)
			return std::fmaxf(-std::abs(Z - Height2 - Step * DistanceBetweenSteps), -std::abs(Z - Height1 - Step * DistanceBetweenSteps));
		else
			return std::fminf(std::abs(Z - Height2 - Step * DistanceBetweenSteps), std::abs(Z - Height1 - Step * DistanceBetweenSteps));
	}
	else
		return 1;
}

FVoxelMaterial FMyWorldGeneratorInstance::GetMaterialImpl(v_flt X, v_flt Y, v_flt Z, int32 LOD, const FVoxelItemStack& Items) const
{
	FVoxelMaterialBuilder Builder;
	Builder.SetMaterialConfig(EVoxelMaterialConfig::SingleIndex);

	if (MaterialNumber == 0)
	{
		Builder.SetSingleIndex(0);
		return Builder.Build();
	}
	else
	{
		const int Step = std::roundf(FMath::Abs(Z) / DistanceBetweenSteps);
		int32 RandNumber = FMath::Clamp((int)FMath::Abs(FMath::Fmod(X + Y + Z, 4)) + Step, 0, MaterialNumber - 1);
		Builder.SetSingleIndex(RandNumber);
		return Builder.Build();
	}
}

TVoxelRange<v_flt> FMyWorldGeneratorInstance::GetValueRangeImpl(const FVoxelIntBox& Bounds, int32 LOD, const FVoxelItemStack& Items) const
{
	// Return the values that GetValueImpl can return in Bounds
	// Used to skip chunks where the value does not change
	// Be careful, if wrong your world will have holes!
	// By default return infinite range to be safe
	return TVoxelRange<v_flt>::Infinite();

	// Example for the GetValueImpl above

	// Noise is between -1 and 1
	const TVoxelRange<v_flt> Height = TVoxelRange<v_flt>(-1, 1) * NoiseHeightMax;

	// Z can go from min to max
	TVoxelRange<v_flt> Value = TVoxelRange<v_flt>(Bounds.Min.Z, Bounds.Max.Z) - Height;

	return Value / SmoothNess;
}

FVector FMyWorldGeneratorInstance::GetUpVector(v_flt X, v_flt Y, v_flt Z) const
{
	// Used by spawners
	return FVector::UpVector;
}