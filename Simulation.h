#pragma once
#include<iostream>
#include<math.h>
#include<chrono>
#include"Projectile.h"
#include<opencv2/core.hpp>
#include<opencv2/video.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>

#define HEIGHT 800
#define WIDTH 1200

class Simulation
{
private:
	std::string m_WindowName; //Nom de la fenetre de la simulation
	cv::Mat Window; //Matrice contenant l'arri�re plan de la simulation
	Projectile m_obj; //Projectile dont on effectue la simulation de projection


private:

/// <summary>
/// Permet d'afficher la fenetre de la simulation. Cela correspond � l'arri�re plan pendant ue simulation
/// </summary>
	void ConstructWindow() const;


/// <summary>
/// Permet de dessiner sur l'arri�re plan de la simulation la pr�vision de la trajectoire du projectile
/// </summary>
	void PreviewTrajectory();


/// <summary>
/// Fonction dans laquelle on ajoute tous les elements graphiques qui sont mis � jour � chaque frame
/// </summary>
/// <param name="img">Image qui sera ensuite affich�e � l'�cran</param>
/// <param name="t">Temps t auquel on se trouve dans l'animation</param>
/// <param name="ElapsedTime">Temps que prend la boucle g�n�ral de la simulation pour faire un tour. Permet de connaitre la fr�quence de raffraichissement de l'animation</param>
	void Draw(cv::Mat& img, float x, float& ETime);


/// <summary>
/// Cr�er une copie de l'image du background pour ne pas la modifier. C'est sur cette copie qu'on applique ensuite la fonction Draw().
/// Finalement, on peut afficher l'image obtenue.
/// </summary>
/// <param name="t">Temps t auquel on se trouve dans l'animation</param>
/// <param name="Etime">Temps que prend la boucle g�n�ral de la simulation pour faire un tour. Permet de connaitre la fr�quence de raffraichissement de l'animation </param>
	void Update(float x, float& ETime);


/// <summary>
/// Fonction qui permet de d�terminer le rapport entre la hauteur de la fentre et la hauteur max ET celui entre 
/// </summary>
/// <returns></returns>
	float Scale();


/// <summary>
/// Fonction qui retourne le plus petit deux float
/// </summary>
/// <param name="a">Premier float</param>
/// <param name="b">Second float</param>
/// <returns>La plus petite valeur entre a et b</returns>
	float Smallest(float a, float b);



public:

/// <summary>
/// Constructeur par d�faut de la classe Simulation
/// </summary>
	Simulation();


/// <summary>
/// Constructeur par param�tres de la classe Simulation
/// </summary>
/// <param name="WinName">Nom de la fentre</param>
/// <param name="WinHeight">Hauteur de la fenetre en pixel</param>
/// <param name="WinWidth">Largeur de la fenetre en pixel</param>
/// <param name="obj">Projectile dont on veut faire la simulation de projection</param>
	Simulation(std::string WinName, const unsigned int WinHeight, const unsigned int WinWidth, const Projectile& obj);


/// <summary>
/// Cette boucle permet d'appeler la fonction update � chaque frame pour mettre � jour la simulation pendant toute la dur�e de cette derni�re.
/// On en profite pour calculer 
/// </summary>
	void PlaySimulation(float StartX, float Timespeed);

};

