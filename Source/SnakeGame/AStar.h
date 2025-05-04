// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
struct FPathNode
{

	int32 X;
	int32 Y;
	int32 GCost;  // Cost from start node
	int32 HCost;  // Heuristic cost to end
	int32 FCost() const { return GCost + HCost; }
	FPathNode* Parent;

	FPathNode() : X(0), Y(0), GCost(0), HCost(0), Parent(nullptr) {}
	FPathNode(int32 InX, int32 InY) : X(InX), Y(InY), GCost(0), HCost(0), Parent(nullptr) {}

	bool operator==(const FPathNode& Other) const
	{
		return X == Other.X && Y == Other.Y;
	}
};

class SNAKEGAME_API AStar
{
public:
	AStar();
	
	~AStar();
	
	TArray<FVector> FindPath(const FVector& Start, const FVector& Target, 
                           const TArray<FVector>& OccupiedPosition);

private:
	TArray<FVector> PositionArrayToGridArray(const TArray<FVector> PositionArray) const;
	FVector PositionToGridPos(const FVector Position) const;
	int GetHeuristic(const FVector& A, const FVector& B)
	{
		return FMath::Abs(A.X - B.X) + FMath::Abs(A.Y - B.Y);
	}
    
	
};
