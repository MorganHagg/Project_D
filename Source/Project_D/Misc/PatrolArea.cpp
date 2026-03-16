// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolArea.h"

APatrolArea::APatrolArea()
{
	PrimaryActorTick.bCanEverTick = true;
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	RootComponent = Spline;
	Spline->SetClosedLoop(true);

}

void APatrolArea::BeginPlay()
{
	TriangulateSpline();
	Super::BeginPlay();
}

bool APatrolArea::IsEar(const TArray<FVector>& Polygon, const TArray<int32>& Indices, int32 A, int32 B, int32 C)
{
	FVector VertexA = Polygon[A];
	FVector VertexB = Polygon[B];
	FVector VertexC = Polygon[C];	

	// Check if triangle ABC is convex by computing the cross product
	// If zero or negative, the triangle is concave or degenerate - not a valid ear
	float Convexity = (VertexB.X - VertexA.X) * (VertexC.Y - VertexA.Y) - (VertexB.Y - VertexA.Y) * (VertexC.X - VertexA.X);
	if (Convexity <= 0) return false;

	for (int32 Idx : Indices)
	{
		// Skip the triangle's own vertices
		if (Idx == A || Idx == B || Idx == C) continue;

		FVector TestPoint = Polygon[Idx];

		// Compute which side of each triangle edge the test point is on
		float SideOfAB = (TestPoint.X - VertexB.X) * (VertexA.Y - VertexB.Y) - (VertexA.X - VertexB.X) * (TestPoint.Y - VertexB.Y);
		float SideOfBC = (TestPoint.X - VertexC.X) * (VertexB.Y - VertexC.Y) - (VertexB.X - VertexC.X) * (TestPoint.Y - VertexC.Y);
		float SideOfCA = (TestPoint.X - VertexA.X) * (VertexC.Y - VertexA.Y) - (VertexC.X - VertexA.X) * (TestPoint.Y - VertexA.Y);

		bool HasNegative = (SideOfAB < 0) || (SideOfBC < 0) || (SideOfCA < 0);
		bool HasPositive = (SideOfAB > 0) || (SideOfBC > 0) || (SideOfCA > 0);

		// If all signs match, the test point is inside the triangle - not a valid ear
		if (!(HasNegative && HasPositive)) return false;
	}

	return true;
}
void APatrolArea::TriangulateSpline()
{
	// Creates a 2D Polygon of the patrol area
	TArray<FVector> Polygon;
	for (int32 i = 0; i < Spline->GetNumberOfSplinePoints(); i++)
	{
		FVector Point = Spline->GetLocationAtSplinePoint(i, ESplineCoordinateSpace::World);
		Polygon.Add(Point);
	}

	// List of all the indices of the polygon
	TArray<int32> Indices;
	for (int32 i = 0; i < Polygon.Num(); i++) Indices.Add(i);
	
	// Iterate through the indices and create triangles
	while (Indices.Num() > 3)
	{
		for (int32 i = 0; i < Indices.Num(); i++)
		{
			int32 A = Indices[(i - 1 + Indices.Num()) % Indices.Num()];
			int32 B = Indices[i];
			int32 C = Indices[(i + 1) % Indices.Num()];

			// 
			if (IsEar(Polygon, Indices, A, B, C))
			{
				FTriangle Tri;
				Tri.A = Polygon[A];
				Tri.B = Polygon[B];
				Tri.C = Polygon[C];
				Triangles.Add(Tri);
				Indices.RemoveAt(i);
				break;
			}
		}
	}

	// The alst triangle
	FTriangle LastTri;
	LastTri.A = Polygon[Indices[0]];
	LastTri.B = Polygon[Indices[1]];
	LastTri.C = Polygon[Indices[2]];
	Triangles.Add(LastTri);
}

bool APatrolArea::isPointInTriangle(FVector CheckingPoint)
{
	// Iterates through triangle to see if the point that is checked for is inside a triangle - if it is, the function immediately returns true
	for (FTriangle& Tri : Triangles)
	{
		FVector V0 = Tri.C - Tri.A;
		FVector V1 = Tri.B - Tri.A;
		FVector V2 = CheckingPoint - Tri.A;

		float Dot00 = FVector::DotProduct(V0, V0);
		float Dot01 = FVector::DotProduct(V0, V1);
		float Dot02 = FVector::DotProduct(V0, V2);
		float Dot11 = FVector::DotProduct(V1, V1);
		float Dot12 = FVector::DotProduct(V1, V2);

		float InvDenom = 1.0f / (Dot00 * Dot11 - Dot01 * Dot01);
		float U = (Dot11 * Dot02 - Dot01 * Dot12) * InvDenom;
		float V = (Dot00 * Dot12 - Dot01 * Dot02) * InvDenom;

		if ((U >= 0) && (V >= 0) && (U + V <= 1)) return true;
	}

	return false;
}

void APatrolArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

