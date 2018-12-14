
typedef struct {
	char * mots[3840];
	int nb_mots;
} dico_t;

static dico_t DICO;

int main( int argc, char ** argv ) {
	char * msg = argv[1]; // lemessage est donné en argument au début
	DICO.nb_mots = 0;
	
	char S[BUFSIZ]; // on suppose cette taille suffisamment grande
	
	S[0] = '\0'; // initialement c'est la chaine vide
	
	for( int k=0; k < argc; k += 1 ) {
		char c = msg[k]; // récupérer le kième carcatère du message

		// blah blah blah
	
		/**
		 * on savoir si la chaine S+c est dans le DICO
		 * (1) on contruit S+c
		 * (2) on recherche S+c dans le DICO
		 * (3) si elle n'y est pas, on l'y range et on réinitialise S avec c
		 * 	   Sinon S contient déjà S+c et on continue avec le prochain
		 *	   carcatère du message.
		 */
		int i;
		int lgth = strlen(S);
		S[lgth] = c;
		S[lgth+1] = '\0';
	
		for( i=0; i < DICO.nb_mots && strcmp(S,DICO.mots[i]; i+=1 ) ;
		if( i == DICO.nb_mots ) {
			DICO.mots[DICO.nb_mots] = (char *)malloc((lgth+1)*sizeof(char));
			strcpy(DICO.mots[DICO.nb_mots], S);
			S[lgth] = '\0'; // on enlève c
		
			// émettre code(S)
		
			S[0] = c; // on réinitialise la chaîne avec c
			S[1] = '\0';
		}
	}
}