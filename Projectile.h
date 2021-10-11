#pragma once
#include<math.h>

struct Projectile
{
public:
	float g = 9.8f; //Force de gravit�e exerc�e sur le projectile
	float Vinit;	//Vitesse initiale donn�e au projectile
	float Hauteur;  //Hauteur de laquelle le projectile est lanc�
	float Angle;	//Angle de lanc� du projectile par rapport � la normale (appartient � ]pi/2 ; 0[).


public:
	/// <summary>
	/// Consct
	/// </summary>
	Projectile()
	{
		g = 9.8f;
		Vinit = 0;
		Hauteur = 0;
		Angle = 3.14f / 4.0f;
	}


	/// <summary>
	/// 	//Construteur par param�tre
	/// </summary>
	/// <param name="V">Vitesse initiale du projectile</param>
	/// <param name="hauteur">Hauteur de laquelle il est lanc�</param>
	/// <param name="ang">Angle auquel il est lanc� par rapport � la normale</param>
	Projectile(float V, float hauteur, float ang)
	{
		Vinit = V;
		Hauteur = hauteur;
		Angle = ang;
		CheckAngle(); //V�rifie que l'angle de lanc� appartient � ]pi/2 ; 0[
	}


	/// <summary>
	/// Retourne la hauteur en tout point X selon l'�quation de la trajectoire sans frottement de l'air
	/// </summary>
	inline float Zcoord(float x)
	{
		float z = -g / 2.0f * (x * x) / (Vinit * Vinit * cos(Angle) * cos(Angle)) + tan(Angle) * x + Hauteur; //Equation de la trajectoire
		return z;
	}


	/// <summary>
	///Duree de vol du projectile
	/// </summary>
	inline float DureeParcours()
	{
		return Xmax() / (Vinit * cos(Angle));
	}

	

	/// <summary>
	/// Portee du tir du projectile
	/// </summary>
	inline float Xmax()
	{
		return (Vinit * cos(Angle) / g * (Vinit * sin(Angle) + sqrt((Vinit * sin(Angle)) * (Vinit * sin(Angle)) + 2 * g * Hauteur)));
	}


	/// <summary>
	///Hauteur maximale atteinte par le projectile
	/// </summary>
	inline float Zmax()
	{
		float zmax = Vinit * Vinit * sin(Angle) * sin(Angle) / (2.0f * g) + Hauteur;
		return zmax;
	}


	
	/// <summary>
	///Modifier les propri�t�s du projectile
	/// </summary>
	/// <param name="V">Vitesse initiale du projectile</param>
	/// <param name="hauteur">Hauteur de laquelle il est lanc�</param>
	/// <param name="ang">Angle auquel il est lanc� par rapport � la normale</param>
	inline void SetNewProperties(float V, float h, float ang)
	{
		Vinit = V;
		Hauteur = h;
		Angle = ang;
		CheckAngle();
	}



	/// <summary>
	///Coordonn�es x en fonction de t
	/// </summary>
	inline float xt(float t)
	{
		return (Vinit * cos(Angle) * t);
	}


	/// <summary>
	///Coordonn�es z en fonction de t
	/// </summary>
	inline float zt(float t)
	{
		return(-g / 2.0f * t * t + Vinit * sin(Angle) * t + Hauteur);
	}


	/// <summary>
	///Vitesse du projectile en tout point x
	/// </summary>
	inline float VitesseEnX(float x)
	{
		return sqrt(Vinit * Vinit - 2 * g * x * tan(Angle) + ((g * x) / (Vinit * cos(Angle)))* ((g * x) / (Vinit * cos(Angle))));
	}


private:

	//Fonctions de debogage
	
	/// <summary>
	/// Fonction V�rifiant que l'angle de lanc� appartient � ]pi/2 ; 0[
	/// </summary>
	inline void CheckAngle()
	{
		if (Angle >= 3.14 / 2.0f)
		{
			Angle = 3.13f / 2.0f;
		}
		if (Angle <= 0)
		{
			Angle = 0.01f;
		}
	}
};