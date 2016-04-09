Afin de configurer le projet de tests unitaires correctement, il faut faire les actions suivantes

- Bouton droit sur "UnitTest1" dans l'explorateur de solutions
	- Propriétés > Propriétés de configuration > Répertoires VC++
		- Ajouter dans "Repertoires Include":    "$(SolutionDir)" (sans les guillemets)
		- Ajouter dans "Repertoires de bibliotheques":        "$(SolutionDir)Debug" (sans les guillemets)

- Bouton droit sur "UnitTest1" dans l'explorateur de solutions
	- Propriétés > Propriétes de configuration > Editeur de liens > Entrée
		- Ajouter dans "Dependances supplementaires":    "$(SolutionDir)Debug\Automates.exe.lib"

- Bouton droit sur "Automates" dans l'explorateur de solutions
	- Propriétés > Propriétés de configuration > Evenements de build > Evenements post-build
		- Lignes de commandes: lib /NOLOGO /OUT:"$(TargetPath).lib" "$(ProjectDir)$(Configuration)\*.obj" (avec guillemets)
		- Description: "Exporte les *.obj en un .lib pour les tests unitaires" (sans guillemets)
		- Utilisation dans la génération: Oui