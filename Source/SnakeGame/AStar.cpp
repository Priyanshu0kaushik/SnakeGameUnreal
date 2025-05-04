// Fill out your copyright notice in the Description page of Project Settings.


#include "AStar.h"
#include  "Core.h"
#include "DrawDebugHelpers.h"

AStar::AStar()
{
    
}

AStar::~AStar()
{
   
}

TArray<FVector> AStar::FindPath(const FVector& Start, const FVector& Target, const TArray<FVector>& OccupiedPosition)
{
	FVector StartLocation = PositionToGridPos(Start);
	FVector GoalLocation = PositionToGridPos(Target);
	TArray<FVector> OccupiedGrid = PositionArrayToGridArray(OccupiedPosition);
	auto CompareNodes = [](FPathNode* A, FPathNode* B) { return A->FCost() < B->FCost(); };
	TArray<FPathNode*> OpenList;
	TSet<FVector> ClosedSet;

	FPathNode* StartNode = new FPathNode(StartLocation.X, StartLocation.Y);
	StartNode->GCost = 0;
	StartNode->HCost = GetHeuristic(StartLocation, GoalLocation);
	OpenList.Add(StartNode);
	TArray<FVector> Directions = {
		FVector(1, 0, 0),
		FVector(-1, 0, 0),
		FVector(0, 1, 0),
		FVector(0, -1, 0)
	};

	while (OpenList.Num() > 0)
	{
		FPathNode* Current = OpenList[0];
		for (FPathNode* Node : OpenList)
		{
			if (Node->FCost() < Current->FCost() ||
				(Node->FCost() == Current->FCost() && Node->HCost < Current->HCost))
			{
				Current = Node;
			}
		}

		if (Current->X == GoalLocation.X && Current->Y == GoalLocation.Y)
		{
			TArray<FVector> FinalPath;
			FPathNode* PathNode = Current;
			while (PathNode)
			{
				FinalPath.Insert(FVector(PathNode->X, PathNode->Y, 0), 0);
				PathNode = PathNode->Parent;
			}
			for (FPathNode* Node : OpenList) delete Node;
			return FinalPath;
		}

		OpenList.Remove(Current);
		ClosedSet.Add(FVector(Current->X, Current->Y, 0));

		for (const FVector& Dir : Directions)
		{
			int32 NX = Current->X + Dir.X;
			int32 NY = Current->Y + Dir.Y;
			FVector NeighborPos(NX, NY, 0);

			if (ClosedSet.Contains(NeighborPos) || OccupiedGrid.Contains(NeighborPos))
				continue;

			int32 TentativeG = Current->GCost + 1;

			FPathNode* Existing = nullptr;
			for (FPathNode* Node : OpenList)
			{
				if (Node->X == NX && Node->Y == NY)
				{
					Existing = Node;
					break;
				}
			}

			if (!Existing)
			{
				FPathNode* Neighbor = new FPathNode(NX, NY);
				Neighbor->GCost = TentativeG;
				Neighbor->HCost = GetHeuristic(NeighborPos, GoalLocation);
				Neighbor->Parent = Current;
				OpenList.Add(Neighbor);
			}
			else if (TentativeG < Existing->GCost)
			{
				Existing->GCost = TentativeG;
				Existing->Parent = Current;
			}
		}
	}

	for (FPathNode* Node : OpenList) delete Node;
	UE_LOG(LogTemp, Warning, TEXT("AStar::FindPath"));
	return {};

}


FVector AStar::PositionToGridPos(const FVector Position) const
{
	FVector GridPos;
	GridPos.X = FMath::RoundToInt(Position.X / TileSize);
	GridPos.Y = FMath::RoundToInt(Position.Y / TileSize);
	GridPos.Z = Position.Z;
	return GridPos;
}

TArray<FVector> AStar::PositionArrayToGridArray(const TArray<FVector> PositionArray) const
{
	TArray<FVector> GridArray;
	for (FVector WorldPos : PositionArray)
	{
		GridArray.Add(PositionToGridPos(WorldPos));
	}
	return GridArray;
}

