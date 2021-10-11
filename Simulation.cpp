#include "Simulation.h"


/// <summary>
/// Fonction dans laquelle on ajoute tous les elements graphiques qui sont mis � jour � chaque frame
/// </summary>
/// <param name="img">Image qui sera ensuite affich�e � l'�cran</param>
/// <param name="t">Temps t auquel on se trouve dans l'animation</param>
/// <param name="ElapsedTime">Temps que prend la boucle g�n�ral de la simulation pour faire un tour. Permet de connaitre la fr�quence de raffraichissement de l'animation</param>
void Simulation::Draw(cv::Mat& img, float t, float& ElapsedTime) //Function called every frame
{
	float radius = 10;
	//circle(img, cv::Point(t, Window.rows - m_obj.Zcoord(t)), radius, cv::Scalar(255, 255, 255), cv::FILLED); //Draw the projectile (x, Zcoord(x))

	circle(img, cv::Point(m_obj.xt(t) * Scale(), Window.rows - m_obj.zt(t) * Scale()), radius, cv::Scalar(255, 255, 255), cv::FILLED); //Draw the projectile (xt, zt)

	cv::putText(img, "Speed = " + std::to_string(m_obj.VitesseEnX(m_obj.xt(t))), cv::Point(10, 20), cv::FONT_HERSHEY_SIMPLEX, 0.7f, cv::Scalar(25, 255, 255)); //Vitesse en temps r�el
	cv::putText(img, "FPS = " + std::to_string(1/ElapsedTime*pow(10,9)), cv::Point(WIDTH - 150, 20), cv::FONT_HERSHEY_SIMPLEX, 0.7f, cv::Scalar(25, 255, 255)); //FPS

}




/// <summary>
/// Fonction qui permet de d�terminer le rapport entre la hauteur de la fentre et la hauteur max ET celui entre 
/// </summary>
/// <returns></returns>
float Simulation::Scale()
{
	float ScaleX = (Window.cols) / m_obj.Xmax();
	float ScaleZ = (Window.rows-30 ) / m_obj.Zmax(); //le -30 pour laisser 30pixels du haut libre
	return Smallest(ScaleX, ScaleZ);
}




/// <summary>
/// Fonction qui retourne le plus petit deux float
/// </summary>
/// <param name="a">Premier float</param>
/// <param name="b">Second float</param>
/// <returns>La plus petite valeur entre a et b</returns>
float Simulation::Smallest(float a, float b)
{
	return ((a < b) ? a : b);
}




/// <summary>
/// Constructeur par d�faut de la classe Simulation
/// </summary>
Simulation::Simulation()
{
	m_WindowName = "DEFAULT";
	Window = NULL;
}




/// <summary>
/// Constructeur par param�tres de la classe Simulation
/// </summary>
/// <param name="WinName">Nom de la fentre</param>
/// <param name="WinHeight">Hauteur de la fenetre en pixel</param>
/// <param name="WinWidth">Largeur de la fenetre en pixel</param>
/// <param name="obj">Projectile dont on veut faire la simulation de projection</param>
Simulation::Simulation(std::string WinName, const unsigned int WinHeight, const unsigned int WinWidth, const Projectile& obj)
{
	m_obj = obj;
	m_WindowName = WinName;
	Window = cv::Mat(WinHeight, WinWidth, CV_64FC1);
}




/// <summary>
/// Permet d'afficher la fenetre de la simulation. Cela correspond � l'arri�re plan pendant ue simulation
/// </summary>
void Simulation::ConstructWindow() const
{
	cv::imshow(m_WindowName, Window);
}




/// <summary>
/// Permet de dessiner sur l'arri�re plan de la simulation la pr�vision de la trajectoire du projectile
/// </summary>
void Simulation::PreviewTrajectory() //Add the trajectory on the bg image
{
	/// <summary>
	/// Pas entre les diff�rentes points de la pr�vision. On multiplie par le facteur Scale() pour avoir un nombre de point adaptatif selon la taille de la simulation
	/// </summary>
	float Pas = 15 /Scale();

	/// <summary>
	/// Boucle qui balaye tous les pixels de 0 � la port�e maximale. Tous les "pas" pixels, on dessine un petit cercle plein.
	/// On multiplie les coordonn�es de ce cercle par le Scale() pour obtenir une simulation qui entre bien dans la fenetre de la simulation.
	/// On oublie pas d'inverser la coordonn�e Z puisque dans opencv, le 0, 0 correspond au coin en haut � gauche de l'�cran et non en bas � gauche
	/// </summary>
	float x = 0;
	while (x <= m_obj.Xmax())
	{
		circle(Window, cv::Point(x * Scale() ,Window.rows - m_obj.Zcoord(x) * Scale()), 1, cv::Scalar(255, 255, 255), cv::FILLED);
		x += Pas;
	}
}




/// <summary>
/// Cr�er une copie de l'image du background pour ne pas la modifier. C'est sur cette copie qu'on applique ensuite la fonction Draw().
/// Finalement, on peut afficher l'image obtenue.
/// </summary>
/// <param name="t">Temps t auquel on se trouve dans l'animation</param>
/// <param name="Etime">Temps que prend la boucle g�n�ral de la simulation pour faire un tour. Permet de connaitre la fr�quence de raffraichissement de l'animation </param>
void Simulation::Update(float t, float& Etime)
{
	cv::Mat temp;
	Window.copyTo(temp);
	Draw(temp, t, Etime);
	cv::imshow(m_WindowName, temp);
}




/// <summary>
/// Fonction Servant de boucle g�n�rale de la simulation
/// </summary>
/// <param name="StartT">Temps � partir duquel on veut d�marrer la simulation</param>
/// <param name="Timespeed">Facteur de vitesse d'�coulement du temps. On peut le modifier pour ralentir ou acc�l�rer l'animation</param>
void Simulation::PlaySimulation(float StartT, float Timespeed)
{
	std::cout << "Debut de la simulation " << std::endl;


	/// <summary>
	/// On commence par effectuer les modifications que l'on souhaite � l'arri�re plan de la simulation
	/// </summary>
	PreviewTrajectory();
	std::cout << "Trajectoire ajoutee au bg" << std::endl;



	/// <summary>
	/// Cette boucle permet d'appeler la fonction update � chaque frame pour mettre � jour la simulation pendant toute la dur�e de cette derni�re.
	/// On en profite pour calculer 
	/// </summary>
	float ElapsedTime = 0;
	float t = StartT;
	float PreviousElapsedTime = 0;

	while (t <= m_obj.DureeParcours())
	{
		auto start = std::chrono::steady_clock::now();

		Update(t, PreviousElapsedTime);
		
		if (cv::waitKey(1) >= 0) break;

		auto end = std::chrono::steady_clock::now();

		ElapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		PreviousElapsedTime = ElapsedTime;
		/// <summary>
		/// On multiplie le temps par le temps qu'� mis la boucle pour faire l'update. Cela permet d'avoir un �coulement du temps t constant.
		/// En effet, sur certains tours de la boucle, les calculs pourraient �tre effectu� plus rapidement, on verrait alors la simulation
		/// s'acc�l�rer sans raison. Cette boucle r�m�die � cela.
		/// </summary>
		t += 1.0f * Timespeed * ElapsedTime * pow(10, -9);

	}

	cv::waitKey(0);
}
