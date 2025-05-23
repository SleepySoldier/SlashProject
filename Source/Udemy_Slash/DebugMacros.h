#pragma once

#include "DrawDebugHelpers.h"

#define DRAW_SPHERE(Location) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12, FColor::Red, true);
#define DRAW_SPHERE_COLOR(Location, Color) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 8.f, 12, Color, false, 5.f);
#define DRAW_SPHERE_SINGLEFRAME(Location) if (GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12, FColor::Red, false, -1.f);
#define DRAW_LINE(StartLocation, EndLocation) if (GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 60.f);
#define DRAW_LINE_SINGLEFRAME(StartLocation, EndLocation) if (GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.f);
#define DRAW_POINT(Location) if (GetWorld()) DrawDebugPoint(GetWorld(), Location, 20.f, FColor::Yellow, true, -1.f);
#define DRAW_VECTOR(StartLocation, EndLocation) if (GetWorld()) \
	{ \
		 DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 60.f); \
		 DrawDebugPoint(GetWorld(), EndLocation, 20.f, FColor::Yellow, true, -1.f); \
	}
#define DRAW_VECTOR_SINGLEFRAME(StartLocation, EndLocation) if (GetWorld()) \
	{ \
		 DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.f); \
		 DrawDebugPoint(GetWorld(), EndLocation, 20.f, FColor::Yellow, false, -1.f); \
	}
#define DRAW_CRAPSULE(StartLocation, EndLocation, Color) if (GetWorld()) \
	{ \
		DrawDebugSphere(GetWorld(), StartLocation, 25.f, 12, Color, true); \
		DrawDebugSphere(GetWorld(), EndLocation, 25.f, 12, Color, true); \
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, Color, true); \
	}

#define DRAW_POINT_SINGLEFRAME(Location) if (GetWorld()) DrawDebugPoint(GetWorld(), Location, 20.f, FColor::Yellow, false, -1.f);
