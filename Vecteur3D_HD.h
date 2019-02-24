class Vecteur3D {
	private:
		double x;  	// J'ai decide de ne pas choisir le type vector car
		double y;	//je pense que la syntaxe d'initialisation sera trop
		double z;	// longue et je visualiserai		
					// personnellement moins bien les differents attributs 
					// caracterisants  le vecteur 3D
		
	public:
		Vecteur3D(double x=0.0, double y=0.0, double z=0.0) : x(x), y(y), z(z) {};
		
		/*Valuer par defaut a 0.0 car */
		
		void affiche() const;
		bool compare(Vecteur3D) const;
		
		Vecteur3D addition(Vecteur3D const&) const;
		Vecteur3D soustraction(Vecteur3D const&) const;
		Vecteur3D oppose() const;
		Vecteur3D mult(double const&) const;
		double prod_scal(Vecteur3D const&) const;
		Vecteur3D prod_vect(Vecteur3D const&) const;
		double norme() const;
		double norme2() const;
		Vecteur3D unitaire() const;
	
};

double prod_mixte(Vecteur3D const&, Vecteur3D const&, Vecteur3D const&);
/* Nous avons decide de mettre le produit mixte comme une fonction qui 
 * effectue le calcul et non pas comme une methode car cela allourdirait
 * probablement la syntaxe*/
