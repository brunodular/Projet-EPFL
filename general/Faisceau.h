#include "Dessinable.h"
#include "Particule.h"
#include <vector>
#include "Element.h"

typedef Particule* p_Particule;
typedef Element* p_Element;

typedef std::vector<p_Particule> Collection_P;

//=======================================================================

class Faisceau:public Dessinable {
	private:
		p_Particule particule_typique_;
		unsigned int lambda_;
		Collection_P particules_;

		//méthodes privées, utilisées dans les autres méthodes
			//paramètres radiaux
		double moyenne_pos_2_r() const;
		double moyenne_vit_2_r() const;
		double moyenne_pos_vit_r() const;

			//paramètres verticaux
		double moyenne_pos_2_z() const;
		double moyenne_vit_2_z() const;
		double moyenne_pos_vit_z() const;
    
		//methodes privees utilisees pour trouver la particule typique du faisceau  
		Vecteur3D moyenne_pos() const;
		Vecteur3D moyenne_vit() const;
		Vecteur3D F_moyenne() const;
		double m_moyenne() const;
		double q_moyenne() const;

	public:

		//Constructeur + Destructeur
		Faisceau (Collection_P const& particules, unsigned int lambda=1.0, SupportADessin* support=nullptr, p_Particule p=nullptr);
		
		Faisceau(SupportADessin* support);
		
		Faisceau () = default;
		
		~Faisceau ();

		//Methodes
		std::ostream& affiche(std::ostream&) const;
		std::ostream& affiche_part(std::ostream&) const;
		void set_support(SupportADessin*);

		//GETTERS
		p_Particule particule_typique() const; //renvoie la particule typique/de reference
		
		Collection_P particules() const;
		
		double E_moyenne() const;	//renvoie énergie moyenne

		double emittance_r() const;
		double emittance_z() const;

		double A_11_r() const;
		double A_12_r() const;		//renvoie les coefficients elliptiques demandees selon les coordonnees orthogonales
		double A_22_r() const;

		double A_11_z() const;
		double A_12_z() const;		//renvoie selon les coordonnees verticales
		double A_22_z() const;

		unsigned int nombre_particules() const;	//renvoie le nombre de macro-particules
		unsigned int nombre_particules_simulees() const; //renvoie le nombre de particules hypothétique

		//Modifier la collection de particules
		void supprimer_par(size_t i);		//supprime i-eme particules du faisceau
		void supprimer_par();
		void ajouter_par(p_Particule const&);
		void initialiser_particules(p_Element const&);
		
		//DESSINER
		virtual void dessine() override { support->dessine(*this); }
		
		//EVOLUTION
		void evolue(double);
};
