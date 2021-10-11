//
// Codé par William ISABELLE. Ce programme a été réalisé dans le cadre de ma deuxième année de prépa intégrée à POLYTECH Orléans.
//

#include<iostream>
#include"Simulation.h"
#include"Projectile.h"
using namespace cv;
using namespace std;


void Run()
{
	int StartPosSimulation = 0;
	float TimeSpeed = 2.0f;

	Projectile obj(100, 50, 3.14f / 3.0f);

	Simulation Demo("DEMO", HEIGHT, WIDTH, obj);

	Demo.PlaySimulation(StartPosSimulation, TimeSpeed);
}


int main()
{
	Run();
	return 0;
}	
