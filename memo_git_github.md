# Git et GitHub

## Initialisation

* `git init` : Initialiser un répertoire Git
* `git status` : Obtenir le statut du répertoire courant
* `git add fichier.txt` : Ajoute fichier.txt à l'index (avant un commit)
* `git commit -m "Mon message" ` : Effectuer un commit (màj) associé à son message descriptif obligatoire
	* `git commit -am "Mon message" ` : Si déjà ajouté une fois à l'index, évite de répéter `git add`


##historique

* `git log` : Voir l'historique des commits
* `git checkout monSha` : Se positionner sur le commit dont on a précisé le sha
* `git checkout main` : Se positionner sur le dernier commit

*Un commit depuis un état passé supprime les commits qui lui succédaient.*